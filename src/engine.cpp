#include "engine.hpp"
#include "utils/mat4.hpp"
#include "utils/transform.hpp"
#include "utils/vec3.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Engine::Engine(const std::string& objPath, const std::string& texPath)
    : _shader("shaders/vert.glsl", "shaders/frag.glsl"),
      _texture(texPath),
      _mesh(objPath)
{
}

void Engine::update(double dt)
{
	(void)dt;
}

void Engine::render()
{
	glClearColor(0.2f, 0.3f, 0.3, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_texture.bind();

	_shader.use();

	scm::Mat4 model = scm::Mat4::identity();
	model = scm::rotateX(model, scm::radians(-55.0f));

	scm::Mat4 view = scm::Mat4::identity();
	view = translate(view, scm::Vec3(0.0f, 0.0f, -3.0f));

	scm::Mat4 projection = scm::Mat4::identity();

	_shader.setMat4("model", model);
	_shader.setMat4("view", view);
	_shader.setMat4("projection", projection);

	_mesh.draw();
}
