#pragma once

#include "app_window.hpp"

#include <cstdint>
#include <string_view>
#include <memory>
#include <unordered_map>

namespace LearnImGui
{

class ApplicationWindowRegistry
{
public:
    using WindowId = uint32_t;

    static ApplicationWindowRegistry& GetInstance();

    ApplicationWindowBase& GetWindowById(WindowId id);
    
    WindowId RegisterWindow(std::unique_ptr<ApplicationWindowBase> window);
    void UnregisterWindow(WindowId id);

private:
    ApplicationWindowRegistry();

    WindowId GenerateWindowId() const;
    
    ApplicationWindowRegistry(const ApplicationWindowRegistry&) = delete;
    ApplicationWindowRegistry(ApplicationWindowRegistry&&) = delete;

    ApplicationWindowRegistry& operator=(const ApplicationWindowRegistry&) = delete;
    ApplicationWindowRegistry& operator=(ApplicationWindowRegistry&) = delete;

    std::unordered_map<WindowId, std::unique_ptr<ApplicationWindowBase>> m_widowRegistry;
};

inline ApplicationWindowRegistry& ApplicationWindowRegistry::GetInstance()
{
    static ApplicationWindowRegistry instance;
    return instance;
}

}