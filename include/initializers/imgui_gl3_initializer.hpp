#pragma once

#include "initializers/initializer_base.hpp"

#include <imgui/backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace LearnImGui
{

class ImGuiGl3Initializer final : public Initializer
{
public:
    ImGuiGl3Initializer(std::shared_ptr<Initializer>&& arg, const char* ogl_version)
    : Initializer(std::forward<std::shared_ptr<Initializer>>(arg))
    {
        ImGui_ImplOpenGL3_Init(ogl_version);
    }

    ~ImGuiGl3Initializer() override
    {
        ImGui_ImplOpenGL3_Shutdown();
    }
};

} // namespace LearnImGui
