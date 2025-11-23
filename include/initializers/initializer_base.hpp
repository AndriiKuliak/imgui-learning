#pragma once

#include <memory>
#include <iostream>

namespace LearnImGui
{

class Initializer
{
public:
    Initializer(std::shared_ptr<Initializer>&& val)
    : m_initialise(val)
    {
    }
    virtual ~Initializer() = 0;

private:
    std::shared_ptr<Initializer> m_initialise;
};

Initializer::~Initializer()
{
}

}