add_executable(filetransfer_download download.cc)
target_link_libraries(filetransfer_download cgmuduo pthread)

add_executable(filetransfer_download2 download2.cc)
target_link_libraries(filetransfer_download2 cgmuduo pthread)

add_executable(filetransfer_download3 download3.cc)
target_link_libraries(filetransfer_download3 cgmuduo pthread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -fPIC")