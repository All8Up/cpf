//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////
#include <Configuration.hpp>
#include <stdlib.h>


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_MEMORY
#		define CPF_EXPORT_MEMORY
#	else // CPF_STATIC_MEMORY
#		if CPF_BUILD_MEMORY
#			define CPF_EXPORT_MEMORY CPF_EXPORT
#		else
#			define CPF_EXPORT_MEMORY CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_MEMORY CPF_EXPORT
#	else
#		define CPF_EXPORT_MEMORY
#	endif
#endif // CPF_TARGET_WINDOWS


//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	struct MemoryInitializer
	{
		CPF_EXPORT_MEMORY static int Install();
		CPF_EXPORT_MEMORY static int Remove();

	private:
		MemoryInitializer() = delete;
		~MemoryInitializer() = delete;
	};
}


namespace CPF
{
	/** @brief The generic global allocator. */
	class CPF_EXPORT_MEMORY Allocator
	{
	public:
		static Allocator& Default();

		void* Allocate(size_t size);
		template< typename T >
		T* Allocate(size_t n);
		void Deallocate(void*);

	private:
	};

	/**
	 * @brief Allocates memory as a specific type.
	 * @tparam T The type of pointer to return.
	 * @param n The number of T's to allocate for.
	 * @return null if it fails, else a T*.
	 */
	template< typename T > inline
	T* Allocator::Allocate(size_t n)
	{
		return reinterpret_cast<T*>( Allocator::Allocate(sizeof(T)*n) );
	}


	/**
	 * @brief Aligned malloc.
	 * @param size	    The size.
	 * @param alignment The alignment.
	 * @return null if it fails, else a void*.
	 */
	inline void* AlignedMalloc(size_t size, size_t alignment)
	{
#if CPF_TARGET_WINDOWS
		return _aligned_malloc(size, alignment);
#elif CPF_TARGET_DARWIN
		// TODO: Only getting 16byte alignment here!
		return malloc(size);
#elif CPF_TARGET_LINUX
        return aligned_alloc(alignment, size);
#else
		static_assert(false, "Unknown aligned malloc environment.");
#endif
	}


	inline void AlignedFree(void* ptr)
	{
#if CPF_TARGET_WINDOWS
		_aligned_free(ptr);
#elif CPF_TARGET_DARWIN
		free(ptr);
#else
		static_assert(false, "Unknown aligned malloc environment.");
#endif
	}
}


#if CPF_TARGET_WINDOWS
#	define CPF_ALIGNED_OBJECT(T)									\
	static void* operator new(std::size_t size) {					\
		void* result = Cpf::AlignedMalloc(size, alignof(T));		\
		return result; }											\
	static void operator delete(void* ptr) {						\
		Cpf::AlignedFree(ptr); }
#elif CPF_TARGET_DARWIN
#	define CPF_ALIGNED_OBJECT(T)
#else
	static_assert(false, "Unknown aligned malloc environment.");
#endif
