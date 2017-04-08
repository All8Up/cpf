//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RefCounted.hpp"


namespace Cpf
{
	namespace Graphics
	{
		struct iDevice;

		class BinaryBlob;
		enum class ShaderType : int32_t;

		class iShader : public iRefCounted
		{
		public:
			virtual ~iShader() = 0;

			virtual bool LoadFrom(iDevice* device, const BinaryBlob*) = 0;
		};
	}
}
