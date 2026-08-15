#pragma once

#include "shader.hpp"
#include "model/texture.hpp"
#include "model/mesh.hpp"
#include "utils/mat4.hpp"

struct State
{
	scm::Mat4 model;
	scm::Mat4 view;
	scm::Mat4 projection;

	float rotation;
	int   width;
	int   height;

	State()
	    : model(scm::Mat4::identity()),
	      view(scm::Mat4::identity()),
	      projection(scm::Mat4::identity()),
	      rotation(0.0f) {};
};

class Engine
{
	Shader  _shader;
	Texture _texture;
	Mesh    _mesh;
	State   _state;

public:
	Engine(const std::string& objPath, const std::string& texPath);

	void update(double dt, int width, int height);
	void render();
};
