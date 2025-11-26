cmake_minimum_required(VERSION 3.20)
project(SpaceGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

# Find SDL3
find_package(SDL3 QUIET)

if(NOT SDL3_FOUND)
    message(STATUS "SDL3 not found, fetching from source...")
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL3)
endif()

# Find GLM
find_package(glm QUIET)
if (NOT glm_FOUND)
    message(STATUS "GLM not found, fetching from source...")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(glm)
endif()


# Source files
set(SOURCES
    src/main.cpp
    src/voxel.cpp
    src/renderer.cpp
    src/entity.cpp
    src/ship.cpp
    src/camera.cpp
)

set(HEADERS
    src/voxel.h
    src/renderer.h
    src/entity.h
    src/ship.h
    src/camera.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 glm::glm)

# Copy data files to bin directory
file(COPY ${CMAKE_SOURCE_DIR}/data/ship.bin DESTINATION ${CMAKE_SOURCE_DIR}/bin/data)