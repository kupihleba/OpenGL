#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::draw()
{
	for (auto & i : _objects) {
		i.draw();
	}
}
