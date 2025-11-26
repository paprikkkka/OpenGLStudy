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

##ステンシルテスト、ステンシルバファ

デプステスト、バファと似ている。？

ステンシル起動
ステンシルテスト設定
※ステンシルバファは255まで記録できない。
glStencilFunc(func,ref,mask)
func:テストする方法、GL_NEVERなどがある
ref:指定するステンシルバファ値
mask:比べるビット数
前段で glStencilFunc(GL_ALWAYS, 1, 0xFF); glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); glStencilMask(0xFF); だから、モデル本体を描いたピクセルのステンシルは「1」に置換される。未描画のところは「0」のまま。
値は「0 or 1」しか存在しない（INCR/DECRじゃなくREPLACEだから2以上は絶対に出ない）。
この前提で比較すると

GL_LESS（Passes if (ref & mask) < (stencil & mask)）
ref=1 → 条件は「1 < stencil」。
通るのは stencil >= 2 の場所のみ。今回そんな値は存在しないから通らない。
GL_GREATER（Passes if (ref & mask) > (stencil & mask)）
ref=1 → 条件は「1 > stencil」。
通るのは stencil == 0 の場所。つまり「モデルがまだステンシルを書いてない外周」だけが通る。アウトライン抽出にちょうど効く。
だから今の挙動は仕様通り。LESSが通らないのはステンシルが2以上にならない設計（REPLACEで1固定）だから。GREATERが通るのは未書き込み領域（0）を選別できるからだよ。

用途別のオススメ

モデル外周だけ描きたい: glStencilFunc(GL_GREATER, 1, 0xFF)（今のままでOK）
モデル内部だけ描きたい: glStencilFunc(GL_EQUAL, 1, 0xFF)
「1以外全部」を通したい: glStencilFunc(GL_NOTEQUAL, 1, 0xFF)
もし「LESSを使いたい」なら、前段をINCR/DECRで2以上が生まれるように変える必要があるけど、いまの目的（外周抽出）ならGREATERが一番クリアだね。

レンダリングする
ステンシルテストを通過するとステンシルバファへ書き込む。
書き込む設定は



