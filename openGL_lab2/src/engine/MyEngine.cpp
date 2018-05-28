#include "MyEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <objects/Drawable.h>
#include <utils/kupihleba.h>

/*
 * Учет ослабления интенсивности света с расстоянием от источника;
 * 
 * Моделирование движения тела (с заданной начальной скоростью) 
 * при условии абсолютно упругого отражения объекта от границ
 * некоторого ограничивающего объема (регулярной формы);
 *
 * Использование текстуры для определения свойств
 * поверхности (модулирование коэффициента диффузного отражения);
 *
 */

MyEngine::MyEngine()
{
	_setKeyCallback(_keyCallback);
	_setWindowSizeCallback(_window_size_callback);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	obj::Object::setScreenDims(_activity.width, _activity.height);

	_initObjects();
	_mode = SPIRAL;
	_run();
}

void MyEngine::_initObjects()
{
	glEnable(GL_DEPTH_TEST);
	auto shader(_shaderFactory.getSuperShader());
	_shaders.push_back(shader);
	
	_cube = shared_ptr<obj::Cube>(new obj::Cube(shader));
	_miniCube = shared_ptr<obj::Cube>(new obj::Cube(_shaderFactory.getBasicShader()));
	_projCube = shared_ptr<obj::Cube>(new obj::Cube(_shaderFactory.getBasicShader()));

	_spiral = shared_ptr<obj::Spiral>(new obj::Spiral(shader));
	_projSpiral = shared_ptr<obj::Spiral>(new obj::Spiral(_shaderFactory.getBasicShader()));

	auto textureA = obj::Drawable::loadTexture("D:\\progi\\С++\\openGL_lab2\\openGL_lab2\\res\\textures\\abstract.bmp");
	auto textureB = obj::Drawable::loadTexture("D:\\progi\\С++\\openGL_lab2\\openGL_lab2\\res\\textures\\galaxy.bmp");

	_spiral->setTexture(textureA);
	_cube->setTexture(textureB);

	_spiral->setPosition(0.0f, -0.7f, 0.0f)
		.setSize(0.25f)
		.setYangle(0.5f);

	_cube->setXangle(0.5f)
		.setYangle(0.5f)
		.setXangle(0.5f)
		.setXangle(0.5f);

	_miniCube->setXangle(0.5f)
		.setYangle(0.5f)
		.setSize(0.2f)
		.setPosition(1.2f, -0.7f, 0.0f);

	_projCube->setXangle(0.5f)
		.setYangle(0.5f)
		.setSize(0.2f);

	float proj[] = {
		1.0f,   0.0f,  0.0f,  0.0f,
		0.0f,   1.0f,  0.0f,  0.0f,
		0.0f,   0.0f,  1.0f,  0.0f,
	   -0.9f,  -0.9f,  0.9f,  1.0f,
	};
	_projCube->setTransformation(glm::make_mat4(proj))
		.setPosition(-1.2f, -0.7f, 0.0f);

	_projSpiral->setPosition(-1.2f, -0.7f, 0.0f)
		.setSize(0.10f)
		.setYangle(0.5f)
		.setTransformation(glm::make_mat4(proj));
}

void MyEngine::_draw()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	_light = {
		_camera.position(),
		glm::vec3(1.0f, 1.0f, 1.0f) // white light
	};
	//for (auto & shader : _shaders) {
		_shaders[0]->enable()
			.camera(_camera.matrix())
			.light(_light.position, _light.intensities)
			.color(1.0f, 0.5f, 0.5f, 1.0f);
		//for ever;
	//}
	switch (_mode)
	{	
	case CUBE:
		_focus = std::dynamic_pointer_cast<obj::Drawable, obj::Cube>(_cube);
		_cube->draw();
		_projCube->draw();
		_miniCube->draw();
		break;
	case SPIRAL:
		_focus = std::dynamic_pointer_cast<obj::Drawable, obj::Spiral>(_spiral);
		_focus = _spiral;
		_spiral->draw();
		_projSpiral->draw();
		break;
	default:
		break;
	}	
	glfwSwapBuffers(_activity.ref);
}

