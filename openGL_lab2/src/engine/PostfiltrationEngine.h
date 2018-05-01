#pragma once
#include <engine/AbstractEngine.h>
#include <vector>

#define use(ns) using ns;
use(std::vector)

class PostfiltrationEngine : public AbstractEngine
{
public:
	PostfiltrationEngine();
	~PostfiltrationEngine();
private:
	struct Edge {
		int x0, y0, x1, y1;
		int x_cross; //x-координата пересечения строк
		double tg;
		Edge(int x0, int y0, int x1, int y1) : x0(x0), y0(y0), x1(x1), y1(y1) {}

		bool operator == (const Edge &edge) const {
			return this->x0 == edge.x0 && 
				   this->x1 == edge.x1 && 
				   this->y0 == edge.y0 && 
				   this->y1 == edge.y1 && 
				   this->x_cross == edge.x_cross && 
				   this->tg == edge.tg;
		}
	};

	struct Vertex {
		int x, y;
		vector<Edge> incident_edges;
		Vertex(int x, int y) : x(x), y(y) {}

		bool operator < (const Vertex &point) const {
			return this->y < point.y;
		}
	};
	vector<Vertex> vertices;
	vector<Edge> edges;

	const double EPS = 1e-5;

	double rotate_y = 0, rotate_x = 0, rotate_z = 0, scale = 1, a, b, c, a1 = 1, b1 = 1;
	char mode = 0;
	int width = 700, height = 700;
	unsigned int* myData;
	unsigned int amount_of_vertices = 0;

	unsigned int color = 0;

	virtual void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	virtual void _mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void setCallbacks();

	void draw_edges();
	void draw_without_filling();
	void add_vertex(int x, int y);
};

