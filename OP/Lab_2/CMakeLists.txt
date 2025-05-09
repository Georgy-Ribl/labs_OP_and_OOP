# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(Lab2_OP LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
    arrayutils.cpp
    stringutils.cpp
    demodata.cpp
    operations.cpp
    entrypoint.cpp
)

set(HEADERS
    mainwindow.h
    arrayutils.h
    stringutils.h
    demodata.h
    operations.h
    entrypoint.h
)

qt_add_executable(Lab2_OP ${SOURCES} ${HEADERS}
    entrypoint.h entrypoint.cpp)
target_link_libraries(Lab2_OP PRIVATE Qt6::Widgets)
