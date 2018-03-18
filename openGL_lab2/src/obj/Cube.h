#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"

#define use(ns) using ns;
use(std::vector)

namespace obj {

	class Cube : public Object
	{
	public:
		Cube(GLuint shader);
		~Cube();

		void draw();

	private:
		GLuint _VBufObj;
		// GLuint _VArrObj;

		GLuint _shader;
	};

}

