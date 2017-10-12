[StructLayout(LayoutKind.Sequential)]
public class iClassInstanceVTable : iUnknownVTable
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate UInt32 CreateInstanceFunc(IntPtr self, iRegistry registry, GOMiUnknown outer, GOMiUnknown outInstance);    
    
    [MarshalAs(UnmanagedType.FunctionPtr)]
    public CreateInstanceFunc CreateInstance;

}
public interface iClassInstance
{
    UInt32 CreateInstance(IntPtr self, iRegistry registry, GOMiUnknown outer, GOMiUnknown outInstance);    
}
public class iClassInstanceWrapper
{
    private IntPtr unmanagedInstance;
    private iClassInstance instance;
    private iClassInstanceVTable vTable = new iClassInstanceVTable();
    private GenericObject genericObject = new GenericObject();

    public iClassInstanceWrapper(IntPtr unmanagedInst)
    {
        unmanagedInstance = unmanagedInst;
        Marshal.PtrToStructure(unmanagedInst, genericObject);
        Marshal.PtrToStructure(genericObject.VTablePtr, vTable);
    }

    public iClassInstanceWrapper(iClassInstance inst)
    {
        instance = inst;
        var unknown = (IUnknown)inst;
        
        vTable.AddRef = unknown.AddRef;
        vTable.Release = unknown.Release;
        vTable.QueryInterface = unknown.QueryInterface;
        vTable.CreateInstance = inst.CreateInstance;
    }

    public UInt32 CreateInstance(iRegistry registry, GOMiUnknown outer, GOMiUnknown outInstance)
    {
         return vTable.CreateInstance(unmanagedInstance, registry, outer, outInstance);
    }
}
