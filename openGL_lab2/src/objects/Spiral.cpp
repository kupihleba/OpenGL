#include "Spiral.h"
#include <math.h>
#include <vector>
#include <tuple>
#include <GLFW/glfw3.h>
#include <glm/gtx/normal.hpp>
#include <glm/gtc/type_ptr.hpp>

#define $ _vertices.push_back(1.0f);
#include <utils/Structures.h>
#include <limits>
# define PI 3.14159265358979323846 

using namespace obj;

obj::Spiral::Spiral(std::shared_ptr<Shader> shader)
	:Drawable(shader)
{
	_precision = 90;
	_build(_precision, 0.4f, 1.0f, 2.0f);
}


void obj::Spiral::_draw()
{
	//_newShader->color(1.0f, 0.3f, 0.3f, 0.9f);
	if (Drawable::_vertices.size() > std::numeric_limits<GLsizei>::max())
		throw std::exception("vertices size is too big");
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_vertices.size() / 3));
}

void obj::Spiral::_defineVao()
{
	const GLsizei DIM = 3;
	const GLsizei ARGB = 4;
	using proto::AttributeType;
	*this << Chunk{ AttributeType::POSITION, DIM}
	      << Chunk{ AttributeType::NORMAL, DIM }
	      << Chunk{ AttributeType::TEXTURE, 2 }
	      << Chunk{ AttributeType::COLOR, ARGB };
}


Spiral::~Spiral() {}

void obj::Spiral::_build(int precision, float r, float R, float len)
{
	using std::get;
	const int X = 0;
	const int Y = 1;
	const int Z = 2;

	auto _f = [r, R](float u, float v) -> Point3D {
		return Point3D {
			r*cos(u) + R*cos(v),
			r*v,
			r*sin(u) + R*sin(v)
		};
	};

	//const float len = 2.0f;
	float delta = static_cast<float>(2 * PI / precision);
	//Point3D coords;
	float u = 0, v = 0;
	_vertices.clear();

	using std::move;
	for (v = 0; v <= 2 * PI * len + delta; v += delta) {
		for (u = 0; u <= 2 * PI + delta; u += delta) {
			Point3D 
				a = _f(u, v),
				b = _f(u, v + delta),
				c = _f(u + delta, v);
			pushBack(a);
			pushNormal(a, b, c);
			_vertices.push_back(u / (2 * PI + delta));
			_vertices.push_back(v / (2 * PI * len + delta));
			$ $ $ $
			pushBack(b);
			pushNormal(a, b, c);
			_vertices.push_back(u / (2 * PI + delta));
			_vertices.push_back((v + delta) / (2 * PI * len + delta));
			$ $ $ $
			pushBack(c);
			pushNormal(a, b, c);
			_vertices.push_back((u + delta) / (2 * PI + delta));
			_vertices.push_back(v / (2 * PI * len + delta));
			$ $ $ $

			a = _f(u + delta, v + delta);
			b = _f(u, v + delta);
			c = _f(u + delta, v);
			pushBack(a);
			pushNormal(b, a, c);
			_vertices.push_back((u + delta) / (2 * PI + delta));
			_vertices.push_back((v + delta) / (2 * PI * len + delta));
			$ $ $ $
			pushBack(b);
			pushNormal(b, a, c);
			_vertices.push_back(u / (2 * PI + delta));
			_vertices.push_back((v + delta) / (2 * PI * len + delta));
			$ $ $ $
			pushBack(c);
			pushNormal(b, a, c);
			_vertices.push_back((u + delta) / (2 * PI + delta));
			_vertices.push_back(v / (2 * PI * len + delta));
			$ $ $ $
		}
	}
	/*for (u = 0; u <= 2 * PI + delta; u += delta) { 
		// TODO: Wrong vertices inserted!
		coords = _f(u, v);
		_vertices.push_back(get<0>(coords));
		_vertices.push_back(get<1>(coords));
		_vertices.push_back(get<2>(coords));
	}*/
	loadVertices();
}

void obj::Spiral::pushBack(Point3D point)
{
	_vertices.push_back(std::move(point.x));
	_vertices.push_back(std::move(point.y));
	_vertices.push_back(std::move(point.z));
}

void obj::Spiral::pushNormal(const Point3D & a, const Point3D & b, const Point3D & c)
{
	auto n = glm::triangleNormal(a.toVec(), b.toVec(), c.toVec());
	_vertices.push_back(std::move(n.x));
	_vertices.push_back(std::move(n.y));
	_vertices.push_back(std::move(n.z));
}

void obj::Spiral::reconstruct(int precision) 
{
	_precision = precision;
	_build(precision, 0.4f, 1.0f, 2.0f);
	//_newShader->regenerateBuffer();
/*	glBindBuffer(GL_ARRAY_BUFFER, _newShader->getBufAllocation());
	
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/
}

int obj::Spiral::getBuildPrecision()
{
	return _precision;
}

string obj::Spiral::toString() const
{
	return "Spiral";
}
