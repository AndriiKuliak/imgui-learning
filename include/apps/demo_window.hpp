#pragma once

#include "app_window.hpp"

namespace LearnImGui
{

class DemoWindow : public ApplicationWindowBase
{
public:
    DemoWindow();

private:
    void InitializeContext(const ImVec2& screen_size) override;
    void Prepare() override;
    void DataUpdate() override;
    void Render() override;
};

}