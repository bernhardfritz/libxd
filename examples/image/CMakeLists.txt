project(image)
add_executable(${PROJECT_NAME} sketch.cpp)
target_include_directories(${PROJECT_NAME}
    PRIVATE include
)
target_link_libraries(${PROJECT_NAME}
    xd
)
set_target_properties(${PROJECT_NAME}
    PROPERTIES OUTPUT_NAME sketch
)
