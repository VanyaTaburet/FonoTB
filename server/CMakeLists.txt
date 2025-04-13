cmake_minimum_required(VERSION 3.16)

project(SimpleQtServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем пути для включаемых директорий Qt и PostgreSQL
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.0/msvc2019_64/lib/cmake")
include_directories("C:/Program Files/PostgreSQL/13/include")
link_directories("C:/Program Files/PostgreSQL/13/lib")

# Находим нужные модули Qt
find_package(Qt5 REQUIRED COMPONENTS Core Network WebSockets Sql)

# Все исходные файлы
set(SOURCES
    main.cpp
    SimpleWebSocketServer.cpp
    TrackRepository.cpp
)

# Все заголовочные файлы, включая те, что требуют MOC
set(HEADERS
    SimpleWebSocketServer.h
    TrackRepository.h
)

# Генерация MOC файлов
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Создание исполняемого файла
add_executable(SimpleQtServer ${SOURCES} ${MOC_SOURCES})

# Линковка с библиотеками Qt и PostgreSQL
target_link_libraries(SimpleQtServer
    Qt5::Core
    Qt5::Network
    Qt5::WebSockets
    Qt5::Sql
)