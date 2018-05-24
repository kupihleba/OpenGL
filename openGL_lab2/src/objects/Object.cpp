#include "Object.h"

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace obj;

glm::mat4 Object::_screen_transf(1.0f);

obj::Object::Object(GLint shader)
	:_newShader(nullptr)
{
	setSize(1.0f);
	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	clsTransformation();
	_view = GL_LINE;

	_shader = shader;
}

obj::Object::Object(std::shared_ptr<Shader> shader)
	:_newShader(shader) {
	setSize(1.0f);
	setPosition(0.0f, 0.0f, 0.0f);
	setRotation(0.0f, 0.0f, 0.0f);
	clsTransformation();
	_view = GL_LINE;
}

Object::~Object() {}

Object & Object::setSize(float k) {
	_size_koefficient = k;
	_size = glm::scale(glm::vec3(k, k, k));
	return *this;
	return *this;
}

float Object::getSize() {
	return _size_koefficient;
}

std::tuple<float, float, float> obj::Object::getRotation() {
	return std::tuple<float, float, float>(_x_angle, _y_angle, _z_angle);
}

Object & obj::Object::setPosition(float x, float y, float z) {
	_x = x;
	_y = y;
	_z = z;
	_position = glm::transpose(glm::translate(glm::vec3(_x, _y, _z)));
	//_translation = glm::translate(glm::vec3(_x, _y, _z));
	return *this;
}

Object & obj::Object::setXpos(float x_pos) {
	setPosition(x_pos, _y, _z);
	return *this;
}

Object & obj::Object::setYpos(float y_pos) {
	setPosition(_x, y_pos, _z);
	return *this;
}

Object & obj::Object::setZpos(float z_pos) {
	setPosition(_x, _y, z_pos);
	return *this;
}

std::tuple<float, float, float> obj::Object::getPosition() {
	return std::tuple<float, float, float>(_x, _y, _z);
}

void obj::Object::setScreenDims(int width, int height) {
	if (width < height) {
		_screen_transf = glm::scale(glm::vec3(1.0f, (float)width / (float)height, 1.0f));
	}
	else {
		_screen_transf = glm::scale(glm::vec3((float)height / (float)width, 1.0f, 1.0f));
	}
}

void obj::Object::clsScreenDims() {
	_screen_transf = glm::mat4(1.0f);
}

Object & Object::setRotation(float x_angle, float y_angle, float z_angle) {
	_x_angle = x_angle;
	_y_angle = y_angle;
	_z_angle = z_angle;
	_rotation = glm::eulerAngleYXZ(_x_angle, _y_angle, _z_angle);
	return *this;
}

Object & obj::Object::setXangle(float x_angle) {
	setRotation(x_angle, _y_angle, _z_angle);
	return *this;
}

Object & obj::Object::setYangle(float y_angle) {
	setRotation(_x_angle, y_angle, _z_angle);
	return *this;
}

Object & obj::Object::setZangle(float z_angle) {
	setRotation(_x_angle, _y_angle, z_angle);
	return *this;
}

Object & obj::Object::setTransformation(glm::mat4 m) {
	_custom_transformation = m;
	return *this;
}

void obj::Object::clsTransformation() {
	_custom_transformation = glm::mat4(1.0f);
}

void obj::Object::draw() {
	if (_newShader.get() != nullptr) {
		_newShader->enable();
		_newShader->tranformation(_getTransformations());
		glPolygonMode(GL_FRONT_AND_BACK, _view);
		_draw();
		_newShader->disable();
	} else {
		glUseProgram(_shader);
		GLint myTranformation = glGetUniformLocation(_shader, "myTransformation");
		glUniformMatrix4fv(myTranformation, 1, GL_FALSE, glm::value_ptr(_getTransformations()));
		GLint myColor = glGetUniformLocation(_shader, "myColor");
		glUniform4f(myColor, 1.0f, 1.0f, 0.3f, 0.9f);

		_draw();
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
		glUseProgram(0);
	}
}

string obj::Object::toString() const {
	return "Object";
}

void obj::Object::setView(GLint view) {
	_view = view;	
}

GLint obj::Object::getView() const {
	return _view;
}

void obj::Object::_draw() {
	throw std::exception("Method _draw was not defined!");
}


glm::mat4 obj::Object::_getTransformations() {	
	return  _rotation * _size * _custom_transformation * _position * _screen_transf; // The order is from left to right!
}
