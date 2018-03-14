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

	/// <summary>
	/// Loads the shader from the given filepath
	/// </summary>
	/// <returns>
	/// Shader id
	/// </returns>
	GLuint loadShader(const string & filepath);

	/// <summary>
	/// Loads the basic shader
	/// </summary>
	/// <returns>
	/// Shader id
	/// </returns>
	/*static*/ GLuint getBasicShader();

private:
	GLuint _createShader(string & vertexShader, string & fragmentShader);
	GLuint _compileShader(GLuint type, const string & src);
};
