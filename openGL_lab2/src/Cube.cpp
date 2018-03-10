#include "Cube.h"

#define DIM 3	// dimension
#define PT_PER_EDGE 4
#define EDGES 6 // number of edges


using namespace obj;

Cube::Cube()
{
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

	glGenBuffers(1, &_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ARRAY_BUFFER, DIM * EDGES * PT_PER_EDGE * sizeof(float), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);
}


Cube::~Cube()
{
}

void obj::Cube::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glDrawArrays(GL_QUADS, 0, 4);
}
