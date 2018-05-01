//#define Lab4_1

/// Sorry, no time to write it pretty & cool :(

#ifdef Lab4_1
#include <stdio.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <cstdlib>
#include <cmath>

const int N = 3;

using std::vector;

typedef struct _Point {
	GLint x;
	GLint y;
} Point;
Point lastPoint;

GLfloat *buff;
vector <Point> points;

bool filterFlag = false;

int height = 640;
int width = 720;

void clsBuf() {
	std::fill_n(buff, height * width * N, 1);
}

void init() {
	buff = new GLfloat[width * height * N];
	glViewport(0, 0, width, height);

	clsBuf();
}

int sign(int x) {
	return (x == 0) ? 0 : x / abs(x);
}

int id(int x, int y, int c) {
	return (x + y * width) * N + c;
}

void fillZero(int x, int y) {
	for (int c = 0; c < N; c++) {
		buff[id(x, y, c)] = 0;
	}
}

int mul(int x, int y) {
	float res = 1.0f;
	for (int c = 0; c < N; c++) {
		res *= buff[id(x, y, c)];
	}
	return static_cast<int>(res);
}

void drawLine(const Point &pA, const Point &pB) {

	bool flag = false;

	int x = pA.x,
		y = pA.y;

	int dx = abs(pB.x - pA.x),
		dy = abs(pB.y - pA.y);

	int sX = sign(pB.x - pA.x),
		sY = sign(pB.y - pA.y);

	if (dy > dx) {
		flag = true;
		std::swap(dx, dy);
	}

	int k = 2 * dy - dx;

	for (int i = 0; i < dx; i++)
	{
		fillZero(x, y);

		if (k >= 0) {
			if (flag) {
				x += sX;
			}
			else {
				y += sY;
			}
			k -= 2 * dx;
			fillZero(x, y);
		}

		if (flag) {
			y += sY;
		}
		else {
			x += sX;
		}

		k += 2 * dy;
	}

}

/*
* Kind of magic here
*/
void filterFrame() {
	const int kernel[] = { 0, 1, 0, 1, 2, 1, 0, 1, 0 };
	//const int kernel[] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
	const double norm = 6;

	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {
			float c = 0;

			for (int i = x - 1; i <= x + 1; i++) {
				for (int k = y - 1; k <= y + 1; k++) {
					c += kernel[(i - x + 1) * N - y + 1 + k] * buff[id(i, k, 0)];
				}
			}

			for (int i = 0; i < N; i++) {
				buff[id(x, y, i)] = c / norm;
			}
		}
	}
}

void draw(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT);

	clsBuf();

	if (!points.empty()) {
		for (int i = 0; i < points.size(); i++)
			drawLine(points[i], points[(i + 1) % points.size()]);
	}

	if (filterFlag) {
		filterFrame();
	}

	glDrawPixels(width, height, GL_RGB, GL_FLOAT, (void*)buff);
	glfwSwapBuffers(window);
}

void resizeCallback(GLFWwindow * window, int w, int h) {
	height = h;
	width = w;

	delete[] buff;

	points.clear();

	filterFlag = false;

	buff = new GLfloat[width * height * N];

	clsBuf();

	glViewport(0, 0, width, height);
}

void keyboardHandler(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {

		case GLFW_KEY_F:
			filterFlag = !filterFlag;
			break;

		case GLFW_KEY_DELETE:
			points.clear();
			filterFlag = false;
			clsBuf();
			break;

		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		}
	}
}

void mouseHandler(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			clsBuf();
			Point tmp{
				static_cast<int>(x),
				static_cast<int>(height - y)
			};
			points.push_back(tmp);
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			lastPoint.x = static_cast<int>(x);
			lastPoint.y = static_cast<int>(height - y);
		}
	}
}

void mainLoop(GLFWwindow *window) {
	while (!glfwWindowShouldClose(window)) {
		draw(window);
		glfwPollEvents();
	}
}

void setCallbacks(GLFWwindow *window) {
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyboardHandler);
	glfwSetMouseButtonCallback(window, mouseHandler);
	glfwSetWindowSizeCallback(window, resizeCallback);
}


int main() {

	if (!glfwInit()) {
		return EXIT_FAILURE;
	}
	GLFWwindow *window = glfwCreateWindow(width, height, "Kupihleba lab 4", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return EXIT_FAILURE;
	}

	setCallbacks(window);
	init();

	mainLoop(window);

	glfwDestroyWindow(window);
	glfwTerminate();

	delete[] buff;

	return EXIT_SUCCESS;
}
#endif

/* Kind of code */
#ifdef Lab4_2
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::min;
using std::max;
#define uint unsigned int

const double EPSILON = 1e-6;

double rotate_y = 0,
rotate_x = 0,
rotate_z = 0,
scale = 1;

char mode = 0;
int width = 700,
height = 700;

vector<uint> myData;
uint verticesCount = 0;
uint color = 0;


struct Edge {
	int x0, y0, x1, y1;
	int x_cross;
	double tg;
	Edge(int x0, int y0, int x1, int y1) : x0(x0), y0(y0), x1(x1), y1(y1) {}

	bool operator == (const Edge &edge) const {
		return x0 == edge.x0 && x1 == edge.x1 && y0 == edge.y0 &&
			y1 == edge.y1 && x_cross == edge.x_cross && tg == edge.tg;
	}
};

struct Vertex {
	int x, y;
	vector<Edge> incidentEdges;
	Vertex(int x, int y) : x(x), y(y) {}

	bool operator < (const Vertex &point) const {
		return this->y < point.y;
	}
};

