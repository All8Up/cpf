/**
* @brief Implements the hash initializer class.
*/
#include "Attributes/Attributes.hpp"

using namespace Cpf;
using namespace Platform;

namespace
{
	/** @brief Number of references to this library. */
	int s_RefCount = 0;
}


/**
* @brief Initialize the library.
* @return An int.
*/
CPF_EXPORT_ATTRIBUTES int AttributesInitializer::Install()
{
	return ++s_RefCount;
}

/**
* @brief Release a reference count and potentially shutdown the library.
* @return An int.
*/
CPF_EXPORT_ATTRIBUTES int AttributesInitializer::Remove()
{
	return --s_RefCount;
}


//////////////////////////////////////////////////////////////////////////
/*
Vector<Attribute> TestNode::sAttributes{
	Attribute(AttributeType::eVector2f, "Point"),
	Attribute(AttributeType::eInt, "Octaves"),
	Attribute(AttributeType::eFloat, "Frequency"),
	Attribute(AttributeType::eFloat, "Amplitude"),
	Attribute(AttributeType::eFloat, "Value")
};
*/

Attribute* TestNode::mpPoint		= nullptr;
Attribute* TestNode::mpOctaves		= nullptr;
Attribute* TestNode::mpFrequency	= nullptr;
Attribute* TestNode::mpAmplitude	= nullptr;
Attribute* TestNode::mpValue		= nullptr;

Node* TestNode::Create()
{
	return new TestNode();
}

bool TestNode::Initialize()
{
	if (
		!AddAttribute(mpPoint = AttributeVector2f::Create("Point")
			.Input()) ||
		!AddAttribute(mpOctaves = AttributeFloat::Create("Octaves")
			.Input()) ||
		!AddAttribute(mpFrequency = AttributeFloat::Create("Frequency")
			.Input()) ||
		!AddAttribute(mpAmplitude = AttributeFloat::Create("Amplitude")
			.Input())
		)
		/* Do something with the error. */;

	if (
		!AddAttribute(mpValue = AttributeFloat::Create("Value")
			.Output())
		)
		/* Do something with the error. */;

	if (
		!AddDependency(mpValue, mpPoint) ||
		!AddDependency(mpValue, mpOctaves) ||
		!AddDependency(mpValue, mpFrequency) ||
		!AddDependency(mpValue, mpAmplitude)
		)
		/* Do something with the error. */;

	return true;
}

Result TestNode::operator()(const Plug& plug, DataBlock& dblock) const
{
	/*
	CPF_ASSERT(plug==mpValue);

	Vector2f point = dblock.GetInput(mpPoint).AsVector2f();
	int32_t octaves = dblock.GetInput(mpOctaves).AsInt();
	float frequency = dblock.GetInput(mpFrequency).AsFloat();
	float amplitude = dblock.GetInput(mpAmplitude).AsFloat();

	float result = 0.0f;
	dblock.GetOutput(mpValue).Set(result);
	dblock.SetClean(plug);
	*/

	return Error::eSuccess;
}
