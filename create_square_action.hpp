#ifndef __create_square_action__
#define __create_square_action__

#include "action.hpp"
#include "primitive.hpp"

#include "input_event_manager.hpp"
#include <vector>
#include "window.hpp"
namespace maze_gl
{
    class CreateSquareAction : public Action
    {

    public:
        CreateSquareAction(input::InputEventManager * manager, Window & window);
        void execute() const override;

    private:
        input::InputEventManager * manager;
        Window * window;
    };
} // namespace maze_gl
#endif