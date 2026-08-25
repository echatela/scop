#pragma once

#include "math/vec3.hpp"

#include <vector>

struct ObjData
{
	std::vector<scm::Vec3>        positions;
	std::vector<std::vector<int>> faces;
};
