#pragma once


#include "RayTracer/RayTracer.hpp"
#include <string>

// Forward reference.
class JSONValue;


namespace RayTracer
{
	bool		Parse( JSONValue* src, std::string attrName, uint32_t& out );
	bool		Parse( JSONValue* src, std::string attrName, float& out );
	bool		Parse( JSONValue* src, std::string attrName, std::string& out );
	bool		Parse( JSONValue* src, std::string attrName, Vector3& out );
	bool		Parse( JSONValue* src, std::string attrName, Vector4& out );
}
