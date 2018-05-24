#include "ShaderFactory.h"
#include <iostream>
#include <sstream>
#include <fstream>

ShaderFactory::ShaderFactory() 
{
	_basicShader = 0;
}

ShaderFactory::~ShaderFactory() {}

GLuint ShaderFactory::_createShader(string && vertexShader, string && fragmentShader)
{
	GLuint prog = glCreateProgram();
	GLuint vs = _compileShader(GL_VERTEX_SHADER, std::move(vertexShader));
	GLuint fs = _compileShader(GL_FRAGMENT_SHADER, std::move(fragmentShader));

	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return prog;
}

GLuint ShaderFactory::_compileShader(GLuint type, const string & src)
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
		cout << "Failed to compile the ";
		switch (type)
		{
		case GL_VERTEX_SHADER:
			cout << "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			cout << "fragment";
			break;
		default:
			cout << "unknown";
		}
		cout << "shader" << endl;
		cout << msg << endl;
		return 0;
	}

	return id;
}

GLuint ShaderFactory::loadShader(string && path)
{
	enum Type {
		UNDEF, VERTEX, FRAGMENT
	};
	Type mode = UNDEF;
	std::stringstream vertexCode, fragmentCode;

	std::ifstream stream(std::move(path));

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

GLuint ShaderFactory::getBasicShader()
{
	if (!_basicShader) {
		_basicShader = loadShader("res/shaders/factory/basic.shader");
	}
	return _basicShader;
}

std::shared_ptr<Shader> ShaderFactory::getSuperShader()
{
	return std::shared_ptr<Shader>(new Shader(loadShader("res/shaders/factory/basic.shader")));
}
