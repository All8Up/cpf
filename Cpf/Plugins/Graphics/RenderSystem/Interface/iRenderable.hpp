//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/iComponent.hpp"

namespace Cpf
{
	static constexpr GOM::ClassID kRenderableCID = GOM::ClassID("Cpf::iRenderable"_crc64);

	struct iRenderable : EntityService::iComponent
	{
		static constexpr GOM::InterfaceID kIID = GOM::InterfaceID("Cpf::iRenderable"_crc64);


	};
}
