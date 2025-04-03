cmake_minimum_required(VERSION 3.14)
project(SimpleQtClient LANGUAGES CXX)

# Указываем, что требуется Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к Qt5
set(Qt5_DIR "E:/QT/5.15.0/msvc2019_64/lib/cmake/Qt5")  # Путь к Qt5 (если он у тебя в другом месте, измени!)

# Указываем путь для QtQuick
set(Qt5Quick_DIR "E:/QT/5.15.0/msvc2019_64/lib/cmake/Qt5Quick")  # Путь к QtQuick (если отличается, поправь!)

# Подключаем необходимые модули Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Quick Widgets WebSockets)
find_package(Qt5 REQUIRED COMPONENTS WebSockets)


# Добавляем исходники
add_executable(SimpleQtClient 
    main.cpp 
    MainWindow.cpp 
    MainWindow.h 
    qml.qrc  # Добавь этот файл, если используешь QML
)

# Подключаем библиотеки Qt5
target_link_libraries(SimpleQtClient PRIVATE 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Quick 
    Qt5::Widgets 
    Qt5::WebSockets
)

# Указываем, где находятся заголовочные файлы
target_include_directories(SimpleQtClient PRIVATE ${CMAKE_SOURCE_DIR})

# Копируем необходимые Qt DLL после сборки (для Windows)
if (WIN32)
    add_custom_command(TARGET SimpleQtClient POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:Qt5::Core>/Qt5Core.dll"
        "$<TARGET_FILE_DIR:Qt5::Gui>/Qt5Gui.dll"
        "$<TARGET_FILE_DIR:Qt5::Widgets>/Qt5Widgets.dll"
        "$<TARGET_FILE_DIR:Qt5::WebSockets>/Qt5WebSockets.dll"
        $<TARGET_FILE_DIR:SimpleQtClient>
    )
endif()
