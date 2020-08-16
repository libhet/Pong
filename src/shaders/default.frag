#version 330 core

out vec4 color;

uniform vec3 ourColor;

void main()
{
   vec3 color1 = ourColor;
   color = vec4(color1, 1.0);
}


