use cpf::*;
use std::mem;
use std::ptr;
use std::ops::Deref;
use std::ops::DerefMut;
use std::os::raw::c_void;

#[derive(Debug)]
pub struct IntrusivePtr<T: gom::Unknown>
{
	ptr: *mut T
}

// Traits to allow casting.
pub unsafe trait AsPtr<T> {}
unsafe impl<T: gom::Unknown> AsPtr<c_void> for T {}

pub unsafe trait GomInterface: AsPtr<gom::iUnknown>
{
    #[doc(hidden)]
    type Vtable;
}

// Implementation for intrusive_ptr.
impl<T: gom::Unknown> IntrusivePtr<T>
{
	pub fn new() -> IntrusivePtr<T>
	{
		IntrusivePtr { ptr: ptr::null_mut() }
	}

	pub fn from_raw(ptr: *mut T) -> IntrusivePtr<T>
	{
		let mut result = IntrusivePtr { ptr: ptr };
		result.add_ref();
		result
	}

	pub fn is_null(&self) -> bool
	{
		self.ptr.is_null()
	}

	pub fn as_ptr<U>(&self) -> *const U where T: AsPtr<U>
	{
		self.ptr as *const U
	}

	pub fn as_mut_ptr<U>(&mut self) -> &mut *mut U where T: AsPtr<U>
	{
		unsafe { mem::transmute(&mut self.ptr) }
	}
}

impl<T: gom::Unknown> Clone for IntrusivePtr<T>
{
	fn clone(&self) -> IntrusivePtr<T>
	{
		if !self.is_null()
		{
			unsafe { (*self.ptr).add_ref(); }
		}
		IntrusivePtr {ptr: self.ptr}
	}
}

impl<T: gom::Unknown> Drop for IntrusivePtr<T>
{
	fn drop(&mut self)
	{
		if !self.is_null()
		{
			unsafe { (*self.ptr).release(); }
		}
	}
}

impl<T: gom::Unknown> Deref for IntrusivePtr<T>
{
	type Target = T;
	fn deref<'a>(&'a self) -> &'a T
	{
		assert!(!self.is_null(), "Deref of null pointer.");
		unsafe {&*self.ptr}
	}
}

impl<T: gom::Unknown> DerefMut for IntrusivePtr<T>
{
	fn deref_mut<'a>(&'a mut self) -> &'a mut T
	{
		assert!(!self.is_null(), "Deref of null pointer.");
		unsafe {&mut *self.ptr}
	}
}
