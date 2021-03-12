#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
namespace maze_gl
{
    void camera::turn_left(float degrees)
    {
        eye = glm::mat3(glm::rotate(degrees, up)) * eye;
    }
    void camera::turn_up(float degrees)
    {
        glm::vec3 c = glm::cross(eye, up);
        eye = glm::mat3(glm::rotate(degrees, c)) * eye;
        up = glm::mat3(glm::rotate(degrees, c)) * up;
    }
    void camera::turn_right(float degrees)
    {
    }
    void camera::turn_down(float degrees)
    {
    }

    void camera::move_forward()
    {
    }
    void camera::move_backward()
    {
    }

    glm::mat4 camera::get_view()
    {

        return glm::lookAt(eye, at, up);
    }
} // namespace maze_gl