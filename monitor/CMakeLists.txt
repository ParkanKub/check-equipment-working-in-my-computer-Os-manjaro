cmake_minimum_required(VERSION 3.16)

project(monitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(monitor
    main.cpp
    cpu/cpu.cpp
    disk/disk.cpp
    ram/ram.cpp
    network/network.cpp
)

target_link_libraries(monitor
    Qt5::Widgets
)