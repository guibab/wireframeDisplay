cmake_minimum_required(VERSION 2.6)
project(wireframeDisplay)

SET(MAYA_VERSION 2016 CACHE STRING "Maya version number")
SET(SOURCE_FILES 
	"PluginMain.cpp"
	"wireframeDisplay.cpp"
    "wireframeDisplay.h"
    "shapesDefinition.h" 
)

FIND_PACKAGE(OpenGL REQUIRED)

# OS Specific environment setup
SET(CUSTOM_DEFINITIONS "REQUIRE_IOSTREAM;_BOOL")
SET(MAYA_INSTALL_BASE_SUFFIX "")
SET(MAYA_INC_SUFFIX "include")
SET(MAYA_LIB_SUFFIX "lib")
IF(WIN32)
    # Windows
    SET(MAYA_INSTALL_BASE_DEFAULT "C:/Program Files/Autodesk")
    SET(CUSTOM_DEFINITIONS "${CUSTOM_DEFINITIONS};NT_PLUGIN")
ELSEIF(APPLE)
    # Apple
    SET(MAYA_INSTALL_BASE_DEFAULT "/Applications/Autodesk")
    SET(MAYA_INC_SUFFIX "devkit/include")
    SET(MAYA_LIB_SUFFIX "Maya.app/Contents/MacOS")
    SET(CUSTOM_DEFINITIONS "${CUSTOM_DEFINITIONS};OSMac_")
ELSE(WIN32)
    # Linux
    SET(MAYA_INSTALL_BASE_DEFAULT "/usr/autodesk")
    SET(MAYA_INSTALL_BASE_SUFFIX "-x32")
ENDIF(WIN32)

SET(MAYA_INSTALL_BASE_PATH ${MAYA_INSTALL_BASE_DEFAULT} CACHE STRING
    "Path containing all your maya installations, like /usr/autodesk or /Applications/Autodesk/")

SET(LIBRARIES ${LIBRARIES} "Foundation" "OpenMaya" "OpenMayaAnim" "OpenMayaUI" "OpenMayaRender" "clew" ${OPENGL_LIBRARIES})

SET(_MAYA_LOCATION ${MAYA_INSTALL_BASE_PATH}/maya${MAYA_VERSION}${MAYA_INSTALL_BASE_SUFFIX})
SET(_PROJECT ${PROJECT_NAME})

INCLUDE_DIRECTORIES(${_MAYA_LOCATION}/${MAYA_INC_SUFFIX} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

LINK_DIRECTORIES(${_MAYA_LOCATION}/${MAYA_LIB_SUFFIX})

ADD_LIBRARY(${_PROJECT} SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${_PROJECT} ${LIBRARIES})

SET_TARGET_PROPERTIES(${_PROJECT} PROPERTIES COMPILE_DEFINITIONS "${CUSTOM_DEFINITIONS}")
SET_TARGET_PROPERTIES(${_PROJECT} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
SET_TARGET_PROPERTIES(${_PROJECT} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

IF (WIN32)
    SET_TARGET_PROPERTIES(${_PROJECT} PROPERTIES SUFFIX ".mll" )
    SET_TARGET_PROPERTIES(${_PROJECT} PROPERTIES LINK_FLAGS "/export:initializePlugin /export:uninitializePlugin" )
ELSEIF(APPLE)
    SET_TARGET_PROPERTIES(${_PROJECT} PROPERTIES PREFIX "" )
    SET_TARGET_PROPERTIES(${_PROJECT} PROPERTIES SUFFIX ".bundle" )
ELSE(WIN32)
    SET_TARGET_PROPERTIES(${_PROJECT} PROPERTIES PREFIX "" )
ENDIF(WIN32)


set(USERBINPATH $"C:/Users/guillaume/Documents/maya/2016.5/plug-ins")

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND  ${CMAKE_COMMAND} -E copy  "$(ProjectDir)/$<CONFIGURATION>/${PROJECT_NAME}.mll"  "$USERBINPATH"
)