void MyEngine::_keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	MyEngine *context = static_cast<MyEngine*>(glfwGetWindowUserPointer(window));
	const float POS_STEP = 0.1f;
	const float ROT_STEP = 0.05f;
	const float SIZE_STEP = 0.05f;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		if (context->_focus->getView() == GL_FILL) {
			context->_focus->setView(GL_LINE);
		} else {
			context->_focus->setView(GL_FILL);
		}
	}
	else {
		float x_angle, y_angle;
		float x, y, z;
		switch (key)
		{
		case GLFW_KEY_KP_ADD:
			context->_focus->setSize(context->_focus->getSize() + SIZE_STEP);
			break;
		case GLFW_KEY_KP_SUBTRACT:
			context->_focus->setSize(context->_focus->getSize() - SIZE_STEP);
			break;

		case GLFW_KEY_LEFT:
			x_angle = std::get<0>(context->_focus->getRotation());
			context->_focus->setXangle(x_angle - ROT_STEP);
			context->_projCube->setXangle(x_angle - ROT_STEP);
			context->_projSpiral->setXangle(x_angle - ROT_STEP);
			break;
		case GLFW_KEY_RIGHT:
			x_angle = std::get<0>(context->_focus->getRotation());
			context->_focus->setXangle(x_angle + ROT_STEP);
			context->_projCube->setXangle(x_angle + ROT_STEP);
			context->_projSpiral->setXangle(x_angle + ROT_STEP);
			break;

		case GLFW_KEY_UP:
			y_angle = std::get<1>(context->_focus->getRotation());
			context->_focus->setYangle(y_angle - ROT_STEP);
			context->_projCube->setYangle(y_angle - ROT_STEP);
			context->_projSpiral->setYangle(y_angle - ROT_STEP);
			break;

		case GLFW_KEY_DOWN:
			y_angle = std::get<1>(context->_focus->getRotation());
			context->_focus->setYangle(y_angle + ROT_STEP);
			context->_projCube->setYangle(y_angle + ROT_STEP);
			context->_projSpiral->setYangle(y_angle + ROT_STEP);
			break;

		case GLFW_KEY_W:
			y = std::get<1>(context->_focus->getPosition());
			context->_focus->setYpos(y + POS_STEP);
			break;
		case GLFW_KEY_S:
			y = std::get<1>(context->_focus->getPosition());
			context->_focus->setYpos(y - POS_STEP);
			break;

		case GLFW_KEY_A:
			x = std::get<0>(context->_focus->getPosition());
			context->_focus->setXpos(x - POS_STEP);
			break;
		case GLFW_KEY_D:
			x = std::get<0>(context->_focus->getPosition());
			context->_focus->setXpos(x + POS_STEP);
			break;

		case GLFW_KEY_Q:
			z = std::get<2>(context->_focus->getPosition());
			context->_focus->setZpos(z + POS_STEP);
			break;
		case GLFW_KEY_E:
			z = std::get<2>(context->_focus->getPosition());
			context->_focus->setZpos(z - POS_STEP);
			break;

		case GLFW_KEY_TAB:
			if (action == GLFW_PRESS) {
				if (context->_mode == CUBE) {
					context->_mode = SPIRAL;
				}
				else {
					context->_mode = CUBE;
				}
			}
			break;

		case GLFW_KEY_1:
			context->_spiral->reconstruct(10);
			break;
		case GLFW_KEY_2:
			context->_spiral->reconstruct(20);
			break;
		case GLFW_KEY_3:
			context->_spiral->reconstruct(30);
			break;
		case GLFW_KEY_4:
			context->_spiral->reconstruct(40);
			break;
		case GLFW_KEY_5:
			context->_spiral->reconstruct(50);
			break;
		case GLFW_KEY_6:
			context->_spiral->reconstruct(60);
			break;
		case GLFW_KEY_7:
			context->_spiral->reconstruct(70);
			break;
		case GLFW_KEY_8:
			context->_spiral->reconstruct(80);
			break;
		case GLFW_KEY_9:
			context->_spiral->reconstruct(90);
			break;
		default:
			break;
		}
	}
}

void MyEngine::_window_size_callback(GLFWwindow* window, int width, int height)
{
	MyEngine *context = static_cast<MyEngine*>(glfwGetWindowUserPointer(window));
	glViewport(0, 0, width, height);
	obj::Object::setScreenDims(width, height);
	context->_activity.height = height;
	context->_activity.width = width;
}