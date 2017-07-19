use cpf::*;
use std::mem;
use std::ptr;
use std::ops::Deref;
use std::os::raw::c_void;

#[derive(Debug)]
pub struct IntrusivePtr<T: RefCounted>
{
	ptr: *mut T
}

// Traits to allow casting.
pub unsafe trait AsPtr<T> {}
unsafe impl<T: RefCounted> AsPtr<c_void> for T {}


// Implementation for intrusive_ptr.
impl<T: RefCounted> IntrusivePtr<T>
{
	pub fn new() -> IntrusivePtr<T>
	{
		IntrusivePtr { ptr: ptr::null_mut() }
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

impl<T: RefCounted> Clone for IntrusivePtr<T>
{
	fn clone(&self) -> IntrusivePtr<T>
	{
		if !self.is_null()
		{
			unsafe { (*self.ptr).AddRef() }
		}
		IntrusivePtr {ptr: self.ptr}
	}
}

impl<T: RefCounted> Drop for IntrusivePtr<T>
{
	fn drop(&mut self)
	{
		if !self.is_null()
		{
			unsafe { (*self.ptr).Release() }
		}
	}
}

impl<T: RefCounted> Deref for IntrusivePtr<T>
{
	type Target = T;
	fn deref<'a>(&'a self) -> &'a T
	{
		assert!(!self.is_null(), "Deref of null pointer.");
		unsafe {&*self.ptr}
	}
}
