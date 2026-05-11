cmake_minimum_required(VERSION 3.16)
project(gui_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    Qt/src/main.cpp
)

file(GLOB_RECURSE EXTRA_SOURCES Qt/src/*.cpp)
list(APPEND SOURCES ${EXTRA_SOURCES})

file(GLOB_RECURSE HEADERS Qt/inc/*.hpp)

file(GLOB_RECURSE UI_FILES UI/*.ui)

add_executable(gui_app ${SOURCES} ${HEADERS} ${UI_FILES})

set_target_properties(gui_app PROPERTIES
    AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/UI
)

target_include_directories(gui_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Qt/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(gui_app PRIVATE Qt6::Widgets)