#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <utils/kupihleba.h>

class Shader
{
public:
	Shader();
	Shader(GLint shaderId);
	Shader(Shader && shader);
	~Shader();

	Shader & color(const float & r, 
		const float & g, 
		const float & b, 
		const float & a);
	Shader & tranformation(const glm::mat4 & transformation); // TODO: optimize
	Shader & enable();
	Shader & disable();

	//Shader & operator << (vector<float> && bufferArray);  // TODO

	GLuint &getBufAllocation();
	void regenerateBuffer();

private:
	GLint _shaderId;

	GLuint _vao;
	GLuint _vbo;

	// Uniform:
	GLint _myColor;
	GLint _myTransformation;

	// Attributes:
	GLint _position;
	GLint _normal;
	GLint _color;
};

