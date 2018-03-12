#vertex
#version 330 core
layout(location = 0) in vec4 position;
uniform mat4 myTransformation;
uniform float k;

mat4 stretch(float kf) {
	return mat4(
		vec4(k, 0.0, 0.0, 0.0),
		vec4(0.0, k, 0.0, 0.0),
		vec4(0, 0.0, k, 0.0),
		vec4(0.0, 0.0, 0.0, 1.0)
	);
}
void main()
{
	gl_Position = position * stretch(k) * myTransformation;
}

#fragment
#version 330 core

layout(location = 0) out vec4 color;
uniform vec4 myColor;

void main()
{
	color = myColor;
}