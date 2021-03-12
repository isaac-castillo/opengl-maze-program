#include "transform.hpp"

#include <glm/gtx/transform.hpp>
glm::mat4 Transform::compute(){

    auto rotate = glm::rotate(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
    glm::rotate(glm::radians(rotation.y), glm::vec3(0.0f,1.0f,0.0f)) * glm::rotate(glm::radians(rotation.z), glm::vec3(0.0f,0.0f,1.0f));
    return glm::translate(translation) * rotate * glm::scale(scale);

};