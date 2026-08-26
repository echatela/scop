#include "data/mesh_data.hpp"
#include "loader/obj_data.hpp"

#include "math/mat4.hpp"
#include "math/transform.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

static float faceGrey(unsigned index)
{
	static const float greys[] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
	uint32_t           h = index;

	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;
	return greys[h % (sizeof(greys) / sizeof(greys[0]))];
}

static scm::Vec3 getNormal(const scm::Vec3& a, const scm::Vec3& b,
                           const scm::Vec3& c)
{
	return scm::normalize(scm::cross(b - a, c - a));
}

static void triangulate(MeshData& md, const std::vector<VertexRef>& face,
                        const ObjData& od, unsigned index)
{
	const VertexRef a = face[0];
	VertexRef       b, c;
	Vertex          v;

	if (od.normals.empty())
		v.normal = getNormal(od.positions[face[0].position],
		                     od.positions[face[1].position],
		                     od.positions[face[2].position]);
	v.color = scm::Vec3(faceGrey(index));
	for (size_t i = 0; i < face.size() - 2; i++)
	{
		v.position = scm::Vec3(od.positions[a.position]);
		if (a.texCoord != kNoIndex)
			v.texCoord = scm::Vec2(od.texCoords[a.texCoord]);
		if (a.normal != kNoIndex)
			v.normal = scm::Vec3(od.normals[a.normal]);
		md.vertices.push_back(v);

		b = face[1 + i];
		v.position = scm::Vec3(od.positions[b.position]);
		if (b.texCoord != kNoIndex)
			v.texCoord = scm::Vec2(od.texCoords[b.texCoord]);
		if (b.normal != kNoIndex)
			v.normal = scm::Vec3(od.normals[b.normal]);
		md.vertices.push_back(v);

		c = face[2 + i];
		v.position = scm::Vec3(od.positions[c.position]);
		if (c.texCoord != kNoIndex)
			v.texCoord = scm::Vec2(od.texCoords[c.texCoord]);
		if (c.normal != kNoIndex)
			v.normal = scm::Vec3(od.normals[c.normal]);
		md.vertices.push_back(v);
	}
}

static scm::Mat4 centerMesh(const scm::Vec3& min, const scm::Vec3& max)
{
	scm::Vec3 mid = (min + max) / 2;

	return scm::translate(scm::Mat4::identity(), -mid);
}

static scm::Mat4 boundMesh(const scm::Vec3& min, const scm::Vec3& max)
{
	scm::Vec3 extent = max - min;
	float     e = std::max({extent.x, extent.y, extent.z});
	float     s = e > 0.0001f ? 1.0 / e : 1.0f;

	return scm::scale(scm::Mat4::identity(), scm::Vec3(s));
}

static void normalizeMesh(MeshData& md)
{
	scm::Vec3 min = md.vertices[0].position;
	scm::Vec3 max = min;
	scm::Mat4 trans;
	scm::Mat4 scale;

	for (size_t i = 1; i < md.vertices.size(); i++)
	{
		min = scm::min(min, md.vertices[i].position);
		max = scm::max(max, md.vertices[i].position);
	}

	trans = centerMesh(min, max);
	scale = boundMesh(min, max);
	scm::Mat4 transform = scale * trans;

	for (size_t i = 0; i < md.vertices.size(); i++)
	{
		scm::Vec4 r = transform * scm::Vec4(md.vertices[i].position, 1.0f);
		md.vertices[i].position = r.xyz();
	}
}

static void basicTexCoords(MeshData& md)
{
	for (size_t i = 0; i < md.vertices.size(); i++)
	{
		Vertex& v = md.vertices[i];
		if (std::fabs(v.normal.x) >= std::fabs(v.normal.y) &&
		    std::fabs(v.normal.x) >= std::fabs(v.normal.z))
			v.texCoord = scm::Vec2(-v.position.z + 0.5f, v.position.y + 0.5f);
		else if (std::fabs(v.normal.y) >= std::fabs(v.normal.x) &&
		         std::fabs(v.normal.y) >= std::fabs(v.normal.z))
			v.texCoord = scm::Vec2(v.position.x + 0.5f, -v.position.z + 0.5f);
		else if (std::fabs(v.normal.z) >= std::fabs(v.normal.x) &&
		         std::fabs(v.normal.z) >= std::fabs(v.normal.y))
			v.texCoord = scm::Vec2(v.position.x + 0.5f, v.position.y + 0.5f);
	}
}

namespace mesh
{
MeshData build(const ObjData& od)
{
	MeshData md;

	if (od.faces.empty())
		throw std::runtime_error(
		    "meshBuilder: mesh should have at least one face");

	for (size_t i = 0; i < od.faces.size(); i++)
		triangulate(md, od.faces[i], od, i);
	normalizeMesh(md);
	if (od.texCoords.empty())
		basicTexCoords(md);
	return md;
}
} // namespace mesh
