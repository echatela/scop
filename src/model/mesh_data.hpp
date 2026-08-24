#pragma once

#include "model/vertex.hpp"
#include <vector>

struct MeshData
{
	std::vector<Vertex> vertices;
	unsigned int faces;
};
