cmake_minimum_required(VERSION 3.12)
project(mdra_example_project CXX)

# ソースコードの標準はC++17（必要に応じて変更可）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ヘッダファイルのディレクトリをインクルードパスに追加
include_directories(${CMAKE_SOURCE_DIR}/include)

# メインライブラリ(mdra)
add_library(mdra STATIC
    src/mdra.cpp
    include/mdra.hpp
)

target_include_directories(mdra PUBLIC ${CMAKE_SOURCE_DIR}/include)

# example実行ファイル
add_executable(example
    example/example.cpp
)

target_link_libraries(example PRIVATE mdra)
