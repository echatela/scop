#pragma once

#include "frame_context.hpp"
#include "shader.hpp"
#include "model/texture.hpp"
#include "model/mesh.hpp"
#include "utils/mat4.hpp"
#include "utils/transform.hpp"
#include "utils/vec3.hpp"

struct State
{
	scm::Mat4 model;
	scm::Mat4 view;
	scm::Mat4 projection;

	int width = 0;
	int height = 0;

	State()
	    : model(scm::Mat4::identity()),
	      view(scm::translate(scm::Mat4::identity(),
	                          scm::Vec3(0.0f, 0.0f, -2.0f))),
	      projection(scm::Mat4::identity()) {};
};

class Engine
{
	Shader _shader;
	//	Texture _texture;
	Mesh  _mesh;
	State _state;

public:
	Engine(const std::string& objPath);

	void update(const FrameContext& frame);
	void render();
};
