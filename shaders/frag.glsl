#version 330 core
out vec4 FragColor;

in vec3 myColor;
in vec2 TexCoord;

uniform sampler2D myTexture;

void main()
{
	FragColor = vec4(myColor, 1.0f);
}
