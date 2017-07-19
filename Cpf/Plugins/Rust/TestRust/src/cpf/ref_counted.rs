pub trait RefCounted
{
	fn AddRef(&mut self);
	fn Release(&mut self);
}
