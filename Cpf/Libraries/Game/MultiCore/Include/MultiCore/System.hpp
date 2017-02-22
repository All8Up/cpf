//////////////////////////////////////////////////////////////////////////
#pragma once
#include "MultiCore/Types.hpp"
#include "RefCounted.hpp"
#include "String.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		class System : public tRefCounted<iRefCounted>
		{
		public:
			// Empty base class for system descriptors.
			struct Desc
			{};

			using Creator = System* (*)(const String&, const Desc*);

			// System factory.
			template <typename TYPE>
			static TYPE* Create(const String&, const Desc* = nullptr);
			static bool Install(SystemID id, Creator);
			static bool Remove(SystemID id);

			// System interface.
			Pipeline* GetOwner() const { return mpOwner; }
			void SetOwner(Pipeline* pipeline) { mpOwner = pipeline; }
			Stage* GetStage(StageID id) const;

			const String& GetName() const;
			SystemID GetID() const;

			const StageVector& GetStages() const;

			virtual bool Configure() { return true; }

		protected:
			// Implementation interface.
			System(const String& name);
			virtual ~System();

			bool AddStage(Stage*);
			bool RemoveStage(StageID);

		private:
			// Untyped factory interface.
			static System* _Create(SystemID, const String&, const Desc* desc);

			// Implementation data.
			Pipeline* mpOwner;
			StageVector mStages;
			String mName;
			SystemID mID;
		};

		// Typed system factory.
		template <typename TYPE>
		TYPE* System::Create(const String& name, const Desc* desc)
		{
			return static_cast<TYPE*>(_Create(TYPE::kID, name, desc));
		}
	}
}
