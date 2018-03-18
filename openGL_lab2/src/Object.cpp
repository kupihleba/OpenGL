#include "Object.h"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace obj;

glm::mat4 Object::_screen_transf(1.0f);

Object::Object()
{
	setSize(1.0f);
	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	clsTransformation();
}

Object::~Object()
{
}

void Object::setSize(float k)
{
	_size_koefficient = k;
	_size = glm::scale(glm::vec3(k, k, k));
}

float Object::getSize()
{
	return _size_koefficient;
}

std::tuple<float, float, float> obj::Object::getRotation()
{
	return std::tuple<float, float, float>(_x_angle, _y_angle, _z_angle);
}

void obj::Object::setPosition(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_position = glm::transpose(glm::translate(glm::vec3(_x, _y, _z)));
	//_translation = glm::translate(glm::vec3(_x, _y, _z));
}

void obj::Object::setXpos(float x_pos)
{
	setPosition(x_pos, _y, _z);
}

void obj::Object::setYpos(float y_pos)
{
	setPosition(_x, y_pos, _z);
}

void obj::Object::setZpos(float z_pos)
{
	setPosition(_x, _y, z_pos);
}

std::tuple<float, float, float> obj::Object::getPosition()
{
	return std::tuple<float, float, float>(_x, _y, _z);
}

void obj::Object::setScreenDims(int width, int height)
{
	if (width < height) {
		_screen_transf = glm::scale(glm::vec3(1.0f, (float)width / (float)height, 1.0f));
	}
	else {
		_screen_transf = glm::scale(glm::vec3((float)height / (float)width, 1.0f, 1.0f));
	}
}

void obj::Object::clsScreenDims()
{
	_screen_transf = glm::mat4(1.0f);
}

void Object::setRotation(float x_angle, float y_angle, float z_angle)
{
	_x_angle = x_angle;
	_y_angle = y_angle;
	_z_angle = z_angle;
	_rotation = glm::eulerAngleYXZ(_x_angle, _y_angle, _z_angle);
}

void obj::Object::setXangle(float x_angle)
{
	setRotation(x_angle, _y_angle, _z_angle);
}

void obj::Object::setYangle(float y_angle)
{
	setRotation(_x_angle, y_angle, _z_angle);
}

void obj::Object::setZangle(float z_angle)
{
	setRotation(_x_angle, _y_angle, z_angle);
}

void obj::Object::setTransformation(glm::mat4 m)
{
	_custom_transformation = m;
}

void obj::Object::clsTransformation()
{
	_custom_transformation = glm::mat4(1.0f);
}

void obj::Object::draw()
{
	throw std::exception("Method draw was not defined!");
}

glm::mat4 obj::Object::_getTransformations()
{	
	return  _rotation * _size * _custom_transformation * _position * _screen_transf; // The order is from left to right!
}
