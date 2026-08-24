#include "parsing/mesh_resolver.hpp"
#include "model/mesh_data.hpp"
#include "model/vertex.hpp"
#include "parsing/obj_data.hpp"
#include "utils/vec2.hpp"
#include "utils/vec3.hpp"
#include <cstddef>
#include <iostream>
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

static void printVertex(const Vertex& v)
{
	std::cout << v.position << " " << v.color << " " << v.texCoords;
}

namespace mesh
{
MeshData resolve(const ObjData& od)
{
	MeshData md;

	for (size_t i = 0; i < od.faces.size(); i++)
		triangulate(md, od.faces[i], od);

	for (size_t i = 0; i < md.vertices.size(); i += 3)
	{
		for (size_t j = 0; j < 3; j++)
		{
			printVertex(md.vertices[i + j]);
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	return md;
}
} // namespace mesh
