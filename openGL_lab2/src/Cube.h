#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
		virtual void draw();

		void setView(GLint view);
		void Cube::customDraw();
		void Cube::projDraw();

	private:
		GLuint _VBufObj;
		GLuint _VArrObj;

		GLuint _shader;

		GLint _view;
	};

}

