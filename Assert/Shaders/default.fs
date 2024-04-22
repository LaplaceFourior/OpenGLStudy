# version 330 core

// light type
// Direct 1
// Point 2
// Spot 3

// light
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

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
uniform Material material;
#define NR_DIRECT_LIGHTS 10
uniform DirectLight directLights[NR_DIRECT_LIGHTS];
#define NR_POINT_LIGHTS 10
uniform PointLight pointLights[NR_POINT_LIGHTS];
#define NR_SPOT_LIGHTS 10
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform int directLightNumber;
uniform int pointLightNumber;
uniform int spotLightNumber;

vec3 calculateDirectLight(DirectLight light)
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

    // diff
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    
    // specular
    vec3 viewDir = normalize(viewPos - FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

    return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light)
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

    // attenuation
    float distance    = length(light.position - FragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                 light.quadratic * (distance * distance));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight light)
{
    vec3 lightDir = normalize(light.position - FragmentPosition);
    float theta = dot(lightDir, normalize(-light.direction));
    if (theta > light.cutOff) {
        float epsilon   = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);   
        // ambient
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

        // diff
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
        
        // specular
        vec3 viewDir = normalize(viewPos - FragmentPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

        diffuse *= intensity;
        specular *= intensity;

        return (ambient + diffuse + specular);

    } else {
        return light.ambient * vec3(texture(material.diffuse, TexCoord));
    }
    
}


void main()
{
    vec3 result;
    for (int i = 0; i < directLightNumber; i++) {
        result += calculateDirectLight(directLights[i]);
    }
    for (int i = 0; i < pointLightNumber; i++) {
        result += calculatePointLight(pointLights[i]);
    }
    for (int i = 0; i < spotLightNumber; i++) {
        result += calculateSpotLight(spotLights[i]);
    }
    
    FragColor = vec4(result, 1.0);
}