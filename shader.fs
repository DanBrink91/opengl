#version 130

uniform int screenWidth;
uniform int screenHeight;
in vec4 Color;
out vec4 FragColor;

void main()
{
	FragColor = Color;
}
