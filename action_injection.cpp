#include "action_injection.hpp"

#include "MoveAction.hpp"
#include "create_square_action.hpp"
#include "place_square_action.hpp"
#include <iostream>

namespace maze_gl
{

    ActionInjection::ActionInjection() {}

    void ActionInjection::injectCamera(camera &cam_)
    {
        cam = &cam_;
    }

    void ActionInjection::injectPrimitives(std::vector<Primitive> &primitives_)
    {
        primitives = &primitives_;
    }

    void ActionInjection::injectInput(input::InputEventManager * manager_){
        manager = manager_;
    }

    void ActionInjection::injectWindow(Window * window_){
        window = window_;
    }

    ActionResult ActionInjection::parse(const input::ResolvedAction &input)
    {

        switch (input.first)
        {
        case (input::ActionRequest::MoveCamera):
            return ActionResult{new MoveAction(cam, 0.1, maze_gl::direction::left), false};
            break;

        case (input::ActionRequest::CreateSquare):
            return ActionResult { new CreateSquareAction(manager, *window), false};
            break;
        case (input::ActionRequest::PlaceSquare):

            if (input.second.has_value())
            {
                float xpos = input.second.value().mouseX;
                float ypos = input.second.value().mouseY;

                std::cout << "pre: " << xpos << " " << ypos << std::endl;
                xpos /= 800;
                ypos /= 600;
                xpos = 2 * xpos - 1;
                ypos = 1 - 2 * ypos;
                xpos = 0;
                ypos = 0;
                std::cout << "post: " << xpos << " " << ypos << std::endl;
                std::vector<float> vertices = {
                    xpos + 0.5f, ypos + 0.5f, 0.0f, // top right
                    xpos + 0.5f, ypos - 0.5f, 0.0f, // bottom right
                    xpos - 0.5f, ypos - 0.5f, 0.0f, // bottom left
                    xpos - 0.5f, ypos + 0.5f, 0.0f  // top left
                };

                // std::cout << vertices[0] << vertices[1] << vertices[2] << std::endl;
                std::vector<unsigned int> indices = {
                    // note that we start from 0!
                    0, 1, 3, // first Triangle
                    1, 2, 3  // second Triangle
                };
                Square square { vertices, indices};
                Scene scene { window, primitives};
                return ActionResult{new PlaceSquareAction(square, scene), false};
            }
            break;
        }

        return ActionResult{nullptr, false};
    }
} // namespace maze_gl