//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Configuration/Configuration.hpp"


//////////////////////////////////////////////////////////////////////////
#ifdef CPF_TARGET_WINDOWS
#	ifdef CPF_STATIC_ATTRIBUTES
#		define CPF_EXPORT_ATTRIBUTES
#	else // CPF_STATIC_ATTRIBUTES
#		if CPF_BUILD_ATTRIBUTES
#			define CPF_EXPORT_ATTRIBUTES CPF_EXPORT
#		else
#			define CPF_EXPORT_ATTRIBUTES CPF_IMPORT
#		endif
#	endif
#else // CPF_TARGET_WINDOWS
#	if __GNUC__ >= 4
#		define CPF_EXPORT_ATTRIBUTES CPF_EXPORT
#	else
#		define CPF_EXPORT_ATTRIBUTES
#	endif
#endif // CPF_TARGET_WINDOWS


#include "Vector.hpp"
#include "String.hpp"
#include "Math/Math.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector3v.hpp"
#include "Math/Vector4v.hpp"
#include "Math/Color.hpp"
#include "Math/Matrix33v.hpp"
#include "Math/Matrix44v.hpp"
//#include "Math/Quaternion.hpp"
namespace Cpf
{
	// TODO: Needs to be moved to the application layer.
	namespace Platform
	{
		//////////////////////////////////////////////////////////////////////////
		struct AttributesInitializer
		{
			CPF_EXPORT_ATTRIBUTES static int Install();
			CPF_EXPORT_ATTRIBUTES static int Remove();

		private:
			AttributesInitializer() = delete;
			~AttributesInitializer() = delete;
		};


		//////////////////////////////////////////////////////////////////////////
		enum class AttributeType : uint32_t
		{
			eUnknown = 0,
			eBool,
			eUint,
			eInt,
			eFloat,
			eString,
			eVector2i,
			eVector2f,
			eVector3i,
			eVector3f,
			eVector4f,
			eColor3f,
			eColor4f,
			eQuaternionf,
			eMatrix33f,
			eMatrix44f
		};

		//////////////////////////////////////////////////////////////////////////
		enum class AttributeDirection : uint32_t
		{
			eUnknown = 0,
			eInput,
			eOutput
		};

		//////////////////////////////////////////////////////////////////////////
		struct AttributeValue
		{
			AttributeType mType : 5;
			bool mIsVector : 1;
			union Value
			{
				Value() {}
				~Value() {}

				bool mBool;
				int64_t mInt;
				uint64_t mUint;
				float mFloat;
				String mString;
				Math::Vector2i mVector2i;
				Math::Vector2f mVector2f;
				Math::Vector3i mVector3i;
				Math::Vector3fv mVector3f;
				Math::Vector4fv mVector4f;
				Math::Color3f mColor3f;
				Math::Color4f mColor4f;
//				Math::Quaternionf mQuaternionf;
				Math::Matrix33fv mMatrix33f;
				Math::Matrix44fv mMatrix44f;
			} mValue;
			Vector<Value> mVector;
		};

		//////////////////////////////////////////////////////////////////////////
		enum class Error : uint32_t
		{
			eSuccess = 0
		};
		class Result
		{
		public:
			Result() : mError(Error::eSuccess) {}
			Result(Error err) : mError(err) {}

			operator bool() const {return mError!=Error::eSuccess;}

			void SetError(Error err) {mError = err;}

		private:
			Error mError;
		};

		//////////////////////////////////////////////////////////////////////////
		class Plug
		{
		public:
		};

		//////////////////////////////////////////////////////////////////////////
		class DataBlock
		{
		public:
		};

		//////////////////////////////////////////////////////////////////////////
		class Attribute;
		class Node
		{
		public:
			Node();
			virtual ~Node();

			virtual bool Initialize() = 0;
			virtual Result operator()(const Plug&, DataBlock&) const = 0;

			Result AddAttribute(Attribute* attr) {mAttributes.push_back(attr); return Error::eSuccess;}
			const Vector<Attribute*>& GetAttributes() const {return mAttributes;}
			Result AddDependency(Attribute*, Attribute*) {return Error::eSuccess;}

		protected:
			size_t GetDataBlockSize() const {return 0;}

		private:
			Vector<Attribute*> mAttributes;
		};

		//////////////////////////////////////////////////////////////////////////
		class Attribute
		{
		public:
			//
			template<typename TYPE>
			class BuilderBase
			{
			public:
				BuilderBase(const char* const name)
					: mpName(name)
					, mDirection(AttributeDirection::eUnknown)
				{}

				TYPE& Input() {mDirection = AttributeDirection::eInput; return *static_cast<TYPE*>(this);}
				TYPE& Output() {mDirection = AttributeDirection::eOutput; return *static_cast<TYPE*>(this);}

			protected:
				const char* const mpName;
				AttributeDirection mDirection;
			};

			//
			Attribute()
				: mType(AttributeType::eUnknown)
				, mpName(nullptr)
				, mDirection(AttributeDirection::eUnknown) {}
			Attribute(AttributeType type, const char* const name, AttributeDirection dir)
				: mType(type)
				, mpName(name)
				, mDirection(dir)
			{}
			~Attribute() {}

			AttributeType GetType() const {return mType;}
			const char* const GetName() const {return mpName;}
			AttributeDirection GetDirection() const {return mDirection;}

			size_t GetAttributeSize() const {return 0;}
			size_t GetAttributeAlignment() const {return 0;}

		private:
			//
			AttributeType mType;
			const char* const mpName;
			AttributeDirection mDirection;
		};

		//////////////////////////////////////////////////////////////////////////
		class AttributeVector2f : public Attribute
		{
		public:
			class Builder : public Attribute::BuilderBase<Builder>
			{
			public:
				Builder(const char* const name) : Attribute::BuilderBase<Builder>(name) {}
				operator Attribute* () {return new AttributeVector2f(mpName, mDirection);}
			};

			AttributeVector2f(const char* const name, AttributeDirection dir)
				: Attribute(AttributeType::eVector2f, name, dir)
			{}

			static Builder Create(const char* const name) {return Builder(name);}
		};

		//////////////////////////////////////////////////////////////////////////
		class AttributeFloat : public Attribute
		{
		public:
			class Builder : public Attribute::BuilderBase<Builder>
			{
			public:
				Builder(const char* const name) : Attribute::BuilderBase<Builder>(name) {}
				operator Attribute* () {return new AttributeFloat(mpName, mDirection);}
			};

			AttributeFloat(const char* const name, AttributeDirection dir)
				: Attribute(AttributeType::eVector2f, name, dir)
			{}

			static Builder Create(const char* const name) {return Builder(name);}
		};

		//////////////////////////////////////////////////////////////////////////
		class TestNode : public Node
		{
		public:
			static Node* Create();

			bool Initialize() override;
			Result operator()(const Plug&, DataBlock&) const override;

		private:
			static Attribute* mpPoint;
			static Attribute* mpOctaves;
			static Attribute* mpFrequency;
			static Attribute* mpAmplitude;
			static Attribute* mpValue;
		};
	}
}
