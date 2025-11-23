#pragma once

#include "initializers/initializer_base.hpp"

#include <imgui/imgui.h>

namespace LearnImGui
{

class ImGuiInitializer final : public Initializer
{
public:
    ImGuiInitializer(std::shared_ptr<Initializer>&& arg)
    : Initializer(std::forward<std::shared_ptr<Initializer>>(arg))
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
    }

    ~ImGuiInitializer() override
    {
        ImGui::DestroyContext();
    }
};

} // namespace LearnImGui
