cmake_minimum_required(VERSION 3.1)
project(scc)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

aux_source_directory(src scc_src)

add_executable(
    scc
    ${scc_src}
)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(scc ${llvm_libs})
