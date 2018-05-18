#pragma once
#include <engine/AbstractEngine.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <utils/kupihleba.h>
#include <utils/Structures.h>

class AlgorithmEngine : public AbstractEngine
{
public:
	AlgorithmEngine();
	~AlgorithmEngine();

private:
	vector<Point> _vertices;
	vector<Line> _edges;

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

	void drawPoly(const vector<Point> & poly, RGB color, GLfloat lineWidth) const;
	void drawLine(const Line & line, RGB color, GLfloat lineWidth) const;
	vector<Line> castToLineLoop(const vector<Point> & points) const;

	vector<Line> goSutherlandHodgeman();
	vector<Line> goSutherlandHodgeman(const vector<Line> & poly, const vector<Line> & clip);
	vector<Line> _clip(const vector<Line> & vertices, const Line & line);
	bool isInside(const vector<Point> & clipArea, const Point & p) const;

	SILENT void _proccessCase(vector<Line> & toAddEdges, const Line & poly, const Line & clip, vector<Point> & intersectionPoints = vector<Point>());
	bool isClockwise() const;
	bool isClockwise(const vector<Point> & poly) const;
};

