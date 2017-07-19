cmake_minimum_required(VERSION 3.9)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set(PLUGIN_VERSION 1)

get_filename_component(PLUGIN_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PLUGIN_NAME ${PLUGIN_NAME})

file(GLOB PLUGIN_SOURCES
     "${CMAKE_SOURCE_DIR}/include/*.h"
     "${CMAKE_SOURCE_DIR}/src/*.cpp")

source_group("" FILES ${PLUGIN_SOURCES})

add_definitions(
  -DPLUGIN_NAME="${PLUGIN_NAME}"
  -DPLUGIN_VERSION=${PLUGIN_VERSION})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third-party)
 
link_directories(
    ${CMAKE_SOURCE_DIR}/third-party)

add_library(${PLUGIN_NAME} SHARED
            ${PLUGIN_SOURCES})

set_target_properties(${PLUGIN_NAME} PROPERTIES
                      SUFFIX ".dp64"
                      ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin/debug"
                      LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin/debug"
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin/debug"
                      ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/release"
                      LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/release"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/release")
 
