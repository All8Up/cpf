using System;

namespace ComTest
{
	public class MyClassInstance : Unknown, iClassInstance
	{
		public MyClassInstance()
		{
			AddWrapper(new iClassInstanceWrapper(this));
		}

		public uint CreateInstance(IntPtr self, IntPtr registry, IUnknown outer, out IntPtr outInstance)
		{
			var testPlugin = new TestPlugin(outer);

			outInstance = testPlugin.QueryInterface<iTestPluginWrapper>();

			return 0x7b48e63f;
		}
	}
}