cmake_minimum_required(VERSION 3.15)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

project(regexp VERSION 1.0.0 DESCRIPTION "Regular Expression on data")


set(QT_REQUIRED_VERSION "5.12.0")
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets)

set(CPP_FILES main.cpp)



add_executable(regexp ${CPP_FILES})
target_include_directories(regexp PRIVATE ../src)

target_link_libraries(regexp PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets regexpcore)
