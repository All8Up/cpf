using System.Collections.Generic;
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