project(quadtree)
add_executable(${PROJECT_NAME} sketch.cpp)
target_sources(${PROJECT_NAME} PUBLIC xy.cpp quadtree.cpp aabb.cpp)
target_include_directories(${PROJECT_NAME}
    PRIVATE include
)
target_link_libraries(${PROJECT_NAME}
    xd
)
set_target_properties(${PROJECT_NAME}
    PROPERTIES OUTPUT_NAME sketch
)
