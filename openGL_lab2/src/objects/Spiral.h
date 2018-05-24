#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Object.h"
#include <future>
#include <tuple>
#include <string>
#include <utils/kupihleba.h>
#include <utils/Structures.h>

namespace obj {
	class Spiral : public Object
	{
	public:
		//using obj::Object::Object;
		Spiral(GLuint shader);
		Spiral(std::shared_ptr<Shader> shader);
		
		virtual void _draw() override;
		void reconstruct(int precision);
		int getBuildPrecision();

		virtual string toString() const override;

		~Spiral();

	private:

		std::vector<float> _vertices;

		GLuint _VBufObj;

		int _precision;

		void _build(int precision, float r, float R, float len);

		void pushBack(Point3D point);
		void pushNormal(const Point3D & a, const Point3D & b, const Point3D & c);

		//std::function<std::tuple<float, float, float>(float, float)> _f;
	};
}

