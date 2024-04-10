cmake_minimum_required(VERSION 3.10)

project(engine)

add_definitions(-DPROJECT_PATH="${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glm)
add_subdirectory(3rdparty/freetype)

set(GLAD_SOURCES 3rdparty/glad/src/glad.c)

set(HEADERS
    OpenGLStudy/Camera.h
    OpenGLStudy/Input.h
    OpenGLStudy/FileSystem.h
    OpenGLStudy/TextRender2D.h
    OpenGLStudy/Shader.h
    OpenGLStudy/Mesh.h
    OpenGLStudy/Window.h
    OpenGLStudy/Panel.h
    OpenGLStudy/Character.h
    OpenGLStudy/Time.h
    OpenGLStudy/Texture.h
)
set(SOURCES
    OpenGLStudy/main.cpp
    OpenGLStudy/Camera.cpp
    OpenGLStudy/Input.cpp
    OpenGLStudy/FileSystem.cpp
    OpenGLStudy/TextRender2D.cpp
    OpenGLStudy/Shader.cpp
    OpenGLStudy/Mesh.cpp
    OpenGLStudy/Window.cpp
    OpenGLStudy/Panel.cpp
    OpenGLStudy/Time.cpp
    OpenGLStudy/Texture.cpp
)
include_directories(
    3rdparty/glad/include
    3rdparty/glfw/include
    3rdparty/freetype/include
    3rdparty/glm
    3rdparty/
    ${HEADERS}
)

add_executable(studyopengl
    ${HEADERS}
    ${GLAD_SOURCES}
    ${SOURCES}
)

target_link_libraries(studyopengl PRIVATE glfw freetype ${Vulkan_LIBRARIES})

