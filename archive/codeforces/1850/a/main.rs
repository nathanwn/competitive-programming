use std::{
    io::{self},
};

fn main() {
    let reader = io::BufReader::new(io::stdin);
    let buf_cap = 8192;
    let buf = Vec<u8>::with_capacity(buf_cap);
    for _ in 0..buf_cap {
        buf.push(u8::default);
    }
}
