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
		static constexpr COM::ClassID kStageListCID = COM::ClassID("StageListClass"_crc64);

		struct iStageList : COM::iUnknown
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iStageList"_crc64);

			virtual COM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const = 0;
			virtual COM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const = 0;
			virtual void CPF_STDCALL AddDependency(BlockDependency dep) = 0;
			virtual COM::Result CPF_STDCALL AddStage(iStage* stage) = 0;
			virtual COM::Result CPF_STDCALL RemoveStage(StageID id) = 0;
		};

		struct iSystem : iStageList
		{
			static constexpr COM::InterfaceID kIID = COM::InterfaceID("iSystem"_crc64);
			// Empty base class for system descriptors.
			struct Desc
			{};

			virtual COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, iPipeline* owner, const char* name) = 0;
			virtual iPipeline* CPF_STDCALL GetOwner() const = 0;
			virtual SystemID CPF_STDCALL GetID() const = 0;
			virtual COM::Result CPF_STDCALL Configure() = 0;

			virtual COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) = 0;
			virtual COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) = 0;

			//////////////////////////////////////////////////////////////////////////
			// System factory.
			using Creator = iSystem* (*)(Plugin::iRegistry*, iPipeline* owner, const char*, const Desc*);

			template <typename TYPE>
			static TYPE* Create(Plugin::iRegistry*, iPipeline* owner, const char*, const Desc* = nullptr);
			static bool Install(SystemID id, Creator);
			static bool Remove(SystemID id);

			// Untyped factory interface.
			static iSystem* _Create(Plugin::iRegistry*, iPipeline* owner, SystemID, const char*, const Desc* desc);
		};

		// Typed system factory.
		template <typename TYPE>
		TYPE* iSystem::Create(Plugin::iRegistry* rgy, iPipeline* owner, const char* name, const Desc* desc)
		{
			return static_cast<TYPE*>(_Create(rgy, owner, TYPE::kID, name, desc));
		}

		class System : public tRefCounted<iSystem>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface);

			COM::Result CPF_STDCALL Initialize(Plugin::iRegistry* rgy, iPipeline* owner, const char* name) override;
			iPipeline* CPF_STDCALL GetOwner() const override;
			SystemID CPF_STDCALL GetID() const override;
			COM::Result CPF_STDCALL Configure() override { return COM::kOK; }

			COM::Result CPF_STDCALL FindStage(StageID id, iStage** outStage) const override;
			COM::Result CPF_STDCALL GetStages(int32_t* count, iStage** outStages) const override;
			COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) override;
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) override;

			COM::Result CPF_STDCALL AddStage(iStage*) override;
			COM::Result CPF_STDCALL RemoveStage(StageID) override;

		protected:
			// Implementation interface.
			System();
			virtual ~System();

		private:
			// Implementation data.
			iPipeline* mpOwner;
			StageVector mStages;
			SystemID mID;
			BlockDependencies mDependencies;
		};
	}
}
