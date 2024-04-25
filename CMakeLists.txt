cmake_minimum_required(VERSION 3.10)

project(RenderStudy)

add_definitions(-DPROJECT_PATH="${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/freetype)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/assimp)

set(GLAD_SOURCES ${PROJECT_SOURCE_DIR}/3rdparty/glad/src/glad.c)

include_directories(
    ${PROJECT_SOURCE_DIR}/3rdparty/glad/include
    ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include
    ${PROJECT_SOURCE_DIR}/3rdparty/freetype/include
    ${PROJECT_SOURCE_DIR}/3rdparty/glm
    ${PROJECT_SOURCE_DIR}/3rdparty/
    ${PROJECT_SOURCE_DIR}/3rdparty/assimp/include
)

add_subdirectory(OpenGLStudy)
add_subdirectory(VulkanStudy)
add_subdirectory(Application)