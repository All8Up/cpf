using System;
using System.Runtime.InteropServices;
using ComTest;

[StructLayout(LayoutKind.Sequential)]
public class iTestPluginVTable : iUnknownVTable
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate UInt32 TestFunc(IntPtr self);    
    
    [MarshalAs(UnmanagedType.FunctionPtr)]
    public TestFunc Test;

}
public interface iTestPlugin
{
    UInt32 Test(IntPtr self);    
}
public class iTestPluginWrapper : IWrapper
{
    private IntPtr unmanagedInstance;
    private iTestPlugin instance;
    private iTestPluginVTable vTable = new iTestPluginVTable();
    private GenericObject genericObject = new GenericObject();

    public IntPtr NativePointer => unmanagedInstance;
    public UInt64 CID => 0x5B145B3470AE5B89;

    public iTestPluginWrapper(IntPtr unmanagedInst)
    {
        unmanagedInstance = unmanagedInst;
        Marshal.PtrToStructure(unmanagedInst, genericObject);
        Marshal.PtrToStructure(genericObject.VTablePtr, vTable);
    }

    public iTestPluginWrapper(iTestPlugin inst)
    {
        instance = inst;
        var unknown = (IUnknown)inst;
        
        vTable.AddRef = unknown.AddRef;
        vTable.Release = unknown.Release;
        vTable.QueryInterface = unknown.QueryInterface;
        vTable.Test = inst.Test;
        genericObject.VTablePtr = Marshal.AllocHGlobal(Marshal.SizeOf(vTable));
        unmanagedInstance = Marshal.AllocHGlobal(Marshal.SizeOf(genericObject));
        Marshal.StructureToPtr(vTable, genericObject.VTablePtr, false);
        Marshal.StructureToPtr(genericObject, unmanagedInstance, false);
    }

    public UInt32 Test()
    {
         return vTable.Test(unmanagedInstance);
    }
}
