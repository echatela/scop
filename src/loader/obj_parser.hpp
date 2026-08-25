#pragma once

#include "loader/obj_data.hpp"

namespace obj
{
ObjData parse(std::istream& in);
ObjData parseFile(const std::string& path);
}
