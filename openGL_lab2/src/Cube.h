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

		void setView(GLint view);

		// TODO: REMOVE MULTIPLE METHODS!
#if 0
		void draw();
		void Cube::customDraw();
		void Cube::projDraw();
#endif

		void simpleDraw();

	private:
		GLuint _VBufObj;
		GLuint _VArrObj;

		GLuint _shader;

		GLint _view;
	};

}

