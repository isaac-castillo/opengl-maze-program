#version 330 core

layout ( location = 0) in vec3 object_position;

void main(void){

    gl_Position = vec4(object_position, 1.0f);

}