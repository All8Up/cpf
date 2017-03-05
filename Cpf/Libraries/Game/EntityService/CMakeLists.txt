# ###############################################
# Public headers.
set (PUBLIC_HEADERS
	Public/EntityService.hpp
)
set (PUBLIC_HEADERS_ENTITYSERVICE
	Public/EntityService/Export.hpp
	Public/EntityService/Types.hpp
)
set (PUBLIC_HEADERS_ENTITYSERVICE_HELPERS
	Public/EntityService/Helpers/ComponentBase.hpp
)
set (PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES
	Public/EntityService/Interfaces/iStage.hpp
	Public/EntityService/Interfaces/iSystem.hpp
	Public/EntityService/Interfaces/iEntity.hpp
	Public/EntityService/Interfaces/iManager.hpp
	Public/EntityService/Interfaces/iComponent.hpp
)
set (PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_STAGES
	Public/EntityService/Interfaces/Stages/iEntityStage.hpp
)
set (PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_SYSTEMS
	Public/EntityService/Interfaces/Systems/iAwarenessSystem.hpp
)
set (PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_COMPONENTS
	Public/EntityService/Interfaces/Components/iTransformComponent.hpp
	Public/EntityService/Interfaces/Components/iAwarenessComponent.hpp
)
set (PRIVATE_HEADERS_ENTITYSERVICE_SYSTEMS
)
set (PRIVATE_HEADERS_ENTITYSERVICE_STAGES
)

# ###############################################
# Private headers.
set (PRIVATE_HEADERS
)
set (PRIVATE_HEADERS_ENTITYSERVICE
	Private/EntityService/Entity.hpp
	Private/EntityService/Manager.hpp
)
set (PRIVATE_HEADERS_ENTITYSERVICE_SYSTEMS
)

# ###############################################
# Private sources.
set (PRIVATE_SOURCES
	Private/EntityService.cpp
)
set (PRIVATE_SOURCES_ENTITYSERVICE
	Private/EntityService/Component.cpp
	Private/EntityService/Entity.cpp
	Private/EntityService/Manager.cpp
)
set (PRIVATE_SOURCES_ENTITYSERVICE_COMPONENTS
	Private/EntityService/Components/TransformComponent.cpp
)
set (PRIVATE_SOURCES_ENTITYSERVICE_SYSTEMS
)
set (PRIVATE_SOURCES_ENTITYSERVICE_STAGES
	Private/EntityService/Stages/EntityStage.cpp
)

# ###############################################
add_library (s_EntityService STATIC
	${PUBLIC_HEADERS}
	${PUBLIC_HEADERS_ENTITYSERVICE}
	${PUBLIC_HEADERS_ENTITYSERVICE_HELPERS}
	${PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES}
	${PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_STAGES}
	${PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_SYSTEMS}
	${PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_COMPONENTS}

	${PRIVATE_HEADERS}
	${PRIVATE_SOURCES}
	${PRIVATE_HEADERS_ENTITYSERVICE}
	${PRIVATE_SOURCES_ENTITYSERVICE}
	${PRIVATE_HEADERS_ENTITYSERVICE_COMPONENTS}
	${PRIVATE_SOURCES_ENTITYSERVICE_COMPONENTS}
	${PRIVATE_HEADERS_ENTITYSERVICE_STAGES}
	${PRIVATE_SOURCES_ENTITYSERVICE_STAGES}
	${PRIVATE_HEADERS_ENTITYSERVICE_SYSTEMS}
	${PRIVATE_SOURCES_ENTITYSERVICE_SYSTEMS}
)
target_compile_definitions (s_EntityService
	PUBLIC CPF_STATIC_ENTITYSERVICE
	PRIVATE CPF_BUILD_ENTITYSERVICE
)
target_include_directories (s_EntityService
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
		$<INSTALL_INTERFACE:Public>
)
target_link_libraries (s_EntityService
	LINK_PUBLIC
		Configuration s_Collections RefCount Logging s_Hash s_Math s_MultiCore
)
set_property (TARGET s_EntityService PROPERTY FOLDER Libraries/Static/Game)

# ###############################################
source_group (Public FILES ${PUBLIC_HEADERS})
source_group (Public\\EntityService FILES ${PUBLIC_HEADERS_ENTITYSERVICE})
source_group (Public\\EntityService\\Helpers FILES ${PUBLIC_HEADERS_ENTITYSERVICE_HELPERS})
source_group (Public\\EntityService\\Interfaces FILES ${PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES})
source_group (Public\\EntityService\\Interfaces\\Stages FILES ${PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_STAGES})
source_group (Public\\EntityService\\Interfaces\\Systems FILES ${PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_SYSTEMS})
source_group (Public\\EntityService\\Interfaces\\Components FILES ${PUBLIC_HEADERS_ENTITYSERVICE_INTERFACES_COMPONENTS})

source_group (Private FILES ${PRIVATE_HEADERS} ${PRIVATE_SOURCES})
source_group (Private\\EntityService FILES ${PRIVATE_HEADERS_ENTITYSERVICE} ${PRIVATE_SOURCES_ENTITYSERVICE})
source_group (Private\\EntityService\\Components FILES ${PRIVATE_HEADERS_ENTITYSERVICE_COMPONENTS} ${PRIVATE_SOURCES_ENTITYSERVICE_COMPONENTS})
source_group (Private\\EntityService\\Stages FILES ${PRIVATE_HEADERS_ENTITYSERVICE_STAGES} ${PRIVATE_SOURCES_ENTITYSERVICE_STAGES})
source_group (Private\\EntityService\\Systems FILES ${PRIVATE_HEADERS_ENTITYSERVICE_SYSTEMS} ${PRIVATE_SOURCES_ENTITYSERVICE_SYSTEMS})
