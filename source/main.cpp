#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include <thread>

constexpr auto g_statistics_interval = std::chrono::seconds(5);
constexpr auto g_window_width = 600;
constexpr auto g_window_height = 800;

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

static bool dump_window_position(const std::chrono::nanoseconds& since_updated)
{
    if (std::chrono::duration_cast<std::chrono::seconds>(since_updated) < g_statistics_interval) {
        return false;
    }

    const auto window_pos = ImGui::GetWindowPos();
    std::cout << "Current window pos: X: " << window_pos.x << ", Y: " << window_pos.y << std::endl;
    return true;
}

int main(int argc, char* argv[])
{
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

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
    glfwWindowHint(GLFW_POSITION_X, ((screen_mode->width / 2) - (g_window_width / 2)));
    glfwWindowHint(GLFW_POSITION_Y, ((screen_mode->height / 2) - (g_window_height / 2)));

    GLFWwindow* window = 
        glfwCreateWindow((int)(g_window_width * main_scale), (int)(g_window_height * main_scale), "ImGUI example", nullptr, nullptr);
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

    bool show_demo_window = true;
    ImVec4 clear_color{ 0.45f, 0.55f, 1.00f, 1.00f };

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

        // Data update
        ImGui::ShowDemoWindow(&show_demo_window);

        // Window rendering
        ImGui::Render();
        int display_w, display_h;
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
