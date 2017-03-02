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

			using Creator = System* (*)(Pipeline* owner, const char*, const Desc*);

			// System factory.
			template <typename TYPE>
			static TYPE* Create(Pipeline* owner, const char*, const Desc* = nullptr);
			static bool Install(SystemID id, Creator);
			static bool Remove(SystemID id);

			// System interface.
			Pipeline* GetOwner() const;
			Stage* GetStage(StageID id) const;

			SystemID GetID() const;

			const StageVector& GetStages() const;
			Instructions GetInstructions() const;

			void AddDependency(const BlockDependency& dependency);
			BlockDependencies GetDependencies() const;

			virtual bool Configure() { return true; }

		protected:
			// Implementation interface.
			System(Pipeline* owner, const char* name);
			virtual ~System();

			bool AddStage(Stage*);
			bool RemoveStage(StageID);

		private:
			// Untyped factory interface.
			static System* _Create(Pipeline* owner, SystemID, const char*, const Desc* desc);

			// Implementation data.
			Pipeline* mpOwner;
			StageVector mStages;
			SystemID mID;
			BlockDependencies mDependencies;
		};

		// Typed system factory.
		template <typename TYPE>
		TYPE* System::Create(Pipeline* owner, const char* name, const Desc* desc)
		{
			return static_cast<TYPE*>(_Create(owner, TYPE::kID, name, desc));
		}
	}
}
