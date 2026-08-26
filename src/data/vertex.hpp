#pragma once

#include "math/vec3.hpp"
#include "math/vec2.hpp"

struct Vertex
{
	scm::Vec3 position;
	scm::Vec2 texCoord;
	scm::Vec3 normal;
	scm::Vec3 color;
};
