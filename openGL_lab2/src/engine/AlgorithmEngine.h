#pragma once
#include <engine/AbstractEngine.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <kupihleba.h>


class AlgorithmEngine : public AbstractEngine
{
public:
	AlgorithmEngine();
	~AlgorithmEngine();

private:
	// Structures //
	struct Point {
		GLint x;
		GLint y;
		int calcOffset() const;
		string toString() const;
		static int width;
		static int floatsInVertex;
	};
	struct Line {
		Point beg;
		Point end;
		Point center();
		string toString() const;
	};

	struct RGB {
		GLfloat r;
		GLfloat g;
		GLfloat b;
	};

	vector<Point> _vertices;
	const size_t floatsInVertex = 3;

	vector<RGB> _buffer;
	//vector<RGB> _tmpBuffer;

	virtual void _draw();

	int _checkSide(const Line & line, const Point & p) const;
	Point _intersection(const Line & a, const Line & b) const;

	vector<Point> _cropArea;

	void _drawCropArea();
	void _drawPolyArea();

	enum Handler {
		CROP,
		POLY_DRAW
	};
	Handler _currentHandler = POLY_DRAW;
	vector<Point> _unhandledClicks;

	typedef std::pair<vector<Point>, RGB> PolyRGB;
	typedef std::pair<Line, RGB> LineRGB;
	vector<PolyRGB> _polygons;
	vector<LineRGB> _lines;

	void _drawLineDESTRUCTIVE(vector<RGB> & buffer, const Point & a, const Point & b);
	void _colorPointDESTRUCTIVE(vector<RGB> & buffer, const Point & p, const RGB & color);
	void drawLineDESTRUCTIVE(const Point & a, const Point & b);
	void colorPointDESTRUCTIVE(const Point & p, const RGB & color);

	void drawPoly(const vector<Point> & poly, RGB color, GLfloat lineWidth) const;
	void drawLine(const Line & line, RGB color, GLfloat lineWidth) const;

	vector<AlgorithmEngine::Line> goSutherlandHodgeman();
	vector<AlgorithmEngine::Point> _clip(const vector<Point> & vertices, const Line & line) const;
	int isInside(Point p);

	bool isClockwise() const
	{
		auto& r = _cropArea;
		long sum = 0;
		for (int i = 1; i <= r.size(); i++) {
			sum += r[i % r.size()].x *
				(r[(i + 1) % r.size()].y - r[(i - 1) % r.size()].y);
		}
		return sum < 0;
	}
};

