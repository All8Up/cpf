//////////////////////////////////////////////////////////////////////////
#include "RayTracer/SceneReader.hpp"
#include "IO/Stream.hpp"

using namespace RayTracer;

//////////////////////////////////////////////////////////////////////////
struct Version
{
	int32_t Major;
	int32_t Minor;
};
namespace jsoncons
{
	template<class Json>
	struct json_type_traits<Json, Version>
	{
		static bool is(const Json& rhs) noexcept
		{
			return rhs.is_object() &&
				rhs.has_key("Major") &&
				rhs.has_key("Minor");
		}
		static Version as(const Json& rhs)
		{
			Version val;
			val.Major = rhs["Major"]. template as<int32_t>();
			val.Minor = rhs["Minor"]. template as<int32_t>();
			return val;
		}
		static Json to_json(const Version& val)
		{
			Json j;
			j["Major"] = val.Major;
			j["Minor"] = val.Minor;
			return j;
		}
	};
};
//////////////////////////////////////////////////////////////////////////


SceneReader::SceneReader(Scene& scene, const NodeFactory& factory)
	: mScene(scene)
	, mFactory(factory)
{}

bool SceneReader::Load(Cpf::IO::Stream* source)
{
	auto json = ReadText(source);
	jsoncons::json jsonDoc(jsoncons::json::parse(json.data()));

	// Check the version information.
	auto versionJson = jsonDoc["Version"];
	if (versionJson.is_null())
		return false;
	Version version = versionJson.as<Version>();

	for (const auto& entry : jsonDoc.object_range())
	{
		// Skip the version key.
		if (entry.key() == "Version")
			continue;

		// Attempt to create a node for the key.
		Node* node = nullptr;
		if (mFactory.Create(entry.key(), &node))
		{
			if (node->Parse(entry.value(), mScene))
			{

			}
			else
			{
				delete node;
				printf("Error parsing: %s\n", entry.key().data());
				return false;
			}
			delete node;
		}
		else
		{
			printf("Unknown node type: %s\n", entry.key().data());
			return false;
		}
	}
	return true;
}
