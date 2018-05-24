#include "Shader.h"
#include <ShaderFactory.h>
#include <glm/gtc/type_ptr.hpp>
#include <utils/kupihleba.h>

Shader::Shader() : Shader(ShaderFactory().getBasicShader()) {}

Shader::Shader(GLint shaderId)
{
	const GLsizei DIM = 3;
	const GLsizei RGBA = 4;
	_shaderId = shaderId;
	glUseProgram(_shaderId);

	// Get uniform locations:	
	_myTransformation = prt(glGetUniformLocation(_shaderId, "myTransformation"));
	_myColor = prt(glGetUniformLocation(_shaderId, "myColor"));

	// Get attribute locations:
	_position = prt(glGetAttribLocation(_shaderId, "position"));
	//_color = prt(glGetAttribLocation(_shaderId, "color"));
	_normal = glGetAttribLocation(_shaderId, "normal");


	glGenVertexArrays(1, &_vao); // Generate 1 VAO
	glGenBuffers(1, &_vbo); // Generate 1 VBO

	glBindBuffer(GL_ARRAY_BUFFER, _vbo); // Bind VBO first
	glBindVertexArray(_vao); // Bind VAO properties to VBO
	{
		GLsizei packSize = DIM * sizeof(GLfloat) * 2;

		glEnableVertexAttribArray(_position);
		glVertexAttribPointer(_position, DIM, GL_FLOAT, GL_FALSE, packSize, (GLvoid*)0);

		glEnableVertexAttribArray(_normal);
		glVertexAttribPointer(_normal, DIM, GL_FLOAT, GL_FALSE, packSize, (GLvoid*)3);

		//glEnableVertexAttribArray(_color);
		//glVertexAttribPointer(_color, RGBA, GL_FLOAT, GL_FALSE, RGBA * sizeof(GLfloat) + DIM * sizeof(GLfloat) * 2, (GLvoid*)6);
	}
	glBindVertexArray(0); // Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO

	glUseProgram(0);
}

Shader::Shader(Shader && shader)
{
	using std::move;
	_shaderId = move(shader._shaderId);

	_vao = move(shader._vao);

	_myColor = move(shader._myColor);
	_myTransformation = move(shader._myTransformation);

	_position = move(shader._position);
	_normal = move(_normal);
	_color = move(shader._color);
}


Shader::~Shader()
{
	glDeleteBuffers(1, &_vbo);
	// TODO: delete atrributes, clear memory?
}

Shader & Shader::color(const float & r, const float & g, const float & b, const float & a)
{
	glUniform4f(_myColor, r, g, b, a);
	return *this;
}

Shader & Shader::tranformation(const glm::mat4 & transformation)
{
	glUniformMatrix4fv(_myTransformation, 1, GL_FALSE, glm::value_ptr(transformation));
	return *this;
}

Shader & Shader::enable()
{
	glUseProgram(_shaderId);
	glBindVertexArray(_vao); // Turns on all attributes

	return *this;
}

Shader & Shader::disable()
{
	glUseProgram(0);
	glBindVertexArray(0); // Turn everything back off
	return *this;
}
/*
Shader & Shader::operator << (vector<float> && bufferArray)
{
	// TODO

	return *this;
}*/

GLuint &Shader::getBufAllocation()
{
	return _vbo;
}

void Shader::regenerateBuffer()
{
	glDeleteBuffers(1, &_vbo);
	glGenBuffers(1, &_vbo);
}
