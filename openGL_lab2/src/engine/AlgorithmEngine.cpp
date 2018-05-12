#include "AlgorithmEngine.h"

int AlgorithmEngine::Point::width = 0;
int AlgorithmEngine::Point::floatsInVertex = 0;

template <typename T> int sign(T val) {
	return (T(0) < val) - (val < T(0));
}

AlgorithmEngine::AlgorithmEngine()
{
	//_setWindowSizeCallback([](GLFWwindow*, int, int) -> void {});
	_setKeyCallback([&](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
		if (action == GLFW_PRESS) {
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
					glfwSetWindowShouldClose(_activity.ref, GL_TRUE);
					break;
			case GLFW_KEY_C:
				if (_currentHandler == CROP) {
					_currentHandler = POLY_DRAW;
				} else {
					_currentHandler = CROP;
				}
				break;
			case GLFW_KEY_ENTER:
				if (isClockwise()) {
					//goSutherlandHodgeman();
					vector<Line> lines(goSutherlandHodgeman());
					for (Line & l : lines) {
						_lines.push_back(LineRGB(l, RGB{ 1.0f, 0.0f, 0.0f }));
					}
				}
				else {
					std::reverse(_cropArea.begin(), _cropArea.end());
					//goSutherlandHodgeman();
					vector<Line> lines(goSutherlandHodgeman());
					for (Line & l : lines) {
						_lines.push_back(LineRGB(l, RGB{ 1.0f, 0.0f, 0.0f }));
					}
				}
				break;
			default:
				break;
			}
		}
	});
	_setMouseButtonCallback([&](GLFWwindow* window, int button, int action, int mods) -> void {
		if (action == GLFW_PRESS) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			Point p {
				static_cast<int>(x),
				static_cast<int>(_activity.height - y)
			};
			cout << p.toString() << endl;
			switch (_currentHandler) {
			case POLY_DRAW:
				_vertices.push_back(p);
				break;
			case CROP:
				_cropArea.push_back(p);
				break;
			default:
				throw std::exception("Unknown handler!");
			}
		}
	});

	AlgorithmEngine::Point::width = _activity.width;
	AlgorithmEngine::Point::floatsInVertex = floatsInVertex;
	
	_buffer.resize(_activity.width * _activity.height * floatsInVertex);
	//_tmpBuffer.resize(_activity.width * _activity.height * floatsInVertex);
	std::fill_n(_buffer.data(), _activity.height * _activity.width * floatsInVertex, RGB { 0.9f, 0.9f, 0.9f });
	//std::fill_n(_tmpBuffer.data(), _activity.height * _activity.width * floatsInVertex, RGB{ 1.0f, 1.0f, 1.0f });

	_run();
}

AlgorithmEngine::~AlgorithmEngine()
{
}


void AlgorithmEngine::_draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glDrawPixels(_activity.width, _activity.height, GL_RGB, GL_FLOAT, (void*)_buffer.data());
	_drawCropArea();
	_drawPolyArea();
	for (PolyRGB & i : _polygons) {
		drawPoly(i.first, i.second, 2.0f);
	}
	for (LineRGB & i : _lines) {
		drawLine(i.first, i.second, 2.0f);
	}
	glfwSwapBuffers(_activity.ref);
}

void AlgorithmEngine::colorPointDESTRUCTIVE(const Point & p, const RGB & color)
{
	_colorPointDESTRUCTIVE(_buffer, p, color);
}

int AlgorithmEngine::_checkSide(const Line & line, const Point & p) const
{
	return sign((line.end.x - line.beg.x) * (p.y - line.beg.y) -
		(line.end.y - line.beg.y) * (p.x - line.beg.x));
}

AlgorithmEngine::Point AlgorithmEngine::_intersection(const Line & a, const Line & b) const
{
https://www.geeksforgeeks.org/polygon-clipping-sutherland-hodgman-algorithm-please-change-bmp-images-jpeg-png/
	
	//typedef decltype (Line::beg.x) T;
	//T denominator;
	auto crossProductA = a.beg.x*a.end.y - a.beg.y*a.end.x;
	auto crossProductB = b.beg.x*b.end.y - b.beg.y*b.end.x;
	auto dxB = b.end.x - b.beg.x;
	auto dyB = b.end.y - b.beg.y;
	auto dxA = a.end.x - a.beg.x;
	auto dyA = a.end.y - a.beg.y;

	auto denominator = dxA * dyB - dyA * dxB;

	return Point {
		(dxA * crossProductB - crossProductA * dxB) /
						denominator,
		(dyA * crossProductB - crossProductA * dyB) /
						denominator
	};
}

void AlgorithmEngine::_drawCropArea()
{
	if (_cropArea.empty()) {
		return;
	}
	auto iter = _cropArea.begin();
	Point &start = *iter;
	if (iter == _cropArea.end()) {
		colorPointDESTRUCTIVE(start, RGB { 0.0f, 0.0f, 0.0f });
		return;
	}
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(1.0f);
	glBegin(GL_LINE_LOOP);
	for (iter; iter + 1 != _cropArea.end(); iter++) {
		Point &a = *iter;
		Point &b = *(iter + 1);
		glVertex2i(a.x, a.y);
		glVertex2i(b.x, b.y);
		//drawLine(*iter, *(iter + 1));
	}
	glEnd();

	//drawLine(*iter, start);
}

void AlgorithmEngine::_drawPolyArea()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1.0f);

	if (_vertices.size() == 1) {
		glBegin(GL_POINTS);
		const Point & p = _vertices.back();
		glVertex2i(p.x, p.y);
		glEnd();
	} else if (_vertices.size() > 1) {
		glBegin(GL_LINE_LOOP);
		for (const Point & p : _vertices) {
			glVertex2i(p.x, p.y);
		}
		glEnd();
	}
}

