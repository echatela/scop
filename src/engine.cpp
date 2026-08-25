#include "engine.hpp"
#include "parsing/mesh_resolver.hpp"
#include "parsing/obj_parser.hpp"
#include "utils/mat4.hpp"
#include "utils/perspective.hpp"
#include "utils/transform.hpp"
#include "utils/vec3.hpp"

#include <glad/glad.h>

Engine::Engine(const std::string& objPath)
    : _shader("shaders/vert.glsl", "shaders/frag.glsl"),
      _mesh(mesh::resolve(obj::parseFile(objPath)))
{
	glEnable(GL_DEPTH_TEST);
}

static float rotateRatio(int rotation, double dt)
{
	return (float)rotation * (float)dt * scm::radians(50.0f);
}

void Engine::update(const FrameContext& frame)
{
	if (frame.resetPosition)
	{
		_state.model = scm::Mat4::identity();
		_state.view =
		    scm::translate(scm::Mat4::identity(), scm::Vec3(0.0f, 0.0f, -2.0f));
	}

	if (frame.rotationX)
		_state.model =
		    scm::rotateX(_state.model, rotateRatio(frame.rotationX, frame.dt));
	if (frame.rotationY)
		_state.model =
		    scm::rotateY(_state.model, rotateRatio(frame.rotationY, frame.dt));
	if (frame.rotationZ)
		_state.model =
		    scm::rotateZ(_state.model, rotateRatio(frame.rotationZ, frame.dt));

	if (frame.zoom)
		_state.view = scm::translate(
		    _state.view, scm::Vec3(0.0f, 0.0f, (float)frame.zoom / 5.0f));

	if (frame.width != _state.width || frame.height != _state.height)
	{
		_state.width = frame.width;
		_state.height = frame.height;
		_state.projection = scm::perspective(
		    scm::radians(45.0f), (float)_state.width / (float)_state.height,
		    0.1f, 100.0f);
	}
}

void Engine::render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	_texture.bind();

	_shader.use();

	_shader.setMat4("model", _state.model);
	_shader.setMat4("view", _state.view);
	_shader.setMat4("projection", _state.projection);

	_mesh.draw();
}
