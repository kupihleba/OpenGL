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

	_precision = 50;
	_build(_precision, 0.4f, 1.0f, 2.0f);

	//std::cout << "0: " << (*((float*)&(_vertices.data()[0]))) << '\t' << _vertices[0] << std::endl
	//	<< "size " << _vertices.size() * sizeof(float) << std::endl;

	glGenBuffers(1, &_VBufObj);

	glBindBuffer(GL_ARRAY_BUFFER, _VBufObj);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void obj::Spiral::draw()
{
	glUseProgram(_shader);
	glm::mat4 res = _getTransformations();

	GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");
	GLint myColor = glGetUniformLocation(_shader, "myColor");

	glUniformMatrix4fv(myTranformation, 1, GL_FALSE, glm::value_ptr(res));
	glUniform4f(myColor, 1.0f, 0.3f, 0.3f, 0.9f);
	glPolygonMode(GL_FRONT_AND_BACK, _view);
	

	glBindVertexArray(_VBufObj);
	glBindBuffer(GL_ARRAY_BUFFER, _VBufObj);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 3);
	glBindVertexArray(0);
}


Spiral::~Spiral()
{
	glDeleteBuffers(1, &_VBufObj);
}

void obj::Spiral::_build(int precision, float r, float R, float len)
{
	using std::get;

	_f = [k=r, m=R](float u, float v) -> Coords {
		//const float k = 0.4f;
		//const float m = 1.0f;

		return Coords(
			k*cos(u) + m*cos(v),
			k*v,
			k*sin(u) + m*sin(v));
	};
	//const float len = 2.0f;
	float delta = 2 * PI / precision;
	Coords coords;
	float u = 0, v = 0;
	_vertices.clear();

	for (v = 0; v <= 2 * PI * len + delta; v += delta) {
		for (u = 0; u <= 2 * PI + delta; u += delta) {
			coords = _f(u, v);
			_vertices.push_back(get<0>(coords));
			_vertices.push_back(get<1>(coords));
			_vertices.push_back(get<2>(coords));

			coords = _f(u, v + delta);
			_vertices.push_back(get<0>(coords));
			_vertices.push_back(get<1>(coords));
			_vertices.push_back(get<2>(coords));

			coords = _f(u + delta, v);
			_vertices.push_back(get<0>(coords));
			_vertices.push_back(get<1>(coords));
			_vertices.push_back(get<2>(coords));

			coords = _f(u + delta, v + delta);
			_vertices.push_back(get<0>(coords));
			_vertices.push_back(get<1>(coords));
			_vertices.push_back(get<2>(coords));

			coords = _f(u, v + delta);
			_vertices.push_back(get<0>(coords));
			_vertices.push_back(get<1>(coords));
			_vertices.push_back(get<2>(coords));

			coords = _f(u + delta, v);
			_vertices.push_back(get<0>(coords));
			_vertices.push_back(get<1>(coords));
			_vertices.push_back(get<2>(coords));
		}
	}
	for (u = 0; u <= 2 * PI + delta; u += delta) { 
		// TODO: Wrong vertices inserted!
		coords = _f(u, v);
		_vertices.push_back(get<0>(coords));
		_vertices.push_back(get<1>(coords));
		_vertices.push_back(get<2>(coords));
	}
}

/// ATTENTION! RACE CONDITIONS HERE!
void obj::Spiral::reconstruct(int precision) 
{
	_precision = precision;
	// TODO: BLOCK EVERYTHING DURING REBUILD!
	// MEMORY LEAKS POSSIBLE
	_build(precision, 0.4f, 1.0f, 2.0f);
	glDeleteBuffers(1, &_VBufObj);
	glGenBuffers(1, &_VBufObj);
	glBindBuffer(GL_ARRAY_BUFFER, _VBufObj);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

int obj::Spiral::getBuildPrecision()
{
	return _precision;
}
