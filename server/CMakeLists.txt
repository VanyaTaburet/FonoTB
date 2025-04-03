cmake_minimum_required(VERSION 3.16)
project(SimpleQtServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем пути для включаемых директорий Qt
include_directories("C:/Qt/5.15.0/msvc2019_64/include")
link_directories("C:/Qt/5.15.0/msvc2019_64/lib")

# Находим Qt5 Core и Network компоненты
find_package(Qt5 REQUIRED COMPONENTS Core Network WebSockets)


# Указываем все исходники для проекта
set(SOURCES
    main.cpp
    SimpleWebSocketServer.cpp
)

set(HEADERS
    SimpleWebSocketServer.h
)

# Добавляем MOC обработку для Qt классов
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Собираем исполняемый файл
add_executable(SimpleQtServer ${SOURCES} ${MOC_SOURCES})

# Линкуем с нужными библиотеками Qt
target_link_libraries(SimpleQtServer Qt5::Core Qt5::Network Qt5::WebSockets)
