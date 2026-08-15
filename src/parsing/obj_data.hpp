#pragma once

#include "utils/scm.hpp"

#include <vector>

struct ObjCorner
{
	int position;
	int texCoord;
	int normal;
};

struct ObjFace
{
	std::vector<ObjCorner> corners;
	int                    material; // -1 if none
};

struct ObjData

{
	std::vector<scm::Vec3> positions;
	std::vector<scm::Vec2> texCoords;
	std::vector<scm::Vec3> normals;
	std::vector<ObjFace>   faces;

	std::string              name;
	std::string              materialLibrary;
	std::vector<std::string> materialNames;
};
