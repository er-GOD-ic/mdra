cmake_minimum_required(VERSION 3.20)
project(mdra_project LANGUAGES CXX)

# compile_commands.json を生成
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# C++ 標準
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include ディレクトリを追加
include_directories(${PROJECT_SOURCE_DIR}/include)

# mdra ライブラリを作成
add_library(mdra STATIC src/mdra.cpp)

# example 実行ファイル
add_executable(example example/example.cpp)

# example に mdra ライブラリをリンク
target_link_libraries(example PRIVATE mdra)

