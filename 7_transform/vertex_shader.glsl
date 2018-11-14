#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1);
    ourColor = inColor;
    //TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    TexCoord = aTexCoord;
}