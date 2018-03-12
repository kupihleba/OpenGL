#pragma once
#include <glm/glm.hpp>
#include <tuple>

namespace obj {
	class Object
	{
	public:
		Object();

		virtual ~Object();

		void setSize(float k);
		float getSize();

		std::tuple<float, float, float> getRotation();
		void setRotation(float x_angle, float y_angle, float z_angle);
		void setXangle(float x_angle);
		void setYangle(float y_angle);
		void setZangle(float z_angle);

		virtual void draw();

	protected:
		float _size_koefficient;
		glm::mat4x4 _size;

		float _x_angle, _y_angle, _z_angle;
		glm::mat4 _rotation;
	};
}