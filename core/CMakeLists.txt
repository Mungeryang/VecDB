cmake_minimum_required(VERSION 3.30)
project(vectorDB)

set(CMAKE_CXX_STANDARD 17)

find_package(faiss REQUIRED)
find_package(spdlog REQUIRED)
find_path(RAPIDJSON_INCLUDE_DIR rapidjson/document.h REQUIRED)

add_executable(vectorDB main.cpp)

add_executable(faiss_test faiss_test.cpp)
target_link_libraries(faiss_test PRIVATE faiss)

add_executable(vdb_server vdb_server.cpp logger.cpp faiss_index.cpp index_factory.cpp http_server.cpp)
target_include_directories(vdb_server PRIVATE ${RAPIDJSON_INCLUDE_DIR})
target_link_libraries(vdb_server PRIVATE faiss spdlog::spdlog)

add_executable(http_test http_test.cpp)
target_include_directories(http_test PRIVATE ${RAPIDJSON_INCLUDE_DIR})