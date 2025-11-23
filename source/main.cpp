#include "apps/demo_window.hpp"
#include "app_window_registry.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include <iostream>

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

GLFWwindow* app_window_init(LearnImGui::ApplicationWindowBase& app_window)
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
        std::cerr << "Cannot create application window!" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return window;
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

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "GLFW Initialization error!" << std::endl;
        return 1;
    }

    // Define GLFW context
    const char* glfwVersion = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create GLFW window
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    const GLFWvidmode* screen_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    AppRegistry::GetInstance().RegisterWindow(std::make_unique<LearnImGui::DemoWindow>());

    auto& app_window = AppRegistry::GetInstance().GetWindowById(0);
    app_window.InitializeContext(ImVec2(screen_mode->width, screen_mode->height), main_scale);

    GLFWwindow* gl_window = app_window_init(app_window);
    if (!gl_window) {
        std::cerr << "Cannot create main window!" << std::endl;
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGuiContext* main_ctx = ImGui::CreateContext();
    if (!main_ctx) {
        std::cerr << "Cannot create render context!" << std::endl;
        return 1;
    }

    app_window.Configure();

    ImGui_ImplGlfw_InitForOpenGL(gl_window, true);
    ImGui_ImplOpenGL3_Init(glfwVersion);

    app_main_loop(gl_window, app_window);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(gl_window);
    glfwTerminate();

    return 0;
}
