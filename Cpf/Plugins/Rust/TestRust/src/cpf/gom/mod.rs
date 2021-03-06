pub mod result;
pub use self::result::*;
pub mod iid_cid;
pub use self::iid_cid::*;

#[macro_use]
pub mod gom_interface;
#[macro_use]
pub mod iunknown;
pub use self::iunknown::*;
