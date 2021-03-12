#include <GL/glew.h>

#include <iostream>

#include "window.hpp"
#include "camera.hpp"
#include "primitive.hpp"
#include "action_injection.hpp"

#include "src/opengl/compiler.hpp"
#include "src/opengl/shader.hpp"

#include "glfw_callbacks.cpp"
#include "input_event_manager.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "imgui_ui.hpp"

// const char *vertexShaderSource = "#version 330 core\n"
//                                  "layout (location = 0) in vec3 aPos;\n"
//                                  "void main()\n"
//                                  "{\n"
//                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                  "}\0";

// const char *fragmentShaderSource = "#version 330 core\n"
//                                    "out vec4 FragColor;\n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "   FragColor = vec4(0.5f, 0.2f, 1.0f, 1.0f);\n"
//                                    "}\n\0";

const char *fragmentShaderStencil = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(0.04, 0.28, 0.26, 1.0);\n"
                                    "}\n\0";

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
int create_shapes();

struct AxesLines
{

public:
    void create_lines();
    void draw_lines();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 pers = glm::mat4(1.0f);

    GLuint program;
    GLuint lineVAO;
    GLuint lineVBO;
    GLuint lineEBO;
    GLuint lineCBO;

    GLint projectionPos;
    GLint viewPos;
    GLint modelPos;
    GLint colorPos;

    glm::vec3 xColor = glm::vec3(0);
    glm::vec3 yColor = glm::vec3(0);
    glm::vec3 zColor = glm::vec3(0);
};

struct Grid
{

    GLuint VAO;
    int length;
    GLuint program;
    GLint mv;
};

