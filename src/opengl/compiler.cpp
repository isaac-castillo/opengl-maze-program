#include "compiler.hpp"

#include <string>

#include "shader.hpp"

bool Compiler::compile(const Shader &shader)
{

    GLuint gl_shader = glCreateShader(shader.get_type());

    auto str = shader.as_text();
    const auto cstr = {str.c_str()};
    glShaderSource(gl_shader, 1, cstr.begin(), NULL);
    glCompileShader(gl_shader);

    GLint compiled;
    glGetShaderiv(gl_shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint length;
        glGetShaderiv(gl_shader, GL_INFO_LOG_LENGTH, &length);
        GLchar *infoLog = new GLchar[length + 1];
        glGetShaderInfoLog(gl_shader, length, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        delete [] infoLog;
        return false;
    }
    else
    {
        std::cout << "Compiled " << ((shader.get_type() == GL_FRAGMENT_SHADER) ? "fragment" : "vertex" ) << " shader" << std::endl;
        shaders.push_back(gl_shader);
        return true;
    }
}

GLuint Compiler::link()
{
    GLuint program = glCreateProgram();
    GLint linked;
    for (const auto &gl_shader : shaders)
    {
        glAttachShader(program, gl_shader);
    }
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar *infoLog = new GLchar[length + 1];
        glGetProgramInfoLog(program, length, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
        delete [] infoLog;
    }
    else{
        glUseProgram(program);
    }
    return program;
}