cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(MultiplayerServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the AWS SDK path (common location on Arch)
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/cmake/AWSSDK")

# Find AWS SDK
find_package(AWSSDK REQUIRED COMPONENTS s3)

# Source files
add_executable(${PROJECT_NAME} 
    src/Server.cpp
    src/main.cpp
)

# Include paths
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${AWSSDK_LINK_LIBRARIES}
    Threads::Threads
)
