cmake_minimum_required(VERSION 3.14)
project(winapilab)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(winapilab main.cpp graphisobject.cpp graphisobject.h objects/segmentobject.cpp objects/segmentobject.h objectmanager.cpp objectmanager.h objects/rectangleobject.cpp objects/rectangleobject.h objects/brokenlineobject.cpp objects/brokenlineobject.h objects/pentagonobject.cpp objects/pentagonobject.h objects/circleobject.cpp objects/circleobject.h objects/ellipseobject.cpp objects/ellipseobject.h)
target_link_libraries(winapilab "Comctl32.lib")
