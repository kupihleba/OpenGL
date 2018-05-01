#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <objects/Cube.h>
#include <objects/Spiral.h>
#include <ShaderFactory.h>
#include <memory>

#define use(ns) using ns;
use(std::string) use(std::shared_ptr)

class MyEngine
{
public:
	MyEngine();
	~MyEngine();

	enum Show {
		CUBE,
		SPIRAL
	};

private:
	GLFWwindow *_activity;
	int _activityWidth = 1280;
	int _activityHeight = 768;

	Show _mode;

	GLuint _basicShader;
	GLuint _staticShader;
	GLuint _buffer;

	void _initObjects();
	void _draw();
	void _destroyObjects();

	ShaderFactory _shaderFactory;

	shared_ptr<obj::Object> _focus;

	shared_ptr<obj::Cube> _cube;
	shared_ptr<obj::Cube> _miniCube;
	shared_ptr<obj::Cube> _projCube;

	shared_ptr<obj::Spiral> _spiral;
	shared_ptr<obj::Spiral> _projSpiral;

	void _mainLoop();

	static void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void _window_size_callback(GLFWwindow* window, int width, int height);
};

