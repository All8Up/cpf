using System;

namespace CPF.Plugin
{
	public class TestPlugin : Unknown, iTestPlugin
	{
		public TestPlugin(IntPtr iUnknown)
		{
			AddWrapper(new iTestPluginWrapper(this));
		}

		public uint Test(IntPtr self)
		{
			return 0;
		}
	}
}
