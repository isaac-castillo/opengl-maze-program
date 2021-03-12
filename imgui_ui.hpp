#ifndef __imgui_ui__
#define __imgui_ui__

#include <vector>
#include "input_event_manager.hpp"
#include "primitive.hpp"
#include "camera.hpp"
class ImguiUI {

    public:
    static void displayKeybinds(const input::Bindings & bindings, bool * p_open);
    static void displayShapes(std::vector<Primitive> & shapes, bool *p_open, Primitive *& selected);
    static void displayCamera(maze_gl::camera & camera, bool *p_open);

};

#endif