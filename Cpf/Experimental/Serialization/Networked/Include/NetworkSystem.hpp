//////////////////////////////////////////////////////////////////////////
#pragma once
#include "asio.hpp"
#include "MultiCore/System.hpp"

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
		NetworkSystem(MultiCore::iPipeline*, const char* name, const Desc*);
		static System* _Creator(MultiCore::iPipeline* owner, const char* name, const System::Desc* desc);

		static void _Update(Concurrency::ThreadContext&, void*);

		asio::io_service mASIO;
	};
}
