#ifndef __action__
#define __action__

#include "camera.hpp"

namespace maze_gl
{

    /* abstract Action class */
    class Action
    {

    public:
        Action() = default;
        virtual void execute() const = 0;
    };

} // namespace maze_gl

#endif