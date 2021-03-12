
#include "MoveAction.hpp"

#include "camera.hpp"
#include "action.hpp"

#include <iostream>
#include <glm/gtx/string_cast.hpp>
namespace maze_gl
{

    MoveAction::MoveAction(camera * _cam, float _degrees, direction _direction) : Action(), cam(_cam), degrees(_degrees), dir(_direction)
    {
    }

    void MoveAction::execute() const
    {

        if (dir == direction::left)
        {
            cam->turn_left(degrees);
        }
        else if (dir == direction::right)
        {
            cam->turn_left(-degrees);
        }

    }

} // namespace maze_gl
