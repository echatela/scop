#pragma once

#include "data/mesh_data.hpp"
#include "loader/obj_data.hpp"

namespace mesh
{
MeshData build(const ObjData& data);
}
