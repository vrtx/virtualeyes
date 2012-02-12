#
# Virtualeyes cmake configuration
#
# Date Created: 2/3/11
# Author(s): Ben Becker (benjamin.becker@gmail.com)
#
###################################################

# Project setup
project(virtualeyes)
cmake_minimum_required(VERSION 2.8.0)

# Include QT4
find_package(Qt4 COMPONENTS
                 QtCore
                 QtGui
                 # QtWebKit
                 QtOpenGL
                 QtNetwork
                 QtScript
                 REQUIRED)
find_package(OpenGL REQUIRED)
include(${QT_USE_FILE})
add_definitions(-DQT_GUI_LIBS -DQT_CORE_LIB)
add_definitions(-Wall)
add_definitions(-Werror)
add_definitions(-g)
# add_definitions(-DDEBUG_ALLOCATIONS)
# add_definitions(-std=gnu++0x)

# include source directory
add_subdirectory(src)

