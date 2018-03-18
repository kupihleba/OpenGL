#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "obj/Cube.h"
#include "obj/Spiral.h"
#include "ShaderFactory.h"
#include <memory>

#define use(ns) using ns;
use(std::string) use(std::shared_ptr)

class MyEngine
{
public:
	MyEngine();
	~MyEngine();

private:
	GLFWwindow *_activity;
	int _activityWidth = 1280;
	int _activityHeight = 768;

	GLuint _basicShader;
	GLuint _staticShader;
	GLuint _buffer;

	GLint _type = GL_LINE;

	void _initObjects();
	void _draw();
	void _destroyObjects();

	ShaderFactory _shaderFactory;

	shared_ptr<obj::Object> _focus;

	shared_ptr<obj::Cube> _cube;
	shared_ptr<obj::Cube> _miniCube;
	shared_ptr<obj::Cube> _projCube;

	shared_ptr<obj::Spiral> _spiral;

	void _mainLoop();

	static void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

