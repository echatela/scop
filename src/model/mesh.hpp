#pragma once

#include "model/mesh_data.hpp"
#include "model/vertex.hpp"

#include <vector>

class Mesh
{
	unsigned int _vao;
	unsigned int _vbo;

	std::vector<Vertex> _vertices;

	unsigned int _faces;

public:
	Mesh();
	Mesh(const MeshData& data);
	~Mesh();

	void draw();

private:
	void setupMesh();
	void setupTestMesh();
};
