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

			using Creator = System* (*)(const String&, const Desc*, const SystemDependencies& deps);

			// System factory.
			template <typename TYPE>
			static TYPE* Create(const String&, const Desc* = nullptr, const SystemDependencies& dependencies = SystemDependencies());
			static bool Install(SystemID id, Creator);
			static bool Remove(SystemID id);

			// System interface.
			Pipeline* GetOwner() const { return mpOwner; }
			void SetOwner(Pipeline* pipeline) { mpOwner = pipeline; }
			Stage* GetStage(StageID id) const;

			const String& GetName() const;
			SystemID GetID() const;

			const StageVector& GetStages() const;

			void AddDependency(const SystemDependency& dependency) { mDependencies.push_back(dependency); }
			const SystemDependencies& GetSystemDependencies() const { return mDependencies; }
			virtual bool Configure() { return true; }

		protected:
			// Implementation interface.
			System(const String& name, const SystemDependencies& deps);
			virtual ~System();

			bool AddStage(Stage*);
			bool RemoveStage(StageID);

		private:
			// Untyped factory interface.
			static System* _Create(SystemID, const String&, const Desc* desc, const SystemDependencies& deps);

			// Implementation data.
			Pipeline* mpOwner;
			StageVector mStages;
			String mName;
			SystemID mID;
			SystemDependencies mDependencies;
		};

		// Typed system factory.
		template <typename TYPE>
		TYPE* System::Create(const String& name, const Desc* desc, const SystemDependencies& deps)
		{
			return static_cast<TYPE*>(_Create(TYPE::kID, name, desc, deps));
		}
	}
}
