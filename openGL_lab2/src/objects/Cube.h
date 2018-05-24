#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"
#include <utils/kupihleba.h>

namespace obj {

	class Cube : public Object
	{
	public:
		Cube(GLuint shader);
		~Cube();

		virtual void _draw() override;

		virtual string toString() const override;

	private:

		const string name = "Cube";

		GLuint _VBufObj;
		// GLuint _VArrObj;
	};

}

