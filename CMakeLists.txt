cmake_minimum_required(VERSION 3.31)
project(graph_c C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Werror")

add_library(${PROJECT_NAME}.Library INTERFACE)
target_include_directories(${PROJECT_NAME}.Library INTERFACE helpers/include)

add_executable(graph_c main.c helpers/src/vector.c helpers/src/result.c helpers/src/queue.c)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}.Library)