#ifndef __place_square_action__
#define __place_square_action__

#include "action.hpp"
#include "primitive.hpp"
#include <vector>
#include "window.hpp"
#include "scene.hpp"

namespace maze_gl
{

    class PlaceSquareAction : public Action
    {

    public:
        PlaceSquareAction(const Square & square, Scene scene );
        // PlaceSquareAction(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<Primitive> *primitives, Window & window);
        void execute() const override;

    private:
        Square square;
        Scene scene;
    };
} // namespace maze_gl
#endif