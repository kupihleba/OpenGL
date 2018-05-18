#pragma once
namespace algorithm {

	template<typename T>
	int sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

}
