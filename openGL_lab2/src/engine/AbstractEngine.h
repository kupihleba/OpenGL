#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
//#include <obj/Object.h>
#define DEBUG
#ifdef DEBUG
#include <iostream>
#define debug(a) std::cout << a << std::endl
#else
#define debug(a) ;
#endif

using std::vector;

class AbstractEngine
{
public:
	AbstractEngine();
	~AbstractEngine();

protected:
	struct Activity {
		GLFWwindow *ref;
		int width = 1280;
		int height = 768;
	} _activity;

	//virtual void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//virtual void _mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	//std::function<void(GLFWwindow* window, int button, int action, int mods)> _mouseButtonCallback = nullptr;

	virtual void _draw() {};

private:
	static void _staticWindowSizeCallback(GLFWwindow* window, int width, int height);
	std::function <void(GLFWwindow*, int, int)> _windowSizeCallback;
	static void _staticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	std::function <void(GLFWwindow* window, int key, int scancode, int action, int mods)> _keyCallback;
	static void _staticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	std::function <void(GLFWwindow* window, int button, int action, int mods)> _mouseButtonCallback;

	void _mainLoop();

protected:
	void _setSizeCallback(decltype(_windowSizeCallback) callback);
	void _setKeyCallback(decltype(_keyCallback) callback);
	void _setMouseButtonCallback(decltype(_mouseButtonCallback) callback);
};

