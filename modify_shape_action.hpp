#ifndef __modify_shape_action__
#define __modify_shape_action__

#include "action.hpp"
#include "primitive.hpp"
#include <vector>
#include "window.hpp"

#include <glm/glm.hpp>
namespace maze_gl
{
    class ModifyShapeAction : public Action
    {

    public:
        ModifyShapeAction(int VAO, const glm::mat4 & transform);
        void execute() const override;

    private:
        glm::mat4 transform;
    };
} // namespace maze_gl
#endif