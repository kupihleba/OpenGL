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
		Cube();
		~Cube();
		void draw();

	private:
		GLuint _buffer;
	};

}

