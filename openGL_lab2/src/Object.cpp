#include "Object.h"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace obj;

Object::Object()
{
	setSize(1.0f);
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

void Object::setRotation(float x_angle, float y_angle, float z_angle)
{
	_x_angle = x_angle;
	_y_angle = y_angle;
	_z_angle = z_angle;
	_rotation = glm::eulerAngleYXZ(_x_angle, _y_angle, _z_angle);
}

void obj::Object::setXangle(float x_angle)
{
	_x_angle = x_angle;
	setRotation(_x_angle, _y_angle, _z_angle);
}

void obj::Object::setYangle(float y_angle)
{
	_y_angle = y_angle;
	setRotation(_x_angle, _y_angle, _z_angle);
}

void obj::Object::setZangle(float z_angle)
{
	_z_angle = z_angle;
	setRotation(_x_angle, _y_angle, _z_angle);
}

void obj::Object::setTransrmation(glm::mat4 m)
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
	return _custom_transformation * _rotation * _size;
}
