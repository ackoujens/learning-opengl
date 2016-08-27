# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects                                                        │
# └──────────────────────────────────────────────────────────────────┘
add_executable(1-hello-opengl 1-hello-opengl/hello-opengl.cpp)
target_link_libraries(1-hello-opengl ${ENGINE_NAME})

add_executable(2-color-animation 2-color-animation/color-animation.cpp)
target_link_libraries(2-color-animation ${ENGINE_NAME})

add_executable(3-hello-shaders-dot 3-hello-shaders-dot/hello-shaders-dot.cpp)
target_link_libraries(3-hello-shaders-dot ${ENGINE_NAME})

add_executable(4-hello-shaders-triangle 4-hello-shaders-triangle/hello-shaders-triangle.cpp)
target_link_libraries(4-hello-shaders-triangle ${ENGINE_NAME})

add_executable(5-pipeline-vertex-attributes 5-pipeline-vertex-attributes/pipeline-vertex-attributes.cpp)
target_link_libraries(5-pipeline-vertex-attributes ${ENGINE_NAME})

add_executable(6-pipeline-passing-data 6-pipeline-passing-data/pipeline-passing-data.cpp)
target_link_libraries(6-pipeline-passing-data ${ENGINE_NAME})

add_executable(7-pipeline-interface-blocks 7-pipeline-interface-blocks/pipeline-interface-blocks.cpp)
target_link_libraries(7-pipeline-interface-blocks ${ENGINE_NAME})

add_executable(8-tessellation-control-shader 8-tessellation-control-shader/tessellation-control-shader.cpp)
target_link_libraries(8-tessellation-control-shader ${ENGINE_NAME})

add_executable(9-geometry-shader 9-geometry-shader/geometry-shader.cpp)
target_link_libraries(9-geometry-shader ${ENGINE_NAME})

add_executable(10-fragment-shader 10-fragment-shader/fragment-shader.cpp)
target_link_libraries(10-fragment-shader ${ENGINE_NAME})

add_executable(11-fragment-shader-2 11-fragment-shader-2/fragment-shader-2.cpp)
target_link_libraries(11-fragment-shader-2 ${ENGINE_NAME})

add_executable(12-compute-shader 12-compute-shader/compute-shader.cpp)
target_link_libraries(12-compute-shader ${ENGINE_NAME})
