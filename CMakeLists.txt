cmake_minimum_required(VERSION 3.5.1)

project(http_server)

aux_source_directory(data DATA)

add_executable(serv ${DATA} Main.cpp Err.cpp Io.cpp ThreadPool.cpp Handle.cpp Server.cpp Epoll.cpp Socket.cpp)

target_link_libraries(serv pthread)

add_definitions(-std=c++11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
