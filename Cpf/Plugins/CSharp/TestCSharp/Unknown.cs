using System;

namespace ComTest
{
	public class Unknown : IUnknown
	{
		private int refCount;

		public Unknown()
		{
			refCount = 1;
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
				
			}

			return refCount;
		}

		public virtual int QueryInterface(IntPtr self, ulong id, IntPtr outInterface)
		{
			throw new NotImplementedException();
		}
	}
}