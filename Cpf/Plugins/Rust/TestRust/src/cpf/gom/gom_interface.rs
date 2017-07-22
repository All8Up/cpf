#[macro_export]
macro_rules! gom_interface
{
	(
		$(#[$attribs:meta])*
		interface $interface:ident: $base:ty
		{
			vtable: $vtable:ident;
			$(
				$(#[$fn_attr:meta])*
				fn $func:ident($($i:ident: $t:ty),*) -> $rt:ty;
			)*
		}
	) =>
	{
        #[repr(C)]
        pub struct $vtable {
            base: <$base as $crate::GomInterface>::Vtable,
            $($func: extern "stdcall" fn(*mut $interface, $($t),*) -> $rt),*
        }

		#[repr(C)]
		pub struct $interface
		{
			pub vtbl: *const $vtable
		}
	};
}


#[macro_export]
macro_rules! gom_implementation
{
	(
		$(#[$attribs:meta])*
		interface $interface:ident: $base:ty
		{
			vtable: $vtable:ident;
			members: { $($(#[$mbr_attr:meta])* $mbr:ident: $mbr_ty:ty,)* }
			$( $(#[$fn_attr:meta])* fn $func:ident($($i:ident: $t:ty),*) -> $rt:ty; )*
		}
	) =>
	{
        #[repr(C)]
        pub struct $vtable
        {
            base: <$base as $crate::GomInterface>::Vtable,
            $($func: extern "stdcall" fn(*mut $interface, $($t),*) -> $rt),*
        }

		#[repr(C)]
		pub struct $interface
		{
			pub vtbl: *const $vtable,
			$(pub $mbr: $mbr_ty),*
		}
	};
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
