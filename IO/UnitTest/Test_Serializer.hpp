//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IO/Serializer.hpp"
#include "IO/JsonArchive.hpp"

namespace TestSerialize
{
	struct TestObject
	{
		int mTest0;
		bool mTest1;
		Cpf::String mTest2;
		int64_t mTest3;
	};
}

namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			template<typename ARCHIVE>
			void Serialize(ARCHIVE& ar, TestSerialize::TestObject& o, int version)
			{
				ar & o.mTest0;
				ar & o.mTest1;
				ar & o.mTest2;
				ar & o.mTest3;
			}
		}
	}
}

TEST(IO, Serialize)
{
	{
		TestSerialize::TestObject testObject
		{
			1, true, "Blargo", 2
		};

		Cpf::IntrusivePtr<Cpf::Platform::IO::Stream> outStream(
			Cpf::Platform::IO::File::Create("testArchive.ta", Cpf::Platform::IO::StreamAccess::eWrite));

		Cpf::Platform::IO::JsonArchive archive(outStream, 1);
		/*
		archive & Version(1);
		archive & testObject;
		*/
	}
	{
		TestSerialize::TestObject testObject;
		Cpf::IntrusivePtr<Cpf::Platform::IO::Stream> inStream(
			Cpf::Platform::IO::File::Create("testArchive.ta", Cpf::Platform::IO::StreamAccess::eRead));

		Cpf::Platform::IO::JsonArchive archive(inStream, 1);
		/*
		archive & Version(1);
		archive & testObject;
		 */
	}
}
