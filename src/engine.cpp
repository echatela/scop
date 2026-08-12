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

	scm::Mat4 trans = scm::Mat4::identity();
	trans = scm::translate(trans, scm::Vec3(0.5f, -0.5f, 0.0f));
	trans = scm::rotateZ(trans, glfwGetTime());

	_shader.setMat4("transform", trans);

	_mesh.draw();

	trans = scm::Mat4::identity();
	trans = scm::translate(trans, scm::Vec3(-0.5f, 0.5f, 0.0f));
	trans = scm::scale(trans, scm::Vec3(std::sin(glfwGetTime())));

	_shader.setMat4("transform", trans);

	_mesh.draw();
}
