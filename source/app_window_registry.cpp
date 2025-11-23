#include "app_window_registry.hpp"

#include <stdexcept>

namespace LearnImGui
{

ApplicationWindowRegistry::ApplicationWindowRegistry()
{

}

ApplicationWindowRegistry::WindowId ApplicationWindowRegistry::GenerateWindowId() const
{
    static WindowId id;
    return id++;
}

ApplicationWindowBase& ApplicationWindowRegistry::GetWindowById(ApplicationWindowRegistry::WindowId id)
{
    if (m_widowRegistry.empty()) {
        throw std::runtime_error("No registered windows!");
    }

    auto it = m_widowRegistry.find(id);
    if (it == m_widowRegistry.end()) {
        throw std::invalid_argument("No window with such id!");
    }

    return *it->second;
}
    
ApplicationWindowRegistry::WindowId ApplicationWindowRegistry::RegisterWindow(std::unique_ptr<ApplicationWindowBase> window)
{
    if (window == nullptr) {
        throw std::invalid_argument("Window is null!");
    }

    const WindowId id = GenerateWindowId();
    m_widowRegistry.emplace(id, std::move(window));

    return id;
}

void ApplicationWindowRegistry::UnregisterWindow(ApplicationWindowRegistry::WindowId id)
{
    m_widowRegistry.erase(id);
}

} // namespace LearnImGui
