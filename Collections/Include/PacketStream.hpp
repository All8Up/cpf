//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Tuple.hpp"
#include "Vector.hpp"


namespace Cpf
{
	template<typename Index>
	struct PacketRef
	{
		PacketRef(const uint8_t* memBlock) : mpPacket(memBlock) {}

		Index TypeIndex() const
		{
			return *reinterpret_cast<const Index*>(mpPacket);
		}
		template<typename TYPE>
		const TYPE& As() { return *reinterpret_cast<const TYPE*>(_GetPayload()); }
		const void* Payload() const { return mpPacket + sizeof(Index); }

	private:
		const uint8_t* _GetPayload() const { return mpPacket + sizeof(Index); }

		const uint8_t* mpPacket;
	};

	/*
	*/
	template <typename T, typename TupleType>
	struct TupleIndex;

	template <typename T, typename... Types>
	struct TupleIndex<T, Tuple<T, Types...>>
	{
		static constexpr size_t value = 0;
	};

	template <typename T, typename U, typename... Types>
	struct TupleIndex<T, Tuple<U, Types...>>
	{
		static constexpr size_t value = 1 + TupleIndex<T, Tuple<Types...>>::value;
	};

	///
	template<typename... ARGS>
	struct PacketCallable
	{
		using FunctionType = void (*)(const void*, ARGS...);

		template<typename TYPE>
		static void Callable(const void* packet, ARGS... args)
		{
			(*reinterpret_cast<const TYPE*>(packet))(args...);
		}
	};


	///
	template<const int INDEX, typename TYPETUPLE, typename PacketCallable, typename PacketCallable::FunctionType... FUNCS>
	struct PacketCallableArray;

	template<typename TYPETUPLE, typename PacketCallable, typename PacketCallable::FunctionType... FUNCS>
	struct PacketCallableArray<0, TYPETUPLE, PacketCallable, FUNCS...>
	{
		using VC15Workaround = void(*)(const void*, Tuple<>);
		static constexpr VC15Workaround Functions[TupleSize<TYPETUPLE>::value] = {FUNCS...};
	};
	template<typename TYPETUPLE, typename PacketCallable, typename PacketCallable::FunctionType... FUNCS>
	constexpr typename PacketCallableArray<0, TYPETUPLE, PacketCallable, FUNCS...>::VC15Workaround PacketCallableArray<0, TYPETUPLE, PacketCallable, FUNCS...>::Functions[TupleSize<TYPETUPLE>::value];

	template<const int INDEX, typename TYPETUPLE, typename PacketCallable, typename PacketCallable::FunctionType... FUNCS>
	struct PacketCallableArray
		: PacketCallableArray<
			INDEX-1,
			TYPETUPLE,
			PacketCallable,
			&PacketCallable::template Callable<typename TupleElement<INDEX-1, TYPETUPLE>::type>,
			FUNCS...>
	{};

	///
	template<const int INDEX, typename TYPETUPLE, size_t... SIZES>
	struct PacketSizeArray;

	template<typename TYPETUPLE, size_t... SIZES>
	struct PacketSizeArray<0, TYPETUPLE, SIZES...>
	{
		static constexpr size_t Sizes[TupleSize<TYPETUPLE>::value] = {SIZES...};
	};

	template<const int INDEX, typename TYPETUPLE, size_t... SIZES>
	struct PacketSizeArray :
		PacketSizeArray<INDEX-1, TYPETUPLE, sizeof(typename TupleElement<INDEX-1, TYPETUPLE>::type), SIZES...>
	{};


	///
	template<typename CallableType, typename... TYPES>
	struct PacketTypes
	{
		static constexpr size_t kTypeCount = sizeof...(TYPES);
		using TypeTuple = Tuple<TYPES...>;
		using SizeArray = PacketSizeArray<TupleSize<TypeTuple>::value, TypeTuple>;
		using CallableArray = PacketCallableArray<kTypeCount, Tuple<TYPES...>, CallableType>;

		template<typename TYPE>
		static constexpr size_t IndexOf()
		{
			return TupleIndex<TYPE, TypeTuple>::value;
		}

		template<typename TYPE>
		static constexpr size_t SizeOf()
		{
			return SizeArray::Sizes[IndexOf<TYPE>()];
		}

		static constexpr size_t SizeOf(size_t index)
		{
			return SizeArray::Sizes[index];
		}

		template<typename... ARGS>
		static void Call(size_t typeIndex, const void* target, ARGS... args)
		{
			(*CallableArray::Functions[typeIndex])(target, args...);
		}
	};


	template<typename T, typename PacketTypes>
	class Packet
	{
	public:
		using TypeList = typename PacketTypes::TypeTuple;
		static constexpr size_t TypeIndex()
		{
			return size_t(TupleIndex<T, TypeList>::value);
		}

		Packet(const T& rhs) : mData(rhs) {}

		const T& Data() const { return mData; }

	private:
		T mData;
	};


	template<typename PacketTypeList, typename Backing=Vector<uint8_t>>
	class PacketStream
	{
	public:
		using TypeList = PacketTypeList;
		using PacketTypes = typename PacketTypeList::TypeTuple;
		using PacketRef = PacketRef<size_t>;

		struct const_iterator
		{
			const_iterator(const uint8_t* data) : mpData(data) {}
			const_iterator(const const_iterator& rhs) : mpData(rhs.mpData) {}
			const_iterator(const_iterator&& rhs) noexcept : mpData(rhs.mpData) {}

			const_iterator& operator = (const const_iterator& rhs) { mpData = rhs.mpData; return *this; }
			const_iterator& operator = (const_iterator&& rhs) noexcept { mpData = rhs.mpData; return *this; }

			bool operator ==(const const_iterator& rhs) const { return mpData == rhs.mpData; }
			bool operator !=(const const_iterator& rhs) const { return mpData != rhs.mpData; }

			const_iterator operator +(const size_t offset) const
			{
				return const_iterator(mpData + offset);
			}

			const_iterator& operator ++()
			{
				PacketRef packet(mpData);
				size_t offset = sizeof(size_t) + PacketTypeList::SizeOf(packet.TypeIndex());
				mpData += offset;
				return *this;
			}
			PacketRef operator *() const { return PacketRef(mpData); }

		private:
			const uint8_t* mpData;
		};

		template<typename TYPE>
		static constexpr int TypeOf() { return 0; }

		PacketStream() {}

		const_iterator begin() const { return const_iterator(mData.begin()); }
		const_iterator end() const { return const_iterator(mData.end()); }

		template<typename TYPE>
		void Insert(const TYPE& packet)
		{
			size_t index = packet.TypeIndex();
			mData.insert(mData.end(), reinterpret_cast<const uint8_t*>(&index), reinterpret_cast<const uint8_t*>(&index) + sizeof(size_t));
			mData.insert(mData.end(), reinterpret_cast<const uint8_t*>(&packet), reinterpret_cast<const uint8_t*>(&packet) + sizeof(TYPE));
		}

	private:
		Backing mData;
	};

	template<typename PacketStreamType, typename PacketType>
	PacketStreamType& operator << (PacketStreamType& ps, const PacketType& rhs)
	{
		ps.template Insert<PacketType>(rhs);
		return ps;
	}
}
