using System;
using System.CodeDom;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using ComTest;

public static class IDStore
{
	public const UInt64 iUnknown = 123;
	public const UInt64 ITestPlugin = 0x5b145b3470ae5b89;
	public const UInt64 KTestPlugin = 0xcc551f9f2177bbb2;
}

public class Plugin : IPlugin
{
	public uint Install(IntPtr registryPtr)
	{
		var registry = new iRegistryWrapper(registryPtr);
		var myClassInstance = new MyClassInstance();

		return registry.Install(IDStore.KTestPlugin, myClassInstance.QueryInterface<iClassInstanceWrapper>());
	}

	public uint Uninstall(IntPtr registryPtr)
	{
		var registry = new iRegistryWrapper(registryPtr);

		return registry.Remove(IDStore.ITestPlugin);
	}
}

[StructLayout(LayoutKind.Sequential)]
public class GenericObject
{
	public IntPtr VTablePtr;
}

[StructLayout(LayoutKind.Sequential)]
public class iUnknownVTable
{
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate Int32 AddRefFunc(IntPtr self);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public AddRefFunc AddRef;

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate Int32 ReleaseFunc(IntPtr self);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public ReleaseFunc Release;

	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate Int32 QueryInterfaceFunc(IntPtr self, UInt64 id, IntPtr outIFace);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public QueryInterfaceFunc QueryInterface;
}

[StructLayout(LayoutKind.Sequential)]
public struct IID_CID
{
	public UInt64 mIID { get; set; }
	public UInt64 mCID { get; set; }
}