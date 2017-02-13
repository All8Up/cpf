# ###############################################
include( CheckTypeSize )
check_type_size( "void*" SIZEOF_VOID_P BUILTIN_TYPES_ONLY )

# ###############################################
if( SIZEOF_VOID_P EQUAL 8 )
	set( CPF_ARCHITECTURE_SIZE 64 )
else()
	set( CPF_ARCHITECTURE_SIZE 32 )
endif()
