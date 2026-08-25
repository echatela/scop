#pragma once

#include "math/vec2.hpp"
#include "math/vec3.hpp"

#include <vector>

static constexpr int kNoIndex = -1;

struct VertexRef
{
	int position = kNoIndex;
	int texCoord = kNoIndex;
	int normal = kNoIndex;
};

struct ObjData
{
	std::vector<scm::Vec3>              positions;
	std::vector<scm::Vec2>              texCoords;
	std::vector<scm::Vec3>              normals;
	std::vector<std::vector<VertexRef>> faces;
};
