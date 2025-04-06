cmake_minimum_required(VERSION 3.10)
project(TrackManager)

# Настройки компиляции
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

# Поиск Qt
find_package(Qt5 REQUIRED COMPONENTS Core Sql)

# Список файлов
set(SOURCES
    main.cpp
    #Track.cpp
    TrackRepository.cpp
)

set(HEADERS
    #Track.h
    TrackRepository.h
)

# Создание исполняемого файла
add_executable(track_manager ${SOURCES} ${HEADERS})

# Подключение библиотек
target_link_libraries(track_manager
    Qt5::Core
    Qt5::Sql
)
