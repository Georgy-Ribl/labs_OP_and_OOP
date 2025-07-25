cmake_minimum_required(VERSION 3.16)

project(Lab3_OOP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
    tokenizer.cpp
    Token.cpp
    CalculatorEngine.cpp
    CalculatorFacade.cpp
)

set(HEADERS
    mainwindow.h
    tokenizer.h
    Token.h
    CalculatorEngine.h
    CalculatorFacade.h
)

qt_add_executable(Lab3_OOP
    MANUAL_FINALIZATION
    ${SOURCES}
    ${HEADERS}
    mainwindow.ui
)

target_link_libraries(Lab3_OOP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Lab3_OOP)
endif()
