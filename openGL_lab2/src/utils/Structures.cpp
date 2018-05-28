#include "Structures.h"
#include <sstream>

int Point::calcOffset() const
{
	return x + y * width;
}

string Point::toString() const
{
	std::stringstream ss;
	ss << '(' << x << "; " << y << ')';
	return ss.str();
}

Point Line::center() const
{
	return Point{
		(beg.x + end.x) / 2,
		(beg.y + end.y) / 2
	};
}

string Line::toString() const {
	std::stringstream ss;
	ss << beg.toString() << " -> " << end.toString();
	return ss.str();
}

glm::vec3 Point3D::toVec() const
{
	return glm::vec3(x, y, z);
}


