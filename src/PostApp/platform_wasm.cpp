#include "platform.h"

#include <emscripten.h>  //EM_ASMで必要！
#include <QMimeDatabase>
#include <QString>
#include <QDebug>
#include <QFile>

//アプリ本体へコールバックするための関数ポインタ
std::function<void(const char *, size_t, const char *)> g_fileLoaded = nullptr;
//JavaScriptからコールバックされる関数
extern "C" EMSCRIPTEN_KEEPALIVE
void callFileLoaded(const char *data, size_t size, const char *file_name)
{
  qDebug() << "Call from JavaScript";

  if(g_fileLoaded == nullptr){
    return;
  }
  g_fileLoaded(data, size, file_name);
  g_fileLoaded = nullptr;
}

void Platform::selectFile(const QString &filter)
{
  //コールバック先の保存処理をラムダ式で用意
  g_fileLoaded = [=](const char *data, size_t size, const char *file_name){
    //テンポラリフォルダに一時保存
    QString file_path = tempLocation() + "/" + QString(file_name);
    QFile file(file_path);
    if(file.open(QIODevice::WriteOnly)){
      file.write(data, size);
      file.close();
      //選択したファイルのプロパティへ設定（QMLへ通知される）
      setSelectedFile(file_path);
    }
  };

  //ダイアログのフィルタ指定でMIMETYPEが必要なので変換
  QMimeDatabase db;
  QString filter_mime = db.mimeTypeForFile(filter).name();

  EM_ASM({
    //debugger;
    const filter = UTF8ToString($0);
    //inputタグを非表示で作成
    var element = document.createElement("input");
    element.type = "file";
    element.style = "display:none";
    element.accept = filter;
    //body配下に追加
    document.body.appendChild(element);
    //選択したときのイベント
    element.onchange = function(event){
      //ダイアログのキャンセル対策
      if(event.target.files.length == 0) return;
      //ファイルオブジェクト取得
      const file = event.target.files[0];
      //オブジェクト作成
      var reader = new FileReader();
      //読み込み完了イベント
      reader.onload = function(){
        //読み込んだファイルのデータをバイト配列に変換
        var dataArray = new Uint8Array(reader.result);
        //領域の確保
        var pointer = Module._malloc(dataArray.length);
        //確保した領域にコピー
        Module.HEAPU8.set(dataArray, pointer);
        //C++の関数を呼び出し
        ccall("callFileLoaded", null,
           ["number", "number", "string"],
           [pointer, dataArray.length, file.name]);
        //解放
        Module._free(pointer);
      };
      //ファイルを読み込む
      reader.readAsArrayBuffer(file);
      //追加したタグを消す
      document.body.removeChild(element);
    };
    //ダイアログ表示！
    element.click();

  },
  //JavaScriptへ渡す引数（const char*に変換）
  filter_mime.toUtf8().constData());
}

void Platform::saveFile(const QString &temp_file_path, const QString &default_name)
{
  QFile file(temp_file_path);
  if(file.open(QIODevice::ReadOnly)){
    const QByteArray &data = file.readAll();
    //ファイルを開いて読み込めたらブラウザに処理してもらう
    EM_ASM_({
      const data = $0;
      const size = $1;
      const default_name = UTF8ToString($2);
      //C++の領域からバイト配列に変換
      const dataArray = Module.HEAPU8.subarray(data, data + size);
      //バイナリオブジェクトを作成
      const blob = new Blob([dataArray], {type:"application/octet-stream"});
      //aタグを非表示で作成
      var element = document.createElement("a");
      element.download = default_name;
      element.style = "display:none";
      //BlobオブジェクトをダウンロードするためのURL作成
      element.href = window.URL.createObjectURL(blob);
      //body配下に追加
      document.body.appendChild(element);
      //リンクをクリック
      element.click();
      //タグを削除
      document.body.removeChild(element);

    },
    //JavaScriptへ渡す引数（数値かconst char*に変換）
    data.constData(), data.size(), default_name.toUtf8().constData());

    //テンポラリのファイルを削除
    file.remove();
  }
}
