#include "shader.hpp"
#include <iostream>
#include <fstream>

Shader::Shader(shader_input_type input_type, GLenum _type, std::string name) : type(_type)
{

    if (input_type == shader_input_type::file)
    {
        std::ifstream in(name);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            buffer = contents;
        }
    }
    else if (input_type == shader_input_type::string)
    {
        buffer = name;
    }
}

bool Shader::has_error() const
{
    return error.empty();
}

void Shader::set_error(std::string &error)
{
    this->error = error;
}
GLenum Shader::get_type() const
{
    return type;
}
std::string Shader::as_text() const
{
    return buffer;
}
