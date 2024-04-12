cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    Camera.h
    Input.h
    FileSystem.h
    TextRender2D.h
    Shader.h
    Mesh.h
    Window.h
    Panel.h
    Character.h
    Time.h
    Texture.h
    Render.h
    Material.h
    Object.h
    MeshFactory.h
    RenderEnv.h
)
set(SOURCES
    main.cpp
    Camera.cpp
    Input.cpp
    FileSystem.cpp
    TextRender2D.cpp
    Shader.cpp
    Mesh.cpp
    Window.cpp
    Panel.cpp
    Time.cpp
    Texture.cpp
    Render.cpp
    Material.cpp
    Object.cpp
    MeshFactory.cpp
    RenderEnv.cpp
)
include_directories(
    ${HEADERS}
)

add_executable(studyopengl
    ${HEADERS}
    ${GLAD_SOURCES}
    ${SOURCES}
)

target_link_libraries(studyopengl PRIVATE glfw freetype)

