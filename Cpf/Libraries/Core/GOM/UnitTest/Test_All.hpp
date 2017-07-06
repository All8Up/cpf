#include "GOM/Result.hpp"


TEST(GOM, Info)
{
	auto error = Cpf::GOM::GetError(Cpf::GOM::kOK);
	auto subsystem = Cpf::GOM::GetSubSystem(Cpf::GOM::kOK);
	auto code = Cpf::GOM::GetCode(Cpf::GOM::kOK);

	printf("Error: %d Subsystem: %d Code: %d", error, subsystem, code);
}
