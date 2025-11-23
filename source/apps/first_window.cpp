#include "apps/first_window.hpp"

#include <iostream>

namespace LearnImGui
{

namespace {
ApplicationContext g_demo_window_context
{
    .window_name = "My First Window",
    .viewport_size = ImVec2{600, 600}
};
}
    
FirstWindow::FirstWindow()
: ApplicationWindowBase(g_demo_window_context)
, m_is_btn_clicked(false)
, m_is_chk_clicked(false)
{

}

void FirstWindow::InitializeContext(const ImVec2& screen_size, float scale)
{
    ApplicationWindowBase::InitializeContext(screen_size, scale);
    m_context.scale = scale;
    m_context.viewport_pos = ImVec2(
        (screen_size.x / 2) - m_context.viewport_size.x / 2, 
        (screen_size.y / 2) - m_context.viewport_size.y / 2
    );
}

void FirstWindow::Configure()
{
    ApplicationWindowBase::Configure();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;

    ImGui::StyleColorsLight();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(m_context.scale);
    style.FontScaleDpi = m_context.scale;
}

void FirstWindow::Prepare()
{
    ApplicationWindowBase::Prepare();

    ImGui::SetNextWindowPos(ImVec2{0, 0});
    ImGui::SetNextWindowSize(GetContext().viewport_size);

    ImGui::Begin(GetContext().window_name.data(), nullptr);
    ImGui::BulletText("This is a first test window!");
    ImGui::NewLine();
    ImGui::Checkbox("Please, click me!", &m_is_chk_clicked);
    m_is_btn_clicked = ImGui::Button("Click me!");
    ImGui::End();
}

void FirstWindow::DataUpdate()
{
    if (m_is_btn_clicked) {
        std::cout << "Button has been clicked" << std::endl;
        std::cout << "Check box state: " << std::boolalpha << m_is_chk_clicked << std::endl; 
    }

    ApplicationWindowBase::DataUpdate();
}

void FirstWindow::Render()
{
    ApplicationWindowBase::Render();
}

} // namespace LearnImGui
