//////////////////////////////////////////////////////////////////////////
#pragma once
#include "asio.hpp"
#include "MultiCore/iSystem.hpp"

namespace Cpf
{
	class NetworkSystem : public MultiCore::System
	{
	public:
		static constexpr MultiCore::SystemID kID = Hash::Create<MultiCore::SystemID_tag>("Network System"_hashString);

		static bool Install();
		static bool Remove();

		struct Desc : public System::Desc
		{};

	private:
		NetworkSystem(Plugin::iRegistry* rgy, MultiCore::iPipeline*, const char* name, const Desc*);
		static iSystem* _Creator(Plugin::iRegistry* rgy, MultiCore::iPipeline* owner, const char* name, const System::Desc* desc);

		static void _Update(Concurrency::ThreadContext&, void*);

		asio::io_service mASIO;
	};
}
