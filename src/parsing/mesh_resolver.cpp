#include "parsing/mesh_resolver.hpp"
#include "model/mesh_data.hpp"
#include "model/vertex.hpp"
#include "parsing/obj_data.hpp"
#include "utils/vec2.hpp"
#include "utils/vec3.hpp"
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
	v.position = scm::Vec3(od.positions[a]);
	md.vertices.push_back(v);
	for (size_t i = 0; i < face.size() - 2; i++)
	{
		md.faces++;
		b = face[1 + i] - 1;
		v.position = scm::Vec3(od.positions[b]);
		md.vertices.push_back(v);
		c = face[2 + i] - 1;
		v.position = scm::Vec3(od.positions[c]);
		md.vertices.push_back(v);
	}
}

namespace mesh
{
MeshData resolve(const ObjData& od)
{
	MeshData md;

	for (size_t i = 0; i < od.faces.size(); i++)
		triangulate(md, od.faces[i], od);
	return md;
}
} // namespace mesh
