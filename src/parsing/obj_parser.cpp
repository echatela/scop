#include "obj_parser.hpp"
#include "parsing/obj_data.hpp"
#include "utils/vec3.hpp"
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
class ObjParser
{
	ObjData _data;
	int     _line;

public:
	void feed(const std::string& text);

	void parseVertex(std::istringstream& ss);
	void parseFace(std::istringstream& ss);

	ObjData data() const;

	void error(const std::string& message);
};

void ObjParser::feed(const std::string& text)
{
	_line++;

	std::string        content = text.substr(0, text.find('#'));
	std::istringstream ss(content);
	std::string        keyword;

	if (!(ss >> keyword))
		return; // empty line

	if (keyword == "v")
		parseVertex(ss);
	else if (keyword == "f")
		parseFace(ss);
}

void ObjParser::parseVertex(std::istringstream& ss)
{
	scm::Vec3 v;

	if (!(ss >> v.x >> v.y >> v.z))
		error("v: three values are expected");

	_data.positions.push_back(v);
}

void ObjParser::parseFace(std::istringstream& ss)
{
	std::vector<int> f;
	int              a, b, c, d;

	if (!(ss >> a >> b >> c))
		error("f: three or four indices are expected");
	f.push_back(a);
	f.push_back(b);
	f.push_back(c);
	if (ss >> d)
		f.push_back(d);

	_data.faces.push_back(f);
}

ObjData ObjParser::data() const
{
	return _data;
}

void ObjParser::error(const std::string& message)
{
	std::ostringstream ss;

	ss << "obj: line " << _line << ": " << message;
	throw std::runtime_error(ss.str());
}
} // namespace

ObjData obj::parse(std::istream& in)
{
	ObjParser   parser;
	std::string line;

	while (std::getline(in, line))
		parser.feed(line);

	return parser.data();
}

ObjData obj::parseFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
		throw std::runtime_error("Failed to open obj file");

	return parse(file);
}
