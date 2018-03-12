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
		void setRotation(float x_angle, float y_angle, float z_angle);
		std::tuple<float, float, float> getAngles();
		void setXangle(float x_angle);
		void setYangle(float y_angle);
		void setZangle(float z_angle);

	private:
		GLuint _VBufObj;
		GLuint _VArrObj;

		GLuint _shader;
		
		float _size;
		float _xAngle;
		float _yAngle;
		float _zAngle;

		GLint _view;
	};

}

