#include "PostfiltrationEngine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>

using std::min;
using std::max;

PostfiltrationEngine::PostfiltrationEngine()
	//:AbstractEngine(nullptr)
{
}


PostfiltrationEngine::~PostfiltrationEngine()
{
}

void PostfiltrationEngine::_keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_F:
			mode ^= 1;
			mode ? draw_edges() : draw_without_filling();
		default: break;
		}
	}
}

void PostfiltrationEngine::_mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		//cout << "Cursor Position at (" << xpos << " : " << ypos << ")" << endl;
		add_vertex((int)xpos, (int)ypos);
		mode ? draw_edges() : draw_without_filling();
	}
}

void PostfiltrationEngine::setCallbacks()
{

}

void PostfiltrationEngine::draw_edges()
{
	
}

void PostfiltrationEngine::draw_without_filling()
{
	
}

void PostfiltrationEngine::add_vertex(int x, int y)
{
	
}
