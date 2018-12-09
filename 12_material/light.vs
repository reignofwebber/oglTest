#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 norm;
out vec3 fragPos;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);    
    fragPos = vec3(model * vec4(position, 1.0f));
    // norm = aNorm;
    // for rotate or non-uniform scale operation
    // but inverse operation is expensive, better on cpu and set it uniform.
    norm = mat3(transpose(inverse(model))) * aNorm;
}