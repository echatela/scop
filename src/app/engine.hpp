#pragma once

#include "app/frame_context.hpp"
#include "render/shader.hpp"
#include "render/mesh.hpp"
#include "render/texture.hpp"

#include "math/mat4.hpp"
#include "math/vec3.hpp"
#include "math/transform.hpp"

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
