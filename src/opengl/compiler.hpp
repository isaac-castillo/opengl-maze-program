class shader;

#include <string>
#include <vector>

#include <GL/glew.h>

class Shader;
class Compiler {


    private:
        std::vector<GLuint> shaders;

    public:

        bool compile(const Shader & shader);
        GLuint link();

};