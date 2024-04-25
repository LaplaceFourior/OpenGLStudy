cmake_minimum_required(VERSION 3.10)

project(OpenGLStudy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(OpenGLStudyLib STATIC ${HEADERS} ${GLAD_SOURCES} ${SOURCES})
target_include_directories(OpenGLStudyLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(OpenGLStudyLib PRIVATE glfw glm freetype assimp)

