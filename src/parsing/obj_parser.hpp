#pragma once

#include "parsing/obj_data.hpp"

#include <istream>
#include <string>

namespace obj
{
ObjData parse(std::istream& in);
ObjData parseFile(const std::string& path);
}
