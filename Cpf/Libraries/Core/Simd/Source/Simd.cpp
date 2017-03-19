//////////////////////////////////////////////////////////////////////////
#include <Simd/Simd.hpp>
#include <Simd/Types.hpp>


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Simd
	{
		namespace Reference
		{
			Int8x16::ValueType Int8x16::kZero = Int8x16::Create(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			Int8x16::ValueType Int8x16::kOne = Int8x16::Create(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

			const Float32x4::ValueType Float32x4::kZero = Float32x4::Create(0.0f, 0.0f, 0.0f, 0.0f);
			const Float32x4::ValueType Float32x4::kOne = Float32x4::Create(1.0f, 1.0f, 1.0f, 1.0f);
		}

#if CPF_SIMD_SSE1
		namespace Sse1
		{
			const Float32x4::ValueType Float32x4::kZero = Float32x4::Create(0.0f, 0.0f, 0.0f, 0.0f);
			const Float32x4::ValueType Float32x4::kOne = Float32x4::Create(1.0f, 1.0f, 1.0f, 1.0f);
		}
#endif

#if CPF_SIMD_SSE3
		namespace Sse2
		{
			Int8x16::ValueType Int8x16::kZero = Int8x16::Create(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			Int8x16::ValueType Int8x16::kOne = Int8x16::Create(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
		}
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
