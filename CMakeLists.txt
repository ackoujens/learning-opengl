cmake_minimum_required(VERSION 2.8)
set(ENGINE_NAME "your-engine-name")


# ┌──────────────────────────────────────────────────────────────────┐
# │  VARIABLE POOL                                                   │
# └──────────────────────────────────────────────────────────────────┘
set(GLFW_SOURCE_DIR "lib/glfw")
include_directories(${PROJECT_SOURCE_DIR}/YourEngineName)
set(SOURCE YourEngineName/src/Application.cpp)
set(HEADERS YourEngineName/include/Application.hpp)
#file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*)


# ┌──────────────────────────────────────────────────────────────────┐
# │  GLFW                                                            │
# └──────────────────────────────────────────────────────────────────┘
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
add_subdirectory(${GLFW_SOURCE_DIR})
include_directories(${GLFW_SOURCE_DIR}/include ${GLFW_SOURCE_DIR}/deps)

# ┌──────────────────────────────────────────────────────────────────┐
# │  FLAGS                                                           │
# └──────────────────────────────────────────────────────────────────┘
# C++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
# Linker
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit")

# ┌──────────────────────────────────────────────────────────────────┐
# │  APPLE CLAUSE                                                    │
# └──────────────────────────────────────────────────────────────────┘
if (APPLE)
    set(APP_NAME "glfw-cmake-boilerplate-launcher")

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns)
        add_executable(${APP_NAME} MACOSX_BUNDLE main.cpp icon.icns)
        set_source_files_properties("icon.icns" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
        set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns)
    else ()
        add_executable(${APP_NAME} MACOSX_BUNDLE main.cpp)
        #add_executable(${APP_NAME} MACOSX_BUNDLE ${SOURCE_FILES})
    endif ()

#    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/app.plist.in)

    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME})
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "1.0")
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING "OpenGL boilerplate example app")
else()
    set(APP_NAME "glfw-cmake-boilerplate")
    add_executable(${APP_NAME} main.cpp)
endif()

#add_executable(${APP_NAME} MACOSX_BUNDLE main.cpp ${HEADER_FILES})
#add_library(${APP_NAME}_static STATIC ${SOURCE_FILES})


# ┌──────────────────────────────────────────────────────────────────┐
# │  LINK LIBRARIES                                                  │
# └──────────────────────────────────────────────────────────────────┘
add_subdirectory(${ENGINE_NAME})
include_directories(${ENGINE_NAME}/include)
target_link_libraries(${APP_NAME} ${ENGINE_NAME})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects                                                        │
# └──────────────────────────────────────────────────────────────────┘
add_executable(1-hello-opengl 1-hello-opengl/hello-opengl.cpp)
target_link_libraries(1-hello-opengl ${ENGINE_NAME})

add_executable(2-color-animation 2-color-animation/color-animation.cpp)
target_link_libraries(2-color-animation ${ENGINE_NAME})

add_executable(3-hello-shaders 3-hello-shaders/hello-shaders.cpp)
target_link_libraries(3-hello-shaders ${ENGINE_NAME})

# ┌──────────────────────────────────────────────────────────────────┐
# │  POST BUILD COMMANDS                                             │
# └──────────────────────────────────────────────────────────────────┘
add_custom_target(run
    COMMAND open glfw-cmake-boilerplate.app
)
