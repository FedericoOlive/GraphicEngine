#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform vec3 colorTint;
uniform float alpha;

void main()
{
    FragColor = vec4(ourColor.x * colorTint.x, ourColor.y * colorTint.y, ourColor.z * colorTint.z, alpha);
}