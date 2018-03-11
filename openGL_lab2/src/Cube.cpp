#include "Cube.h"

#define DIM 3	// dimension
#define PT_PER_EDGE 4
#define COLOURS 6 * 3
#define EDGES 6 // number of edges 
#define PI 3.141592654

using namespace obj;

Cube::Cube(GLuint shader)
{
	_shader = shader;
#if 0
	float data[DIM * EDGES * PT_PER_EDGE /*+ COLOURS*/] = {
		
		//0.0f,  0.0f, 5.0f,
		//     TOP      //
   	     1.0f,  1.0f, 1.0f,
	     1.0f, -1.0f, 1.0f,
	    -1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f,

		//0.0f,  0.0f, 1.0f,
		//    BOTTOM    //
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,	

		 //0.0f,  0.5f, 0.0f,
		 //     LEFT     //
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,		

		 //0.0f,  0.1f, 0.0f,
		 //    RIGHT     //
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,

		//0.5f,  0.0f, 0.0f,
		//     FACE     //
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f

		//1.0f,  0.0f, 0.0f,
		//     BACK     //
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
	};
#endif
#if 0
	float data[] = {
		// Позиции             
		-0.5f, -0.5f, -0.5f,   
		0.5f, -0.5f, -0.5f,    
		0.5f,  0.5f, -0.5f,    
		0.5f,  0.5f, -0.5f,    
		-0.5f,  0.5f, -0.5f,   
		-0.5f, -0.5f, -0.5f,   

		-0.5f, -0.5f,  0.5f,  
		0.5f, -0.5f,  0.5f,    
		0.5f,  0.5f,  0.5f,    
		0.5f,  0.5f,  0.5f,    
		-0.5f,  0.5f,  0.5f,   
		-0.5f, -0.5f,  0.5f,   

		-0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f, -0.5f,   
		-0.5f, -0.5f, -0.5f,   
		-0.5f, -0.5f, -0.5f,   
		-0.5f, -0.5f,  0.5f,   
		-0.5f,  0.5f,  0.5f,  

		0.5f,  0.5f,  0.5f,    
		0.5f,  0.5f, -0.5f,    
		0.5f, -0.5f, -0.5f,   
		0.5f, -0.5f, -0.5f,    
		0.5f, -0.5f,  0.5f,   
		0.5f,  0.5f,  0.5f,    

		-0.5f, -0.5f, -0.5f,   
		0.5f, -0.5f, -0.5f,    
		0.5f, -0.5f,  0.5f,    
		0.5f, -0.5f,  0.5f,    
		-0.5f, -0.5f,  0.5f,  
		-0.5f, -0.5f, -0.5f,  

		-0.5f,  0.5f, -0.5f,  
		0.5f,  0.5f, -0.5f,    
		0.5f,  0.5f,  0.5f,   
		0.5f,  0.5f,  0.5f,    
		-0.5f,  0.5f,  0.5f,   
		-0.5f,  0.5f, -0.5f,  
	};
#endif
#if 1
	float data[3 * 4 * 6] = {
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f
	};
#endif
	for (int i = 0; i < DIM * EDGES * PT_PER_EDGE; i++) {
		data[i] /= 2.0f;
	}
	/*
	for (int i = 0; i < 24*3; i++) {
		data[i] /= 2.0f;
	}*/
	
#if 1
	glGenBuffers(1, &_VBufObj);
	glGenVertexArrays(1, &_VArrObj);

	glBindVertexArray(_VArrObj);
	glBindBuffer(GL_ARRAY_BUFFER, _VBufObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
#endif
}



Cube::~Cube()
{
}


void obj::Cube::draw()
{
	GLfloat timeValue = glfwGetTime();
	float k = 1.0f;
	const int SZ = 16;
	float fi = timeValue;
	float norm[SZ] = {
		1.0f, 0.0f,      0.0f,    0.0f,
		0.0f, k*cos(fi), sin(fi), 0.0f,
		0.0f, -sin(fi),  cos(fi), 0.0f,
		0.0f, 0.0f,      0.0f,    1.0f,
	};
	
	GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
	GLint vertexColorLocation = glGetUniformLocation(_shader, "myColor");
	GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");
	GLint y_angle = glGetUniformLocation(_shader, "y_angle");

	glUniform1f(y_angle, fi);
	glUseProgram(_shader);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 1.0f, 1.0f);
	//glMatrixMode(GL_PROJECTION);
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
	
	//glDrawArrays(GL_QUADS, 0, 24);

	glBindVertexArray(_VBufObj);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
	glBindVertexArray(0);
}