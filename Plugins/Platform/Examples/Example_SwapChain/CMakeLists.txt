add_executable (Example_SwapChain_D3D12 WIN32
	Source/Main.cpp
)
target_link_libraries (Example_SwapChain_D3D12
	Core_s
	Application_s
	PlatformGraphicsD3D12_s
	PlatformDesktopSDL2_s
)
target_compile_definitions (Example_SwapChain_D3D12
	PUBLIC
		CPF_GRAPHICS_DRIVER=D3D12
)
set_property (TARGET Example_SwapChain_D3D12 PROPERTY FOLDER Examples/Graphics/Driver)

# ########################################
add_executable (Example_SwapChain_Vulkan WIN32
	Source/Main.cpp
)
target_link_libraries (Example_SwapChain_Vulkan
	Core_s
	Application_s
	PlatformGraphicsVulkan_s
	PlatformDesktopSDL2_s
)
target_compile_definitions (Example_SwapChain_Vulkan
	PUBLIC
		CPF_GRAPHICS_DRIVER=Vulkan
)
set_property (TARGET Example_SwapChain_Vulkan PROPERTY FOLDER Examples/Graphics/Driver)
