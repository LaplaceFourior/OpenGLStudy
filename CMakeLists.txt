cmake_minimum_required(VERSION 3.10)

project(RenderStudy)

add_definitions(-DPROJECT_PATH="${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/freetype)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/assimp)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/imgui_cmakelists)

set(GLAD_SOURCES ${PROJECT_SOURCE_DIR}/3rdparty/glad/src/glad.c)

include_directories(
    ${PROJECT_SOURCE_DIR}/3rdparty/glad/include
    ${PROJECT_SOURCE_DIR}/3rdparty/glfw/include
    ${PROJECT_SOURCE_DIR}/3rdparty/freetype/include
    ${PROJECT_SOURCE_DIR}/3rdparty/glm
    ${PROJECT_SOURCE_DIR}/3rdparty/
    ${PROJECT_SOURCE_DIR}/3rdparty/assimp/include
    ${PROJECT_SOURCE_DIR}/3rdparty/imgui
    ${PROJECT_SOURCE_DIR}/3rdparty/imgui/backends
)

add_subdirectory(Tenet)
add_subdirectory(Application)