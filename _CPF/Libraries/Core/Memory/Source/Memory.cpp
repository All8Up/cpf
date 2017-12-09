//////////////////////////////////////////////////////////////////////////
#include <Memory/Memory.hpp>

using namespace CPF;

namespace
{
	int s_RefCount = 0;
	Allocator s_Default;
}


int MemoryInitializer::Install()
{
	return ++s_RefCount;
}


int MemoryInitializer::Remove()
{
	return --s_RefCount;
}


//////////////////////////////////////////////////////////////////////////
Allocator& Allocator::Default()
{
	return s_Default;
}

void* Allocator::Allocate(size_t size)
{
	return new uint8_t[size];
}

void Allocator::Deallocate(void* p)
{
	delete[] reinterpret_cast<uint8_t*>(p);
}
