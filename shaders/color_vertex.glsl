#version 330 core
layout (location = 0) in vec3 object_position;   // the position variable has attribute position 0
layout (location = 1) in vec3 object_color; // the color variable has attribute position 1
  
out vec3 ourColor; // output a color to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(object_position, 1.0f);
    ourColor = object_color; // set color to the input color we got from the vertex data
};