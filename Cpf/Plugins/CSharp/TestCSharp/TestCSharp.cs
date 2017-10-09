using System;
using System.CodeDom;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;

internal static class ReferenceStorage
{
	private class PinnedObj
	{
		private object unknown;
		private GCHandle handle;

		public PinnedObj(object unknown)
		{
			this.unknown = unknown;
			handle = GCHandle.Alloc(unknown);
		}

		public void Release()
		{
			handle.Free();
			unknown = null;
		}
	}

	private static readonly Dictionary<object, PinnedObj> objectSet = new Dictionary<object, PinnedObj>();

	public static void Add(object obj)
	{
		objectSet.Add(obj, new PinnedObj(obj));
	}

	public static void Remove(object obj)
	{
		if (objectSet.TryGetValue(obj, out var pinned))
		{
			pinned.Release();
			objectSet.Remove(obj);
		}
	}
}

[AttributeUsage(AttributeTargets.Class)]
public class VTableAttribute : Attribute
{

}

[VTable]
[StructLayout(LayoutKind.Sequential)]
public class TestPluginVTable
{
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 TestFunc(IntPtr self);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public TestFunc Test;
}

public static class IDStore
{
	public const UInt64 iUnknown = 123;
	public const UInt64 ITestPlugin = 0x5b145b3470ae5b89;
	public const UInt64 KTestPlugin = 0xcc551f9f2177bbb2;
}

[StructLayout(LayoutKind.Sequential)]
public class TestPlugin : iUnknown
{
	public TestPluginVTable TestPluginVTable = new TestPluginVTable();
	
	public TestPlugin(iUnknown outer)
	{
		VTable.QueryInterface = (self, id, face) =>
		{
			switch (id)
			{
				case IDStore.iUnknown:
				{
					Marshal.WriteIntPtr(face, self);
					break;
				}
				case IDStore.ITestPlugin:
				{
					Marshal.WriteIntPtr(face, self);
					break;
				}
				default:
					return 999;
			}

			VTable.AddRef(self);
			return 0x7b48e63f;
		};
		TestPluginVTable.Test = self => 0;
	}
}

public class Plugin : IPlugin
{
	public uint Install(IntPtr registryPtr)
	{
		var registry = Marshal.PtrToStructure<iRegistry>(registryPtr);
		var iRegistryVTable = Marshal.PtrToStructure<iRegistryVTable>(registry.vTable);
		var classInstance = new iClassInstance {ClassInstanceVTable = {CreateInstance = CreateInstanceFunc}};

		var marshalledClassInstance = CustomMarshal(classInstance);
		ReferenceStorage.Add(marshalledClassInstance);
		return iRegistryVTable.Install(registryPtr, IDStore.KTestPlugin, marshalledClassInstance);
	}

	private uint CreateInstanceFunc(IntPtr self, iRegistry registry1, iUnknown outer, out IntPtr outInstance)
	{
		var testPlugin = new TestPlugin(outer);

		//outInstance = Marshal.AllocHGlobal(Marshal.SizeOf(testPlugin));
		//Marshal.StructureToPtr(testPlugin, outInstance, false);

		outInstance = CustomMarshal(testPlugin);
		ReferenceStorage.Add(outInstance);

		return 0x7b48e63f;
	}

	public uint Uninstall(IntPtr registryPtr)
	{
		var registry = Marshal.PtrToStructure<iRegistry>(registryPtr);
		var iRegistryVTable = Marshal.PtrToStructure<iRegistryVTable>(registry.vTable);

		return iRegistryVTable.Remove(registryPtr, IDStore.ITestPlugin);
	}

