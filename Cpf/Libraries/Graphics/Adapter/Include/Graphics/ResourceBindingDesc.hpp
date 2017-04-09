//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics.hpp"
#include "Graphics/ParamFlags.hpp"
#include "Graphics/BindingType.hpp"
#include <initializer_list>
#include "Vector.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class BindingType : int32_t;
		enum class ParamVisibility : int32_t;

		//////////////////////////////////////////////////////////////////////////
		// An entry in the resource binding.
		class BindingParameter
		{
		public:
			BindingParameter(BindingType type) : mType(type) {}

			struct Constants
			{
				int32_t mRegisterIndex;
				int32_t mCount;
				ParamVisibility mVisibility;
			};
			struct ConstantBuffer
			{
				int32_t mRegisterIndex;
				ParamFlags mFlags;
				ParamVisibility mVisibility;
			};
			struct SamplerBinding
			{
				int32_t mRegisterIndex;
			};
			struct TextureBinding
			{
				int32_t mRegisterIndex;
			};

			BindingType GetType() const;
			void SetConstants(int32_t regidx, int32_t count, ParamVisibility visibility);
			void SetConstantBuffer(int32_t regidx, ParamFlags flags, ParamVisibility visibility);
			void SetSamplerBinding(int32_t regidx);
			void SetTextureBinding(int32_t regidx);

			const Constants& GetConstants() const;
			const ConstantBuffer& GetConstantBuffer() const;
			const SamplerBinding& GetSamplerBinding() const;
			const TextureBinding& GetTextureBinding() const;

		private:
			friend class ResourceBindingDesc;
			BindingType mType;
			union
			{
				Constants mConstants;
				ConstantBuffer mConstantBuffer;
				SamplerBinding mSamplerBinding;
				TextureBinding mTextureBinding;
			} mData;
		};

		//////////////////////////////////////////////////////////////////////////
		// Utilities to build parameter descriptors.
		BindingParameter ParamConstants(int32_t index, int32_t count, ParamVisibility visibility);
		BindingParameter ParamConstantBuffer(int32_t index, ParamVisibility visibility, ParamFlags flags = ParamFlags::eStatic);
		BindingParameter ParamSampler(int32_t index);
		BindingParameter ParamTexture(int32_t index);

		//////////////////////////////////////////////////////////////////////////
		class ResourceBindingDesc
		{
		public:
			ResourceBindingDesc(const Vector<BindingParameter>& params);

			const Vector<BindingParameter>& GetParameters() const { return mParameters; }

		private:
			Vector<BindingParameter> mParameters;
		};

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		inline BindingType BindingParameter::GetType() const { return mType; }
		inline void BindingParameter::SetConstants(int32_t regidx, int32_t count, ParamVisibility visibility)
		{
			CPF_ASSERT(mType == BindingType::eConstants);
			mData.mConstants.mRegisterIndex = regidx;
			mData.mConstants.mCount = count;
			mData.mConstants.mVisibility = visibility;
		}
		inline void BindingParameter::SetConstantBuffer(int32_t regidx, ParamFlags flags, ParamVisibility visibility)
		{
			CPF_ASSERT(mType == BindingType::eConstantBuffer);
			mData.mConstantBuffer.mRegisterIndex = regidx;
			mData.mConstantBuffer.mFlags = flags;
			mData.mConstantBuffer.mVisibility = visibility;
		}

		inline void BindingParameter::SetSamplerBinding(int32_t regidx)
		{
			CPF_ASSERT(mType == BindingType::eSampler);
			mData.mSamplerBinding.mRegisterIndex = regidx;
		}

		inline void BindingParameter::SetTextureBinding(int32_t regidx)
		{
			CPF_ASSERT(mType == BindingType::eTexture);
			mData.mTextureBinding.mRegisterIndex = regidx;
		}


		inline const BindingParameter::Constants& BindingParameter::GetConstants() const
		{
			CPF_ASSERT(mType == BindingType::eConstants);
			return mData.mConstants;
		}
		inline const BindingParameter::ConstantBuffer& BindingParameter::GetConstantBuffer() const
		{
			CPF_ASSERT(mType == BindingType::eConstantBuffer);
			return mData.mConstantBuffer;
		}

		inline const BindingParameter::SamplerBinding& BindingParameter::GetSamplerBinding() const
		{
			CPF_ASSERT(mType == BindingType::eSampler);
			return mData.mSamplerBinding;
		}

		inline const BindingParameter::TextureBinding& BindingParameter::GetTextureBinding() const
		{
			CPF_ASSERT(mType == BindingType::eTexture);
			return mData.mTextureBinding;
		}

		//////////////////////////////////////////////////////////////////////////
		inline BindingParameter Graphics::ParamConstants(int32_t index, int32_t count, ParamVisibility visibility)
		{
			BindingParameter result(BindingType::eConstants);
			result.SetConstants(index, count, visibility);
			return result;
		}

		inline  BindingParameter Graphics::ParamConstantBuffer(int32_t index, ParamVisibility visibility, ParamFlags flags)
		{
			BindingParameter result(BindingType::eConstantBuffer);
			result.SetConstantBuffer(index, flags, visibility);
			return result;
		};

		inline BindingParameter Graphics::ParamSampler(int32_t index)
		{
			BindingParameter result(BindingType::eSampler);
			result.SetSamplerBinding(index);
			return result;
		}

		inline BindingParameter Graphics::ParamTexture(int32_t index)
		{
			BindingParameter result(BindingType::eTexture);
			result.SetTextureBinding(index);
			return result;
		}

		//////////////////////////////////////////////////////////////////////////

		inline ResourceBindingDesc::ResourceBindingDesc(const Vector<BindingParameter>& params)
			: mParameters(params)
		{
		}
	}
}
