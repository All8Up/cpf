//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Graphics.hpp"
#include <initializer_list>
#include "Vector.hpp"

namespace Cpf
{
	namespace Graphics
	{
		enum class BindingType : int32_t
		{
			eConstants,
			eConstantBuffer,
			eResourceBuffer,
			eUnorderedBuffer,
			eRange,
		};

		struct ParamVisibility
		{
			enum : int32_t
			{
				eVisibilityAll = 0,
				eVertex = 1,
				eHull = 2,
				eDomain = 3,
				eGeometry = 4,
				ePixel = 5
			};
		};

		struct ParamFlags
		{
			enum : int32_t
			{
				eVolatile = 0x02,
				eStaticWhileSet = 0x04,
				eStatic = 0x08
			};
		};

		//////////////////////////////////////////////////////////////////////////
		// An entry in the resource binding.
		class CPF_EXPORT_GRAPHICS_DRIVER BindingParameter
		{
		public:
			BindingParameter(BindingType type) : mType(type) {}

			struct Constants
			{
				int32_t mRegisterIndex;
				int32_t mCount;
				int32_t mVisibility;
			};
			struct ConstantBuffer
			{
				int32_t mRegisterIndex;
				int32_t mFlags;
				int32_t mVisibility;
			};

			BindingType GetType() const;
			void SetConstants(int32_t regidx, int32_t count, int32_t visibility);
			void SetConstantBuffer(int32_t regidx, int32_t flags, int32_t visibility);

			const Constants& GetConstants() const;
			const ConstantBuffer& GetConstantBuffer() const;

		private:
			friend class ResourceBindingDesc;
			BindingType mType;
			union
			{
				Constants mConstants;
				ConstantBuffer mConstantBuffer;
			} mData;
		};

		//////////////////////////////////////////////////////////////////////////
		// Utilities to build parameter descriptors.
		CPF_EXPORT_GRAPHICS_DRIVER BindingParameter ParamConstants(int32_t index, int32_t count, int32_t visibility);
		CPF_EXPORT_GRAPHICS_DRIVER BindingParameter ParamConstantBuffer(int32_t index, int32_t visibility, int32_t flags = ParamFlags::eStatic);

		//////////////////////////////////////////////////////////////////////////
		class ResourceBindingDesc
		{
		public:
			ResourceBindingDesc(const Vector<BindingParameter>& params);

			const Vector<BindingParameter>& GetParameters() const { return mParameters; }

		private:
			Vector<BindingParameter> mParameters;
		};
	}
}
