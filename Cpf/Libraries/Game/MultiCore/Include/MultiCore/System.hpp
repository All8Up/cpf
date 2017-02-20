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
			using Creator = System* (*)(Pipeline*, const String&);

			// System factory.
			template <typename TYPE>
			static TYPE* Create(Pipeline*, const String&);
			static bool Install(SystemID id, Creator);
			static bool Remove(SystemID id);

			// System interface.
			Pipeline* GetOwner() const { return mpOwner; }
			Stage* GetStage(StageID id) const;
			Stage* GetStage(const String& name) const;

			const String& GetName() const;
			SystemID GetID() const;

			const StageVector& GetStages() const;

			virtual bool Configure() { return true; }

		protected:
			// Implementation interface.
			System(Pipeline* owner, const String& name);
			virtual ~System();

			bool AddStage(Stage*);
			bool RemoveStage(StageID);

		private:
			// Untyped factory interface.
			static System* _Create(SystemID, Pipeline*, const String&);

			// Implementation data.
			Pipeline* mpOwner;
			StageVector mStages;
			String mName;
			SystemID mID;
		};

		// Typed system factory.
		template <typename TYPE>
		TYPE* System::Create(Pipeline* pipeline, const String& name)
		{
			return static_cast<TYPE*>(_Create(TYPE::kID, pipeline, name));
		}
	}
}
