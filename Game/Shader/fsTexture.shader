#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 colorTint;
uniform float alpha;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor.x * colorTint.x, ourColor.y * colorTint.y, ourColor.z * colorTint.z, alpha);
}