#ifndef __scene__
#define __scene__

#include "window.hpp"
#include "primitive.hpp"

#include <vector>
namespace maze_gl
{
    struct Scene
    {

    public:
        Window * window;
        std::vector<Primitive> * primitives;
    };
} // namespace maze_gl

#endif