cmake_minimum_required(VERSION 3.20)

project(
    imgui-sandbox 
    LANGUAGES CXX
    VERSION 1.0
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(SOURCES "${SOURCE_PATH}/main.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})
