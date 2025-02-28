cmake_minimum_required(VERSION 3.14)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure build type is set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# --- Find OpenCV
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please install OpenCV.")
endif()

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add source files
set(SOURCES
    main.cpp
    src/lab1.cpp
)

set(HEADERS
    src/lab1.h
)

# Create executable
add_executable(Lab1 ${SOURCES} ${HEADERS})

# Link OpenCV
target_link_libraries(Lab1 PRIVATE ${OpenCV_LIBS})

# Set working directory for Visual Studio
set_target_properties(Lab1 PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
