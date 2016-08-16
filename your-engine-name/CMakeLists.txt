# ┌──────────────────────────────────────────────────────────────────┐
# │  COLLECT HEADERS / SOURCE FILES                                  │
# └──────────────────────────────────────────────────────────────────┘
file(GLOB_RECURSE ENGINE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE ENGINE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# ┌──────────────────────────────────────────────────────────────────┐
# │  INCLUDES                                                        │
# └──────────────────────────────────────────────────────────────────┘
include_directories(include)

# ┌──────────────────────────────────────────────────────────────────┐
# │  BUILD GAME ENGINE                                               │
# └──────────────────────────────────────────────────────────────────┘
add_library(${ENGINE_NAME} SHARED ${ENGINE_HEADERS} ${ENGINE_SOURCE})
target_link_libraries(${ENGINE_NAME} glfw ${GLFW_LIBRARIES})
