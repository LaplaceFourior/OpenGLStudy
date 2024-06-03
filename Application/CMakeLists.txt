cmake_minimum_required(VERSION 3.10)

project(TenetTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



include_directories (${OPENGL_RENDER_INCLUDE})

set(APP_SOURCES
    main.cpp
    MySpotLightComponent.cpp
)

set(APP_HEADERS
    MySpotLightComponent.h
)

add_executable(TenetTest
    ${APP_SOURCES}
    ${APP_HEADERS}
)


target_link_libraries(TenetTest PRIVATE glfw glm freetype TenetLib)

