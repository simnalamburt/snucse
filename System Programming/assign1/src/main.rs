#![feature(std_misc)]

extern crate time;

use time::PreciseTime;

fn test(stride: usize, size: usize) {
    let a = vec![b'a'; size];
    let mut b = vec![0u8; size];

    let t0 = PreciseTime::now();

    // Sequential Access
    let mut idx: usize = 0;
    while idx < size {
        b[idx] = a[idx];
        idx += 1;
    }

    let t1 = PreciseTime::now();

    // Random Access
    let mut base: usize = 0;
    while base < stride {
        let mut idx = base;
        while idx < size {
            b[idx] = a[idx];
            idx += stride;
        }
        base += 1;
    }

    let t2 = PreciseTime::now();

    let friendly = t0.to(t1).num_nanoseconds().unwrap();
    let unfriendly = t1.to(t2).num_nanoseconds().unwrap();

    println!("{:>4}, {:>10}, {:>15}, {:>15}", stride, size, friendly, unfriendly);
}

fn main() {
    println!("{:>6}, {:>8}, {:>15}, {:>15}", "stride", "size", "friendly", "unfriendly");
    for n in 1..2050 {
        let stride = 4*n;
        test(stride, stride * stride)
    }

    /*
    println!("");
    println!("{:>6}, {:>8}, {:>15}, {:>15}", "stride", "size", "friendly", "unfriendly");
    for stride in 1usize..64 {
        for exp in 11..25 {
            test(stride, 2 << exp)
        }
    }
    println!("");
    */
}
