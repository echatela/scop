#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 color;

uniform sampler2D myTexture;
uniform float mixValue;

void main()
{
	FragColor = mix(vec4(color, 1.0f), texture(myTexture, texCoord), mixValue);
}
