# ###############################################
set (INCLUDE_FILES
	Include/Spine2D.hpp
)
set (INCLUDE_SPINE_FILES
	Include/spine/Animation.h
)
set (INTERFACE_FILES
	Interface/Spine2D.hpp
)

set (SOURCE_FILES
	Source/Spine2D.cpp
)
set (SOURCE_SPINE_FILES
	Source/spine/Animation.c
	Source/spine/AnimationState.c
	Source/spine/AnimationStateData.c
	Source/spine/Atlas.c
	Source/spine/AtlasAttachmentLoader.c
	Source/spine/Attachment.c
	Source/spine/AttachmentLoader.c
	Source/spine/Bone.c
	Source/spine/BoneData.c
	Source/spine/BoundingBoxAttachment.c
	Source/spine/Event.c
	Source/spine/EventData.c
	Source/spine/extension.c
	Source/spine/IkConstraint.c
	Source/spine/IkConstraintData.c
	Source/spine/Json.c
	Source/spine/Json.h
	Source/spine/kvec.h
	Source/spine/MeshAttachment.c
	Source/spine/PathAttachment.c
	Source/spine/PathConstraint.c
	Source/spine/PathConstraintData.c
	Source/spine/RegionAttachment.c
	Source/spine/Skeleton.c
	Source/spine/SkeletonBinary.c
	Source/spine/SkeletonBounds.c
	Source/spine/SkeletonData.c
	Source/spine/SkeletonJson.c
	Source/spine/Skin.c
	Source/spine/Slot.c
	Source/spine/SlotData.c
	Source/spine/TransformConstraint.c
	Source/spine/TransformConstraintData.c
	Source/spine/VertexAttachment.c
)

# ###############################################
add_library (Spine2D SHARED
	${INCLUDE_FILES}
	${INCLUDE_SPINE_FILES}
	${INTERFACE_FILES}
	${SOURCE_FILES}
	${SOURCE_SPINE_FILES}
)
target_include_directories (Spine2D
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)
target_link_libraries (Spine2D
	PUBLIC
		Configuration Plugin
)
set_property (TARGET Spine2D PROPERTY FOLDER Plugins/Game)


# ###############################################
# Copy as a plugin.
add_custom_command (
	TARGET Spine2D POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Spine2D> ${CPF_COMMON_PLUGINS}/Spine2D.cfp
)

# ###############################################
add_library (i_Spine2D INTERFACE)
target_include_directories (i_Spine2D
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
		$<INSTALL_INTERFACE:Include>
)

# ###############################################
source_group (Headers FILES ${INCLUDE_FILES})
source_group (Interfaces FILES ${INTERFACE_FILES})
source_group (Sources FILES ${SOURCE_FILES})
