#vertex
#version 330 core
layout(location = 0) in vec4 position;
uniform mat4 myTransformation;

void main()
{
	gl_Position = position * myTransformation;
}

#fragment
#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 myColor;

void main()
{
	color = myColor;
}