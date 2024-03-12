cmake_minimum_required(VERSION 3.10)

project(engine)

add_definitions(-DPROJECT_PATH="${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glm)

set(GLAD_SOURCES 3rdparty/glad/src/glad.c)

include_directories(
    3rdparty/glad/include
    3rdparty/glfw/include
    3rdparty/
)

set(SOURCES
    OpenGLStudy/main.cpp
)

add_executable(studyopengl
    ${GLAD_SOURCES}
    ${SOURCES}
)

target_link_libraries(studyopengl PRIVATE glfw)

