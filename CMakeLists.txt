#
# Virtualeyes cmake configuration
#
# Date Created: 2/3/11
# Author(s): Ben Becker (benjamin.becker@gmail.com)
#
###################################################

# Override the default compiler (needs c++0x support)
SET (CMAKE_CXX_COMPILER "g++-4.5")
SET (CMAKE_C_COMPILER "gcc-4.5")

# Project setup
project(virtualeyes)
cmake_minimum_required(VERSION 2.8.0)

# Include QT4
find_package(Qt4 COMPONENTS
                 QtCore
                 QtGui
                 QtWebKit
                 QtOpenGL
                 QtNetwork
                 QtScript
                 REQUIRED)
find_package(OpenGL REQUIRED)
include(${QT_USE_FILE})
add_definitions(-DQT_GUI_LIBS -DQT_CORE_LIB)
add_definitions(-pedantic)
add_definitions(-Wall)
add_definitions(-Werror)
add_definitions(-g)
add_definitions(-std=gnu++0x)

# include source directory
add_subdirectory(src)

