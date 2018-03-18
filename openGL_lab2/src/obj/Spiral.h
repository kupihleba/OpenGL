#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Object.h"
#include <future>
#include <tuple>

namespace obj {
	class Spiral : public Object
	{
	public:
		Spiral(GLuint shader);
		
		void draw();
		void reconstruct(int precision);

		~Spiral();

	private:
		typedef std::tuple<float, float, float> Coords;
		
		std::vector<float> _vertices;
		GLuint _VBufObj;

		void _build(int precision, float r, float R, float len);

		GLuint _shader;

		std::function<std::tuple<float, float, float>(float, float)> _f;
	};
}

