#include "apps/demo_window.hpp"

namespace LearnImGui
{

ApplicationContext g_demo_window_context
{
    .window_name = "Main Window",
    .viewport_size = ImVec2{600, 800}
};
    
DemoWindow::DemoWindow()
: ApplicationWindowBase(g_demo_window_context)
{

}

void DemoWindow::InitializeContext(const ImVec2& screen_size)
{
    ApplicationWindowBase::InitializeContext(screen_size);
    m_context.viewport_pos = ImVec2(
        (screen_size.x / 2) - m_context.viewport_size.x / 2, 
        (screen_size.y / 2) - m_context.viewport_size.y / 2
    );
}

void DemoWindow::Prepare()
{
    ApplicationWindowBase::Prepare();
}

void DemoWindow::DataUpdate()
{
    ImGui::ShowDemoWindow();

    ApplicationWindowBase::DataUpdate();
}

void DemoWindow::Render()
{
    ApplicationWindowBase::Render();
}

} // namespace LearnImGui
