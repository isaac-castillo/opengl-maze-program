#ifndef __primitive__
#define __primitive__

#include <glm/glm.hpp>
#include "transform.hpp"
#include <string>
#include <unordered_map>
#include <vector>
struct Square
{

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

class Primitive
{

public:
    Primitive(int VAO, const Transform &transform = Transform());
    int _VAO{0};
    Transform get_transform() const;
    void set_transform(const Transform &transform);

    Transform _transform = Transform();
private:

    //openGL VAO
};

#endif