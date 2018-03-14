#pragma once
#include <glm/glm.hpp>
#include <tuple>

namespace obj {

	/*
		Abstract object class
		Contains basic tranformations
	*/
	class Object
	{
	public:
		Object();
		virtual ~Object();

		/// <summary>
		/// Sets the scale koefficient
		/// </summary>
		void setSize(float k);

		/// <returns>
		/// The scale koefficient
		/// </returns>
		float getSize();

		/// <returns>
		/// Tuple of angles between Ox, Oy, Oz
		/// </returns>
		std::tuple<float, float, float> getRotation();

		/// <summary>
		/// Set the angles with Ox, Oy, Oz for rotation matrix
		/// </summary>
		void setRotation(float x_angle, float y_angle, float z_angle);
		void setXangle(float x_angle);
		void setYangle(float y_angle);
		void setZangle(float z_angle);


		/// <summary>
		/// Set custom transformation of object
		/// </summary>
		void setTransrmation(glm::mat4 m);
		void clsTransformation();

		/// <summary>
		/// Main draw method
		/// </summary>
		virtual void draw();

	protected:
		float _size_koefficient;
		glm::mat4 _size;
		glm::mat4 _custom_transformation;

		float _x_angle, _y_angle, _z_angle;
		glm::mat4 _rotation;

		glm::mat4 _getTransformations();
	};
}