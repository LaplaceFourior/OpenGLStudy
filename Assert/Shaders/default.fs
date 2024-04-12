# version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform bool useTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    if (useTexture) {
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    } else {
        FragColor = vec4(ourColor, 1.0f);
    }
    // FragColor = texture(ourTexture, TexCoord);
    // FragColor = vec4(ourColor, 1.0f);
}