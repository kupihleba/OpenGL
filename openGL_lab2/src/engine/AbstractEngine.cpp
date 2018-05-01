#include "AbstractEngine.h"

AbstractEngine::AbstractEngine()
{
	if (!glfwInit()) {
		throw std::exception("Glew could not be initialized!");
	}
	
	_activity.ref = glfwCreateWindow(_activity.width, _activity.height, "Kupihleba project", NULL, NULL);

	if (!_activity.ref)
	{
		glfwTerminate();
		throw std::exception("GLFW create window failed!");
	}
	// Set callbacks:
	glfwSetKeyCallback(_activity.ref, AbstractEngine::_staticKeyCallback);
	glfwSetWindowSizeCallback(_activity.ref, AbstractEngine::_staticWindowSizeCallback);
	glfwSetMouseButtonCallback(_activity.ref, AbstractEngine::_staticMouseButtonCallback);

	_windowSizeCallback = [](GLFWwindow*, int, int) -> auto {};
	_mouseButtonCallback = [](GLFWwindow*, int, int, int) -> auto {};
	_keyCallback = [activity = &this->_activity](GLFWwindow*, int key, int, int, int) -> auto {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(activity->ref, GL_TRUE);
		}
	};

	glfwMakeContextCurrent(_activity.ref);
	glfwSetWindowUserPointer(_activity.ref, this);

	if (glewInit() != GLEW_OK) {
		throw std::exception("glewInit failed!");
	}
	else {
		debug(glGetString(GL_VERSION));
	}
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // TODO: move
	
	glViewport(0, 0, _activity.width, _activity.height);

	_mainLoop();
}


AbstractEngine::~AbstractEngine()
{
	glfwTerminate();
}


void AbstractEngine::_staticWindowSizeCallback(GLFWwindow * window, int width, int height)
{
	AbstractEngine *context = static_cast<AbstractEngine*>(glfwGetWindowUserPointer(window));
	context->_windowSizeCallback(window, width, height);
}

void AbstractEngine::_staticKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	AbstractEngine *context = static_cast<AbstractEngine*>(glfwGetWindowUserPointer(window));
	context->_keyCallback(window, key, scancode, action, mods);
}

void AbstractEngine::_staticMouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	AbstractEngine *context = static_cast<AbstractEngine*>(glfwGetWindowUserPointer(window));
	context->_mouseButtonCallback(window, button, action, mods);
}

void AbstractEngine::_mainLoop()
{
	while (!glfwWindowShouldClose(_activity.ref))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		_draw();
		glfwSwapBuffers(_activity.ref);
		glfwPollEvents();
	}
}
void AbstractEngine::_setSizeCallback(decltype(_windowSizeCallback) callback)
{
	_windowSizeCallback = callback;
}
void AbstractEngine::_setKeyCallback(decltype(_keyCallback) callback)
{
	_keyCallback = callback;
}

void AbstractEngine::_setMouseButtonCallback(decltype(_mouseButtonCallback) callback)
{
	_mouseButtonCallback = callback;
}

/*
void AbstractEngine::_keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	debug("unhandled: " << (char)key);
}*/
/*
void AbstractEngine::_windowSizeCallback(GLFWwindow * window, int width, int height)
{
	debug("unhandled: " << width << 'x' << height);
}*/
/*
void AbstractEngine::_mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
#ifdef DEBUG
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	debug("unhandled click (" << x << "; " << y << ')');
#endif
}*/
/*
void AbstractEngine::_staticWindowSizeCallback(GLFWwindow * window, int width, int height)
{
	AbstractEngine *context = static_cast<AbstractEngine*>(glfwGetWindowUserPointer(window));
	context->_windowSizeCallback(window, width, height);
}

void AbstractEngine::_staticKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	AbstractEngine *context = static_cast<AbstractEngine*>(glfwGetWindowUserPointer(window));
	context->_keyCallback(window, key, scancode, action, mods);
}
void AbstractEngine::_staticMouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	AbstractEngine *context = static_cast<AbstractEngine*>(glfwGetWindowUserPointer(window));
	context->_mouseButtonCallback(window, button, action, mods);
}
*/


