#include "app_window.hpp"

namespace LearnImGui
{

ApplicationWindowBase::ApplicationWindowBase(ApplicationContext context)
: m_context(context)
{
}

void ApplicationWindowBase::InitializeContext(const ImVec2& screen_size, float scale)
{

}

void ApplicationWindowBase::Configure()
{

}

void ApplicationWindowBase::Prepare()
{
   
}

void ApplicationWindowBase::DataUpdate()
{

}

void ApplicationWindowBase::Render()
{
    ImGui::Render();
}

}
