#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utils/kupihleba.h>
#include <Shader.h>
#include <memory>

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
	GLuint loadShader(string && filepath);

	/// <summary>
	/// Loads the basic shader
	/// </summary>
	/// <returns>
	/// Shader id
	/// </returns>
	/*static*/ std::shared_ptr<Shader> getBasicShader();

	std::shared_ptr<Shader> getSuperShader();

private:
	GLuint _createShader(string && vertexShader, string && fragmentShader);
	GLuint _compileShader(GLuint type, const string & src);
	GLuint _basicShader;
};
