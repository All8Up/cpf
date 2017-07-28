#[macro_export]
macro_rules! gom_interface
{
    (
        $(#[$attribs:meta])*
        $interface:ident : $iid_name:expr,
        $vtable:ident,
        methods {
            $($(#[$fn_attr:meta])* fn $func:ident($($i:ident: $t:ty),*) -> $rt:ty;)*
        }
    ) => (
        #[repr(C)]
        #[derive(Debug)]
        pub struct $interface
        {
            pub vtable: *const $vtable
        }

        #[repr(C)]
        pub struct $vtable
        {
            pub base: gom::iUnknownVTable,
            $(pub $func: extern "stdcall" fn(*mut $interface, $($i: $t),*) -> $rt),*
        }

        impl $interface
        {
            $(pub fn $func(&mut self, $($i: $t),*) -> $rt
            { unsafe { ((*self.vtable).$func)(self as *mut _ as *mut $interface, $($i),*) } })*
        }

        unsafe impl AsPtr<gom::iUnknown> for $interface {}
        unsafe impl ::GomInterface for $interface { type Vtable = $vtable; }

        impl gom::Unknown for $interface
        {
            fn add_ref(&mut self) -> i32 { unsafe { ((*self.vtable).base.add_ref)(self as *mut _ as *mut gom::iUnknown) } }
            fn release(&mut self) -> i32 { unsafe { ((*self.vtable).base.release)(self as *mut _ as *mut gom::iUnknown) } }
            fn query_interface(&mut self, iid: u64, out_iface: *mut *mut c_void) -> u32
            { unsafe { ((*self.vtable).base.query_interface)(self as *mut _ as *mut gom::iUnknown, iid, out_iface) } }
        }
    );

    (
        $(#[$attribs:meta])*
        impl $impl: ident : $interface:ident : $iid_name:expr,
        $vtable:ident,
        methods {
            $($(#[$fn_attr:meta])* fn $func:ident($($i:ident: $t:ty),*) -> $rt:ty;)*
        }
    ) => (
        #[repr(C)]
        #[derive(Debug)]
        pub struct $interface
        {
            pub vtable: *const $vtable
        }

        #[repr(C)]
        pub struct $vtable
        {
            pub base: gom::iUnknownVTable,
            $(pub $func: extern "stdcall" fn(*mut $interface, $($t),*) -> $rt),*
        }

        unsafe impl AsPtr<gom::iUnknown> for $interface {}
        unsafe impl ::GomInterface for $interface { type Vtable = $vtable; }

        impl gom::Unknown for $interface
        {
            fn add_ref(&mut self) -> i32 { unsafe { ((*self.vtable).base.add_ref)(self as *mut _ as *mut gom::iUnknown) } }
            fn release(&mut self) -> i32 { unsafe { ((*self.vtable).base.release)(self as *mut _ as *mut gom::iUnknown) } }
            fn query_interface(&mut self, iid: u64, out_iface: *mut *mut c_void) -> u32
            { unsafe { ((*self.vtable).base.query_interface)(self as *mut _ as *mut gom::iUnknown, iid, out_iface) } }
        }

        impl $vtable
        {
            extern "stdcall" fn add_ref(inst: *mut gom::iUnknown) -> i32
            {
                unsafe
                {
                    let this : *mut $impl = inst as *mut $impl;
                    (*this).ref_count += 1;
                    (*this).ref_count
                }
            }

            extern "stdcall" fn release(inst: *mut gom::iUnknown) -> i32
            {
                unsafe
                {
                    let this : *mut $impl = inst as *mut $impl;
                    (*this).ref_count -= 1;
                    if (*this).ref_count == 0
                    {
                        // NOTE: Must use the cast pointer or the free will fail to drop internal references.
                        Box::from_raw(this);
                        return 0;
                    }
                    (*this).ref_count
                }
            }

            extern "stdcall" fn query_interface(
                inst: *mut gom::iUnknown,
                iid: u64,
                out_iface: *mut *mut ::libc::c_void
                ) -> u32
            {
                unsafe
                {
                    let this : *mut $impl = inst as *mut $impl;
                    match iid
                    {
                        // TODO: Need a method to generate IID's in Rust code.
                        // I would like to use a compiler plugin to add compile time CRC's but
                        // that requires non-mainline Rust.
                        1 =>
                        {
                            *out_iface = inst as *mut ::libc::c_void;
                            ((*(*this).vtable).base.add_ref)(inst as *mut gom::iUnknown);
                            gom::OK
                        },
                        _ =>
                        {
                            *out_iface = 0 as *mut ::libc::c_void;
                            gom::UNKNOWN_INTERFACE
                        }
                    }
                }
            }
        }
    );
}

#[macro_export]
macro_rules! gom_impl
{
    (
        $implstruct:ident : $vtable:ident
        { $($mname:ident: $mtype:ty,)* }
    )
    =>
    (
        struct $implstruct
        {
            vtable: *const $vtable,
            ref_count: i32,
            $($mname: $mtype),*
        }
    )
}

#[macro_export]
macro_rules! com_interface {
    (
        $(#[$iface_attr:meta])*
        interface $iface:ident: $base_iface:ty {
            iid: $iid:ident,
            vtable: $vtable:ident,
            $(
                $(#[$fn_attr:meta])*
                fn $func:ident($($i:ident: $t:ty),*) -> $rt:ty;
            )*
        }
    ) => (
        #[allow(missing_debug_implementations)]
        #[doc(hidden)]
        #[repr(C)]
        pub struct $vtable {
            base: <$base_iface as $crate::ComInterface>::Vtable,
            $($func: extern "stdcall" fn(*const $iface, $($t),*) -> $rt),*
        }

        $(#[$iface_attr])*
        #[derive(Debug)]
        #[repr(C)]
        pub struct $iface {
            vtable: *const $vtable
        }

        impl $iface {
            $($(#[$fn_attr])*
            pub unsafe fn $func(&self, $($i: $t),*) -> $rt {
                ((*self.vtable).$func)(self $(,$i)*)
            })*
        }

        impl ::std::ops::Deref for $iface {
            type Target = $base_iface;
            fn deref(&self) -> &$base_iface {
                unsafe { ::std::mem::transmute(self) }
            }
        }

        unsafe impl $crate::AsComPtr<$iface> for $iface {}
        unsafe impl $crate::AsComPtr<$base_iface> for $iface {}

        unsafe impl $crate::ComInterface for $iface {
            #[doc(hidden)]
            type Vtable = $vtable;
            #[allow(unused_unsafe)]
            fn iid() -> $crate::IID { unsafe { $iid } }
        }
    );

    (
        $(#[$iface_attr:meta])*
        interface $iface:ident: $base_iface:ty, $($extra_base:ty),+ {
            iid: $iid:ident,
            vtable: $vtable:ident,
            $(
                $(#[$fn_attr:meta])*
                fn $func:ident($($i:ident: $t:ty),*) -> $rt:ty;
            )*
        }
    ) => (
        com_interface! {
            $(#[$iface_attr])*
            interface $iface: $base_iface {
                iid: $iid,
                vtable: $vtable,
                $($(#[$fn_attr])* fn $func($($i: $t),*) -> $rt;)*
            }
        }

        $(unsafe impl $crate::AsComPtr<$extra_base> for $iface {})*
    )
}
