#include "PostfiltrationEngine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <utils/Structures.h>
#include <utils/Algorithm.h>

using std::min;
using std::max;

PostfiltrationEngine::PostfiltrationEngine()
	//:AbstractEngine(nullptr)
{
	Point::width = _activity.width;
	Point::floatsInVertex = floatsInVertex;
	_buffer.resize(_activity.width * _activity.height * floatsInVertex);
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

void PostfiltrationEngine::colorPointDESTRUCTIVE(const Point & p, const RGB & color)
{
	_colorPointDESTRUCTIVE(_buffer, p, color);
}


void PostfiltrationEngine::_drawLineDESTRUCTIVE(vector<RGB>& buffer, const Point & pointA, const Point & pointB)
{
	bool flag = false;

	Point activePoint(pointA);

	int dx = abs(pointB.x - pointA.x),
		dy = abs(pointB.y - pointA.y);

	int stepX = algorithm::sign(pointB.x - pointA.x),
		stepY = algorithm::sign(pointB.y - pointA.y);

	if (dy > dx) {
		flag = true;
		std::swap(dx, dy);
	}

	int k = 2 * dy - dx;

	for (int i = 0; i < dx; i++)
	{
		_colorPointDESTRUCTIVE(buffer, activePoint, RGB{ 0, 0, 0 });

		if (k >= 0) {
			if (flag) {
				activePoint.x += stepX;
			}
			else {
				activePoint.y += stepY;
			}
			k -= 2 * dx;
			_colorPointDESTRUCTIVE(buffer, activePoint, RGB{ 0, 0, 0 });
		}

		if (flag) {
			activePoint.y += stepY;
		}
		else {
			activePoint.x += stepX;
		}

		k += 2 * dy;
	}
}

void PostfiltrationEngine::_colorPointDESTRUCTIVE(vector<RGB>& buffer, const Point & p, const RGB & color)
{
	buffer[p.calcOffset()] = color;
}


void PostfiltrationEngine::drawLineDESTRUCTIVE(const Point & pointA, const Point & pointB)
{
	_drawLineDESTRUCTIVE(_buffer, pointA, pointB);
}