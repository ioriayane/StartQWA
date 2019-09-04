#include "platform.h"

#include <QDebug>
#include <emscripten.h>

std::function<void(const char *, size_t, const char *)> g_fileLoaded = nullptr;
extern "C" EMSCRIPTEN_KEEPALIVE void callFileLoaded(const char *data, size_t size, const char *file_name)
{
  qDebug() << "callFileLoaded";

  if (g_fileLoaded == nullptr)
    return;

  g_fileLoaded(data, size, file_name);
  g_fileLoaded = nullptr;
}

void PlatformImpl::loadFile(const char *filter,
                            std::function<void(const char *, size_t, const char *)> fileLoaded)
{
  if(g_fileLoaded != nullptr)
    qDebug() << "Already running";
    return;

  g_fileLoaded = fileLoaded;

  EM_ASM({
    //debugger;
    const filter = UTF8ToString($0);
    //inputタグを作成してbody配下に追加
    var element = document.createElement("input");
    document.body.appendChild(element);
    element.type = "file";
    element.style = "display:none";
    element.accept = filter;
    element.onchange = function(event){
      const file = event.target.files[0];
      //オブジェクト作成
      var reader = new FileReader();
      //読み込み完了イベント
      reader.onload = function(){
        const name = file.name;
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
        reader = null;
      };
      //ファイルを読み込む
      reader.readAsArrayBuffer(file);
      //追加したタグを消す
      document.body.removeChild(element);
    };
    //ダイアログ表示！
    element.click();

  }, filter);

  qDebug() << "loadFile 3";
}

void PlatformImpl::saveFile(const char *data, size_t size, const char *default_name)
{
  EM_ASM_({
    const data = $0;
    const size = $1;
    const default_name = UTF8ToString($2);
    //C++の領域からバイト配列に変換
    const dataArray = Module.HEAPU8.subarray(data, data + size);
    //バイナリオブジェクトを作成
    const blob = new Blob([dataArray], {type:"application/octet-stream"});
    //aタグを作成してbody配下に追加
    var element = document.createElement("a");
    document.body.appendChild(element);
    element.download = default_name;
    element.style = "display:none";
    //BlobオブジェクトをダウンロードするためのURL作成
    element.href = window.URL.createObjectURL(blob);
    //リンクをクリック
    element.click();
    //タグを削除
    document.body.removeChild(element);

  }, data, size, default_name);
}
