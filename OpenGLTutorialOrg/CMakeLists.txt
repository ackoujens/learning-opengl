# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects                                                        │
# └──────────────────────────────────────────────────────────────────┘
add_executable(1-opening-a-window 1-opening-a-window/OpeningAWindow.cpp)
target_link_libraries(1-opening-a-window ${ENGINE_NAME})

add_executable(2-the-first-triangle 2-the-first-triangle/TheFirstTriangle.cpp)
target_link_libraries(2-the-first-triangle ${ENGINE_NAME})
