using System;
using System.CodeDom;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using ComTest;

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
		var registry = new iRegistryWrapper(registryPtr);
		var classInstanceWrapper = new iClassInstanceWrapper(new MyClassInstance());

		ReferenceStorage.Add(classInstanceWrapper);

		return registry.Install(IDStore.KTestPlugin, classInstanceWrapper.NativePointer);
	}

	public uint Uninstall(IntPtr registryPtr)
	{
		var registry = new iRegistryWrapper(registryPtr);

		return registry.Remove(IDStore.ITestPlugin);
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
}

[StructLayout(LayoutKind.Sequential)]
public class GenericObject
{
	public IntPtr VTablePtr;
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

[StructLayout(LayoutKind.Sequential)]
public struct IID_CID
{
	public UInt64 mIID { get; set; }
	public UInt64 mCID { get; set; }
}