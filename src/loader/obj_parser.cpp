#include "loader/obj_parser.hpp"
#include "loader/obj_data.hpp"
#include "math/vec3.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace
{
class ObjParser
{
	ObjData _data;
	int     _line;

public:
	void feed(const std::string& text);

	void      parseVertex(std::istringstream& ss);
	void      parseTexCoord(std::istringstream& ss);
	void      parseNormal(std::istringstream& ss);
	VertexRef parseVertexRef(std::istringstream& ss);
	void      parseFace(std::istringstream& ss);

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
	if (keyword == "vt")
		parseTexCoord(ss);
	if (keyword == "vn")
		parseNormal(ss);
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

void ObjParser::parseTexCoord(std::istringstream& ss)
{
	scm::Vec2 vt;

	if (!(ss >> vt.x >> vt.y))
		error("vt: two values are expected");

	_data.texCoords.push_back(vt);
}

void ObjParser::parseNormal(std::istringstream& ss)
{
	scm::Vec3 vn;

	if (!(ss >> vn.x >> vn.y >> vn.z))
		error("vn: three values are expected");

	_data.normals.push_back(vn);
}

static int resolveIndex(int raw, std::size_t count)
{
	if (raw > 0)
		return raw - 1;
	if (raw < 0)
		return static_cast<int>(count) + raw;
	return kNoIndex;
}

VertexRef ObjParser::parseVertexRef(std::istringstream& ss)
{
	VertexRef ref;

	std::string token;
	if (!(ss >> token))
		return ref;

	std::istringstream ts(token);

	int raw = 0;
	if (!(ts >> raw) || raw == 0)
		error("f: invalid vertex reference");
	ref.position = resolveIndex(raw, _data.positions.size());
	if (ref.position < 0 ||
	    ref.position >= static_cast<int>(_data.positions.size()))
		error("f: position index out of range");

	if (ts.peek() != '/')
	{
		if (!ts.eof())
			error("f: invalid vertex reference");
		return ref;
	}
	ts.get();

	if (ts.peek() != '/')
	{
		if (!(ts >> raw))
			error("f: invalid texture coordinate index");
		ref.texCoord = resolveIndex(raw, _data.texCoords.size());
		if (ref.texCoord < 0 ||
		    ref.texCoord >= static_cast<int>(_data.texCoords.size()))
			error("f: texture coordinate out of range");
	}

	if (ts.peek() != '/')
	{
		if (!ts.eof())
			error("f: invalid vertex reference");
		return ref;
	}
	ts.get();

	if (!(ts >> raw))
		error("f: invalid normal index");
	ref.normal = resolveIndex(raw, _data.normals.size());
	if (ref.normal < 0 || ref.normal >= static_cast<int>(_data.normals.size()))
		error("f: normal out of range");

	if (!ts.eof())
		error("f: trailing characters in vertex reference");

	return ref;
}

void ObjParser::parseFace(std::istringstream& ss)
{
	std::vector<VertexRef> face;

	for (int i = 0; i < 3; i++)
	{
		VertexRef ref = parseVertexRef(ss);
		if (ref.position == kNoIndex)
			error("f: three or more Vertex References are expected");
		face.push_back(ref);
	}
	for (;;)
	{
		VertexRef ref = parseVertexRef(ss);
		if (ref.position == kNoIndex)
			break;
		face.push_back(ref);
	}

	_data.faces.push_back(face);
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
