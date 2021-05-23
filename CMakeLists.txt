cmake_minimum_required(VERSION 3.1)
project(scc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

aux_source_directory(src scc_src)

add_executable(
    scc
    ${scc_src}
)
