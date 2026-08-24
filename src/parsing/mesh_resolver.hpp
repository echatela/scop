#pragma once

#include "model/mesh_data.hpp"
#include "parsing/obj_data.hpp"

namespace mesh
{
MeshData resolve(const ObjData& data);
}
