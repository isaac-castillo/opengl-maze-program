#include "OpenGLShapeCreator.hpp"
#include "primitive.hpp"


#include <memory>
#include <GL/glew.h>
#include <vector>

std::unique_ptr<Primitive> OpenGLShapeCreator::createSquare(const Square & square)
{


    auto [vertices, indices] = square;
    unsigned int VBO, VAO, EBO;
    /* 1. Create vertex array, and buffers */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* Bind the vertex array */
    glBindVertexArray(VAO);

    /* Bind, and assign buffer */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * square.indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    /* Unbind the VBO, keep element buffer bound */
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Unbind vertex array */
    glBindVertexArray(0);

    return std::make_unique<Primitive>(VAO);
}
