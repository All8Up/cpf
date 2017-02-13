# ###############################################
# Setup the following:
#	CPF_TARGET_OS Windows, Darwin, Linux, XBox360, XBoxOne, Ps4, WiiU, Ios, Android
#	CPF_TARGET_CPU Intel, PPC, Arm
#	CPF_TARGET_CPU_SIZE 32, 64


set (CPF_TARGET_WINDOWS 0)
set (CPF_TARGET_DARWIN 0)
set (CPF_TARGET_IOS 0)
set (CPF_TARGET_ANDROID 0)


# ###############################################
if( NOT CMAKE_CROSSCOMPILING )
	include( CMake/Detection/Architecture.cmake )
	include( CMake/Detection/Compilers/${CMAKE_CXX_COMPILER_ID}.cmake )
	include( CMake/Detection/Targets/${CMAKE_SYSTEM_NAME}.cmake )
endif()


# ###############################################
# CPF_OS_CPU_DIRECTORY
#	Windows/x32
#	Windows/x64
#	Windows/Arm
#	Darwin
#	Linux/x32
#	Linux/x64
#	Linux/Arm32,
#	Linux/Arm64
#	XBox360
#	XBoxOne
#	Ps4
#	WiiU
#	Ios
#	Android/Arm32
#	Android/Arm64
