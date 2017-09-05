//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Patterns/Factory.hpp"
#include "String.hpp"
#include <jsoncons/json.hpp>


namespace Cpf
{
	namespace IO
	{
		class Stream;
	}
}


namespace RayTracer
{
	class Scene;

	class Node
	{
	public:
		virtual bool Parse(const jsoncons::json&, Scene&) const = 0;
	};

	class SceneReader
	{
	public:
		using NodeFactory = Cpf::Patterns::Factory<Cpf::String, Node>;

		SceneReader(Scene&, const NodeFactory&);

		bool Load(Cpf::IO::Stream* source);

	private:
		Scene& mScene;
		const NodeFactory& mFactory;
	};
}
