//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration.hpp"
#include "Atomic.hpp"


#if CPF_TARGET_WINDOWS
#pragma warning(push)
#pragma warning(disable:4201)
#endif

namespace Cpf
{
	/**
	 * @brief The handle value is simply a wrapper around int64_t
	 * intended to prevent common errors when using handles.
	 * @todo Consider if this should be a base and a specialized
	 * version should exist in each handle pool.
	 */
	class HandleValue
	{
	public:
		static const int64_t kInvalid = int64_t(-1);

		HandleValue();
		HandleValue(const HandleValue& rhs);
		HandleValue(HandleValue&& rhs);
		explicit HandleValue(int64_t value);

		explicit operator int64_t() const;

		HandleValue& operator = (const HandleValue& rhs);
		HandleValue& operator = (HandleValue&& rhs);

		bool operator ==(const HandleValue& rhs) const;
		bool operator !=(const HandleValue& rhs) const;
		bool operator <(const HandleValue& rhs) const;

	private:
		int64_t mHandle;
	};

	//////////////////////////////////////////////////////////////////////////
	inline
	HandleValue::HandleValue()
	: mHandle(kInvalid)
	{}
	inline
	HandleValue::HandleValue(const HandleValue& rhs)
	: mHandle(rhs.mHandle)
	{}
	inline
	HandleValue::HandleValue(HandleValue&& rhs)
	: mHandle(rhs.mHandle)
	{
		rhs.mHandle = kInvalid;
	}
	inline
	HandleValue::HandleValue(int64_t value)
	: mHandle(value)
	{}

	inline
	HandleValue::operator int64_t() const
	{
		return mHandle;
	}

	inline
	HandleValue& HandleValue::operator = (const HandleValue& rhs)
	{
		mHandle = rhs.mHandle;
		return *this;
	}

	inline
	HandleValue& HandleValue::operator = (HandleValue&& rhs)
	{
		mHandle = rhs.mHandle;
		rhs.mHandle = kInvalid;
		return *this;
	}

	inline
	bool HandleValue::operator ==(const HandleValue& rhs) const
	{
		return mHandle==rhs.mHandle;
	}

	inline
	bool HandleValue::operator !=(const HandleValue& rhs) const
	{
		return mHandle!=rhs.mHandle;
	}

	inline
	bool HandleValue::operator <(const HandleValue& rhs) const
	{
		return mHandle < rhs.mHandle;
	}


	/**
	 * @brief Pool of typed handles.
	 * @tparam DATATYPE   Type of the pointer to manage.
	 * @tparam MAXHANDLES The maximum number of handles in this manager.
	 */
	template<typename DATATYPE, const int MAXHANDLES=1024>
	class CPF_ALIGN(16) HandlePool
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		HandlePool();
		~HandlePool();

		HandleValue Alloc(DATATYPE* data);
		void Free(HandleValue handle);
		DATATYPE* Get(const HandleValue& handle) const;
		void Set(HandleValue handle, DATATYPE* value);

	private:
		/** @brief A union to manipulate handle values. */
		union alignas(8) HandleUnion
		{
			HandleUnion(int64_t data) : mInt64(data) {}

			struct
			{
				int32_t mIndex;
				int32_t mVersion;
			};
			int64_t mInt64;
		};
		static_assert(sizeof(HandleUnion) == sizeof(int64_t), "Incorrect size.");

		/** @brief Storage for a handle. */
		union alignas(16) HandleData
		{
			struct
			{
				DATATYPE* mpData;
				intptr_t mVersion;
			};
			Atomic::IntPtrPair_t mPair;
		};
		static_assert(sizeof(HandleData) == 16, "Incorrect size.");

