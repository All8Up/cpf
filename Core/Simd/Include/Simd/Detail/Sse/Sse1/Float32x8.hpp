//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Sse1
		{
			//////////////////////////////////////////////////////////////////////////
			struct Float32x8
			{
				struct CPF_ALIGN(32) ValueType
				{
					Float32x4_ValueType data[2];
				};

				static ValueType Load(const float* const data);
			};


			//////////////////////////////////////////////////////////////////////////
			inline Float32x8::ValueType Float32x8::Load(const float* const data)
			{
				ValueType result;
				for (int i = 0; i < 2; ++i)
					result.data[i] = Float32x4::Load(data + (i * 4));
				return result;
			}
		}
	}
}
