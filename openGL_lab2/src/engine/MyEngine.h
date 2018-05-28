#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <objects/Cube.h>
#include <objects/Spiral.h>
#include <ShaderFactory.h>
#include <memory>
#include <engine/AbstractEngine.h>
#include <utils/Structures.h>
#include <utils/kupihleba.h>

using std::shared_ptr;

class MyEngine : public AbstractEngine
{
public:
	MyEngine();

private:

	ObjectType _mode;
	vector<shared_ptr<Shader>> _shaders;
	Light _light;

	void _initObjects();
	virtual void _draw() override;

	ShaderFactory _shaderFactory;

	shared_ptr<obj::Drawable> _focus;

	shared_ptr<obj::Cube> _cube;
	shared_ptr<obj::Cube> _miniCube;
	shared_ptr<obj::Cube> _projCube;

	shared_ptr<obj::Spiral> _spiral;
	shared_ptr<obj::Spiral> _projSpiral;

	static void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void _window_size_callback(GLFWwindow* window, int width, int height);
};

