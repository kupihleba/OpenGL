#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#define use(ns) using ns;
use(std::vector)

namespace obj {

	class Cube
	{
	public:
		Cube(GLuint shader);
		~Cube();
		void draw();

		void setView(GLint view);
		void setSize(float k);
		float getSize();

	private:
		GLuint _VBufObj;
		GLuint _VArrObj;

		GLuint _shader;
		
		float _size;
		GLint _view;
	};

}

