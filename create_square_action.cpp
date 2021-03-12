#include "create_square_action.hpp"

#include "window.hpp"
#include "input_event_manager.hpp"
#include "OpenGLShapeCreator.hpp"
#include <memory>
#include <vector>
#include <cstring>
#include <iostream>
namespace maze_gl
{

    CreateSquareAction::CreateSquareAction(input::InputEventManager * manager_,
        Window & window_) : manager(manager_), window(&window_) {

    }

    void CreateSquareAction::execute() const {

        window->modify_cursor(1);
        std::cout << "executing create square action" << std::endl;
        manager->setRequest(input::ActionRequest::CreateSquare);
    }

}