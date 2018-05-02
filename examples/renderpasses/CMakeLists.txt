project(renderpasses)
add_executable(${PROJECT_NAME} sketch.cpp brightpass.cpp blurpass.cpp bloompass.cpp)
target_include_directories(${PROJECT_NAME}
    PRIVATE include
)
target_link_libraries(${PROJECT_NAME}
    xd
)
set_target_properties(${PROJECT_NAME}
    PROPERTIES OUTPUT_NAME sketch
)
