#include "obj_parser.hpp"
#include "parsing/obj_data.hpp"
#include "utils/vec3.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
class ObjParser
{
	ObjData& _data;
	int      _line;
//	int      _material;

public:
	ObjParser(ObjData& data);

	void feed(const std::string& text);

	void parse(std::istringstream& ss);
	void parseVertex(std::istringstream& ss);
	void parseTexCoord(std::istringstream& ss);
	void parseNormal(std::istringstream& ss);
	void parseFace(std::istringstream& ss);
//	void parseMaterial(std::istringstream& ss);

	ObjCorner parseCorner(std::string& token);

	void error(const std::string& message);
};

ObjParser::ObjParser(ObjData& data)
    : _data(data)
{
}

void ObjParser::error(const std::string& message)
{
	std::ostringstream ss;

	ss << "obj: line " << _line << ": " << message;
	throw std::runtime_error(ss.str());
}

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
	else if (keyword == "vt")
		parseTexCoord(ss);
//	else if (keyword == "vn")
//		parseNormal(ss);
	else if (keyword == "f")
		parseFace(ss);
//	else if (keyword == "usemtl")
//		parseMaterial(ss);
//	else if (keyword == "mtllib")
//		ss >> _data.materialLibrary;
	else if (keyword == "o")
		ss >> _data.name;
}

void ObjParser::parseVertex(std::istringstream& ss)
{
	scm::Vec3 v;

	if (!(ss >> v.x >> v.y >> v.z))
		error("v: three coords are expected");

	_data.positions.push_back(v);
}

void ObjParser::parseTexCoord(std::istringstream& ss)
{
	scm::Vec2 vt;

	if (!(ss >> vt.x))
		error("vt: at least one coord is expected");
	if (!(ss >> vt.y))
		vt.y = 0.0f;

	_data.texCoords.push_back(vt);
}

void ObjParser::parseNormal(std::istringstream& ss)
{
	scm::Vec3 vn;

	if (!(ss >> vn.x >> vn.y >> vn.z))
		error("vn: three coords are expected");

	_data.normals.push_back(vn);
}

void ObjParser::parseFace(std::istringstream& ss)
{
	ObjFace     face;
	std::string token;

	while (ss >> token)
		face.corners.push_back(parseCorner(token));

//	face.material = _material;
	_data.faces.push_back(face);
}

ObjCorner ObjParser::parseCorner(std::string& token)
{
	ObjCorner corner;


}

} // namespace

ObjData obj::parse(std::istream& in)
{
	ObjData     data;
	ObjParser   parser(data);
	std::string line;

	while (std::getline(in, line))
		parser.feed(line);

	return data;
}

ObjData obj::parseFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
		throw std::runtime_error("Failed to open obj file");
	return obj::parse(file);
}
