# version 330 core

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragmentPosition;

uniform vec3 viewPos;

uniform Light light;
uniform Material material;

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // diff
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    
    // specular
    vec3 viewDir = normalize(viewPos - FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}