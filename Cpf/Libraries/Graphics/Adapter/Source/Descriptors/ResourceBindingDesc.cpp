//////////////////////////////////////////////////////////////////////////
#include "Graphics/Descriptors/ResourceBindingDesc.hpp"

using namespace Cpf;
using namespace Graphics;


BindingType BindingParameter::GetType() const { return mType; }
void BindingParameter::SetConstants(int32_t regidx, int32_t count, int32_t visibility)
{
	CPF_ASSERT(mType == BindingType::eConstants);
	mData.mConstants.mRegisterIndex = regidx;
	mData.mConstants.mCount = count;
	mData.mConstants.mVisibility = visibility;
}
void BindingParameter::SetConstantBuffer(int32_t regidx, int32_t flags, int32_t visibility)
{
	CPF_ASSERT(mType == BindingType::eConstantBuffer);
	mData.mConstantBuffer.mRegisterIndex = regidx;
	mData.mConstantBuffer.mFlags = flags;
	mData.mConstantBuffer.mVisibility = visibility;
}

void BindingParameter::SetSamplerBinding(int32_t regidx)
{
	CPF_ASSERT(mType == BindingType::eSampler);
	mData.mSamplerBinding.mRegisterIndex = regidx;
}

void BindingParameter::SetTextureBinding(int32_t regidx)
{
	CPF_ASSERT(mType == BindingType::eTexture);
	mData.mTextureBinding.mRegisterIndex = regidx;
}


const BindingParameter::Constants& BindingParameter::GetConstants() const
{
	CPF_ASSERT(mType == BindingType::eConstants);
	return mData.mConstants;
}
const BindingParameter::ConstantBuffer& BindingParameter::GetConstantBuffer() const
{
	CPF_ASSERT(mType == BindingType::eConstantBuffer);
	return mData.mConstantBuffer;
}

const BindingParameter::SamplerBinding& BindingParameter::GetSamplerBinding() const
{
	CPF_ASSERT(mType == BindingType::eSampler);
	return mData.mSamplerBinding;
}

const BindingParameter::TextureBinding& BindingParameter::GetTextureBinding() const
{
	CPF_ASSERT(mType == BindingType::eTexture);
	return mData.mTextureBinding;
}

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_GRAPHICS_DRIVER BindingParameter Graphics::ParamConstants(int32_t index, int32_t count, int32_t visibility)
{
	BindingParameter result(BindingType::eConstants);
	result.SetConstants(index, count, visibility);
	return result;
}

CPF_EXPORT_GRAPHICS_DRIVER BindingParameter Graphics::ParamConstantBuffer(int32_t index, int32_t visibility, int32_t flags)
{
	BindingParameter result(BindingType::eConstantBuffer);
	result.SetConstantBuffer(index, flags, visibility);
	return result;
};

CPF_EXPORT_GRAPHICS_DRIVER BindingParameter Graphics::ParamSampler(int32_t index)
{
	BindingParameter result(BindingType::eSampler);
	result.SetSamplerBinding(index);
	return result;
}

CPF_EXPORT_GRAPHICS_DRIVER BindingParameter Graphics::ParamTexture(int32_t index)
{
	BindingParameter result(BindingType::eTexture);
	result.SetTextureBinding(index);
	return result;
}

//////////////////////////////////////////////////////////////////////////

ResourceBindingDesc::ResourceBindingDesc(const Vector<BindingParameter>& params)
	: mParameters(params)
{
}
