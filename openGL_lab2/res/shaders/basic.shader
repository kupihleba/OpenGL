#vertex
#version 330 core
layout(location = 0) in vec4 position;
uniform mat4 myTransformation;
uniform float y_angle;
uniform float timer;

mat4 rotate_y(float a)
{
	return mat4(
		vec4(cos(a),  0.0, sin(a), 0.0),
		vec4(  0.0,   1.0,  0.0,   0.0),
		vec4(-sin(a), 0.0, cos(a), 0.0),
		vec4(  0.0,   0.0,  0.0,   1.0)
	);
}

void main()
{
	gl_Position = position * myTransformation * rotate_y(y_angle);
}

#fragment
#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 myColor;

void main()
{
	color = myColor;
}