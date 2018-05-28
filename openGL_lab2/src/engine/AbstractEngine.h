#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include <utils/kupihleba.h>
#include <Scene.h>
#include <lib/Camera.h>

using std::vector;

class AbstractEngine
{
public:
	AbstractEngine();
	~AbstractEngine();

	template <class T>
	std::enable_if_t<std::is_base_of<obj::Object, T>::value, void> addObject(T & object) {
		_scene.addObject(object);
	};

	virtual void start();

protected:
	struct Activity {
		GLFWwindow *ref;
		int width = 1280;
		int height = 768; 
		void setFullscreen();
	} _activity;

	//virtual void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//virtual void _mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	//std::function<void(GLFWwindow* window, int button, int action, int mods)> _mouseButtonCallback = nullptr;


private:
	static void _staticWindowSizeCallback(GLFWwindow* window, int width, int height);
	std::function <void(GLFWwindow*, int, int)> _windowSizeCallback;
	static void _staticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	std::function <void(GLFWwindow* window, int key, int scancode, int action, int mods)> _keyCallback;
	static void _staticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	std::function <void(GLFWwindow* window, int button, int action, int mods)> _mouseButtonCallback;


protected:
	void _setWindowSizeCallback(decltype(_windowSizeCallback) callback);
	void _setKeyCallback(decltype(_keyCallback) callback);
	void _setMouseButtonCallback(decltype(_mouseButtonCallback) callback);
	
	Scene _scene;
	Camera _camera;

	void setupMonitor();

	std::function <void(GLFWwindow* window, int key, int scancode, int action, int mods)> _getKeyCallback();
	virtual void _run();
	virtual void _draw();
};

