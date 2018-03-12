#include "Cube.h"
#include <glm\glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tuple>

#define DIM 3	// dimension
#define PT_PER_EDGE 4
#define COLOURS 6 * 3
#define EDGES 6 // number of edges 
#define PI 3.141592654

using namespace obj;

Cube::Cube(GLuint shader)
{
	_shader = shader;
	_view = GL_LINE;
	_size = 1.0f;
	_xAngle = 0.0f;
	_yAngle = 0.0f;
	_zAngle = 0.0f;

#if 1
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
#if 0
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

void obj::Cube::projDraw()
{
	glUseProgram(_shader);
	glBindVertexArray(_VBufObj);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	//glRotatef(0.7f, 0.0f, 1.0, 0.0f);

	//glm::mat4 rot = glm::eulerAngleYXZ(_xAngle, _yAngle, _zAngle);

	GLint vertexColorLocation = glGetUniformLocation(_shader, "myColor");
	glUniform4f(vertexColorLocation, 0.5f, 0.5f, 1.0f, 1.0f);

	glm::mat4 rot = glm::eulerAngleYXZ(_xAngle, _yAngle, _zAngle);
	//glm::mat4 size = glm::

	GLint k_loc = glGetUniformLocation(_shader, "k");
	glUniform1f(k_loc, 1.0f);

	GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");
	
	//glUniformMatrix4fv(myTranformation, 1, GL_FALSE, glm::value_ptr(rot));
#if 0
	float norm[] = {
		0.1f,   0.0f,     0.0f,  -0.5f,
		0.0f,   0.1f,     0.0f,  -0.5f,
		0.0f,    0.0f,    0.1f,   0.4f,
		0.0f,    0.0f,    0.0f,   1.0f,
	};
#endif

#if 1
	float norm[] = {
		0.1f,   0.0f,     0.0f,   0.0f,
		0.0f,   0.1f,     0.0f,   0.0f,
		0.0f,    0.0f,    0.1f,   0.1f,
	   -0.2f,   -0.2f,    0.2f,   1.0f,
	};
#endif
	
	glm::mat4 res = rot * glm::make_mat4(norm);

	glUniformMatrix4fv(myTranformation, 1, GL_FALSE, glm::value_ptr(res));

	glPolygonMode(GL_FRONT_AND_BACK, _view);
	glDrawArrays(GL_QUADS, 0, 24);
	glBindVertexArray(0);
}


void obj::Cube::customDraw()
{
	glUseProgram(_shader);
	glBindVertexArray(_VBufObj);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	//glRotatef(0.7f, 0.0f, 1.0, 0.0f);
	
	glm::mat4 rot = glm::eulerAngleYXZ(_xAngle, _yAngle, _zAngle);

	GLint vertexColorLocation = glGetUniformLocation(_shader, "myColor");
	glUniform4f(vertexColorLocation, 0.5f, 0.5f, 1.0f, 1.0f);

	GLint k_loc = glGetUniformLocation(_shader, "k");
	glUniform1f(k_loc, 1.0f);

	GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");
	glUniformMatrix4fv(myTranformation, 1, GL_FALSE, glm::value_ptr(rot));


	glPolygonMode(GL_FRONT_AND_BACK, _view);
	glDrawArrays(GL_QUADS, 0, 24);
	glBindVertexArray(0);
}


void obj::Cube::draw()
{
	GLfloat timeValue = (GLfloat)glfwGetTime();
	float k = _size;
	const int SZ = 16;
	float fi = _xAngle; //timeValue;
	float norm[SZ] = {
		1.0f,   0.0f,     0.0f,     0.0f,
		0.0f,  cos(fi),  sin(fi),   0.0f,
		0.0f,  -sin(fi),  cos(fi),  0.0f,
		0.0f,    0.0f,     0.0f,    1.0f,
	};

	glUseProgram(_shader);
	
	//glm::mat4 rotAxis(1.0f, 0.0f, 0.0f, 1.0f);
	float w = 100, h = 100;
	glm::mat4 proj = glm::perspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
	
	GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
	GLint vertexColorLocation = glGetUniformLocation(_shader, "myColor");
	GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");
	GLint y_angle = glGetUniformLocation(_shader, "y_angle");
	GLint k_loc = glGetUniformLocation(_shader, "k");

	glUniform1f(y_angle, timeValue+_yAngle);
	glUseProgram(_shader);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 1.0f, 1.0f);
	//glMatrixMode(GL_PROJECTION);
	glUniformMatrix4fv(myTranformation, 1, GL_FALSE, norm);
	glUniform1f(k_loc, k);

	//glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glPolygonMode(GL_FRONT_AND_BACK, _view);
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
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
	glDrawArrays(GL_QUADS, 0, 24);
	glBindVertexArray(0);
}

void obj::Cube::setView(GLint view)
{
	_view = view;
}

void obj::Cube::setSize(float k)
{
	_size = k;
}

float obj::Cube::getSize()
{
	return _size;
}

void obj::Cube::setRotation(float x_angle, float y_angle, float z_angle)
{
	_xAngle = x_angle;
	_yAngle = y_angle;
	_zAngle = z_angle;
}

std::tuple<float, float, float> obj::Cube::getAngles()
{
	return std::tuple<float, float, float>(_xAngle, _yAngle, _zAngle);
}

void obj::Cube::setXangle(float x_angle)
{
	_xAngle = x_angle;
}

void obj::Cube::setYangle(float y_angle)
{
	_yAngle = y_angle;
}

void obj::Cube::setZangle(float z_angle)
{
	_zAngle = z_angle;
}