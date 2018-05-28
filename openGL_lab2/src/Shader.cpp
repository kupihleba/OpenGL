#include "Shader.h"
#include <ShaderFactory.h>
#include <glm/gtc/type_ptr.hpp>
#include <utils/kupihleba.h>
#include <utils/Structures.h>
#include <functional>
#define DEFAULT_COUT false

//Shader::Shader() : Shader(ShaderFactory().getBasicShader()) {}

Shader::Shader(GLint shaderId)
{
	const GLsizei DIM = 3;
	const GLsizei RGBA = 4;
	_shaderId = shaderId;
	glUseProgram(_shaderId);
	{
		// Get uniform locations:	
		_myTransformation = prt(glGetUniformLocation(_shaderId, "myTransformation"));
		_myColor = prt(glGetUniformLocation(_shaderId, "myColor"));
		_myCamera = prt(glGetUniformLocation(_shaderId, "camera"));
		_light.position = prt(glGetUniformLocation(_shaderId, "myLightStruct.position"));
		_light.intensities = prt(glGetUniformLocation(_shaderId, "myLightStruct.intensities"));
		_tex = prt(glGetUniformLocation(_shaderId, "tex"));
		cout << "- - -" << endl;
		// Get attribute locations:
		_position = prt(glGetAttribLocation(_shaderId, "position"));
		_color = prt(glGetAttribLocation(_shaderId, "color"));
		_normal = prt(glGetAttribLocation(_shaderId, "normal"));
		_texture = prt(glGetAttribLocation(_shaderId, "textureCoords"));
	}
	glUseProgram(0);
}
/*
Shader::Shader(Shader && shader)
{
	using std::move;
	_shaderId = move(shader._shaderId);

	_vao = move(shader._vao);

	_myColor = move(shader._myColor);
	_myTransformation = move(shader._myTransformation);
	_camera = move(shader._camera);

	_position = move(shader._position);
	_normal = move(_normal);
	_color = move(shader._color);
}
*/

Shader::~Shader()
{
}
#if 1
Shader & Shader::color(const float & r, const float & g, const float & b, const float & a)
{
	_checkStatus();
	if (_myColor == -1) {
		return *this; // IGNORED!!!
		throw std::exception("\"color\" attribute does not exist!");
	} 
	glUniform4f(_myColor, r, g, b, a);
	return *this;
}
#endif

Shader & Shader::light(const glm::vec3 & position, const glm::vec3 & intensities)
{
	_checkStatus();
	if (_light.position == -1 || _light.intensities == -1) {
		throw std::exception("Light uniform structure does not exist!");
	}
	cout << "SET light" << endl;
	_cache._light.position = position;
	_cache._light.intensities = intensities;

	glUniform3fv(_light.position, 1, glm::value_ptr(position));
	glUniform3fv(_light.intensities, 1, glm::value_ptr(intensities));
	return *this;
}

Shader & Shader::tranformation(const glm::mat4 & transformation)
{
	_checkStatus();
	if (_myTransformation == -1) {
		throw std::exception("\"myTransformation\" uniform does not exist!");
	}
	cout << "SET tranformation" << endl;
	glUniformMatrix4fv(_myTransformation, 1, GL_FALSE, glm::value_ptr(transformation));
	return *this;
}

Shader & Shader::camera(const glm::mat4 position)
{
	_checkStatus();
	if (_myCamera == -1) {
		throw std::exception("\"camera\" uniform does not exist!");
	}
	cout << "SET camera" << endl;
	_cache.camera = position;
	glUniformMatrix4fv(_myCamera, 1, GL_FALSE, glm::value_ptr(position));
	return *this;
}

Shader & Shader::tex(float tex)
{
	_checkStatus();
	if (_tex == -1) {
		return *this; // IGNORED!!!
		throw std::exception("\"tex\" uniform does not exist!");
	}
	glUniform1f(_tex, tex);
	return *this;
}


Shader & Shader::enable()
{
	glUseProgram(_shaderId);

	//camera(_cache.camera);
	//light(_cache._light.position, _cache._light.intensities);
	return *this;
}

Shader & Shader::disable()
{
	glUseProgram(0);
	glBindVertexArray(0); // Turn everything back off
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Bind VBO first

	return *this;
}

bool Shader::isActive()
{
	GLint active = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &active);
	return _shaderId == active;
}

void Shader::_checkStatus()
{
	if (!isActive()) {
		throw std::exception("Current shader is not active!");
	}
}

#if 0
Shader & Shader::operator << (vector<float> && bufferArray)
{
	/*glBindBuffer(GL_ARRAY_BUFFER, );

	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/
	return *this;
}
#endif

/*
void Shader::regenerateBuffer()
{
	glDeleteBuffers(1, &_data.vbo); // Otherwise it doesn't handle
	glGenBuffers(1, &_data.vbo); // :(

	//_setBindings();
}
*/

/*
void Shader::_setCubeBinding()
{
	const GLsizei DIM = 3;
	const GLsizei RGBA = 4;
	glBindBuffer(GL_ARRAY_BUFFER, _data.vbo); // Bind VBO first
	glBindVertexArray(_data.vao); // Bind VAO properties to VBO
	{
		GLsizei packSize = DIM * sizeof(GLfloat) * 2 +
			+2 * sizeof(GL_FLOAT);		
	}
	glBindVertexArray(0); // Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}*/