	public static IntPtr CustomMarshal(object o)
	{
		var type = o.GetType();
		var vTables = new List<FieldInfo>();
		var vTablePtr = IntPtr.Zero;
		var vTableSize = 0;
		var fields = new List<Tuple<FieldInfo, object>>();
		var marshalSize = 0;

		foreach (var fieldInfo in type.GetFields(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public).OrderBy(f => Marshal.OffsetOf(type, f.Name).ToInt64()))
		{
			if (fieldInfo.FieldType.GetCustomAttributes(typeof(VTableAttribute), true).Length > 0)
			{
				if (vTables.Count == 0)
				{
					marshalSize += Marshal.SizeOf<IntPtr>();
				}

				vTables.Add(fieldInfo);
				vTableSize += Marshal.SizeOf(fieldInfo.FieldType);
				//var fieldPtr = Marshal.AllocHGlobal(Marshal.SizeOf(fieldInfo.FieldType));
				//Marshal.StructureToPtr(fieldInfo.GetValue(o), fieldPtr, false);

				//marshalSize += Marshal.SizeOf(fieldPtr);
				//fields.Add(new Tuple<FieldInfo, object>(fieldInfo, fieldPtr));
			}
			else
			{
				marshalSize += Marshal.SizeOf(fieldInfo.FieldType);
				fields.Add(new Tuple<FieldInfo, object>(fieldInfo, fieldInfo.GetValue(o)));
			}
		}

		if (vTables.Count > 0)
		{
			vTablePtr = Marshal.AllocHGlobal(vTableSize);
			var writeLocation = vTablePtr;

			foreach (var fieldInfo in vTables)
			{
				Marshal.StructureToPtr(fieldInfo.GetValue(o), writeLocation, false);
				writeLocation += Marshal.SizeOf(fieldInfo.FieldType);
			}
		}

		var structPtr = Marshal.AllocHGlobal(marshalSize);
		IntPtr writePtr = structPtr;

		if (vTablePtr != IntPtr.Zero)
		{
			Marshal.WriteIntPtr(writePtr, vTablePtr);
			writePtr += Marshal.SizeOf<IntPtr>();
		}

		foreach (var field in fields)
		{
			var sizeOf = Marshal.SizeOf(field.Item1.FieldType);
			switch (sizeOf)
			{
				case 1:
					Marshal.WriteByte(writePtr, (Byte)field.Item2);
					writePtr += sizeOf;
					break;
				case 2:
					Marshal.WriteInt16(writePtr, (Int16)field.Item2);
					writePtr += sizeOf;
					break;
				case 4:
					Marshal.WriteInt32(writePtr, (Int32)field.Item2);
					writePtr += sizeOf;
					break;
				case 8:
					Marshal.WriteInt64(writePtr, (Int64)field.Item2);
					writePtr += sizeOf;
					break;
				default:
					throw new ArgumentOutOfRangeException();
			}
		}

		return structPtr;
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

[VTable]
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
public class iUnknown
{
	public iUnknownVTable VTable = new iUnknownVTable();
	private int refCount;

	public iUnknown()
	{
		refCount = 1;
		ReferenceStorage.Add(this);

		VTable.AddRef = (self) => ++refCount;
		VTable.Release = (self) =>
		{
			--refCount;

			if (refCount == 0)
			{
				ReferenceStorage.Remove(this);
			}

			return refCount;
		};
		VTable.QueryInterface = (self, id, face) =>
		{
			switch (id)
			{
				case IDStore.iUnknown:
				{
					Marshal.WriteIntPtr(face, self);
					break;
				}
				default:
					return 999;
			}

			VTable.AddRef(self);
			return 0x7b48e63f;
		};
	}
}

[VTable]
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
	public delegate UInt32 InstallFunc(IntPtr self, UInt64 cid, IntPtr clsInst);

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
	public delegate UInt32 CreateFunc(IntPtr self, iUnknown outer, UInt64 cid, UInt64 iid, MarshalVTable outIface);

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

[VTable]
[StructLayout(LayoutKind.Sequential)]
public class iClassInstanceVTable
{
	[UnmanagedFunctionPointer(CallingConvention.StdCall)]
	public delegate UInt32 CreateInstanceFunc(IntPtr self, iRegistry registry, iUnknown outer, out IntPtr outInstance);

	[MarshalAs(UnmanagedType.FunctionPtr)]
	public CreateInstanceFunc CreateInstance;
	//public IntPtr CreateInstance;
}
[StructLayout(LayoutKind.Sequential)]
public class iClassInstance : iUnknown
{
	public iClassInstanceVTable ClassInstanceVTable = new iClassInstanceVTable();
}