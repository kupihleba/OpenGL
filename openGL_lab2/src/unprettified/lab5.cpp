#if 0
#include<iostream>
#include<vector>

//using namespace std;
using std::cout;
using std::endl;
using std::vector;

const int MAX_POINTS = 20;


struct Point {
	int x;
	int y;
	int calcOffset() const;
	static int width;
	static int floatsInVertex;
};
struct Line {
	Point beg;
	Point end;
};


Point _intersection(const Line & a, const Line & b)
{
	auto crossProductA = a.beg.x*a.end.y - a.beg.y*a.end.x;
	auto crossProductB = b.beg.x*b.end.y - b.beg.y*b.end.x;
	auto dxB = b.end.x - b.beg.x;
	auto dyB = b.end.y - b.beg.y;
	auto dxA = a.end.x - a.beg.x;
	auto dyA = a.end.y - a.beg.y;

	auto denominator = dxA * dyB - dyA * dxB;

	return Point{
		(dxA * crossProductB - crossProductA * dxB) /
		denominator,
		(dyA * crossProductB - crossProductA * dyB) /
		denominator
	};
}

vector<Point> clip1(const vector<Point> & vertices,
	const Point &cropI, const Point &cropK)
{
	vector <Point> newPoints;
	for (int i = 0; i < vertices.size(); i++)
	{
		// i and k form a line in polygon
		int k = (i + 1) % vertices.size();

		Point polyI = vertices[i];
		Point polyK = vertices[k];

		//int ix = _vertices[i].x, iy = _vertices[i].y;
		//int kx = _vertices[k].x, ky = _vertices[k].y;

		auto iPos = (cropK.x - cropI.x) * (polyI.y - cropI.y) - (cropK.y - cropI.y) * (polyI.x - cropI.x);

		auto kPos = (cropK.x - cropI.x) * (polyK.y - cropI.y) - (cropK.y - cropI.y) * (polyK.x - cropI.x);

		if (iPos < 0 && kPos < 0)
		{
			//Only second point is added
			newPoints.push_back(polyK);
		}
		else if (iPos >= 0 && kPos < 0) {
			//vector<Point> tmp;

			newPoints.push_back(_intersection(
				Line{
				cropI,
				cropK
			},
				Line{
				polyI,
				polyK
			}));

			newPoints.push_back(polyK);
		}
		else if (iPos < 0 && kPos >= 0)
		{
			newPoints.push_back(_intersection(
				Line{
				cropI,
				cropK
			},
				Line{
				polyI,
				polyK
			}));
		}

		else
		{
		}
	}


	return newPoints;
}

void suthHodgClip1(const vector<Point> & poly_points, int poly_size,
	const vector<Point> & clipper_points, int clipper_size)
{
	vector<Point> tmp(poly_points);
	for (int i = 0; i<clipper_size; i++)
	{
		int k = (i + 1) % clipper_size;

		tmp = clip1(tmp, clipper_points[i], clipper_points[k]);
	}

	for (int i = 0; i < tmp.size(); i++)
		cout << '(' << tmp[i].x <<
		", " << tmp[i].y << ") ";
}

int main()
{
	int poly_size = 3;

	vector<Point> poly_points = { Point{ 100,150 },Point{ 200,250 },
		Point{ 300,200 } };

	int clipper_size = 4;
	vector<Point> clipper_points = { Point{ 150,150 },Point{ 150,200 },
		Point{ 200,200 },Point{ 200,150 } };

	/*int clipper_size = 3;
	int clipper_points[][2] = {{100,300}, {300,300},
	{200,100}};*/

	suthHodgClip1(poly_points, poly_size, clipper_points,
		clipper_size);
	std::cout << std::endl << "(150, 162) (150, 200) (200, 200) (200, 174)" << std::endl;
	system("pause");
	return 0;
}
#endif