void AlgorithmEngine::_drawLineDESTRUCTIVE(vector<RGB>& buffer, const Point & pointA, const Point & pointB)
{
	bool flag = false;

	Point activePoint(pointA);

	int dx = abs(pointB.x - pointA.x),
		dy = abs(pointB.y - pointA.y);

	int stepX = sign(pointB.x - pointA.x),
		stepY = sign(pointB.y - pointA.y);

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

void AlgorithmEngine::_colorPointDESTRUCTIVE(vector<RGB>& buffer, const Point & p, const RGB & color)
{
	buffer[p.calcOffset()] = color;
}

void AlgorithmEngine::drawPoly(const vector<Point> & poly, RGB color, GLfloat lineWidth) const
{
	glColor3f(color.r, color.g, color.b);
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	for (const Point &p : poly) {
		glVertex2i(p.x, p.y);
	}
	glEnd();
}

void AlgorithmEngine::drawLine(const Line & line, RGB color, GLfloat lineWidth) const
{
	glColor3f(color.r, color.g, color.b);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	glVertex2i(line.beg.x, line.beg.y);
	glVertex2i(line.end.x, line.end.y);
	glEnd();
}

void AlgorithmEngine::drawLineDESTRUCTIVE(const Point & pointA, const Point & pointB)
{
	_drawLineDESTRUCTIVE(_buffer, pointA, pointB);
}

vector<AlgorithmEngine::Line> AlgorithmEngine::goSutherlandHodgeman()
{
	vector<Point> poly(_vertices);
	
	for (int i = 0; i < _cropArea.size(); i++) {
		int k = (i + 1) % _cropArea.size();
		poly = _clip(poly, Line {
			_cropArea[i],
			_cropArea[k]
		});
	}
	for (auto &i : poly) {
		_lines.push_back(LineRGB(Line{ i, Point{ i.x + 10, i.y + 10 } }, RGB{ 1.0f, 1.0f, 0 }));
	}


	vector<Line> results;
	
	vector<Line> skin; // skin contains all the vertices
	auto iterV(_vertices.begin());
	while (iterV + 1 != _vertices.end()) {
		skin.push_back(Line {
			*iterV,
			*(iterV + 1)
		});
		iterV++;
	}
	skin.push_back(Line { *iterV, *_vertices.begin() });
	
	auto iterPoly = poly.begin();
	while (iterPoly + 1 != poly.end()) {
		Line tmp = Line {
			*iterPoly,
			*(iterPoly + 1)
		};
		Point onLine = tmp.center();
		cout << onLine.toString() << endl;
		/*if (prt(isInside(onLine)) > 0) {
			results.push_back(tmp);
		}*/
		
		for (Line & l : skin) {
			if (prt(_checkSide(l, onLine)) > 0) {
				cout << "break " << onLine.toString() << endl;
				break;
			}
			results.push_back(tmp);
		}
		iterPoly++;
	}

	Line tmp = Line {
		*poly.begin(),
		*(iterPoly)
	};
	Point onLine = tmp.center();
	/*if (prt(isInside(onLine)) > 0) {
		results.push_back(tmp);
	}*/
	for (Line & l : skin) {
		if (prt(_checkSide(l, onLine)) > 0) {
			cout << "break " << onLine.toString() << endl;
			break;
		}
		results.push_back(tmp);
	}
	return results;
}

vector<AlgorithmEngine::Point> AlgorithmEngine::_clip(const vector<Point> & vertices, const Line & line) const
{
	vector <Point> newPoints;
	for (int i = 0; i < vertices.size(); i++)
	{
		// i and k form a line in polygon
		int k = (i + 1) % vertices.size();

		Point polyI = vertices[i];
		Point polyK = vertices[k];

		// Calculating position of first point
		auto iPos = (line.end.x - line.beg.x) * (polyI.y - line.beg.y) - (line.end.y - line.beg.y) * (polyI.x - line.beg.x);

		// Calculating position of second point
		auto kPos = (line.end.x - line.beg.x) * (polyK.y - line.beg.y) - (line.end.y - line.beg.y) * (polyK.x - line.beg.x);

		if (iPos < 0 && kPos < 0) // Both points are inside
		{
			// Only second point is added
			newPoints.push_back(polyK);
		} else if (iPos >= 0 && kPos < 0) { // First point is outside
			// Point of intersection with edge
			// and the second point is added
			newPoints.push_back(_intersection(
				line,
				Line {
				polyI,
				polyK
			}));

			newPoints.push_back(polyK);
		} else if (iPos < 0 && kPos >= 0) { // Second point is outside
			newPoints.push_back(_intersection(
				line,
				Line {
				polyI,
				polyK
			}));
			
		}

		// Both points are outside
		else
		{
			// Nothing to be added
		}
	}

	return newPoints;
}

int AlgorithmEngine::isInside(Point p)
{
	return 0;
}

int AlgorithmEngine::Point::calcOffset() const
{
	return x + y * width;
}

string AlgorithmEngine::Point::toString() const
{
		std::stringstream ss;
		ss << '(' << x << "; " << y << ')';
		return ss.str();
}

AlgorithmEngine::Point AlgorithmEngine::Line::center()
{
	return Point {
		(beg.x + end.x) / 2,
		(beg.y + end.y) / 2
	};
}

string AlgorithmEngine::Line::toString() const
{
	std::stringstream ss;
	ss << beg.toString() << " -> " << end.toString();
	return ss.str();
}