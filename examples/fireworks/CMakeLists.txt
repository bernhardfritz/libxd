project(fireworks)
add_executable(sketch sketch.cpp)
target_sources(sketch PUBLIC firework.cpp particle.cpp)
target_include_directories(sketch
    PRIVATE include
)
target_link_libraries(sketch
    xd
)