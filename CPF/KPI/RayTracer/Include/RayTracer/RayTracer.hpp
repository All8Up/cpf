//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Configuration.hpp"
#include <string>
#include <cassert>

#include "CPF/Math/Vector3v.hpp"
#include "CPF/Math/Vector4v.hpp"
#include "CPF/Math/Matrix44v.hpp"
#include "CPF/Math/Geometry/Ray3.hpp"


namespace RayTracer
{
	using Vector3 = CPF::Math::Vector3fv;
	using Vector4 = CPF::Math::Vector4fv;
	using Matrix44 = CPF::Math::Matrix44fv;

	using Ray3 = CPF::Math::Ray3<Vector3>;
}


// Helper utility, really don't care about wstring but the JSON library uses it.
// We provide some conversion casts, nasty little things....
template< typename SrcType, typename DstType >
DstType string_cast( const SrcType& )
{
	assert( false );	// No conversion implemented.
}

template< typename DstType >
DstType string_cast( const std::wstring& in )
{
	DstType	result( in.begin(), in.end() );
	return result;
}

template< typename DstType >
DstType string_cast( const std::string& in )
{
	DstType	result( in.begin(), in.end() );
	return result;
}
