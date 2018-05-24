#pragma once
#include <vector>
#include <objects/Object.h>
#include <utils/kupihleba.h>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	template <class T>
	std::enable_if_t<std::is_base_of<obj::Object, T>::value, void> addObject(T & object) {
		cout << object.toString() << endl;
		_objects.push_back(object);
	};

	void draw();

protected:
	vector<obj::Object> _objects;
};

