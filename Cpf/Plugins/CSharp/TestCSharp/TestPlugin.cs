using System;

namespace ComTest
{
	public class TestPlugin : Unknown, iTestPlugin
	{
		public TestPlugin(IUnknown iUnknown)
		{
			AddWrapper(new iTestPluginWrapper(this));
		}

		public uint Test(IntPtr self)
		{
			return 0;
		}
	}
}
