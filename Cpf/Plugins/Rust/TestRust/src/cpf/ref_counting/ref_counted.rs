pub trait RefCounted
{
	fn AddRef(&mut self) -> i32;
	fn Release(&mut self) -> i32;
}
