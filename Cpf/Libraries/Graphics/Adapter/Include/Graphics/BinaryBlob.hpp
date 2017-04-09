//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics.hpp"
#include "COM/iUnknown.hpp"
#include "Vector.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class BinaryBlob : public tRefCounted<iRefCounted>
		{
		public:
			static bool Create(size_t size, const void* data, BinaryBlob**);

			const void* GetData() const;
			size_t GetSize() const;

		private:
			BinaryBlob(size_t size, const void* data);
			~BinaryBlob();

			Vector<uint8_t> mData;
		};
	}
}
