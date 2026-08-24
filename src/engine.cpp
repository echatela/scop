#include "engine.hpp"
#include "parsing/obj_data.hpp"
#include "parsing/obj_parser.hpp"
#include "utils/mat4.hpp"
#include "utils/perspective.hpp"
#include "utils/transform.hpp"
#include "utils/vec3.hpp"

#include <glad/glad.h>

Engine::Engine(const std::string& objPath, const std::string& texPath)
    : _shader("shaders/vert.glsl", "shaders/frag.glsl"),
      _texture(texPath),
      _mesh()
{
	ObjData data = obj::parseFile(objPath);
	glEnable(GL_DEPTH_TEST);
	_state.view = translate(_state.view, scm::Vec3(0.0f, 0.0f, -3.0f));
}

void Engine::update(double dt, int width, int height)
{
	_state.rotation += (float)dt * scm::radians(50.0f);
	_state.model = scm::rotate(scm::Mat4::identity(), _state.rotation,
	                           scm::Vec3(0.5f, 1.0f, 0.0f));
	if (width != _state.width || height != _state.height)
	{
		_state.width = width;
		_state.height = height;
		_state.projection = scm::perspective(
		    scm::radians(45.0f), (float)_state.width / (float)_state.height,
		    0.1f, 100.0f);
	}
}

void Engine::render()
{
	glClearColor(0.2f, 0.3f, 0.3, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_texture.bind();

	_shader.use();

	_shader.setMat4("model", _state.model);
	_shader.setMat4("view", _state.view);
	_shader.setMat4("projection", _state.projection);

	_mesh.draw();
}
