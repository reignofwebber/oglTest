#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;


void main()
{
    color = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
}