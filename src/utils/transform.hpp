#pragma once

#include "mat4.hpp"
#include "utils/vec3.hpp"

namespace scm
{

inline Mat4 scale(const Mat4& m, const Vec3& v)
{
	Mat4 r = m;

	for (int row = 0; row < 4; ++row)
	{
		r.m[0][row] *= v.x;
		r.m[1][row] *= v.y;
		r.m[2][row] *= v.z;
	}
	return r;
}

inline Mat4 translate(const Mat4& m, const Vec3& v)
{
	Mat4 r = m;

	for (int row = 0; row < 4; ++row)
		r.m[3][row] = m.m[0][row] * v.x + m.m[1][row] * v.y +
		              m.m[2][row] * v.z + m.m[3][row];
	return r;
}

inline Mat4 rotateX(const Mat4& m, float angle)
{
	Mat4 r = m;

	r.m[0][1] =
}

} // namespace scm
