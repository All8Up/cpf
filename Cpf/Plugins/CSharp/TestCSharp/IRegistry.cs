using System;
using System.Runtime.InteropServices;

namespace ComTest
{
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
		public delegate UInt32 CreateFunc(IntPtr self, IUnknown outer, UInt64 cid, UInt64 iid, IntPtr outIface);

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
		public delegate UInt32 InstanceInstallFunc(IntPtr self, UInt64 id, IUnknown instance);

		[MarshalAs(UnmanagedType.FunctionPtr)]
		public InstanceInstallFunc InstanceInstall;

		[UnmanagedFunctionPointer(CallingConvention.StdCall)]
		public delegate UInt32 InstanceRemoveFunc(IntPtr self, UInt64 id);

		[MarshalAs(UnmanagedType.FunctionPtr)]
		public InstanceRemoveFunc InstanceRemove;

		[UnmanagedFunctionPointer(CallingConvention.StdCall)]
		public delegate UInt32 GetInstanceFunc(IntPtr self, UInt64 id, IUnknown outIface);

		[MarshalAs(UnmanagedType.FunctionPtr)]
		public GetInstanceFunc GetInstance;

	}
	public interface iRegistry
	{
		UInt32 Load(IntPtr self, char library);
		UInt32 Unload(IntPtr self, char library);
		UInt32 Install(IntPtr self, UInt64 cid, IntPtr clsInst);
		UInt32 Remove(IntPtr self, UInt64 cid);
		UInt32 GetClassInstance(IntPtr self, UInt64 cid, iClassInstance clsInst);
		UInt32 Exists(IntPtr self, UInt64 cid);
		UInt32 Create(IntPtr self, IUnknown outer, UInt64 cid, UInt64 iid, IntPtr outIface);
		UInt32 ClassInstall(IntPtr self, Int32 count, IID_CID pairs);
		UInt32 ClassRemove(IntPtr self, Int32 count, IID_CID pairs);
		UInt32 GetClasses(IntPtr self, UInt64 id, ref Int32 count, ref UInt64 cid);
		UInt32 InstanceInstall(IntPtr self, UInt64 id, IUnknown instance);
		UInt32 InstanceRemove(IntPtr self, UInt64 id);
		UInt32 GetInstance(IntPtr self, UInt64 id, IUnknown outIface);
	}
	public class iRegistryWrapper
	{
		private IntPtr unmanagedInstance;
		private iRegistry instance;
		private iRegistryVTable vTable = new iRegistryVTable();
		private GenericObject genericObject = new GenericObject();

		public iRegistryWrapper(IntPtr unmanagedInst)
		{
			unmanagedInstance = unmanagedInst;
			Marshal.PtrToStructure(unmanagedInst, genericObject);
			Marshal.PtrToStructure(genericObject.VTablePtr, vTable);
		}

		public iRegistryWrapper(iRegistry inst)
		{
			instance = inst;
			var unknown = (IUnknown)inst;

			vTable.AddRef = unknown.AddRef;
			vTable.Release = unknown.Release;
			vTable.QueryInterface = unknown.QueryInterface;
			vTable.Load = inst.Load;
			vTable.Unload = inst.Unload;
			vTable.Install = inst.Install;
			vTable.Remove = inst.Remove;
			vTable.GetClassInstance = inst.GetClassInstance;
			vTable.Exists = inst.Exists;
			vTable.Create = inst.Create;
			vTable.ClassInstall = inst.ClassInstall;
			vTable.ClassRemove = inst.ClassRemove;
			vTable.GetClasses = inst.GetClasses;
			vTable.InstanceInstall = inst.InstanceInstall;
			vTable.InstanceRemove = inst.InstanceRemove;
			vTable.GetInstance = inst.GetInstance;
		}

		public UInt32 Load(char library)
		{
			return vTable.Load(unmanagedInstance, library);
		}

		public UInt32 Unload(char library)
		{
			return vTable.Unload(unmanagedInstance, library);
		}

		public UInt32 Install(UInt64 cid, IntPtr clsInst)
		{
			return vTable.Install(unmanagedInstance, cid, clsInst);
		}

		public UInt32 Remove(UInt64 cid)
		{
			return vTable.Remove(unmanagedInstance, cid);
		}

		public UInt32 GetClassInstance(UInt64 cid, iClassInstance clsInst)
		{
			return vTable.GetClassInstance(unmanagedInstance, cid, clsInst);
		}

		public UInt32 Exists(UInt64 cid)
		{
			return vTable.Exists(unmanagedInstance, cid);
		}

		public UInt32 Create(IUnknown outer, UInt64 cid, UInt64 iid, IntPtr outIface)
		{
			return vTable.Create(unmanagedInstance, outer, cid, iid, outIface);
		}

		public UInt32 ClassInstall(Int32 count, IID_CID pairs)
		{
			return vTable.ClassInstall(unmanagedInstance, count, pairs);
		}

		public UInt32 ClassRemove(Int32 count, IID_CID pairs)
		{
			return vTable.ClassRemove(unmanagedInstance, count, pairs);
		}

		public UInt32 GetClasses(UInt64 id, ref Int32 count, ref UInt64 cid)
		{
			return vTable.GetClasses(unmanagedInstance, id, ref count, ref cid);
		}

		public UInt32 InstanceInstall(UInt64 id, IUnknown instance)
		{
			return vTable.InstanceInstall(unmanagedInstance, id, instance);
		}

		public UInt32 InstanceRemove(UInt64 id)
		{
			return vTable.InstanceRemove(unmanagedInstance, id);
		}

		public UInt32 GetInstance(UInt64 id, IUnknown outIface)
		{
			return vTable.GetInstance(unmanagedInstance, id, outIface);
		}
	}


}