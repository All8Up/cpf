using System;

namespace ComTest
{
	public interface IUnknown
	{
		int AddRef(IntPtr self);
		int Release(IntPtr self);
		int QueryInterface(IntPtr self, ulong id, IntPtr outInterface);
	}
}