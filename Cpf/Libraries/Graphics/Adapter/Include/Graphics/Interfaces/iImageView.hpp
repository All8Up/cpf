//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics/Interfaces/iImage.hpp"

namespace Cpf
{
	namespace Graphics
	{
		class iImageView : public iRefCounted
		{
		public:
			virtual ~iImageView() = 0;
		};
	}
}
