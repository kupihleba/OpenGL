#pragma once
#include <engine\AbstractEngine.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <utils\kupihleba.h>

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
		Point center() const;
		string toString() const;
	};

	struct RGB {
		GLfloat r;
		GLfloat g;
		GLfloat b;
	};

	vector<Point> _vertices;
	vector<Line> _edges;

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
	vector<Line> castToLineLoop(const vector<Point> & points) const;

	vector<AlgorithmEngine::Line> goSutherlandHodgeman();
	vector<AlgorithmEngine::Line> goSutherlandHodgeman(const vector<Line> & poly, const vector<Line> & clip);
	vector<AlgorithmEngine::Line> _clip(const vector<Line> & vertices, const Line & line);
	bool isInside(const vector<Point> & clipArea, const Point & p) const;

	SILENT void _proccessCase(vector<Line> & toAddEdges, const Line & poly, const Line & clip, vector<Point> & intersectionPoints = vector<Point>());
	bool isClockwise() const;
};

