#ifndef __transform__
#define __transform__
#include <glm/glm.hpp>

using Vector3D = glm::vec3;



class Transform {

    public:
        Vector3D rotation = Vector3D(0.0f);
        Vector3D scale = Vector3D(1.0f); 
        Vector3D translation = Vector3D(0.0f); 
        glm::mat4 compute();

};

#endif