# version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragmentPosition;

uniform bool useTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float ambientStrength;
uniform vec4 lightColor;
uniform vec4 objectColor;
uniform vec3 lightPosition;

void main()
{
    vec4 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;
    vec4 result = ambient + diffuse;
    if (useTexture) {
        FragColor = result * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    } else {
        FragColor = result * objectColor;
    }
}