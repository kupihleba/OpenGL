#include "Cube.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <lib/Bitmap.h>

/*
#define DIM 3	// dimension
#define PT_PER_EDGE 4
// #define COLORS 6 * 3
#define EDGES 6 // number of edges */
#define PI 3.14159265358979f

using namespace obj;


obj::Cube::Cube(std::shared_ptr<Shader> shader)
	:Drawable(shader)
{
#if 0
	_vertices = {

		//1.0f,  0.0f, 0.0f,
		//     BACK     //
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f, 
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f, 
		-1.0f,  1.0f,  1.0f,

		//0.5f,  0.0f, 0.0f,
		//     FACE     //
		1.0f, -1.0f, -1.0f, 
		1.0f, -1.0f,  1.0f, 
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f, 
		1.0f,  1.0f,  1.0f,

		//0.0f,  0.1f, 0.0f,
		//    RIGHT     //
		-1.0f,  1.0f, -1.0f, 
		1.0f,  1.0f, -1.0f, 
		1.0f,  1.0f,  1.0f, 
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f, 
		1.0f,  1.0f,  1.0f,

		//0.0f,  0.5f, 0.0f,
		//     LEFT     //
		1.0f, -1.0f, -1.0f, 
		1.0f, -1.0f,  1.0f, 
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, 
		-1.0f, -1.0f,  1.0f,

		//0.0f,  0.0f, 1.0f,
		//    BOTTOM    //
		-1.0f,  1.0f, -1.0f, 
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, 
		1.0f, -1.0f, -1.0f,

		//0.0f,  0.0f, 5.0f,
		//     TOP      //
		1.0f,  1.0f, 1.0f, 
		1.0f, -1.0f, 1.0f, 
		-1.0f, -1.0f, 1.0f, 
		1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f, 
		-1.0f, -1.0f, 1.0f,
	};
#endif;
#if 1
	_vertices = {
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, 1.0f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, -1.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f
	};
	
#endif
	loadVertices();
}


void obj::Cube::_draw()
{
	//glDrawArrays(GL_QUADS, 0, DIM * EDGES * PT_PER_EDGE);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void obj::Cube::_defineVao()
{
	const GLsizei DIM = 3;
	const GLsizei RGBA = 4;
	using proto::AttributeType;
	*this << Chunk{ AttributeType::POSITION, DIM }
		  << Chunk{ AttributeType::TEXTURE, 2 }
		  << Chunk{ AttributeType::NORMAL, DIM }
	      << Chunk{ AttributeType::COLOR, RGBA };
}

string obj::Cube::toString() const
{
	return "Cube";
}
