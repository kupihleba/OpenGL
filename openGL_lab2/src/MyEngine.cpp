#include "MyEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>

#define use(ns) using ns;
use(std::cout) use(std::endl)

MyEngine::MyEngine()
{
	if (!glfwInit())
		throw -1;

	_activity = glfwCreateWindow(_activityWidth, _activityHeight, "Kupihleba project", NULL, NULL);
	if (!_activity)
	{
		glfwTerminate();
		throw -1;
	}
	glfwSetKeyCallback(_activity, _keyCallback);

	glfwMakeContextCurrent(_activity);
	glfwSetWindowUserPointer(_activity, this);

	if (glewInit() != GLEW_OK) {
		cout << "glewInit failed!" << endl;
	}
	else {
		cout << glGetString(GL_VERSION) << endl;
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	_basicShader = _shaderFactory.loadShader("res/shaders/basic.shader");
	_staticShader = _shaderFactory.loadShader("res/shaders/static.shader");

	//glViewport(0, 0, _activityWidth, _activityHeight);

	if (_activityWidth > _activityHeight) {
		int size =  _activityHeight;
		int delta = (_activityWidth - _activityHeight) / 2;
		glViewport(delta, 0, size, size);
	}
	else {
		int size = _activityWidth;
		int delta = (_activityHeight - _activityWidth) / 2;
		glViewport(0, delta, size, size);
	}

	_initObjects();
	_mainLoop();
	_destroyObjects();
}

MyEngine::~MyEngine()
{
	glfwTerminate();
}

void MyEngine::_initObjects()
{
	_cube = shared_ptr<obj::Cube>(new obj::Cube(_basicShader));
	_miniCube = shared_ptr<obj::Cube>(new obj::Cube(_shaderFactory.getBasicShader()));
	_extraCube = shared_ptr<obj::Cube>(new obj::Cube(_staticShader));
	
	_miniCube->setXangle(0.5f);
	_miniCube->setYangle(0.5f);
	_extraCube->setXangle(0.5f);
	_extraCube->setYangle(0.5f);
}

void MyEngine::_destroyObjects() {}

void MyEngine::_draw()
{
	if (_activityWidth > _activityHeight) {
		int size = _activityHeight;
		int delta = (_activityWidth - _activityHeight) / 2;
		glViewport(delta, 0, size, size);
	}
	else {
		int size = _activityWidth;
		int delta = (_activityHeight - _activityWidth) / 2;
		glViewport(0, delta, size, size);
	}
	_cube->setView(_type);
	_cube->draw();
	
	glViewport(0, 0, 100, 100);
	_miniCube->setTranslation(0.25f, 0.4f, 0.0f);
	_miniCube->simpleDraw();

	//glViewport(0, 100, 600, 600);
	//_extraCube->projDraw();
}

void MyEngine::_mainLoop()
{
	while (!glfwWindowShouldClose(_activity))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		_draw();
		glfwSwapBuffers(_activity);
		glfwPollEvents();
	}
}

void MyEngine::_keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	MyEngine *context = static_cast<MyEngine*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		if (context->_type == GL_FILL) {
			context->_type = GL_LINE;
		} else {
			context->_type = GL_FILL;
		}
	}
	else {
		float x_angle, y_angle;
		switch (key)
		{
		case GLFW_KEY_KP_ADD:
			context->_cube->setSize(context->_cube->getSize() + 0.05f);
			break;
		case GLFW_KEY_KP_SUBTRACT:
			context->_cube->setSize(context->_cube->getSize() - 0.05f);
			break;

		case GLFW_KEY_LEFT:
			x_angle = std::get<0>(context->_cube->getRotation());
			context->_cube->setXangle(x_angle + 0.02f);
			break;
		case GLFW_KEY_RIGHT:
			x_angle = std::get<0>(context->_cube->getRotation());
			context->_cube->setXangle(x_angle - 0.02f);
			break;

		case GLFW_KEY_UP:
			y_angle = std::get<1>(context->_cube->getRotation());
			context->_cube->setYangle(y_angle + 0.05f);
			break;
		case GLFW_KEY_DOWN:
			y_angle = std::get<1>(context->_cube->getRotation());
			context->_cube->setYangle(y_angle - 0.05f);
			break;

		case GLFW_KEY_W:
			
			break;
		case GLFW_KEY_S:

			break;
		case GLFW_KEY_A:
			
			break;
		case GLFW_KEY_D:
			
			break;
		default:
			break;
		}
	}
}
