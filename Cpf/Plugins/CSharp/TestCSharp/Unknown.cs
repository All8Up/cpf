using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace CPF.Plugin
{
	public interface IWrapper
	{
		UInt64 CID { get; }
		IntPtr NativePointer { get; }
	}

	public class Unknown : IUnknown
	{
		private int refCount;
		private Dictionary<UInt64, IWrapper> wrappers = new Dictionary<UInt64, IWrapper>();
		private Dictionary<Type, IWrapper> wrappersByType = new Dictionary<Type, IWrapper>();

		public Unknown()
		{
			refCount = 1;
			ReferenceStorage.Add(this);
		}

		public int AddRef(IntPtr self)
		{
			return ++refCount;
		}

		public int Release(IntPtr self)
		{
			--refCount;

			if(refCount == 0)
			{
				ReferenceStorage.Remove(this);
			}

			return refCount;
		}

		public int QueryInterface(IntPtr self, ulong id, IntPtr outInterface)
		{
			if(id == 123456789)
			{
				Marshal.WriteIntPtr(outInterface, wrappers.First().Value.NativePointer);
				AddRef(self);
				return 0x7b48e63f;
			}
			
			if(wrappers.TryGetValue(id, out var wrapper))
			{
				Marshal.WriteIntPtr(outInterface, wrapper.NativePointer);
				AddRef(self);
				return 0x7b48e63f;
			}
			
			return 0;
		}

		public IntPtr QueryInterface<T>() where T : IWrapper
		{
			return wrappersByType[typeof(T)].NativePointer;
		}

		protected void AddWrapper(IWrapper wrapper)
		{
			wrappers.Add(wrapper.CID, wrapper);
			wrappersByType.Add(wrapper.GetType(), wrapper);
		}
	}
}