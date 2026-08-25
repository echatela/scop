#pragma once

#include "data/mesh_data.hpp"
#include "data/vertex.hpp"

#include <vector>

class Mesh
{
	unsigned int _vao = 0;
	unsigned int _vbo = 0;

	std::vector<Vertex> _vertices;

public:
	Mesh(const MeshData& data);
	~Mesh();

	void draw();

private:
	void setupMesh();
};
