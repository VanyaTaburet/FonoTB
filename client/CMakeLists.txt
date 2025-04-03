cmake_minimum_required(VERSION 3.10)

project(SimpleQtClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets WebSockets)

add_executable(SimpleQtClient
    main.cpp
    MainWindow.cpp
    MainWindow.h
)

target_link_libraries(SimpleQtClient PRIVATE Qt5::Widgets Qt5::WebSockets)
