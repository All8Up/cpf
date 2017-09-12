#include "GOM/ResultCodes.hpp"


TEST(GOM, Info)
{
	auto error = CPF::GOM::GetError(CPF::GOM::kOK);
	auto subsystem = CPF::GOM::GetSubSystem(CPF::GOM::kOK);
	auto code = CPF::GOM::GetCode(CPF::GOM::kOK);

	printf("Error: %d Subsystem: %d Code: %d", error, subsystem, code);
}
