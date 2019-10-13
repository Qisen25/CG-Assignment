#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform float intensity;
uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, TexCoord); // set all 4 vector values to 1.0
}
