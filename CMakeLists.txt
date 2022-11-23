cmake_minimum_required(VERSION 3.9)

project(
    "wireframeDisplay"
    VERSION 1.0
    DESCRIPTION "A quick smooth with border conditions"
    LANGUAGES CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)

# (defined in FindMaya.cmake, copied here for reference)
# set(MAYA_INSTALL_BASE_PATH "" CACHE STRING
#     "Root path containing your maya installations, e.g. /usr/autodesk or /Applications/Autodesk/"
# )
set(MAYA_VERSION 2020 CACHE STRING "Maya version")

set(MAYA_FILES
    "src/PluginMain.cpp"
    "src/wireframeDisplay.cpp"
    "src/shapesDefinition.h"
    "src/wireframeDisplay.h"
)

find_package(OpenGL REQUIRED)
find_package(Maya REQUIRED)
add_library(${PROJECT_NAME} SHARED ${MAYA_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE Maya::Maya OpenGL::GL)
target_include_directories(${PROJECT_NAME} 
    PRIVATE Maya::Maya
    PUBLIC "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
)
MAYA_PLUGIN(${PROJECT_NAME})