Grid make_grid();
void draw_grid(Grid g);
int main()
{

    maze_gl::Window window = maze_gl::Window::make_window();
    maze_gl::camera cam;

    input::InputEventManager inputManager;
    inputManager.loadBindings("TEST");

    std::vector<Primitive> primitives;

    maze_gl::ActionInjection injection;
    injection.injectCamera(cam);
    injection.injectPrimitives(primitives);
    injection.injectInput(&inputManager);
    injection.injectWindow(&window);

    window.set_window_callback(inputManager, default_key_callback);
    window.set_window_callback(inputManager, default_mouse_button_callback);

    /* Setup the shaders */
    Compiler c;
    Shader vertex_shader(shader_input_type::file, GL_VERTEX_SHADER, "shaders/vertex.glsl");
    Shader fragment_shader(shader_input_type::file, GL_FRAGMENT_SHADER, "shaders/single_color.f.glsl");

    c.compile(vertex_shader);
    c.compile(fragment_shader);

    auto program = c.link();

    Compiler stencil_c;
    Shader stencil_frag_shader(shader_input_type::string, GL_FRAGMENT_SHADER, fragmentShaderStencil);
    stencil_c.compile(vertex_shader);
    stencil_c.compile(stencil_frag_shader);
    auto stencil_program = stencil_c.link();

    // auto VAO = create_shapes();
    glUseProgram(program);
    // primitives.push_back(VAO);
    // VAOs.push_back(VAO);

    /* Bind uniform variables for primitives */
    auto projectionPos = glGetUniformLocation(program, "projection");
    auto viewPos = glGetUniformLocation(program, "view");
    auto modelPos = glGetUniformLocation(program, "model");

    auto projectionPos2 = glGetUniformLocation(stencil_program, "projection");
    auto viewPos2 = glGetUniformLocation(stencil_program, "view");
    auto modelPos2 = glGetUniformLocation(stencil_program, "model");

    auto perspective = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 50.0f);
    // auto perspective = glm::ortho(5.0f, 5.0f, 5.0f, 5.0f);
    // perspective = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 50.0f);
    glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &perspective[0][0]);

    Primitive *selected = nullptr;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    AxesLines lines;
    lines.create_lines();

    auto tra = cam.at;
    lines.pers = perspective;

    // Compiler line;
    // Shader line_shader(shader_input_type::file, GL_VERTEX_SHADER, "shaders/pass_through.v.glsl");

    // line.compile(line_shader);
    // line.compile(stencil_frag_shader);

    // auto line_p = line.link();

    // Grid g = make_grid();

    while (window.is_open())
    {

        glfwPollEvents();

        glUseProgram(program);
        auto view = cam.get_view();
        glUniformMatrix4fv(viewPos, 1, GL_FALSE, &view[0][0]);

        glStencilMask(0x00);

        for (const auto &primitive : primitives)
        {

            if (selected != nullptr && &primitive == selected)
            {
                continue;
            }
            glUniformMatrix4fv(modelPos, 1, GL_FALSE, &primitive.get_transform().compute()[0][0]);
            glBindVertexArray(primitive._VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        if (selected != nullptr)
        {
            glUseProgram(program);

            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilMask(0xFF);
            glUniformMatrix4fv(modelPos, 1, GL_FALSE, &selected->get_transform().compute()[0][0]);
            glBindVertexArray(selected->_VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glUseProgram(stencil_program);

            glDisable(GL_DEPTH_TEST);
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilMask(0x00);

            auto model = selected->_transform;
            model.scale = 1.05f * model.scale;
            // model.translation = glm::vec3(-0.3f, 0, 0);

            glUniformMatrix4fv(viewPos2, 1, GL_FALSE, &view[0][0]);
            glUniformMatrix4fv(projectionPos2, 1, GL_FALSE, &perspective[0][0]);
            glUniformMatrix4fv(modelPos2, 1, GL_FALSE, &model.compute()[0][0]);
            glBindVertexArray(selected->_VAO);
            glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            glEnable(GL_DEPTH_TEST);
        }

        // lines.model = glm::translate(glm::mat4(1.0f), cam.at);
        lines.view = cam.get_view();
        lines.draw_lines();

        // g.program = program;
        // g.mv = modelPos;
        // draw_grid(g);
        /* Imgui */
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            static float f = 0.0f;
            static int counter = 0;

            if (true)
            {
                ImGui::ShowDemoWindow();
            }

            bool p_open = true;
            if (p_open)
                ImguiUI::displayKeybinds(inputManager.get_bindings(), &p_open);

            bool p_open2 = true;
            if (p_open)
                ImguiUI::displayShapes(primitives, &p_open2, selected);

            if (p_open)
                ImguiUI::displayCamera(cam, &p_open);
        }
        //DRAW
        window.draw();

        //Execute Action
        if (inputManager.has_action())
        {
            auto action = inputManager.release_action().value();
            auto action2 = injection.parse(action);
            action2.action->execute();
            delete action2.action;
        }
    }

    return 0;
}

void AxesLines::create_lines()
{

    float vertices[] = {
        0.0f, 0.0f, 0.0f, // top right
        10.0f, 0.0f, 0.0f, // bottom right
        0.0f, 10.0f, 0.0f, // bottom left
        0.0f, 0.0f, 10.0f  // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1,
        0, 2,
        0, 3
        
    };

    float color[] = {
        0.0f, 0.0f, 0.0f,
        255.0f, 0.0f, 0.0f,
        0.0f, 255.0f, 0.0f,
        0.0f, 0.0f, 255.0f
        
    };

    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(1, &lineVBO);
    glGenBuffers(1, &lineEBO);
    glGenBuffers(1, &lineCBO);

    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(unsigned int), (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, lineCBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(unsigned int), (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Build the program */

    Compiler c;
    Shader vertex_shader(shader_input_type::file, GL_VERTEX_SHADER, "shaders/color_vertex.glsl");
    Shader fragment_shader(shader_input_type::file, GL_FRAGMENT_SHADER, "shaders/our_color.f.glsl");

    c.compile(vertex_shader);
    c.compile(fragment_shader);

    program = c.link();

    projectionPos = glGetUniformLocation(program, "projection");
    viewPos = glGetUniformLocation(program, "view");
    modelPos = glGetUniformLocation(program, "model");

    colorPos = glGetUniformLocation(program, "color");
    std::cout << "transforms" << std::endl;
    std::cout << glm::to_string(model) << std::endl;
    std::cout << glm::to_string(view) << std::endl;
    std::cout << glm::to_string(pers) << std::endl;
}

void AxesLines::draw_lines()
{

    glUseProgram(program);
    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineEBO);
    pers = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 50.0f);

    model = glm::mat4(1.0f);
    glUniformMatrix4fv(modelPos, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &pers[0][0]);
    glUniformMatrix4fv(viewPos, 1, GL_FALSE, &view[0][0]);

    glLineWidth(3.3);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
}

Grid make_grid()
{

    int slices = 6;
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec4> indices;

    for (int j = 0; j <= slices; ++j)
    {
        for (int i = 0; i <= slices; ++i)
        {
            float x = (float)i / (float)slices;
            float y = 0;
            float z = (float)j / (float)slices;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for (int j = 0; j < slices; ++j)
    {
        for (int i = 0; i < slices; ++i)
        {

            int row1 = j * (slices + 1);
            int row2 = (j + 1) * (slices + 1);

            indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
            indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));
        }
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec4), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    auto length = (GLuint)indices.size() * 4;

    Compiler c;

    Shader vertex_shader(shader_input_type::file, GL_VERTEX_SHADER, "shaders/pass_through.v.glsl");
    Shader fragment_shader(shader_input_type::file, GL_FRAGMENT_SHADER, "shaders/single_color.f.glsl");

    c.compile(vertex_shader);
    c.compile(fragment_shader);

    auto p = c.link();
    return Grid{vao, length, p};
}

void draw_grid(Grid g)
{

    glUseProgram(g.program);
    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(g.VAO);

    auto model = glm::mat4(1.0f);
    glUniformMatrix4fv(g.mv, 1, GL_FALSE, &model[0][0]);

    glDrawElements(GL_LINES, g.length, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);

    glLineWidth(1);
    glDisable(GL_DEPTH_TEST);
}