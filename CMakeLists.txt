cmake_minimum_required(VERSION 3.15)
project(RaylibTemplate)

set(CMAKE_CXX_STANDARD 17)

# User: Set these paths to where you provide the libraries/headers
# Raylib installation paths (update if your installation differs)
set(RAYLIB_ROOT "C:/raylib/raylib/src")
set(RAYLIB_INCLUDE_DIR "${RAYLIB_ROOT}")
set(RAYLIB_LIB_DIR "${RAYLIB_ROOT}")

# Add source files here
set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${RAYLIB_INCLUDE_DIR}
)

# On Windows, link additional system libraries for raylib
if (WIN32)
    target_link_libraries(${PROJECT_NAME} 
    "${RAYLIB_LIB_DIR}/libraylib.a"
    winmm gdi32 opengl32)
endif() 