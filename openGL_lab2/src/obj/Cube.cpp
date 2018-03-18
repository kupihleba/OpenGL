#include "Cube.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DIM 3	// dimension
#define PT_PER_EDGE 4
// #define COLORS 6 * 3
#define EDGES 6 // number of edges 
#define PI 3.14159265358979f

using namespace obj;

Cube::Cube(GLuint shader):Object()
{
	_shader = shader;
	_view = GL_LINE;

	float data[DIM * EDGES * PT_PER_EDGE /*+ COLOURS*/] = {
		
		//1.0f,  0.0f, 0.0f,
		//     BACK     //
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		//0.5f,  0.0f, 0.0f,
		//     FACE     //
	     1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
	     1.0f,  1.0f, -1.0f,

		//0.0f,  0.1f, 0.0f,
		//    RIGHT     //
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,

		//0.0f,  0.5f, 0.0f,
		//     LEFT     //
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		
		//0.0f,  0.0f, 1.0f,
		//    BOTTOM    //
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		//0.0f,  0.0f, 5.0f,
		//     TOP      //
   	     1.0f,  1.0f, 1.0f,
	     1.0f, -1.0f, 1.0f,
	    -1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f,
	};

	for (int i = 0; i < DIM * EDGES * PT_PER_EDGE; i++) {
		data[i] /= 2.0f;
	}
	
	glGenBuffers(1, &_VBufObj);
	// glGenVertexArrays(1, &_VArrObj);

	// glBindVertexArray(_VArrObj);
	glBindBuffer(GL_ARRAY_BUFFER, _VBufObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	/*
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	*/

	glBindVertexArray(0);
}


Cube::~Cube() 
{
	glDeleteBuffers(1, &_VBufObj);
}


void obj::Cube::draw() {
	glUseProgram(_shader);
	glm::mat4 res = _getTransformations();

	GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");
	GLint myColor = glGetUniformLocation(_shader, "myColor");

	glUniformMatrix4fv(myTranformation, 1, GL_FALSE, glm::value_ptr(res));
	glUniform4f(myColor, 0.0f, 0.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, _view);

	glBindBuffer(GL_ARRAY_BUFFER, _VBufObj);
	//glBindVertexArray(_VBufObj);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_QUADS, 0, DIM * EDGES * PT_PER_EDGE);
	//glBindVertexArray(0);
}
