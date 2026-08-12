#pragma once

#include "mat4.hpp"
#include "utils/vec3.hpp"
#include <cmath>

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
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	Mat4 r = m;

	for (int row = 0; row < 4; ++row)
	{
		r.m[1][row] = m.m[1][row] * c + m.m[2][row] * s;
		r.m[2][row] = m.m[1][row] * -s + m.m[2][row] * c;
	}
	return r;
}

inline Mat4 rotateY(const Mat4& m, float angle)
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	Mat4 r = m;

	for (int row = 0; row < 4; ++row)
	{
		r.m[2][row] = m.m[2][row] * c + m.m[0][row] * s;
		r.m[0][row] = m.m[2][row] * -s + m.m[0][row] * c;
	}
	return r;
}

inline Mat4 rotateZ(const Mat4& m, float angle)
{
	const float c = std::cos(angle);
	const float s = std::sin(angle);

	Mat4 r = m;

	for (int row = 0; row < 4; ++row)
	{
		r.m[0][row] = m.m[0][row] * c + m.m[1][row] * s;
		r.m[1][row] = m.m[0][row] * -s + m.m[1][row] * c;
	}
	return r;
}

} // namespace scm
