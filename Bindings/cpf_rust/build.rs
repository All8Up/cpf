use std::env;
//use std::fs::File;
//use std::io::Write;
use std::path::Path;
use std::process::Command;

fn main()
{
    let idl_dir = Path::new("../../Bin/Windows");
    let idl_cmd = idl_dir.join("IDL.exe");

    let out_dir = env::var("OUT_DIR").unwrap();
    let dest_path = Path::new(&out_dir).join("gom").join("result_codes.rs");

    let in_file = "\"../../Cpf/Libraries/Core/GOM/IDL/ResultCodes.idl\"";
    let out_file = dest_path.to_string_lossy();
    println!("{}", in_file);
    println!("{}", out_file);
    Command::new(idl_cmd)
        .arg(&format!("--input={} ", in_file))
        .arg(&format!("--output=\"{}\" ", out_file))
        .arg("--rust")
        .status().unwrap();

    /*
    let mut f = File::create(&dest_path).unwrap();

    f.write_all(b"
        pub fn message() -> &'static str {
            \"Hello, World!\"
        }
    ").unwrap();
    */
}
