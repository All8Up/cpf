//////////////////////////////////////////////////////////////////////////
#include "Adapter/D3D12/Output.hpp"
#include "Adapter/D3D12/D3D12Utils.hpp"
#include "Graphics/OutputDesc.hpp"
#include "Graphics/ModeDesc.hpp"
#include "Vector.hpp"
#include "Logging/Logging.hpp"

using namespace Cpf;
using namespace Graphics;
using namespace Adapter;
using namespace D3D12;

//////////////////////////////////////////////////////////////////////////
Output::Output(IDXGIOutput4* output)
{
	mpOutput.Adopt(output);
	CPF_LOG(D3D12, Info) << "Created output: " << intptr_t(this) << " - " << intptr_t(mpOutput.Ptr());
}

Output::~Output()
{
	CPF_LOG(D3D12, Info) << "Destroyed output: " << intptr_t(this) << " - " << intptr_t(mpOutput.Ptr());
}

COM::Result CPF_STDCALL Output::QueryInterface(COM::InterfaceID id, void** outIface)
{
	if (outIface)
	{
		switch (id.GetID())
		{
		case COM::iUnknown::kIID.GetID():
			*outIface = static_cast<COM::iUnknown*>(this);
			break;
		case iOutput::kIID.GetID():
			*outIface = static_cast<iOutput*>(this);
			break;
		default:
			return COM::kUnknownInterface;
		}
		AddRef();
		return COM::kOK;
	}
	return COM::kInvalidParameter;
}

bool Output::GetDesc(OutputDesc* desc) const
{
	if (desc)
	{
		DXGI_OUTPUT_DESC outputDesc;
		::memset(desc, 0, sizeof(OutputDesc));
		::memset(&outputDesc, 0, sizeof(outputDesc));

		if (SUCCEEDED(mpOutput->GetDesc(&outputDesc)))
		{
			for (int i = 0; i < 32; ++i)
				desc->mName[i] = char(outputDesc.DeviceName[i]);
			desc->mAttachedToDesktop = outputDesc.AttachedToDesktop == TRUE;
			desc->mDesktopCoordinates.Left(outputDesc.DesktopCoordinates.left);
			desc->mDesktopCoordinates.Right(outputDesc.DesktopCoordinates.right);
			desc->mDesktopCoordinates.Top(outputDesc.DesktopCoordinates.top);
			desc->mDesktopCoordinates.Bottom(outputDesc.DesktopCoordinates.bottom);
			desc->mRotation = Graphics::ModeRotation(outputDesc.Rotation);
			return true;
		}
	}
	return false;
}

bool Output::EnumerateModes(Graphics::Format format, Graphics::EnumMode enumMode, int32_t& count, Graphics::ModeDesc* descs)
{
	if (count != 0 && descs != nullptr)
	{
		Vector<DXGI_MODE_DESC1> modeDescs;
		modeDescs.resize(count);
		UINT modeCount = UINT(count);
		if (SUCCEEDED(mpOutput->GetDisplayModeList1(Convert(format), ConvertEnumMode(enumMode), &modeCount, modeDescs.data())))
		{
			for (int i = 0; i < count; ++i)
			{
				descs[i].mWidth = modeDescs[i].Width;
				descs[i].mHeight = modeDescs[i].Height;
				descs[i].mRefreshRate = Ratio(modeDescs[i].RefreshRate.Numerator, modeDescs[i].RefreshRate.Denominator);
				descs[i].mFormat = Convert(modeDescs[i].Format);
				descs[i].mScanLineOrder = Convert(modeDescs[i].ScanlineOrdering);
				descs[i].mModeScaling = Convert(modeDescs[i].Scaling);
				descs[i].mStereo = modeDescs[i].Stereo == TRUE;
			}

			return true;
		}
	}
	else
	{
		UINT modeCount = 0;
		if (SUCCEEDED(mpOutput->GetDisplayModeList1(Convert(format), ConvertEnumMode(enumMode), &modeCount, nullptr)))
		{
			count = modeCount;
			return true;
		}
	}

	return false;
}

bool Output::FindClosestMatch(const ModeDesc* matchMode, ModeDesc* closest, iDevice* compatibleCheck)
{
	(void)matchMode; (void)closest; (void)compatibleCheck;
	return false;
}

bool Output::WaitForVBlank()
{
	return false;
}
