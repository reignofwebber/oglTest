#version 330 core

out vec4 color;
in vec2 fragTexCoor;
uniform sampler2D container;
uniform sampler2D face;

void main()
{
    color = mix(texture(face, fragTexCoor), texture(container, fragTexCoor), 0.7);
}