#vertex
#version 330 core
in vec3 position;
uniform mat4 myTransformation;
in vec3 normal;

void main()
{
	gl_Position = vec4(position, 1) * myTransformation;
}

#fragment
#version 330 core

out vec4 color;
uniform vec4 myColor;

void main()
{
	color = myColor;
}