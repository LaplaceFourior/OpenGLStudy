# version 330 core

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragmentPosition;

uniform bool useTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewPos;

uniform Light light;
uniform Material material;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;

    // diff
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    if (useTexture) {
        FragColor = vec4(result, 1.0) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    } else {
        FragColor = vec4(result, 1.0);
        FragColor = vec4(result, 1.0);
    }
}