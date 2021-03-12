#ifndef __camera__
#define __camera__

#include <glm/glm.hpp>
namespace maze_gl
{

    class camera
    {

    public:
        glm::vec3 eye{0, 0, 10};
        glm::vec3 up{0, 1, 0};
        glm::vec3 at{0, 0, 0};

    public:
        void turn_left(float degrees);
        void turn_up(float degrees);
        void turn_right(float degrees);
        void turn_down(float degrees);

        void move_forward();
        void move_backward();

        glm::mat4 get_view();
    };

} // namespace maze_gl

#endif