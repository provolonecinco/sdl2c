#version 410 core

// Outputs colors in RGBA
out vec4 FragColor;
// Inputs the color from the Vertex Shader
in vec3 color;
// Input textures
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	FragColor = texture(tex0, texCoord);
}
 