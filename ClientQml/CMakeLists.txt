cmake_minimum_required(VERSION 3.16)
project(WssQmlClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ��������� ���� � Qt5
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.0/msvc2019_64/lib/cmake")
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.0/msvc2019_64")

# �������� �������������� ��������� MOC, UIC � RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ���������� ������ ������ Qt5
find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    WebSockets
    Widgets
)

# ��������� �������� �����
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

# ������� ����������� ����
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# ������� � ������� Qt5 ��������
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::WebSockets
    Qt5::Widgets
)

