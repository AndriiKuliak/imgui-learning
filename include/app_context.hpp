#pragma once

#include <imgui/imgui.h>

#include <string_view>

namespace LearnImGui
{

constexpr ImVec4 DefaultClearColor{0.5f, 0.5f, 0.5f, 1.0f};

struct ApplicationContext
{
    // Main window name
    std::string_view window_name;
    // Background color
    ImVec4 clear_color = DefaultClearColor;
    // Main viewport position
    ImVec2 viewport_pos;
    // Main viewoirt size
    ImVec2 viewport_size;

    // Main viewport scale
    float scale;

    // Should viewport be resizable
    bool viewportResizable = true;
    // Should viewport be movable
    bool viewportMovable = true;
};

}
