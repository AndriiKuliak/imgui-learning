#pragma once

#include "app_window.hpp"

namespace LearnImGui
{

class FirstWindow : public ApplicationWindowBase
{
public:
    FirstWindow();

private:
    void InitializeContext(const ImVec2& screen_size, float scale) override;
    void Configure() override;
    void Prepare() override;
    void DataUpdate() override;
    void Render() override;

    bool m_is_btn_clicked;
    bool m_is_chk_clicked;
};

}