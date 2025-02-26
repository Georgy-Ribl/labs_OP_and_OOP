cmake_minimum_required(VERSION 3.5)

project(Lab1 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    entry_point.cpp
    converter.cpp
    mainwindow.h
    entry_point.h
    converter.h
    mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Lab1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        memory_utils.h
        memory_utils.cpp





    )
else()
    if(ANDROID)
        add_library(Lab1 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Lab1
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Lab1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Lab1 PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

install(TARGETS Lab1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Lab1)
endif()