vector<Vertex> vertices;
vector<Edge> edges;

void bufferCallback(GLFWwindow *window, int a, int b) {
	//int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	vertices.clear();
	edges.clear();
	int broadness = width < height ? width : height;
	glViewport(0, 0, width, height);
	myData.clear();
	myData.resize(width*height);
}


void drawEdges(GLFWwindow *window) {
	glfwGetFramebufferSize(window, &width, &height);

	vector<Edge> activeEdges;
	vector<Vertex> sortedVertices = vertices;
	sort(sortedVertices.begin(), sortedVertices.end());
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			myData[(height - i - 1) * height + j] = 0;
		}
	}
	for (int i = 0; i < verticesCount; i++) {
		myData[(height - sortedVertices[i].y - 1)*height + sortedVertices[i].x] = color;
		if (i < verticesCount - 1) {
			for (int j = 0; j < sortedVertices[i].incidentEdges.size(); j++) {
				Edge &e = sortedVertices[i].incidentEdges[j];
				auto f = find(activeEdges.begin(), activeEdges.end(), e);
				if (f != activeEdges.end()) {
					activeEdges.erase(f);
				}
				else {
					if (abs(e.tg) < EPSILON) {
						for (int w = min(e.x0, e.x1); w <= max(e.x0, e.x1); w++) {
							myData[(height - sortedVertices[i].y - 1) * height + w] = color;
						}
					}
					else {
						activeEdges.push_back(e);
					}
				}
			}
			int y_cur = sortedVertices[i].y;
			while (y_cur < sortedVertices[i + 1].y) {
				vector<int> xs;
				for (int j = 0; j < activeEdges.size(); j++) {
					int y_start = min(activeEdges[j].y0, activeEdges[j].y1);
					int cur_x_cross = activeEdges[j].x_cross - abs(y_cur - y_start)*1.0 / activeEdges[j].tg;
					xs.push_back(cur_x_cross);
				}
				if (xs.size() % 2 == 1) xs.pop_back();
				sort(xs.begin(), xs.end());
				for (int j = 0; j < xs.size(); j += 2) {
					for (int k = xs[j]; k <= xs[j + 1]; k++) {
						myData[(height - y_cur - 1)*height + k] = color;
					}
				}
				y_cur++;
			}
		}
	}
}


void drawUnfilled(GLFWwindow *window) {
	glfwGetFramebufferSize(window, &width, &height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			myData[(height - i - 1)*height + j] = 0;
		}
	}
	for (int i = 0; i < edges.size(); i++) {
		int x0 = edges[i].x0, y0 = edges[i].y0, x1 = edges[i].x1, y1 = edges[i].y1;
		int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
		int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
		int err = dx + dy, e2;

		while (true) {
			myData[(height - y0 - 1)*height + x0] = color;
			if (x0 == x1 && y0 == y1) {
				break;
			}
			e2 = 2 * err;
			if (e2 >= dy) {
				err += dy;
				x0 += sx;
			}
			if (e2 <= dx) {
				err += dx;
				y0 += sy;
			}
		}
	}
}

void addVertex(int x, int y, GLFWwindow* window) {
	for (int i = 0; i < verticesCount; i++) {
		if (vertices[i].x == x && vertices[i].y == y) {
			return;
		}
	}
	verticesCount++;
	vertices.push_back(Vertex(x, y));

	if (verticesCount > 1) {
		if (edges.size() > 0) {
			edges.pop_back();
		}
		if (vertices[verticesCount - 2].incidentEdges.size()) {
			vertices[verticesCount - 2].incidentEdges.pop_back();
		}
		if (vertices[0].incidentEdges.size()) {
			vertices[0].incidentEdges.pop_back();
		}

		int x0 = vertices[verticesCount - 2].x, y0 = vertices[verticesCount - 2].y;
		int x1 = vertices[verticesCount - 1].x, y1 = vertices[verticesCount - 1].y;
		Edge tmp = Edge(x0, y0, x1, y1);
		int dx = tmp.x1 - tmp.x0;
		int dy = (height - tmp.y1) - (height - tmp.y0);
		double k = double(dy) / dx;
		tmp.tg = k;
		tmp.x_cross = y0 <= y1 ? x0 : x1;
		edges.push_back(tmp);

		vertices[verticesCount - 2].incidentEdges.push_back(tmp);
		vertices[verticesCount - 1].incidentEdges.push_back(tmp);
		x0 = vertices[verticesCount - 1].x;
		y0 = vertices[verticesCount - 1].y;
		x1 = vertices[0].x;
		y1 = vertices[0].y;
		Edge e_cyclic(x0, y0, x1, y1);
		dx = e_cyclic.x1 - e_cyclic.x0;
		dy = (height - e_cyclic.y1) - (height - e_cyclic.y0);
		k = double(dy) / dx;
		e_cyclic.tg = k;
		e_cyclic.x_cross = y0 <= y1 ? x0 : x1;
		edges.push_back(e_cyclic);
		vertices[verticesCount - 1].incidentEdges.push_back(e_cyclic);
		vertices[0].incidentEdges.push_back(e_cyclic);
	}
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		addVertex(static_cast<int>(x), static_cast<int>(y), window);
		mode ? drawEdges(window) : drawUnfilled(window);
	}
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_F:
			mode = !mode;
			if (mode) {
				drawEdges(window);
			}
			else {
				drawUnfilled(window);
			}
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		}
	}
}

int main() {
	color = -1;

	myData.resize(width*height);
	GLFWwindow* window;

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, "Kupihleba Lab4", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, bufferCallback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, myData.data());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
#endif