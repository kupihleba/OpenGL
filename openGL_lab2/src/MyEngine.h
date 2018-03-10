#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#define use(ns) using ns;
use(std::string)

class MyEngine
{
public:
	MyEngine();
	~MyEngine();

private:
	GLFWwindow *_activity;
	int _activityWidth = 640;
	int _activityHeight = 480;

	GLuint _buffer;

	void _initBuffers();
	void draw();
	void _destroyBuffers();
	GLuint _createShader(string &vertexShader, string &fragmentShader);
	GLuint _compileShader(GLuint type, const string & src);
	GLuint _loadShader(const string &path);

	void _mainLoop();

	static void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

