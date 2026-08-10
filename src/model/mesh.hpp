#pragma once

#include <vector>
#include "utils/scm.hpp"

struct Vertex
{
	scm::vec3 position;
	scm::vec3 color;
	scm::vec2 texCoords;
};

class Mesh
{
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;

	std::vector<Vertex>       _vertices;
	std::vector<unsigned int> _indices;

public:
	Mesh(const std::vector<Vertex>&       vertices,
	     const std::vector<unsigned int>& indices);

private:
	void setupMesh();
};
