cmake_minimum_required(VERSION 3.16)
project(gui_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
list(FILTER SOURCES EXCLUDE REGEX "build/")

file(GLOB_RECURSE HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)
list(FILTER HEADERS EXCLUDE REGEX "build/")

file(GLOB_RECURSE UI_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
)
list(FILTER UI_FILES EXCLUDE REGEX "build/")

add_executable(gui_app ${SOURCES} ${HEADERS} ${UI_FILES})

set_target_properties(gui_app PROPERTIES
    AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/UI
)

target_include_directories(gui_app PRIVATE 
    # core
    ${CMAKE_CURRENT_SOURCE_DIR}
    
    # ui
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/ui

)

target_link_libraries(gui_app PRIVATE Qt6::Widgets)