#ifndef __action_parser__
#define __action_parser__

#include "action.hpp"
#include "window.hpp"

#include "input_event_manager.hpp"
#include "primitive.hpp"
#include "camera.hpp"
namespace maze_gl
{

    struct ActionResult {

        Action * action;
        bool executed = false;
    };

    class ActionInjection
    {
        public:
            ActionInjection();
            void injectCamera(camera & cam);
            void injectPrimitives(std::vector<Primitive> & primitives);
            void injectInput(input::InputEventManager * manager);
            void injectWindow(Window * window);
            ActionResult parse(const input::ResolvedAction & input);
        
        private:
            camera * cam;
            std::vector<Primitive> * primitives;
            input::InputEventManager * manager;
            maze_gl::Window * window;

    };
} // namespace maze_gl

#endif