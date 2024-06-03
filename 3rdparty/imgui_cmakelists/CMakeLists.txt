cmake_minimum_required(VERSION 3.10)

project(imgui)

set (IMGUI_ROOT_DIR ${PROJECT_SOURCE_DIR}/../imgui)

if(NOT IMGUI_ROOT_DIR)
    message(FATAL_ERROR "IMGUI ROOT directory does not exit, please check it")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(OpenGL REQUIRED)

add_library(imgui STATIC
    ${IMGUI_ROOT_DIR}/imgui_demo.cpp
    ${IMGUI_ROOT_DIR}/imgui_draw.cpp
    ${IMGUI_ROOT_DIR}/imgui_internal.h
    ${IMGUI_ROOT_DIR}/imgui_tables.cpp
    ${IMGUI_ROOT_DIR}/imgui_tables.cpp
    ${IMGUI_ROOT_DIR}/imgui_widgets.cpp
    ${IMGUI_ROOT_DIR}/imgui.cpp
    ${IMGUI_ROOT_DIR}/imgui.h
    ${IMGUI_ROOT_DIR}/imstb_rectpack.h
    ${IMGUI_ROOT_DIR}/imstb_textedit.h
    ${IMGUI_ROOT_DIR}/imstb_truetype.h
)
