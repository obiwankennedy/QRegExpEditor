cmake_minimum_required(VERSION 3.15)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

project(regexpcore VERSION 1.0.0 DESCRIPTION "Test Regular Expression on data")


set(QT_REQUIRED_VERSION "5.12.0")
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets)

set(CPP_FILES mainwindow.cpp)
set(HEADER_FILES mainwindow.h)
set(UI_FILES mainwindow.ui)


add_library(regexpcore SHARED ${CPP_FILES} ${HEADERS_FILES} ${UI_FILES})

target_link_libraries(regexpcore PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)
