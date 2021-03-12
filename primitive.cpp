
#include <glm/glm.hpp>
#include "primitive.hpp"

Primitive::Primitive(int VAO, const Transform & transform) : _VAO(VAO), _transform(transform)
{

}

void Primitive::set_transform(const Transform & transform)
{
    _transform = transform;
}

Transform Primitive::get_transform() const{
    return _transform;
}
