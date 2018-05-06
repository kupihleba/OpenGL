#pragma once
#include <engine/AbstractEngine.h>
#include <vector>

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
		static int width;
		static int floatsInVertex;
	};
	struct Line {
		Point beg;
		Point end;
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
	vector<std::pair<vector<Point>, RGB>> _polygons;

	void _drawLine(vector<RGB> & buffer, const Point & a, const Point & b);
	void _colorPoint(vector<RGB> & buffer, const Point & p, const RGB & color);
	void drawLine(const Point & a, const Point & b);
	void colorPoint(const Point & p, const RGB & color);

	void drawPoly(const vector<Point> & poly, RGB color, GLfloat lineWidth) const;

	vector<AlgorithmEngine::Point> goSutherlandHodgeman() const;
	vector<AlgorithmEngine::Point> _clip(const vector<Point> & vertices, const Line & line) const;
};

