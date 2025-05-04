cmake_minimum_required(VERSION 3.12)
project(cpp_tojsonl)

set(CMAKE_CXX_STANDARD 17)

# vcpkg toolchain 文件路径
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

find_package(arrow CONFIG REQUIRED)
find_package(parquet CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${Arrow_INCLUDE_DIR}
        ${Parquet_INCLUDE_DIR}
)

add_executable(cpp_tojsonl
        src/main.cpp
        src/text_converter.cpp
        src/parquet_converter.cpp
)

target_link_libraries(cpp_tojsonl
        PRIVATE
        arrow_shared
        parquet_shared
        nlohmann_json::nlohmann_json
)
