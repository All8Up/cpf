using System;
using System.Runtime.InteropServices;

public class iUnknown
{
	private int refCount;

	int AddRef()
	{
		return ++refCount;
	}

	int Release()
	{
		return --refCount;
	}

	UInt32 QueryInterface(UInt64 id, out IntPtr @interface)
	{
		@interface = IntPtr.Zero;
		return 0;
	}
}

public class TestPlugin : iUnknown
{
	public static UInt64 ID = 1234;

	public TestPlugin(iUnknown outer)
	{

	}
}

public class Main
{
	private static iClassInstance classInstance;
	
	public static UInt32 Install(IntPtr registryPtr)
	{
		//var registry = Marshal.PtrToStructure<iRegistry>(registryPtr);
		//var iRegistryVTable = Marshal.PtrToStructure<iRegistryVTable>(registry.vTable);

		//classInstance = new iClassInstance();
		//var iClassInstanceVTable = new iClassInstanceVTable();
		//iClassInstanceVTable.CreateInstance = (iRegistry r, iUnknown outer, iUnknown instance) =>
		//{
		//	instance = new TestPlugin(outer);

		//	return 0x7b48e63f;
		//};

		////Marshal.StructureToPtr(iClassInstanceVTable, classInstance.vTable, true);
		//var classVTableHandle = GCHandle.Alloc(iClassInstanceVTable);
		//classInstance.vTable = GCHandle.ToIntPtr(classVTableHandle);

		//var classHandle = GCHandle.Alloc(classInstance);

		//return iRegistryVTable.Install(registryPtr, TestPlugin.ID, classInstance);
		return 0;
	}
	
	public static UInt32 Remove(IntPtr registryPtr)
	{
		var registry = Marshal.PtrToStructure<iRegistry>(registryPtr);
		var iRegistryVTable = Marshal.PtrToStructure<iRegistryVTable>(registry.vTable);
		
		return iRegistryVTable.Remove(registryPtr, TestPlugin.ID);
	}
}

[StructLayout(LayoutKind.Sequential)]
public class iUnknownVTable
{
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate Int32 AddRefFunc();

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public AddRefFunc AddRef;

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate Int32 ReleaseFunc();

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ReleaseFunc Release;

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate Int32 QueryInterfaceFunc(UInt64 id, IntPtr outIFace);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public QueryInterfaceFunc QueryInterface;
}

[StructLayout(LayoutKind.Sequential)]
public class iRegistryVTable : iUnknownVTable
{
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 LoadFunc(IntPtr self, char library);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public LoadFunc Load;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 UnloadFunc(IntPtr self, char library);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public UnloadFunc Unload;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 InstallFunc(IntPtr self, UInt64 cid, iClassInstance clsInst);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public InstallFunc Install;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 RemoveFunc(IntPtr self, UInt64 cid);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public RemoveFunc Remove;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 GetClassInstanceFunc(IntPtr self, UInt64 cid, iClassInstance clsInst);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetClassInstanceFunc GetClassInstance;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 ExistsFunc(IntPtr self, UInt64 cid);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ExistsFunc Exists;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 CreateFunc(IntPtr self, iUnknown outer, UInt64 cid, UInt64 iid, IntPtr outIface);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public CreateFunc Create;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 ClassInstallFunc(IntPtr self, Int32 count, IID_CID pairs);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ClassInstallFunc ClassInstall;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 ClassRemoveFunc(IntPtr self, Int32 count, IID_CID pairs);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ClassRemoveFunc ClassRemove;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 GetClassesFunc(IntPtr self, UInt64 id, ref Int32 count, ref UInt64 cid);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetClassesFunc GetClasses;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 InstanceInstallFunc(IntPtr self, UInt64 id, iUnknown instance);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public InstanceInstallFunc InstanceInstall;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 InstanceRemoveFunc(IntPtr self, UInt64 id);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public InstanceRemoveFunc InstanceRemove;


	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 GetInstanceFunc(IntPtr self, UInt64 id, iUnknown outIface);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public GetInstanceFunc GetInstance;


}
[StructLayout(LayoutKind.Sequential)]
public class iRegistry
{
	public IntPtr vTable;
}


[StructLayout(LayoutKind.Sequential)]
public struct IID_CID
{
	public UInt64 mIID { get; set; }
	public UInt64 mCID { get; set; }
}

[StructLayout(LayoutKind.Sequential)]
public class iClassInstanceVTable : iUnknownVTable
{
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 CreateInstanceFunc(iRegistry registry, iUnknown outer, iUnknown outInstance);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public CreateInstanceFunc CreateInstance;
}
[StructLayout(LayoutKind.Sequential)]
public class iClassInstance
{
	public IntPtr vTable;
}
