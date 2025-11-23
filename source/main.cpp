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

    const auto windowId = AppRegistry::GetInstance().RegisterWindow(std::make_unique<LearnImGui::DemoWindow>());
    auto& app_window = AppRegistry::GetInstance().GetWindowById(windowId);

    app_window.InitializeContext(ImVec2(screen_mode->width, screen_mode->height));

    glfwWindowHint(GLFW_RESIZABLE, app_window.GetContext().viewportResizable);
    glfwWindowHint(GLFW_FLOATING, app_window.GetContext().viewportMovable);
    glfwWindowHint(GLFW_POSITION_X, app_window.GetContext().viewport_pos.x);
    glfwWindowHint(GLFW_POSITION_Y, app_window.GetContext().viewport_pos.y);

    ImVec2 sizeVec{app_window.GetContext().viewport_size.y * main_scale, app_window.GetContext().viewport_size.y * main_scale};

    GLFWwindow* window = 
        glfwCreateWindow((int)sizeVec.x, (int)sizeVec.y, app_window.GetContext().window_name.data(), nullptr, nullptr);
    if (nullptr == window) {
        std::cerr << "Cannot create application window!" << std::endl;
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGuiContext* main_ctx = ImGui::CreateContext();
    if (!main_ctx) {
        std::cerr << "Cannot create render context!" << std::endl;
        return 1;
    }

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glfwVersion);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
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

        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
