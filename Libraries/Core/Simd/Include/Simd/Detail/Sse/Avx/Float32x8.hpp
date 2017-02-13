//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Avx
		{
			struct Float32x8
			{
				typedef Float32x8_ValueType ValueType;
				typedef ValueType ConstRef;

				static ValueType Load(const float* const data)
				{
					return _mm256_load_ps(data);
				}
			};
		}
	}
}
