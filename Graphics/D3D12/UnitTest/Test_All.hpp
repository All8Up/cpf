#include <DirectXMath.h>
#include "Math/Matrix44v.hpp"

TEST(AdaptersD3D12, Matrix44v)
{
	using namespace Cpf;

	DirectX::XMMATRIX xmPerspectiveLH = DirectX::XMMatrixPerspectiveLH(
		2.0f * 0.25f,
		2.0f * 0.25f,
		1.0f, 1000.0f
	);
	Math::Matrix44fv cpfPerspectiveLH = Math::Matrix44fv::PerspectiveLH(
		2.0f * 0.25f,
		2.0f * 0.25f,
		1.0f, 1000.0f,
		0.0f, 1.0f
	);

	DirectX::XMMATRIX xmTranslation = DirectX::XMMatrixTranslation(1.0f, 2.0f, 3.0f);
	Math::Matrix44fv cpfTranslation = Math::Matrix44fv::Translate(1.0f, 2.0f, 3.0f);

	static int i = 0;
	++i;
}