		HandleData mData[MAXHANDLES];
		intptr_t mFirstFree;
		intptr_t mCurrentVersion;
	};


	//////////////////////////////////////////////////////////////////////////
	/**
	 * @brief Default constructor.
	 * @tparam DATATYPE Type of the pointers being stored.
	 * @tparam MAXHANDLES The maximum number of handles the manager can handle..
	 */
	template<typename DATATYPE, const int MAXHANDLES>
	inline HandlePool<DATATYPE, MAXHANDLES>::HandlePool()
	{
		for (int i=0; i<MAXHANDLES; ++i)
		{
			// When mpData is null, the version indicates
			// the index of the next free slot.
			mData[i].mpData = nullptr;
			if (i!=MAXHANDLES-1)
				mData[i].mVersion = i+1;
			else
				mData[i].mVersion = -1;
		}
		mFirstFree = 0;
		mCurrentVersion = 0;
	}

	/**
	 * @brief Destructor.
	 * @tparam DATATYPE Type of the pointers being stored.
	 * @tparam MAXHANDLES The maximum number of handles the manager can handle..
	 */
	template<typename DATATYPE, const int MAXHANDLES>
	inline HandlePool<DATATYPE, MAXHANDLES>::~HandlePool()
	{}

	/**
	 * @brief Allocates a handle slot.
	 * @tparam DATATYPE Type of the pointers being stored.
	 * @tparam MAXHANDLES The maximum number of handles the manager can handle..
	 * @param [in,out] data The initial pointer value of the slot.
	 * @return A handle to the mangaed pointer.
	 */
	template<typename DATATYPE, const int MAXHANDLES>
	inline HandleValue HandlePool<DATATYPE, MAXHANDLES>::Alloc(DATATYPE* data)
	{
		HandleUnion result(HandleValue::kInvalid);
		intptr_t firstFree;

		while ((firstFree = Atomic::Load(mFirstFree)) >= 0)
		{
			// Attempt to take an entry.
			if (Atomic::CompareExchange(mFirstFree, Atomic::Load(mData[firstFree].mVersion), firstFree))
			{
				// Fill in the entry.
				HandleData target;
				target.mpData = data;
				target.mVersion = Atomic::Inc(mCurrentVersion);

				CPF_ASSERT(intptr_t(&mData[firstFree].mPair) % 16 == 0);
				CPF_ASSERT(intptr_t(&target.mPair) % 16 == 0);
				Atomic::Store(mData[firstFree].mPair, target.mPair);

				// Fill in the result.
				result.mIndex = int(firstFree);
				result.mVersion = int(mData[firstFree].mVersion);

				break;
			}
		}
		return HandleValue(result.mInt64);
	}

	/**
	 * @brief Frees the given handle.
	 * @tparam DATATYPE Type of the pointers being stored.
	 * @tparam MAXHANDLES The maximum number of handles the manager can handle..
	 * @param handle The handle.
	 */
	template<typename DATATYPE, const int MAXHANDLES>
	inline void HandlePool<DATATYPE, MAXHANDLES>::Free(HandleValue handle)
	{
		HandleUnion data(static_cast<int64_t>(handle));
		Atomic::IntPtrPair_t& target = mData[data.mIndex].mPair;
		intptr_t firstFree;
		do
		{
			firstFree = Atomic::Load(mFirstFree);

			HandleData src;
			src.mpData = nullptr;
			src.mVersion = firstFree;

			Atomic::Store(target, src.mPair);
		} while (!Atomic::CompareExchange(mFirstFree, data.mIndex, firstFree));
	}

	/**
	 * @brief Gets the pointer from a handle.
	 * @tparam DATATYPE Type of the pointers being stored.
	 * @tparam MAXHANDLES The maximum number of handles the manager can handle..
	 * @param handle The handle.
	 * @return null if it fails, else a DATATYPE*.
	 */
	template<typename DATATYPE, const int MAXHANDLES>
	inline DATATYPE* HandlePool<DATATYPE, MAXHANDLES>::Get(const HandleValue& handle) const
	{
		// NOTE: While alloc is safe to be called concurrently with this,
		// free's should not be called while others may be attempting to
		// access the data.  A race condition which could seemingly pass here
		// would end up with an invalid pointer in the calling code.
		HandleUnion hdl(static_cast<int64_t>(handle));
		HandleData data;
		data.mPair = Atomic::Load(mData[hdl.mIndex].mPair);
		if (data.mVersion == hdl.mVersion)
			return data.mpData;
		return nullptr;
	}

	/**
	 * @brief Sets the value of a handle.  NOTE: This should only be used if no other system can be accessing the handle concurrently.
	 * @tparam DATATYPE   Type of the datatype.
	 * @tparam MAXHANDLES Type of the maxhandles.
	 * @param handle		 The handle.
	 * @param [in,out] value If non-null, the value.
	 */
	template<typename DATATYPE, const int MAXHANDLES>
	inline void HandlePool<DATATYPE, MAXHANDLES>::Set(HandleValue handle, DATATYPE* value)
	{
		HandleUnion hdl(static_cast<int64_t>(handle));
		HandleData data;
		data.mPair = Atomic::Load(mData[hdl.mIndex].mPair);
		if (data.mVersion == hdl.mVersion)
			mData[hdl.mIndex].mpData = value;
	}
}


#if CPF_TARGET_WINDOWS
#pragma warning(pop)
#endif
