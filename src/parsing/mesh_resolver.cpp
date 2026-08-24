#include "parsing/mesh_resolver.hpp"
#include "model/mesh_data.hpp"
#include "model/vertex.hpp"
#include "parsing/obj_data.hpp"
#include "utils/mat4.hpp"
#include "utils/transform.hpp"
#include "utils/vec2.hpp"
#include "utils/vec3.hpp"
#include "utils/vec4.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

static void triangulate(MeshData& md, const std::vector<int>& face,
                        const ObjData& od)
{
	int    a;
	int    b, c;
	Vertex v;

	a = face[0] - 1; // faces behing 1 based
	v.color = a % 2 ? scm::Vec3(0.1f) : scm::Vec3(0.5f);
	v.texCoords = scm::Vec2(0.0f);
	for (size_t i = 0; i < face.size() - 2; i++)
	{
		v.position = scm::Vec3(od.positions[a]);
		md.vertices.push_back(v);
		b = face[1 + i] - 1;
		v.position = scm::Vec3(od.positions[b]);
		md.vertices.push_back(v);
		c = face[2 + i] - 1;
		v.position = scm::Vec3(od.positions[c]);
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

namespace mesh
{
MeshData resolve(const ObjData& od)
{
	MeshData md;

	for (size_t i = 0; i < od.faces.size(); i++)
		triangulate(md, od.faces[i], od);
	normalizeMesh(md);
	return md;
}
} // namespace mesh
