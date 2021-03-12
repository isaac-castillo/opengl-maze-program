#include "place_square_action.hpp"

#include "OpenGLShapeCreator.hpp"
#include <memory>
#include <vector>
#include <GLFW/glfw3.h>
#include <cstring>
#include "window.hpp"

#include <iostream>
#include <glm/gtx/string_cast.hpp>
namespace maze_gl
{

    // PlaceSquareAction::PlaceSquareAction(std::vector<float> vertices_, 
    // std::vector<unsigned int> indices_, std::vector<Primitive> * primitives_, Window & window_) : vertices(std::move(vertices_)), 
    //     indices(std::move(indices_)), primitives(primitives_), window(&window_){

    // }


    PlaceSquareAction::PlaceSquareAction(const Square & _square, Scene _scene) : square(_square), scene(_scene) { 

    }

    void PlaceSquareAction::execute() const {

        auto primitive = OpenGLShapeCreator::createSquare(square);

        std::cout << glm::to_string(primitive->_transform.rotation) << std::endl;
        std::cout << glm::to_string(primitive->_transform.scale) << std::endl;
        std::cout << glm::to_string(primitive->_transform.translation) << std::endl;
        std::cout << glm::to_string(primitive->_transform.compute()) << std::endl;

        scene.primitives->push_back(*primitive);
        scene.window->modify_cursor(0);


    }

}