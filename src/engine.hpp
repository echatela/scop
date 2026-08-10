#pragma once

#include "shader.hpp"
#include "model/texture.hpp"
#include "model/mesh.hpp"

class Engine
{
	Shader  _shader;
	Texture _texture;
	Mesh    _mesh;
	//	State   _state;

public:
	Engine(const std::string& objPath, const std::string& texPath);

	void update(double dt);
	void render();
};
