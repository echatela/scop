#pragma once

#include "shader.hpp"

class Engine
{
	Shader  _shader;
//	Texture _texture;
//	Mesh    _mesh;
//	State   _state;

public:
	Engine();

	void update(double dt);
	void render();
};
