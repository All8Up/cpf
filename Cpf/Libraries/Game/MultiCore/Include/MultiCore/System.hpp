//////////////////////////////////////////////////////////////////////////
#pragma once
#include "COM/iUnknown.hpp"
#include "MultiCore/Export.hpp"
#include "MultiCore/Types.hpp"
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

			virtual COM::Result CPF_STDCALL Initialize(iPipeline* owner, const char* name) = 0;
			virtual iPipeline* CPF_STDCALL GetOwner() const = 0;
			virtual COM::Result CPF_STDCALL GetStage(StageID id, Stage** outStage) const = 0;
			virtual SystemID CPF_STDCALL GetID() const = 0;
			virtual int32_t CPF_STDCALL GetStageCount() const = 0;
			virtual Stage* CPF_STDCALL GetStage(int32_t index) = 0;
			virtual COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*) = 0;
			virtual void CPF_STDCALL AddDependency(BlockDependency dep) = 0;
			virtual COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) = 0;
			virtual COM::Result CPF_STDCALL Configure() = 0;
		};

		class CPF_EXPORT_MULTICORE System : public tRefCounted<iSystem>
		{
		public:
			COM::Result CPF_STDCALL QueryInterface(COM::InterfaceID id, void** outIface);

			COM::Result CPF_STDCALL Initialize(iPipeline* owner, const char* name) override;
			iPipeline* CPF_STDCALL GetOwner() const override;
			COM::Result CPF_STDCALL GetStage(StageID id, Stage** outStage) const;
			SystemID CPF_STDCALL GetID() const override;
			int32_t CPF_STDCALL GetStageCount() const override { return int32_t(mStages.size()); }
			Stage* CPF_STDCALL GetStage(int32_t index) override { return mStages[index]; }
			COM::Result CPF_STDCALL GetInstructions(int32_t*, Instruction*);
			void CPF_STDCALL AddDependency(BlockDependency dep) override;
			COM::Result CPF_STDCALL GetDependencies(int32_t*, BlockDependency*) override;
			COM::Result CPF_STDCALL Configure() { return COM::kOK; }


			using Creator = System* (*)(iPipeline* owner, const char*, const Desc*);

			// System factory.
			template <typename TYPE>
			static TYPE* Create(iPipeline* owner, const char*, const Desc* = nullptr);
			static bool Install(SystemID id, Creator);
			static bool Remove(SystemID id);

		protected:
			// Implementation interface.
			System(iPipeline* owner, const char* name);
			virtual ~System();

			bool AddStage(Stage*);
			bool RemoveStage(StageID);

		private:
			// Untyped factory interface.
			static System* _Create(iPipeline* owner, SystemID, const char*, const Desc* desc);

			// Implementation data.
			iPipeline* mpOwner;
			StageVector mStages;
			SystemID mID;
			BlockDependencies mDependencies;
		};

		// Typed system factory.
		template <typename TYPE>
		TYPE* System::Create(iPipeline* owner, const char* name, const Desc* desc)
		{
			return static_cast<TYPE*>(_Create(owner, TYPE::kID, name, desc));
		}
	}
}
