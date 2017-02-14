//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IO/TextReader.hpp"

TEST(IO, TextReader)
{
	Cpf::IntrusivePtr<Cpf::Platform::IO::Stream> readStream(
		Cpf::Platform::IO::File::Create("TestTextFile.txt", Cpf::Platform::IO::StreamAccess::eRead)
			);
	Cpf::Platform::IO::TextReader reader(readStream);
}
