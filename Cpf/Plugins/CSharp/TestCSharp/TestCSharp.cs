using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
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

	public int Test()
	{
		return 0;
	}
}

struct PinnedObject
{
	public GCHandle GcHandle { get; set; }
	public Object Obj { get; set; }

	public PinnedObject(GCHandle gcHandle, object obj)
	{
		GcHandle = gcHandle;
		Obj = obj;
	}
}

public interface IPlugin
{
	UInt32 Install(IntPtr registryPtr);
	UInt32 Uninstall(IntPtr registryPtr);
};

public class Plugin : IPlugin
{
	private iClassInstance classInstance;
	private iClassInstanceVTable iClassInstanceVTable;
	private GCHandle classVTableHandle;

	private List<PinnedObject> pinned = new List<PinnedObject>();

	public uint Install(IntPtr registryPtr)
	{
		var registry = Marshal.PtrToStructure<iRegistry>(registryPtr);
		var iRegistryVTable = Marshal.PtrToStructure<iRegistryVTable>(registry.vTable);

		classInstance = new iClassInstance();
		iClassInstanceVTable = new iClassInstanceVTable();
		iClassInstanceVTable.CreateInstance = CreateInstanceFunc;//  Marshal.GetFunctionPointerForDelegate(createInstanceFunc);

		//PinIt(classInstance);
		//PinIt(iClassInstanceVTable);
		//PinIt(createInstanceFunc);

		pinned.Add(new PinnedObject(GCHandle.Alloc(classInstance), classInstance));
		pinned.Add(new PinnedObject(GCHandle.Alloc(iClassInstanceVTable), iClassInstanceVTable));
		//pinned.Add(new PinnedObject(GCHandle.Alloc(createInstanceFunc), createInstanceFunc));

		//classVTableHandle = GCHandle.Alloc(iClassInstanceVTable);
		classInstance.vTable = iClassInstanceVTable; //GCHandle.ToIntPtr(classVTableHandle);

		//var classMemory = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(iClassInstance)));
		//Marshal.StructureToPtr(classInstance, classMemory, false);

		return iRegistryVTable.Install(registryPtr, TestPlugin.ID, MarshalStruct(classInstance));
	}

	private uint CreateInstanceFunc(iRegistry registry1, iUnknown outer, IntPtr outInstance)
	{
		var inst = new TestPlugin(outer);
		Marshal.StructureToPtr(inst, outInstance, false);
		PinIt(inst);

		return 0x7b48e63f;
	}

	public uint Uninstall(IntPtr registryPtr)
	{
		var registry = Marshal.PtrToStructure<iRegistry>(registryPtr);
		var iRegistryVTable = Marshal.PtrToStructure<iRegistryVTable>(registry.vTable);

		return iRegistryVTable.Remove(registryPtr, TestPlugin.ID);
	}

	private void PinIt(object obj)
	{
		pinned.Add(new PinnedObject { Obj = obj, GcHandle = GCHandle.Alloc(obj) });
	}

	private static MarshalVTable MarshalStruct(object ob)
	{
		var marshalVTable = new MarshalVTable();
		var type = ob.GetType();

		var fieldInfo = type.GetFields(BindingFlags.Public | BindingFlags.Instance).First();
		var fieldValue = fieldInfo.GetValue(ob);

		marshalVTable.vTable = Marshal.AllocHGlobal(Marshal.SizeOf(fieldInfo.FieldType));
		Marshal.StructureToPtr(fieldValue, marshalVTable.vTable, false);

		return marshalVTable;



		//foreach(var fieldInfo in fields)
		//{
		//	if(fieldInfo.DeclaringType != typeof(object))
		//	{
		//		var fieldValue = fieldInfo.GetValue(ob);
		//		var ptr = Marshal.AllocHGlobal(Marshal.SizeOf(fieldInfo.FieldType));
		//		Marshal.StructureToPtr(fieldValue, ptr, false);

		//		//if(fieldInfo.FieldType.IsClass)
		//		//{
		//		//	MarshalStruct(fieldInfo.GetValue(ob));
		//		//}
		//		//else
		//		//{
		//		//	var del = (Delegate) fieldInfo.GetValue(ob);
		//		//	var functionPointerForDelegate = Marshal.GetFunctionPointerForDelegate(del);
		//		//	delegates.Add(functionPointerForDelegate);
		//		//}
		//	}
		//}

		//var structureSize = Marshal.SizeOf<Delegate>() * delegates.Count;
		//var allocHGlobal = Marshal.AllocHGlobal(structureSize);

	}
}

[StructLayout(LayoutKind.Sequential)]
public class MarshalVTable
{
	public IntPtr vTable;
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
	public delegate UInt32 InstallFunc(IntPtr self, UInt64 cid, MarshalVTable clsInst);

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
	public delegate UInt32 CreateInstanceFunc(iRegistry registry, iUnknown outer, IntPtr outInstance);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public CreateInstanceFunc CreateInstance;
}
[StructLayout(LayoutKind.Sequential)]
public class iClassInstance
{
	public iClassInstanceVTable vTable;
}