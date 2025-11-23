#pragma once

#include "initializers/initializer_base.hpp"

#include <imgui/backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

namespace LearnImGui
{

class ImGuiGlfwInitializer final : public Initializer
{
public:
    ImGuiGlfwInitializer(std::shared_ptr<Initializer>&& arg, std::shared_ptr<GLFWwindow> gl_window)
    : Initializer(std::forward<std::shared_ptr<Initializer>>(arg))
    {
        ImGui_ImplGlfw_InitForOpenGL(gl_window.get(), true);
    }

    ~ImGuiGlfwInitializer() override
    {
        ImGui_ImplGlfw_Shutdown();
    }
};

} // namespace LearnImGui
