#![feature(std_misc)]

extern crate time;

use time::PreciseTime;

fn test(exp: usize) {
    let size = 2 << exp;
    let mask = size - 1;
    let mut arr = vec![0u8; size];

    let t0 = PreciseTime::now();

    for i in 0usize..64*1024*1024 {
        arr[(i * 16) & mask] += 1;
        // x & lengthMod == x % arr.Length
    }

    let t1 = PreciseTime::now();
    let t = t0.to(t1).num_nanoseconds().unwrap();
    println!("{:>15}, {:>15}", size, t);
}

fn main() {
    println!("{:>15}, {:>15}", "size", "t");
    for n in 10..30 { test(n) }
}
