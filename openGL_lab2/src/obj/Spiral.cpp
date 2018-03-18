#include "Spiral.h"
#include <math.h>
#include <vector>
#include <tuple>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#define DEBUG false

#include <iostream>
#define prt(a) (DEBUG ? ([](auto x) -> auto {std::cout << x << std::endl; return x;}((a))) : (a))


#define PI 3.14159265358979f

using namespace obj;

Spiral::Spiral(GLuint shader)
{
	_shader = shader;
	_view = GL_FILL;

	_f = [](float u, float v) -> Coords {
		const float k = 1.0f;
		const float m = 1.5f;
		const float vl = 1.0f;

		return Coords(
			k*cos(u), //+ m*cos(v),
			vl*v + k*u,
			k*sin(u));//-2*m*abs(sin(v)));
	};
	const int precision = 50;
	float delta = 2 * PI / precision;
	for (float v = 0; v < 2 * PI; v += delta) {
		for (float u = 0; u < 2 * PI; u += delta) {
			Coords coords = _f(u, v);
			_vertices.push_back(prt(std::get<0>(coords)));
			_vertices.push_back(prt(std::get<1>(coords)));
			_vertices.push_back(prt(std::get<2>(coords)));
		}
	}

	glGenBuffers(1, &_VBufObj);

	glBindBuffer(GL_ARRAY_BUFFER, _VBufObj);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size(), _vertices.data(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void obj::Spiral::draw()
{
	glUseProgram(_shader);
	glm::mat4 res = _getTransformations();

	GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");
	GLint myColor = glGetUniformLocation(_shader, "myColor");

	glUniformMatrix4fv(myTranformation, 1, GL_FALSE, glm::value_ptr(res));
	glUniform4f(myColor, 1.0f, 0.3f, 0.3f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, _view);

	glBindVertexArray(_VBufObj);
	glDrawArrays(GL_POINTS, 0, _vertices.size());
	glBindVertexArray(0);
}


Spiral::~Spiral()
{
}