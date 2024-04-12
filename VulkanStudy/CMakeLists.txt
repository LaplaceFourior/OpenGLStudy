cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

set(HEADERS
    
)
set(SOURCES
    main.cpp
)
include_directories(
    ${HEADERS}
)

add_executable(studyvulkan
    ${HEADERS}
    ${GLAD_SOURCES}
    ${SOURCES}
)

target_link_libraries(studyvulkan PRIVATE glfw freetype ${Vulkan_LIBRARIES})

