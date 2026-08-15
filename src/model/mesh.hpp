#pragma once

#include <string>
#include <vector>
#include "utils/scm.hpp"

struct Vertex
{
	scm::Vec3 position;
	scm::Vec3 color;
	scm::Vec2 texCoords;
};

class Mesh
{
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;

	std::vector<Vertex>       _vertices;
	std::vector<unsigned int> _indices;

public:
	Mesh();
	Mesh(const std::string& objPath);
	~Mesh();

	void draw();

private:
	void setupMesh();
	void setupTestMesh();
};
