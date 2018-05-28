#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Object.h"
#include <future>
#include <tuple>
#include <string>
#include "Drawable.h"
#include <utils/Structures.h>
#include <utils/kupihleba.h>

namespace obj {
	class Spiral: 
		public Drawable
	{
	public:
		Spiral(std::shared_ptr<Shader> shader);
		
		void reconstruct(int precision);
		int getBuildPrecision();

		virtual void _draw() override;
		virtual void _defineVao() override;

		virtual string toString() const override;

		~Spiral();

	private:
		
		int _precision;

		void _build(int precision, float r, float R, float len);

		void pushBack(Point3D point);
		void pushNormal(const Point3D & a, const Point3D & b, const Point3D & c);
	};
}

