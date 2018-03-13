cmake_minimum_required(VERSION 3.1)
project(xd)
set (CMAKE_CXX_STANDARD 11)

# set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(glad STATIC lib/glad/src/glad.c)
target_include_directories(glad PRIVATE lib/glad/include)
target_link_libraries(glad ${CMAKE_DL_LIBS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

set(SOURCES
    src/ellipse.cpp
    src/image.cpp
    src/keyboard.cpp
    src/mouse.cpp
    src/pixels.cpp
    src/rect.cpp
    src/settings.cpp
    src/shader.cpp
    src/shape.cpp
    src/triangle.cpp
    src/utils.cpp
    src/xd.cpp
    include/xd/vs.hpp
    include/xd/gs.hpp
    include/xd/fs.hpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PUBLIC lib/glad/include
    PUBLIC lib/glm
    PUBLIC lib/stb/include
)
target_link_libraries(${PROJECT_NAME}
    glad
    glfw
)

add_executable(embedfile src/embedfile.cpp)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/vs.hpp
    COMMAND embedfile vs ${CMAKE_CURRENT_SOURCE_DIR}/resources/vs.glsl ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/vs.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/vs.glsl
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/gs.hpp
    COMMAND embedfile gs ${CMAKE_CURRENT_SOURCE_DIR}/resources/gs.glsl ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/gs.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/gs.glsl
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/fs.hpp
    COMMAND embedfile fs ${CMAKE_CURRENT_SOURCE_DIR}/resources/fs.glsl ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/fs.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/fs.glsl
)

add_subdirectory(examples)

install(
    TARGETS ${PROJECT_NAME} glad
    DESTINATION lib
)
install(
    DIRECTORY include/
    DIRECTORY lib/glad/include/
    DIRECTORY lib/glm/
    DIRECTORY lib/stb/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.inl" PATTERN "*.cmake"
)

set(CPACK_PACKAGE_NAME "libxd")
set(CPACK_PACKAGE_VENDOR "Bernhard Fritz")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libxd - A simple 2D graphics library for C++.")
set(CPACK_PACKAGE_VERSION "0.1.0")

set(CPACK_MONOLITHIC_INSTALL 1)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)

include(CPack)
