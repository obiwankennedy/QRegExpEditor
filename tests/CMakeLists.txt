cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-permissive -pedantic -Wall -Wextra")
set(CMAKE_AUTOMOC ON)
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets Test)

set(sources tst_regexp.cpp)

add_executable(tst_regexp ${sources})


target_link_libraries(tst_regexp PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test regexpcore)
add_test(tst_regulareexpression tst_regexp)
