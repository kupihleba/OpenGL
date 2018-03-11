#include "MyEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define use(ns) using ns;
use(std::cout) use(std::endl)

MyEngine::MyEngine()
{
	if (!glfwInit())
		throw -1;

	_activity = glfwCreateWindow(_activityWidth, _activityHeight, "Hello World", NULL, NULL);
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
	_shader = _loadShader("res/shaders/basic.shader");
	glUseProgram(_shader);

	glViewport(0, 0, _activityWidth, _activityHeight);

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
	_cube = new obj::Cube(_shader);
#if 0
	float data[6] = {
	   -0.5f, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};
	glGenBuffers(1, &_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glBufferData(GL_ARRAY_BUFFER,  6 * sizeof(float), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
}

void MyEngine::_destroyObjects()
{
	delete _cube;
}

GLuint MyEngine::_createShader(string & vertexShader, string & fragmentShader)
{
	GLuint prog = glCreateProgram();
	GLuint vs = _compileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = _compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);

	return prog;
}

GLuint MyEngine::_compileShader(GLuint type, const string & src)
{
	GLuint id = glCreateShader(type);
	const char * ptr = src.c_str();
	glShaderSource(id, 1, &ptr, nullptr);
	glCompileShader(id);
	
	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE) {
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char *msg = (char*)alloca(len * sizeof(len));
		glGetShaderInfoLog(id, len, &len, msg);
		cout << "Failed to compile the " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << endl;
		cout << msg << endl;
		return 0;
	}

	return id;
}

GLuint MyEngine::_loadShader(const string & path)
{
	enum Type {
		UNDEF, VERTEX, FRAGMENT
	};
	Type mode = UNDEF;
	std::stringstream vertexCode, fragmentCode;

	std::ifstream stream(path);
	
	string line;
	while (getline(stream, line))
	{
		if (line.find("#vertex") != string::npos) {
			mode = VERTEX;
		}
		else if (line.find("#fragment") != string::npos) {
			mode = FRAGMENT;
		}
		else {
			switch (mode)
			{
			case VERTEX:
				vertexCode << line << endl;
					break;
			case FRAGMENT:
				fragmentCode << line << endl;
				break;
			default:
				break;
			}
		}
	}
	return _createShader(vertexCode.str(), fragmentCode.str());
}

void MyEngine::_draw()
{
	_cube->setView(_type);
	_cube->draw();
	//glDrawArrays(GL_TRIANGLES, 0, 3);
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
	switch (key)
	{
	case GLFW_KEY_KP_ADD:
		context->_cube->setSize(context->_cube->getSize() + 0.05);
		break;
	case GLFW_KEY_KP_SUBTRACT:
		context->_cube->setSize(context->_cube->getSize() - 0.05);
		break;
	default:
		break;
	}
}
