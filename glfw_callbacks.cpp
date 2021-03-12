#ifndef __glfw_callbacks__
#define __glfw_callbacks__

#include <GLFW/glfw3.h>
#include "MoveAction.hpp"
#include "action.hpp"

#include "OpenGLShapeCreator.hpp"
#include <iostream>
#include "input_event_manager.hpp"


void default_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

    input::InputEventManager * input = reinterpret_cast<input::InputEventManager *>(glfwGetWindowUserPointer(window));

    input->processInput({key, action, std::nullopt});
    // maze_gl::Action * input_action = new maze_gl::KeyAction(key, action));
    // input->set_action(&input_action);

    // if (key == GLFW_KEY_E && action == GLFW_PRESS)
    // {

    // }

    // if (key == GLFW_KEY_A)
    // {

    // }

    // if (key == GLFW_KEY_D)
    // {

    //     // maze_gl::Action *action = new maze_gl::MoveAction(0.1f, maze_gl::direction::right);
    //     // input->set_action(action);
    // }
}

void default_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{

    input::InputEventManager *input = reinterpret_cast<input::InputEventManager *>(glfwGetWindowUserPointer(window));
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    input->processInput({button, action, input::MouseInput{xpos, ypos}});

    // maze_gl::InputAction input_action(maze_gl::MouseAction(button, action, xpos, ypos));
    // input->set_action(&input_action);

    // if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)

    //     std::cout << "mouse: " << xpos << " " << ypos << std::endl;

    // xpos /= 800;
    // ypos /= 600;
    // float xposs = 2 * xpos - 1;
    // float yposs = 1 - 2 * ypos;

    // std::cout << "scene: " << xposs << " " << yposs << std::endl;

    // std::vector<float> vertices = {
    //     xposs + 0.5f, yposs + 0.5f, 0.0f, // top right
    //     xposs + 0.5f, yposs - 0.5f, 0.0f, // bottom right
    //     xposs - 0.5f, yposs - 0.5f, 0.0f, // bottom left
    //     xposs - 0.5f, yposs + 0.5f, 0.0f  // top left
    // };

    // std::cout << vertices[0] << vertices[1] << vertices[2] << std::endl;
    // std::vector<unsigned int> indices = {
    //     // note that we start from 0!
    //     0, 1, 3, // first Triangle
    //     1, 2, 3  // second Triangle
    // };

    // maze_gl::CreateSquareAction action(vertices, indices);
    // OpenGLShapeCreator creator;

    // auto primitive = creator.createSquare(vertices, indices);
    // input->VAOs.push_back(primitive->_VAO);
}

#endif