#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Object.h"
#include <Shader.h>
#include <memory>
#include "Drawable.h"
#include <utils/kupihleba.h>

namespace obj {

	class Cube: 
		public Drawable
	{
	public:
		Cube(std::shared_ptr<Shader> shader);
		virtual void _draw() override;
		virtual void _defineVao() override;
		virtual string toString() const override;
	};

}

