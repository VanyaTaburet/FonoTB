cmake_minimum_required(VERSION 3.16)
project(WssQmlClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к Qt5
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.0/msvc2019_64/lib/cmake")
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.0/msvc2019_64")

# Включаем автоматическую обработку MOC, UIC и RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Подключаем нужные модули Qt5
find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    WebSockets
    Widgets
)

# Добавляем исходные файлы
set(SOURCES
    main.cpp
    WebSocketClient.cpp
    TrackModel.cpp
    resources.qrc
)

set(HEADERS
    WebSocketClient.h
    TrackModel.h
    Track.h
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Линкуем с нужными Qt5 модулями
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::WebSockets
    Qt5::Widgets
)

