# OpenGLのお勉強

## OpenGL
- OpenGLはspecificationであり、実現しない
- 実現は各GPUメーカーがやる

## OpenGLレンダリングパイプライン
- vertex shader
  - VAOを介してVBOから頂点プロパティ(座標、色、UV、法線)取得
- geometry shader
  - meshの組み立て？
- Rasterization
  - 面のピクセルを決める、各ピクセルの情報は頂点から補間で決める
- fragment shader
  - 色情報を決める、テクスチャから色を取得する
- text and blending
  - デプステストやαチャンネルなど諸々

## Buff Object : VBO,VAO,EBO..
### VBO
データを保存するため、GPUで確報したメモリー。

主に下記項目が使用する
- 頂点座標
- 色
- UV座標
- 法線

GPUメモリーなので、CPU側(C++)では保存されていません。
C++で保存するのは確報したVBOのIDのみ。
そのIDを使ってVBOをbindする

Shader内でVBOをアクセスしたい場合、VBOを使わず、VAOを介して使う。

### VAO
VBOを管理するバファ。



