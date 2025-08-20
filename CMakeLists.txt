#CMake ver
cmake_minimum_required(VERSION 3.12)

#プロジェクト名
project(OpenGLStudy)

#C++ver
set(CMAKE_CXX_STANDARD 17)

file(GLOB ASSETS "./Assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

#プロジェクトにマクロを追加
#書き方：-D+マクロ名
add_definitions(-DDEBUG)

add_definitions(-DPERSPECTIVE)
add_definitions(-DTRACKBOLL)

#インクルードディレクトリを追加
include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/include
)

link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/lib
)

#サブフォルダをビルドに追加
#インクルードdirectoryの下に書く必要がある、その上に書くと、インクルードパスが設定されていないため、インクルード失敗になる
add_subdirectory(Wrapper)
add_subdirectory(Application)
add_subdirectory(GLFramWork)
add_subdirectory(Geometry)

#ソースファイルを自動で取得
#ルートフォルダ内cppファイルを取得
aux_source_directory(. SRCS)

#エグゼファイル名
add_executable(glSutdy ${SRCS})

#libをリンクする
#エグゼビルド時サブフォルダを含むように
target_link_libraries(glSutdy glfw3.lib wrapper app glfw geometry)