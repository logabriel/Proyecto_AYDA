cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(ProyectoWFC)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

if(NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)

    if(NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# Our Project
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# Gather all source files
file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
file(GLOB TEST_FILES
    "${PROJECT_SOURCE_DIR}/tests/*.cpp"
)

# Main executable (all sources)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} raylib)

# Test executable
add_executable(tests ${TEST_FILES} src/Constraint3D.cpp
    src/Object3D.cpp
    src/Scene3D.cpp
    src/Wfc3D.cpp

    src/Visualization.cpp)
target_link_libraries(tests raylib)

# Web Configurations
if(${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()