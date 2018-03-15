#include "Object.h"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace obj;

Object::Object()
{
	setSize(1.0f);
	setTranslation(0.0f, 0.0f, 0.0f);
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

void obj::Object::setTranslation(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_translation = glm::transpose(glm::translate(glm::vec3(_x, _y, _z)));
	//_translation = glm::translate(glm::vec3(_x, _y, _z));
	/*for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			std::cout << _translation[j][i] << ' ';
		}
		std::cout << std::endl;
	}*/

#if 0
	float norm[] = {
		1.0f,   0.0f,    0.0f,   0.0f,
		0.0f,   1.0f,    0.0f,   0.8f,
		0.0f,   0.0f,    1.0f,   0.1f,
		0.0f,   0.0f,    0.0f,   1.0f,
	};

	_translation = glm::make_mat4(norm);
#endif
	//_translation = glm::translate(glm::vec3(_x, _y, _z));
	
}

void obj::Object::setXpos(float x_pos)
{
	setTranslation(x_pos, _y, _z);
}

void obj::Object::setYpos(float y_pos)
{
	setTranslation(_x, y_pos, _z);
}

void obj::Object::setZpos(float z_pos)
{
	setTranslation(_x, _y, z_pos);
}

std::tuple<float, float, float> obj::Object::getTranslation()
{
	return std::tuple<float, float, float>(_x, _y, _z);
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
	//glm::vec4 position = glm::vec4(glm::vec3(_x, _y, _z), 1.0f);
	
	return  _translation /** _custom_transformation * _rotation * _size*/;
}
