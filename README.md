# 始める！Qt for WebAssembly

[技術書典7](https://techbookfest.org/event/tbf07)で頒布する「始める！Qt for WebAssembly」のサンプルコードを公開するためのリポジトリです。

サークル情報：https://techbookfest.org/event/tbf07/circle/5199792342827008




# ライセンス関連
サンプルコードはGPLv3での配布になります。

フォルダ `src/PostApp/qhtml5file` のファイルは https://github.com/msorvig/slate の一部を利用しています。
本サンプルに組み込むにあたって以下のファイルを修正しています。

- qhtml5file.cpp
- qhtml5file_html5.cpp

修正内容としては廃止されたAPIの置き換えと未実装部分の実装です。
