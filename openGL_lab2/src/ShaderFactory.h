#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define use(ns) using ns;
use(std::string)

class ShaderFactory
{
public:
	ShaderFactory();
	~ShaderFactory();
	GLuint loadShader(const string & filepath);
	GLuint getBasicShader();

private:
	GLuint _createShader(string & vertexShader, string & fragmentShader);
	GLuint _compileShader(GLuint type, const string & src);
};

