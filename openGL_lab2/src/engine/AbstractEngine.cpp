#include "AbstractEngine.h"

AbstractEngine::AbstractEngine()
{
	if (!glfwInit()) {
		throw std::exception("Glew could not be initialized!");
	}

	_activity.setFullscreen();
	//_activity.ref = glfwCreateWindow(_activity.width, _activity.height, "Kupihleba project", glfwGetPrimaryMonitor(), NULL);
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
		prt(glGetString(GL_VERSION));
	}
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f); // TODO: move
	
	glViewport(0, 0, _activity.width, _activity.height);
	glOrtho(0.0f, _activity.width, 0.0f, _activity.height, 0.0f, 1.0f);

	//_mainLoop();
}


AbstractEngine::~AbstractEngine()
{
	glfwDestroyWindow(_activity.ref);
}

void AbstractEngine::start()
{
	_run();
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

void AbstractEngine::setupMonitor()
{
	GLFWmonitor * monitor = glfwGetPrimaryMonitor();
	glfwGetMonitorPhysicalSize(monitor, &_activity.width, &_activity.height);
}

std::function <void(GLFWwindow* window, int key, int scancode, int action, int mods)> AbstractEngine::_getKeyCallback()
{
	return _keyCallback;
}

void AbstractEngine::_run()
{
	double lastTime = glfwGetTime();
	uint framesCounter = 0;
	while (!glfwWindowShouldClose(_activity.ref))
	{
		//glfwMakeContextCurrent(_activity.ref);
		//glClear(GL_COLOR_BUFFER_BIT);
		_draw();
		//glfwSwapBuffers(_activity.ref);
		glfwPollEvents();
		framesCounter++;
		double currentTime = glfwGetTime();
		if (double delta = currentTime - lastTime >= 1.0) {
			cout << "FPS " << framesCounter / delta << endl;
			lastTime = glfwGetTime();
			framesCounter = 0;
		}
	}
	this->~AbstractEngine();
}
void AbstractEngine::_draw()
{
	_scene.draw();
}
void AbstractEngine::_setWindowSizeCallback(decltype(_windowSizeCallback) callback)
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

void AbstractEngine::Activity::setFullscreen()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	width = mode->width;
	height = mode->height;
}
