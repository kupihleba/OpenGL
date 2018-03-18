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
		Object & setSize(float k);

		/// <returns>
		/// The scale koefficient
		/// </returns>
		float getSize();


		/// <summary>
		/// Set the angles with Ox, Oy, Oz for rotation matrix
		/// </summary>
		Object & setRotation(float x_angle, float y_angle, float z_angle);
		Object & setXangle(float x_angle);
		Object & setYangle(float y_angle);
		Object & setZangle(float z_angle);

		/// <returns>
		/// Tuple of angles between Ox, Oy, Oz
		/// </returns>
		std::tuple<float, float, float> getRotation();

		/// <summary>
		/// Set the position of the object
		/// </summary>
		Object & setPosition(float x, float y, float z);
		Object & setXpos(float x_pos);
		Object & setYpos(float y_pos);
		Object & setZpos(float z_pos);

		/// <returns>
		/// Tuple of coordinates x, y, z
		/// </returns>
		std::tuple<float, float, float> getPosition();

		/// <summary>
		/// Set the transformation matrix, so that the absolute coordinates would form a square
		/// </summary>
		static void setScreenDims(int width, int height);
		static void clsScreenDims();

		/// <summary>
		/// Set custom transformation of object
		/// </summary>
		Object & setTransformation(glm::mat4 m);
		void clsTransformation();

		/// <summary>
		/// Main draw method
		/// </summary>
		virtual void draw();

	protected:

		// Screen transformation:
		static glm::mat4 _screen_transf;

		// Size:
		float _size_koefficient;
		glm::mat4 _size;

		// Position:
		float _x, _y, _z;
		glm::mat4 _position;

		// Rotation:
		float _x_angle, _y_angle, _z_angle;
		glm::mat4 _rotation;

		glm::mat4 _custom_transformation;

		glm::mat4 _getTransformations();
	};
}