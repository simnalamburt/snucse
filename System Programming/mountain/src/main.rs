#![feature(core, std_misc)]

extern crate time;

use std::iter::range_inclusive;
use time::PreciseTime;

fn main() {
    println!("stride,size,t");
    for stride in range_inclusive(1, 32) {
        for size in range_inclusive(10, 25) {
            test(stride, size)
        }
    }
}

fn test(stride: usize, exp: usize) {
    let size = 2 << exp;
    let mut arr = vec![0u8; size];

    let mask = size - 1; // x & mask == x % arr.len()
    let t0 = PreciseTime::now();

    for i in 0usize..64*1024*1024 {
        arr[(i * stride) & mask] += 1;
    }

    let t1 = PreciseTime::now();
    let t = t0.to(t1).num_nanoseconds().unwrap();
    println!("{},{},{}", stride, size, t);
}
