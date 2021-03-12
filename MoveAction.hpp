#ifndef __move_action__
#define __move_action__

#include "camera.hpp"
#include "action.hpp"
namespace maze_gl
{

    enum class direction {
        left, right, up, down, none
    };

    class MoveAction : public Action
    {

    private:
        camera * cam;
        float degrees{0};
        direction dir{direction::none};

    public:
        MoveAction(camera * cam, float degrees, direction dir);
        void execute() const override;
    };

} // namespace maze_gl

#endif