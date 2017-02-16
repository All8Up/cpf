# ###############################################
set (INCLUDE_FILES
	Include/GO.hpp
)
set (INCLUDE_GO_FILES
	Include/GO/Component.hpp
	Include/GO/Export.hpp
	Include/GO/Object.hpp
	Include/GO/Service.hpp
	Include/GO/System.hpp
	Include/GO/Types.hpp
)
set (INCLUDE_GO_COMPONENT_FILES
	Include/GO/Components/TransformComponent.hpp
)

set (SOURCE_FILES
	Source/GO.cpp
)
set (SOURCE_GO_FILES
	Source/GO/Component.cpp
	Source/GO/Object.cpp
	Source/GO/Service.cpp
	Source/GO/System.cpp
)
set (SOURCE_GO_COMPONENT_FILES
	Source/GO/Components/TransformComponent.cpp
)

add_library (s_GO STATIC
	${INCLUDE_FILES}
	${INCLUDE_GO_FILES}
	${INCLUDE_GO_COMPONENT_FILES}
	${SOURCE_FILES}
	${SOURCE_GO_FILES}
	${SOURCE_GO_COMPONENT_FILES}
)
target_compile_definitions (s_GO
	PUBLIC CPF_STATIC_GO
	PRIVATE CPF_BUILD_GO
)
target_include_directories (s_GO
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (s_GO
	LINK_PUBLIC
		Configuration s_Collections RefCount Logging s_Hash s_Math
)
set_property (TARGET s_GO PROPERTY FOLDER Libraries/Static/Game)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
source_group (Headers\\GO FILES ${INCLUDE_GO_FILES})
source_group (Sources\\GO FILES ${SOURCE_GO_FILES})
source_group (Headers\\GO\\Components FILES ${INCLUDE_GO_COMPONENT_FILES})
source_group (Sources\\GO\\Components FILES ${SOURCE_GO_COMPONENT_FILES})
