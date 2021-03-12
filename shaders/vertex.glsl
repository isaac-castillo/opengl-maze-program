#version 420 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


layout ( location = 0) in vec3 object_position;

out vec4 world_position;
out vec3 world_normal;

void main(void){

    //world_position = model * object_position * vec4(1.0);
    // world_normal = normalize((model * vec4(object_normal, 0.0)).xyz);
    gl_Position = projection * view * model * vec4(object_position, 1.0f);
    //gl_Position = vec4(1,1,1,1);

}