#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <vector>
#include <utils/Structures.h>
#include <utils/kupihleba.h>

class Shader
{
public:
	Shader(GLint shaderId);
	//Shader(Shader && shader);
	~Shader();

	Shader & color(
		const float & r, 
		const float & g, 
		const float & b, 
		const float & a);
	Shader & light(
		const glm::vec3 & position, 
		const glm::vec3 & intensities);
	Shader & tranformation(const glm::mat4 & transformation); // TODO: optimize
	Shader & camera(const glm::mat4 position);
	Shader & tex(float tex);
	
	Shader & enable();
	Shader & disable();

	bool isActive();

	GLuint getId() {
		return _shaderId;
	}
	//Shader & operator << (vector<float> && bufferArray);  // TODO

	//GLuint & getBufAllocation();
	//void regenerateBuffer();

private:
	//void _setCubeBinding();

	GLint _shaderId;
	bool _firstTime = true;

	// Uniform:
	GLint _myColor;
	GLint _myTransformation;
	GLint _myCamera;
	struct LightRef {
		GLint position;
		GLint intensities;
	} _light;

	struct Cache {
		Light _light;
		glm::mat4 camera;
	} _cache;

	void _checkStatus();

public:
	// Attributes:
	GLint _position;
	GLint _normal;
	GLint _color;
	GLint _texture;
	GLint _tex;
};

