//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Patterns/Factory.hpp"
#include "String.hpp"
#include <jsoncons/json.hpp>


namespace CPF
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
		using NodeFactory = CPF::Patterns::Factory<CPF::String, Node>;

		SceneReader(Scene&, const NodeFactory&);

		bool Load(CPF::IO::Stream* source);

	private:
		Scene& mScene;
		const NodeFactory& mFactory;
	};
}
