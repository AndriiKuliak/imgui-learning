#pragma once

#include "app_context.hpp"

namespace LearnImGui
{

class ApplicationWindowBase
{
public:
    ApplicationWindowBase(ApplicationContext context);
    virtual ~ApplicationWindowBase() = default;

    virtual void InitializeContext(const ImVec2& screen_size, float scale) = 0;
    virtual void Configure() = 0;
    virtual void Prepare() = 0;
    virtual void DataUpdate() = 0;
    virtual void Render() = 0;

    const ApplicationContext& GetContext() const;

protected:
    ApplicationContext m_context;

private:
    ApplicationWindowBase(const ApplicationWindowBase&) = delete;
    ApplicationWindowBase(ApplicationWindowBase&&) = delete;

    ApplicationWindowBase& operator=(const ApplicationWindowBase&) = delete;
    ApplicationWindowBase& operator=(ApplicationWindowBase&&) = delete;
};

inline const ApplicationContext& ApplicationWindowBase::GetContext() const
{
    return m_context;
}

}
