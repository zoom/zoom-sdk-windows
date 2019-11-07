cmake_minimum_required(VERSION 3.0.0)
project(zoom_bot VERSION 0.1.0)

find_library(DUI_SDK_LIB DuiLib_2017 
            PATH 3rdparty/duilib/lib)

if (NOT DUI_SDK_LIB)
    message(FATAL_ERROR "Failed to find DUI library")
endif()

find_library(ZOOM_SDK_LIB sdk 
            PATH 3rdparty/zoom_sdk/lib)
if (NOT ZOOM_SDK_LIB)
    message(FATAL_ERROR "Failed to find ZOOM library")
endif()
set(ZOOM_SDK_INCLUDE ${CMAKE_SOURCE_DIR}/3rdparty/zoom_sdk/include)
set(DUI_SDK_INCLUDE ${CMAKE_SOURCE_DIR}/3rdparty/duilib/include)

add_subdirectory(src)

install(TARGETS zoom_bot DESTINATION ${CMAKE_SOURCE_DIR}/build/output)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/3rdparty/bin/ DESTINATION ${CMAKE_SOURCE_DIR}/build/output)