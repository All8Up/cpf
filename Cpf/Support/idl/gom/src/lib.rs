#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
    }
}


pub struct Result (pub u32);

pub fn succeeded (result : &Result) -> bool
{
	if result.0 & 0x80000000 == 0
	{
		return true;
	}
	return false;
}

pub fn failed (result : &Result) -> bool
{
	if result.0 & 0x80000000 == 0
	{
		return false;
	}
	return true;
}
