cmake_minimum_required(VERSION 3.1)
project(xd)
set (CMAKE_CXX_STANDARD 11)
find_package(OpenGL REQUIRED)

add_library(glad lib/glad/src/glad.c)
include_directories(
    PRIVATE lib/glad/include
)
link_libraries(
    glad ${CMAKE_DL_LIBS}
)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(lib/glfw)
include_directories(
    PRIVATE lib/glfw/include
)
link_libraries(
    glfw ${GLFW_LIBRARIES}
)

add_subdirectory(lib/glm)
include_directories(
    PRIVATE lib/glm
)

set(SOURCES
    src/ellipse.cpp
    src/image.cpp
    src/mouse.cpp
    src/pixels.cpp
    src/rect.cpp
    src/settings.cpp
    src/shader.cpp
    src/shape.cpp
    src/triangle.cpp
    src/utils.cpp
    src/xd.cpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC include
)
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
)
file (GLOB_RECURSE RESOURCES resources/*.*)
foreach(RESOURCE ${RESOURCES})
configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach(RESOURCE ${RESOURCES})

add_subdirectory(examples)
