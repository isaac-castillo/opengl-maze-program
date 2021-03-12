#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define INCLUDE_IMGUI 

#ifdef INCLUDE_IMGUI
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "imgui_ui.hpp"
#endif

#include <cstring>
/* The callback API implemented in keyboard_callback.cpp */
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
        glViewport(300, 100, 1400, 800);
}
#ifdef INCLUDE_IMGUI
bool show_demo_window = true;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
#endif
namespace maze_gl
{
    Window::Window()
    {
        const char *glsl_version = "#version 130";

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
        glfw_window = glfwCreateWindow(2000, 827, "LearnOpenGL", NULL, NULL);
        glViewport(300, 100, 1400, 800);
        if (glfw_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }

        glfwMakeContextCurrent(glfw_window);
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            std::cerr << "Error: " << glewGetString(err) << std::endl;
        }

        glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);
        #ifdef INCLUDE_IMGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
        #endif
    
        cursors[0] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
        cursors[1] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
        cursors[2] = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
        cursors[3] = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
        cursors[4] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
    

        currentCursor = cursors[0];

    }

    Window Window::make_window()
    {

        return Window();
    }

    void Window::draw()
    {
        #ifdef INCLUDE_IMGUI

        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();


        static float f = 0.0f;
        static int counter = 0;

        // if(show_demo_window){
        //     ImGui::ShowDemoWindow();
        // }


        // ImguiUI::displayKeybinds({});


        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
        // ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
        // ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        if(ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)){
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
        }
        else{
            io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
            glfwSetCursor(glfw_window, currentCursor);

        }

        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        #endif
        glfwSwapBuffers(glfw_window);
        clear();


    }

    void Window::close()
    {
        glfwSetWindowShouldClose(glfw_window, GLFW_FALSE);
    }

    void Window::clear()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    }

    bool Window::is_open()
    {
        return !glfwWindowShouldClose(glfw_window);
    }

    Window::~Window()
    {

        glfwDestroyWindow(glfw_window);
        glfwTerminate();
    }

    void Window::set_window_callback(input::InputEventManager &input, const GLFWkeyfun &function)
    {
        glfwSetWindowUserPointer(glfw_window, reinterpret_cast<void *>(&input));

        glfwSetKeyCallback(glfw_window, function);
    }

    void Window::set_window_callback(input::InputEventManager &input, const GLFWmousebuttonfun &function)
    {
        glfwSetWindowUserPointer(glfw_window, reinterpret_cast<void *>(&input));

        glfwSetMouseButtonCallback(glfw_window, function);
    }

    void Window::modify_cursor(int mode){

        currentCursor = Window::cursors[mode];
        // unsigned char pixels[16 * 16 * 4];
        // memset(pixels, 0xff, sizeof(pixels));
        
        // GLFWimage image;
        // image.width = 16;
        // image.height = 16;
        // image.pixels = pixels;

        
        glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        std::cout << "modifying cursor" << std::endl;
    }
} // namespace maze_gl