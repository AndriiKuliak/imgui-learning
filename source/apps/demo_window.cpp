#include "apps/demo_window.hpp"

namespace LearnImGui
{

ApplicationContext g_demo_window_context
{
    .window_name = "Main Window",
    .viewport_size = ImVec2{400, 600}
};
    
DemoWindow::DemoWindow()
: ApplicationWindowBase(g_demo_window_context)
{

}

void DemoWindow::InitializeContext(const ImVec2& screen_size, float scale)
{
    ApplicationWindowBase::InitializeContext(screen_size, scale);
    m_context.scale = scale;
    m_context.viewport_pos = ImVec2(
        (screen_size.x / 2) - m_context.viewport_size.x / 2, 
        (screen_size.y / 2) - m_context.viewport_size.y / 2
    );
}

void DemoWindow::Configure()
{
    ApplicationWindowBase::Configure();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(m_context.scale);
    style.FontScaleDpi = m_context.scale;
}

void DemoWindow::Prepare()
{
    ApplicationWindowBase::Prepare();
}

void DemoWindow::DataUpdate()
{
    ImGui::ShowDemoWindow();
    ImGui::SetWindowPos(ImVec2{0, 0});

    ApplicationWindowBase::DataUpdate();
}

void DemoWindow::Render()
{
    ApplicationWindowBase::Render();
}

} // namespace LearnImGui
