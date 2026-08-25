#pragma once

#include "math/vec2.hpp"
#include "math/vec3.hpp"

#include <vector>

struct ObjData
{
	std::vector<scm::Vec3>        positions;
	std::vector<scm::Vec2>        texCoords;
	std::vector<std::vector<int>> faces;
};
