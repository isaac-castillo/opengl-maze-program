#ifndef __windowx__
#define __windowx__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "primitive.hpp"
#include "input_event_manager.hpp"

namespace maze_gl
{

    /* A window wrapper that wraps glfw3's window */
    class Window
    {

    private:
        Window();
        GLFWwindow * glfw_window; 
        GLFWcursor * cursors[5];
        GLFWcursor * currentCursor;

    public:

        /* A factory function that makes a window */
        static Window make_window();

        /* Resizes the window */
        void resize(int width, int height);

        /* A simple check that checks that the window is or should be open */
        bool is_open();

        /* Closes the window */
        void close();

        /* Clears the window */
        void clear();

        /* Draws a primitive onto openGL. This Primitive is already registered with the openGL context */
        void draw(const Primitive & primitive);

        /* Actually swap the buffers on the window */
        void draw();

        /* Set the callback for key presses */
        void set_window_callback(input::InputEventManager & input, const GLFWkeyfun & function);

        /* Set the callback for mouse presses */
        void set_window_callback(input::InputEventManager & input, const GLFWmousebuttonfun & function);
        
        /* Modifies the current cursor */
        /* TODO: Add the modes present. Consider using a type-safe approach. */
        void modify_cursor(int mode);
        ~Window();

        /* Prevent the Window from being copyable */
        Window(const Window&) = delete;
        Window& operator= (const Window) = delete;
    };
} // namespace maze_gl

#endif