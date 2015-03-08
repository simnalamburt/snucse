#![feature(std_misc)]

extern crate time;

use time::PreciseTime;

fn main() {
    println!("size,t");
    for n in 10..30 {
        test(n)
    }
}

fn test(exp: usize) {
    let stride = 16;
    let size = 2 << exp;
    let mut arr = vec![0u8; size];

    let mask = size - 1; // x & mask == x % arr.len()
    let t0 = PreciseTime::now();

    for i in 0usize..64*1024*1024 {
        arr[(i * stride) & mask] += 1;
    }

    let t1 = PreciseTime::now();
    let t = t0.to(t1).num_nanoseconds().unwrap();
    println!("{},{}", size, t);
}
