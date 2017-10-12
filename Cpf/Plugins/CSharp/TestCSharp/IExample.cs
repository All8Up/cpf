using System;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;

namespace ComTest
{
	public interface IExample
	{
		int DoThing(IntPtr self);
		void SomeThing(IntPtr self, int i, ref IntPtr ptr);
	}

	[StructLayout(LayoutKind.Sequential)]
	public class GenericObject
	{
		public IntPtr VTablePtr;
	}

	[StructLayout(LayoutKind.Sequential)]
	public class ExampleVTable : iUnknownVTable
	{
		public delegate int DoThingFunc(IntPtr self);
		public delegate void SomeThingFunc(IntPtr self, int i, ref IntPtr ptr);

		public DoThingFunc DoThing;
		public SomeThingFunc SomeThing;
	}

	[StructLayout(LayoutKind.Sequential)]
	public class ExampleWrapper
	{
		private IExample inst;
		private ExampleVTable vTable = new ExampleVTable();
		private GenericObject genericObject = new GenericObject();

		public ExampleWrapper(IExample inst)
		{
			this.inst = inst;
			var unknown = (IUnknown)inst;

			vTable.AddRef = unknown.AddRef;
			vTable.Release = unknown.Release;
			vTable.QueryInterface = unknown.QueryInterface;
			vTable.DoThing = inst.DoThing;
			vTable.SomeThing = inst.SomeThing;

			Marshal.StructureToPtr(vTable, genericObject.VTablePtr, false);
		}
	}
}