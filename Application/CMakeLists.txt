cmake_minimum_required(VERSION 3.10)

project(OpenGLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



include_directories (${OPENGL_RENDER_INCLUDE})

set(APP_SOURCES
    main.cpp
)

set(APP_HEADERS
)

add_executable(OpenGLTest
    ${APP_SOURCES}
    ${APP_HEADERS}
)


target_link_libraries(OpenGLTest PRIVATE glfw glm freetype OpenGLStudyLib)

