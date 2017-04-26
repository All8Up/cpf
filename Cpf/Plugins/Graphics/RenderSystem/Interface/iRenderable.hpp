//////////////////////////////////////////////////////////////////////////
#pragma once
#include "EntityService/Interfaces/iComponent.hpp"

namespace Cpf
{
	static constexpr COM::ClassID kRenderableCID = COM::ClassID("Cpf::iRenderable"_crc64);

	struct iRenderable : EntityService::iComponent
	{
		static constexpr COM::InterfaceID kIID = COM::InterfaceID("Cpf::iRenderable"_crc64);


	};
}
