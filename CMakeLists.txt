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

# set(freetype-gl_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
# set(freetype-gl_BUILD_APIDOC OFF CACHE BOOL "" FORCE)
# set(freetype-gl_BUILD_HARFBUZZ OFF CACHE BOOL "" FORCE)
# set(freetype-gl_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# add_subdirectory(lib/freetype-gl)

set(SOURCES
    src/ellipse.cpp
    src/font.cpp
    src/image.cpp
    src/keyboard.cpp
    src/mouse.cpp
    src/opensans.cpp
    src/passthrough.cpp
    src/pixels.cpp
    src/rect.cpp
    src/renderpass.cpp
    src/shaderprogram.cpp
    src/shape.cpp
    src/texture.cpp
    src/triangle.cpp
    src/utils.cpp
    src/xd.cpp
    include/xd/vs.hpp
    include/xd/gs.hpp
    include/xd/fs.hpp
    include/xd/font_vs.hpp
    include/xd/font_fs.hpp
    include/xd/image_vs.hpp
    include/xd/image_fs.hpp
    include/xd/OpenSans-Regular.hpp
)
set_source_files_properties(src/opensans.cpp PROPERTIES COMPILE_FLAGS -Wno-narrowing)
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

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/font_vs.hpp
    COMMAND embedfile font_vs ${CMAKE_CURRENT_SOURCE_DIR}/resources/font_vs.glsl ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/font_vs.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/font_vs.glsl
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/font_fs.hpp
    COMMAND embedfile font_fs ${CMAKE_CURRENT_SOURCE_DIR}/resources/font_fs.glsl ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/font_fs.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/font_fs.glsl
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/image_vs.hpp
    COMMAND embedfile image_vs ${CMAKE_CURRENT_SOURCE_DIR}/resources/image_vs.glsl ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/image_vs.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/image_vs.glsl
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/image_fs.hpp
    COMMAND embedfile image_fs ${CMAKE_CURRENT_SOURCE_DIR}/resources/image_fs.glsl ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/image_fs.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/image_fs.glsl
)

# add_custom_command(
#     OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/OpenSans-Regular.hpp
#     COMMAND lib/freetype-gl/makefont --font ${CMAKE_CURRENT_SOURCE_DIR}/resources/Open_Sans/OpenSans-Regular.ttf --header ${CMAKE_CURRENT_SOURCE_DIR}/include/xd/OpenSans-Regular.hpp --size 72 --rendermode "sdf" --texture 512x512 --variable OpenSans_Regular
#     DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources/Open_Sans/OpenSans-Regular.ttf
# )

option(BUILD_EXAMPLES "Build examples" ON)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif (BUILD_EXAMPLES)

# the .glsl shaders would not have to be copied over to the build directory since they are already embedded in the header files
# this is currently only relevant for the logo.png resource which is used in the image example and might be handled differently in future
file (GLOB_RECURSE RESOURCES resources/*.*)
foreach(RESOURCE ${RESOURCES})
configure_file(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach(RESOURCE ${RESOURCES})

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
set(CPACK_PACKAGE_VERSION "0.3.2")

set(CPACK_MONOLITHIC_INSTALL 1)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)

include(CPack)
