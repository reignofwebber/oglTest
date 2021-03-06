#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 color;

uniform Material material;
//uniform vec3 objectColor;
uniform Light light;
// uniform vec3 lightColor;
//uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 norm;
in vec3 fragPos;
in vec2 texCood;

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCood));
    // diffuse
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, texCood)));
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, texCood)));

    vec3 result = ambient+diffuse+specular;
    color = vec4(result, 1.0);
}   