include_guard(GLOBAL)

# Base vars
set(EXTERNAL_DEPS_DIR "${CMAKE_BINARY_DIR}/_deps")

# Imgui
set(IMGUI_PACKAGE imgui)
set(IMGUI_VERSION "1.92.4")
set(IMGUI_RENDERED "opengl3")
set(IMGUI_BACKEND "glfw")

# Dependencies
find_package(glfw3 REQUIRED)
find_package(OpenGL 3 REQUIRED)

FetchContent_Declare(
    imgui_external
    URL "https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP 1
    SOURCE_DIR "${EXTERNAL_DEPS_DIR}/${IMGUI_PACKAGE}"
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(imgui_external)

add_library(${IMGUI_PACKAGE} STATIC
    ${imgui_external_SOURCE_DIR}/imgui.cpp
    ${imgui_external_SOURCE_DIR}/imgui_demo.cpp
	${imgui_external_SOURCE_DIR}/imgui_draw.cpp
	${imgui_external_SOURCE_DIR}/imgui_tables.cpp
	${imgui_external_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_external_SOURCE_DIR}/backends/imgui_impl_${IMGUI_BACKEND}.cpp
	${imgui_external_SOURCE_DIR}/backends/imgui_impl_${IMGUI_RENDERED}.cpp
)
target_include_directories(${IMGUI_PACKAGE} PUBLIC $<BUILD_INTERFACE:${imgui_external_SOURCE_DIR}>)
target_include_directories(${IMGUI_PACKAGE} PUBLIC $<BUILD_INTERFACE:${imgui_external_SOURCE_DIR}/..>)
target_link_libraries(${IMGUI_PACKAGE} PUBLIC glfw ${OPENGL_LIBRARIES})
message(${OPENGL_LIBRARIES})
