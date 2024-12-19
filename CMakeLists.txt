cmake_minimum_required(VERSION 3.0.0)
project(DocumentManager VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

# Print the CMAKE_PREFIX_PATH for debugging
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
find_package(spdlog REQUIRED)
# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

# Use file(GLOB ...) to gather all source files in the src directory
file(GLOB TARGET_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create the main executable from the source files
add_executable(main ${TARGET_SRC})

target_link_libraries(main PRIVATE spdlog::spdlog)

# CPack configuration
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
