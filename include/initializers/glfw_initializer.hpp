#pragma once

#include "initializers/initializer_base.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>

namespace LearnImGui
{

class GlfwInitializer final : public Initializer
{
public:
    GlfwInitializer()
    : Initializer(nullptr)
    {
        glfwSetErrorCallback(GlfwInitializer::glfw_error_callback);
        if (!glfwInit()) {
            throw std::runtime_error("Cannot initialize GLFW library!");
        }
    }

    ~GlfwInitializer() override
    {
        glfwTerminate();
    }
private:

    static void glfw_error_callback(int error, const char* description)
    {
        std::cerr << "GLFW Error (code " << error << "): " << description << std::endl;
    }
};

} // namespace LearnImGui
