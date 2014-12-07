# Copyright: (C) 2014 iCub Facility - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.8)
set(PROJECTNAME yarpMinJerk)
project(${PROJECTNAME})

find_package(YARP)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})

file(GLOB model_files auto_src/*.*)
set(src_files src/main.cpp)
source_group("Model Files" FILES ${model_files})
source_group("Source Files" FILES ${src_files})

include_directories(${YARP_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/auto_src)
add_executable(${PROJECTNAME} ${model_files} ${src_files})
target_link_libraries(${PROJECTNAME} ${YARP_LIBRARIES})

