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
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/UI
    ${CMAKE_CURRENT_SOURCE_DIR}/Facade
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/Creators
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/CameraManager
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/DrawManager
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/DrawManager/DrawFactory
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/DrawManager/DrawFactory/Creators
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/DrawManager/DrawFactory/Creators/QtDrawer
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/DrawManager/DrawFactory/Products
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/DrawManager/DrawFactory/Products/QtDrawer
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/BuilderFactory
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/BuilderFactory/ListBuilder
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/BuilderFactory/MatrixBuilder
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/DirectorFactory
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/ReaderFactory
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/ReaderFactory/Creators
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/ReaderFactory/Creators/ObjReaderCreator
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/ReaderFactory/Creators/TxtReaderCreator
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/ReaderFactory/Products
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/ReaderFactory/Products/ObjReader
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/LoadManager/LoadFactory/ReaderFactory/Products/TxtReader
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/SceneManager
    ${CMAKE_CURRENT_SOURCE_DIR}/Managers/TransformManager
    ${CMAKE_CURRENT_SOURCE_DIR}/Exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/Exceptions/Model
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Invisible
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Invisible/Camera
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Invisible/Camera/DefaultCamera
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible/Model
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible/Model/CarcassModel
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible/Model/Edge
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible/Model/Vertex
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible/Model/Structure
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible/Model/Structure/List
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible/Model/Structure/Matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Visible/Model/Transform
    ${CMAKE_CURRENT_SOURCE_DIR}/Objects/Composite
    ${CMAKE_CURRENT_SOURCE_DIR}/Visitors
    ${CMAKE_CURRENT_SOURCE_DIR}/Visitors/Creators
    ${CMAKE_CURRENT_SOURCE_DIR}/Visitors/DrawVisitor
    ${CMAKE_CURRENT_SOURCE_DIR}/Visitors/DrawVisitor/DrawCarcassVisitor
    ${CMAKE_CURRENT_SOURCE_DIR}/Visitors/DrawVisitor/DrawSurfaceVisitor
    ${CMAKE_CURRENT_SOURCE_DIR}/Visitors/TransformVisitor
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene
    ${CMAKE_CURRENT_SOURCE_DIR}/Qt
    ${CMAKE_CURRENT_SOURCE_DIR}/Qt/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Qt/src
)

target_link_libraries(gui_app PRIVATE Qt6::Widgets)