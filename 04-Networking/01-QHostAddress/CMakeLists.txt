cmake_minimum_required(VERSION 3.16)

project(01-QHostAddress LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(01-QHostAddress
  main.cpp
)
target_link_libraries(01-QHostAddress Qt${QT_VERSION_MAJOR}::Core Qt6::Network)

include(GNUInstallDirs)
install(TARGETS 01-QHostAddress
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
