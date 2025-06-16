cmake_minimum_required(VERSION 3.16)

project(Lab3_OOP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp

    mainwindow.h
    mainwindow.cpp
    mainwindow.ui

    Token.h

    tokenizer.h
    tokenizer.cpp

    CalculatorEngine.h
    CalculatorEngine.cpp

    ICommand.h

    InputCommand.h
    InputCommand.cpp

    EvaluateCommand.h
    EvaluateCommand.cpp

    MemoryCommand.h
    MemoryCommand.cpp

    CalculatorFacade.h
    CalculatorFacade.cpp
)

if (QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(Lab3_OOP
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Token.cpp
    )
else()
    add_executable(Lab3_OOP
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(Lab3_OOP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Lab3_OOP)
endif()

set_target_properties(Lab3_OOP PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Lab3_OOP
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
