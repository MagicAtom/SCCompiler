cmake_minimum_required(VERSION 3.1)
project(scc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

aux_source_directory(src scc_src)

if(CMAKE_HOST_APPLE)
include_directories(/usr/local/opt/llvm/include)
llvm_map_components_to_libnames(llvm_libs core)
endif()

add_executable(
    scc
    ${scc_src}
)

target_link_libraries(scc ${llvm_libs})
