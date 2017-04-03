//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "MultiCore/Export.hpp"
#include "MultiCore/Types.hpp"
#include "Plugin/iRegistry.hpp"
#include "RefCounted.hpp"
#include "String.hpp"


namespace Cpf
{
	namespace MultiCore
	{
		struct iSystem : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iSystem"_crc64);
			// Empty base class for system descriptors.
			struct Desc
			{};

			virtual COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, iPipeline* owner, const char* name) = 0;
			virtual iPipeline* CPF_STDCALL GetOwner() const = 0;
			virtual COM::Result CPF_STDCALL GetStage(StageID id, iStage** outStage) const = 0;
			virtual SystemID CPF_STDCALL GetID() const = 0;
			virtual int32_t CPF_STDCALL GetStageCount() const = 0;
			virtual iStage* CPF_STDCALL GetStage(int32_t index) = 0;
			virtual COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) = 0;
			virtual void CPF_STDCALL AddDependency(BlockDependency dep) = 0;
			virtual COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) = 0;
			virtual COM::Result CPF_STDCALL Configure() = 0;
		};

		class System : public tRefCounted<iSystem>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface);

			COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, iPipeline* owner, const char* name) override;
			iPipeline* CPF_STDCALL GetOwner() const override;
			COM::Result CPF_STDCALL GetStage(StageID id, iStage** outStage) const;
			SystemID CPF_STDCALL GetID() const override;
			int32_t CPF_STDCALL GetStageCount() const override { return int32_t(mStages.size()); }
			iStage* CPF_STDCALL GetStage(int32_t index) override { return mStages[index]; }
			COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*);
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) override;
			COM::Result CPF_STDCALL Configure() { return COM::kOK; }


			using Creator = iSystem* (*)(Plugin::iRegistry*, iPipeline* owner, const char*, const Desc*);

			// System factory.
			template <typename TYPE>
			static TYPE* Create(Plugin::iRegistry*, iPipeline* owner, const char*, const Desc* = nullptr);
			static bool Install(SystemID id, Creator);
			static bool Remove(SystemID id);

		protected:
			// Implementation interface.
			System();
			virtual ~System();

			bool AddStage(iStage*);
			bool RemoveStage(StageID);

		private:
			// Untyped factory interface.
			static iSystem* _Create(Plugin::iRegistry*, iPipeline* owner, SystemID, const char*, const Desc* desc);

			// Implementation data.
			iPipeline* mpOwner;
			StageVector mStages;
			SystemID mID;
			BlockDependencies mDependencies;
		};

		// Typed system factory.
		template <typename TYPE>
		TYPE* System::Create(Plugin::iRegistry* rgy, iPipeline* owner, const char* name, const Desc* desc)
		{
			return static_cast<TYPE*>(_Create(rgy, owner, TYPE::kID, name, desc));
		}
	}
}
