cmake_minimum_required(VERSION 3.10)

project(imgui)

set (IMGUI_ROOT_DIR ${PROJECT_SOURCE_DIR}/../imgui)

if(NOT IMGUI_ROOT_DIR)
    message(FATAL_ERROR "IMGUI ROOT directory does not exit, please check it")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(IMGUI_SOURCE
    ${IMGUI_ROOT_DIR}/imgui.cpp
    ${IMGUI_ROOT_DIR}/imgui_demo.cpp
    ${IMGUI_ROOT_DIR}/imgui_draw.cpp
    ${IMGUI_ROOT_DIR}/imgui_tables.cpp
    ${IMGUI_ROOT_DIR}/imgui_widgets.cpp
    ${IMGUI_ROOT_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_ROOT_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(${PROJECT_NAME} STATIC ${IMGUI_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_ROOT_DIR})
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)

# a glfw_opengl3 example
set(EXAMPLE_SOURCE ${IMGUI_ROOT_DIR}/examples/example_glfw_opengl3/main.cpp)
add_executable(example_glfw_opengl3 ${EXAMPLE_SOURCE})
target_link_libraries(example_glfw_opengl3 ${PROJECT_NAME} glfw OpenGL::GL)
target_include_directories(example_glfw_opengl3 PRIVATE ${IMGUI_ROOT_DIR} ${IMGUI_ROOT_DIR}/backends)



