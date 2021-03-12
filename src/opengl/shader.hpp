#ifndef __shader__
#define __shader__

#include <iostream>
#include <GL/glew.h>

enum class shader_input_type {
    file,
    string
};

class Shader {


    public:
        Shader(shader_input_type, GLenum type, std::string name);
        bool has_error() const;
        void set_error(std::string &);
        GLenum get_type() const;
        std::string as_text() const;
    private:

        GLenum type;
        std::string error;
        std::string buffer;

};

#endif