#include "Spiral.h"
#include <math.h>
#include <vector>
#include <tuple>
#define PI 3.14159265358979f

using namespace obj;

Spiral::Spiral()
{
	_f = [](float u, float v) -> Coords {
		return Coords();
	};
	std::vector<float> data;
	const int precision = 200;
	float delta = 2 * PI / precision;
	for (float u = 0; u < 2 * PI; u += delta) {
		Coords coords = _f(u, 0);
		data.push_back(std::get<0>(coords));
		data.push_back(std::get<1>(coords));
		data.push_back(std::get<2>(coords));
	}
}


Spiral::~Spiral()
{
}
