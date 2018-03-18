#pragma once
#include "Object.h"
#include <future>
#include <tuple>

namespace obj {
	class Spiral : Object
	{
	public:
		Spiral();
		~Spiral();

	private:
		typedef std::tuple<float, float, float> Coords;

		std::function<std::tuple<float, float, float>(float, float)> _f;
	};
}

