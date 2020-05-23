cmake_minimum_required(VERSION 3.14)
project(winapilab)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(winapilab main.cpp graphisobject.cpp graphisobject.h objects/segmentobject.cpp objects/segmentobject.h objectmanager.cpp objectmanager.h objects/rectangleobject.cpp objects/rectangleobject.h)
target_link_libraries(winapilab "Comctl32.lib")
