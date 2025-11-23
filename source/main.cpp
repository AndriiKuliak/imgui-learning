#include "apps/demo_window.hpp"
#include "app_window_registry.hpp"

#include "initializers/glfw_initializer.hpp" 
#include "initializers/imgui_initializer.hpp"
#include "initializers/imgui_gl3_initializer.hpp"
#include "initializers/imgui_glfw_initiaizer.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include <iostream>

std::shared_ptr<GLFWwindow> app_window_init(LearnImGui::ApplicationWindowBase& app_window)
{
    const auto& context = app_window.GetContext();

    glfwWindowHint(GLFW_RESIZABLE, context.viewportResizable);
    glfwWindowHint(GLFW_FLOATING, context.viewportMovable);
    glfwWindowHint(GLFW_POSITION_X, context.viewport_pos.x);
    glfwWindowHint(GLFW_POSITION_Y, context.viewport_pos.y);

    ImVec2 sizeVec{context.viewport_size.y * context.scale, context.viewport_size.y * context.scale};

    GLFWwindow* window = 
        glfwCreateWindow((int)sizeVec.x, (int)sizeVec.y, app_window.GetContext().window_name.data(), nullptr, nullptr);
    if (nullptr == window) {
        throw std::runtime_error("Cannot create application window!");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return std::shared_ptr<GLFWwindow>(window, [](GLFWwindow* gl_window){
        glfwDestroyWindow(gl_window);
        gl_window = nullptr;
    });
}

void app_main_loop(GLFWwindow* gl_window, LearnImGui::ApplicationWindowBase& app_window)
{
    while(!glfwWindowShouldClose(gl_window)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(gl_window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Main loop begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        app_window.Prepare();

        // Data update
        app_window.DataUpdate();

        // Window rendering
        app_window.Render();

        int display_w, display_h;
        const ImVec4& clear_color = app_window.GetContext().clear_color;

        glfwGetFramebufferSize(gl_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(gl_window);
    }
}

int main(int argc, char* argv[])
{
    using AppRegistry = LearnImGui::ApplicationWindowRegistry;

    try {
        auto glfw_initializer = std::make_shared<LearnImGui::GlfwInitializer>();

        // Define GLFW context
        const char* glfwVersion = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        // Create GLFW window
        float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
        const GLFWvidmode* screen_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        AppRegistry::GetInstance().RegisterWindow(std::make_unique<LearnImGui::DemoWindow>());

        AppRegistry::WindowId windowId = 0;
        if (argc > 1) {
            windowId = std::atoi(argv[1]);
        }

        auto& app_window = AppRegistry::GetInstance().GetWindowById(windowId);
        app_window.InitializeContext(ImVec2(screen_mode->width, screen_mode->height), main_scale);

        auto gl_window = app_window_init(app_window);

        auto imgui_initializer = std::make_shared<LearnImGui::ImGuiGl3Initializer>(
            std::make_shared<LearnImGui::ImGuiGlfwInitializer>(
                std::make_shared<LearnImGui::ImGuiInitializer>(nullptr), gl_window
            ), glfwVersion);

        app_window.Configure();

        app_main_loop(gl_window.get(), app_window);
    } catch(const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
