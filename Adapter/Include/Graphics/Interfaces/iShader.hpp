//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"


namespace Cpf
{
	namespace Graphics
	{
		class BinaryBlob;

		class iDevice;

		enum class ShaderType : int32_t
		{
			eVertex,
			ePixel,
			eCompute,
			eDomain,
			eGeometry,
			eHull
		};

		class iShader : public iRefCounted
		{
		public:
			virtual ~iShader() = 0;

			virtual bool LoadFrom(iDevice* device, const BinaryBlob*) = 0;
		};
	}
}
