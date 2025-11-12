include_guard(GLOBAL)

# Imgui
set(IMGUI_PACKAGE imgui)
set(IMGUI_VERSION "1.92.4")
set(IMGUI_BACKEND "opengl3")

# Dependencies
find_package(glfw3 REQUIRED)

FetchContent_Declare(
    imgui_external
    URL "https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP 1
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(imgui_external)

add_library(${IMGUI_PACKAGE}
    ${imgui_external_SOURCE_DIR}/imgui.cpp
	${imgui_external_SOURCE_DIR}/imgui_draw.cpp
	${imgui_external_SOURCE_DIR}/imgui_tables.cpp
	${imgui_external_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_external_SOURCE_DIR}/backends/imgui_impl_${IMGUI_BACKEND}.cpp
)
target_include_directories(${IMGUI_PACKAGE} PUBLIC ${imgui_external_SOURCE_DIR})
target_link_libraries(${IMGUI_PACKAGE} PUBLIC glfw)
