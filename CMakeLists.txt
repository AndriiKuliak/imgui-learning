cmake_minimum_required(VERSION 3.20)

project(
    imgui-sandbox 
    LANGUAGES CXX
    VERSION 1.0
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/obj)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)

# Include main CMake modules
include(FetchContent)

# include dependencies
include(Imgui)

set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(SOURCES 
    "${SOURCE_PATH}/main.cpp"
    "${SOURCE_PATH}/app_window.cpp"
    "${SOURCE_PATH}/app_window_registry.cpp"
    "${SOURCE_PATH}/apps/demo_window.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} PUBLIC ${IMGUI_PACKAGE})
