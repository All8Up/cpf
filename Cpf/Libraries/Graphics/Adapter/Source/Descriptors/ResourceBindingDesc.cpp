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

//////////////////////////////////////////////////////////////////////////
CPF_EXPORT_GRAPHICS_ADAPTER BindingParameter Graphics::ParamConstants(int32_t index, int32_t count, int32_t visibility)
{
	BindingParameter result(BindingType::eConstants);
	result.SetConstants(index, count, visibility);
	return result;
}

CPF_EXPORT_GRAPHICS_ADAPTER BindingParameter Graphics::ParamConstantBuffer(int32_t index, int32_t visibility, int32_t flags)
{
	BindingParameter result(BindingType::eConstantBuffer);
	result.SetConstantBuffer(index, flags, visibility);
	return result;
};


//////////////////////////////////////////////////////////////////////////

ResourceBindingDesc::ResourceBindingDesc(const Vector<BindingParameter>& params)
	: mParameters(params)
{
}
