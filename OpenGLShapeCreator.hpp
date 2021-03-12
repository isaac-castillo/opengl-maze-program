#ifndef __openGLshapeCreator__
#define __openGLshapeCreator__

#include <memory>
#include <vector>

#include "primitive.hpp"

class OpenGLShapeCreator {


    public:
        static std::unique_ptr<Primitive> createSquare(const Square & square);

};
#endif