#include "Cube.h"

#define DIM 3	// dimension
#define PT_PER_EDGE 4
#define EDGES 6 // number of edges 

using namespace obj;

Cube::Cube(GLuint shader)
{
	_shader = shader;

	float data[DIM * EDGES * PT_PER_EDGE] = {
		 //     TOP      //
		 1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f,

		 //    BOTTOM    //
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		 //     LEFT     //
		 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		 //    RIGHT     //
		 1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		 //     FACE     //
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,

		 //     BACK     //
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f
	};
	for (int i = 0; i < DIM * EDGES * PT_PER_EDGE; i++) {
		data[i] /= 2.f;
	}


	glGenBuffers(1, &_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ARRAY_BUFFER, DIM * EDGES * PT_PER_EDGE * sizeof(float), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (GLvoid*)0);
	glBindVertexArray(0);
}



Cube::~Cube()
{
}


void obj::Cube::draw()
{
	float k = 2.0f;
	const int SZ = 16;
	float norm[SZ] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  k,   0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	GLfloat timeValue = glfwGetTime();
	GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
	GLint vertexColorLocation = glGetUniformLocation(_shader, "myColor");
	GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");

	glUseProgram(_shader);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 1.0f, 1.0f);
	glUniformMatrix4fv(myTranformation, 1, GL_FALSE, norm);

	//glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	/*glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(norm);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
	//glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/
	//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
	glBindVertexArray(_buffer);
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);
}


