cmake_minimum_required(VERSION 3.16)
project(iu7_cg_lab06_bondarevava)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

file(GLOB_RECURSE APP_HEADERS inc/*.hpp)
file(GLOB_RECURSE UI_FILES ui/*.ui)
file(GLOB_RECURSE APP_SOURCES src/*.cpp)

add_executable(app 
    ${APP_SOURCES}
    ${APP_HEADERS} 
    ${UI_FILES}
)

target_link_libraries(app PRIVATE Qt6::Widgets)
target_link_libraries(app PRIVATE Qt6::Core)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)