#![feature(std_misc)]

extern crate time;

use time::PreciseTime;

fn test(num: usize) {
    let size = num*num;
    let a = vec![b'a'; size];
    let mut b = vec![0u8; size];

    let t0 = PreciseTime::now();

    // Sequential Access
    let mut i = 0;
    while i < size {
        b[i] = a[i];
        i += 1;
    }

    let t1 = PreciseTime::now();

    // Random Access
    let mut x = 0;
    let mut y: usize;
    while x < num {
        y = 0;
        while y < size {
            b[x + y] = a[x + y];
            y += num;
        }
        x += 1;
    }

    let t2 = PreciseTime::now();

    let friendly = t0.to(t1).num_nanoseconds().unwrap();
    let unfriendly = t1.to(t2).num_nanoseconds().unwrap();
    let ratio = friendly as f64/unfriendly as f64;

    println!("{:>5}, {:>10}, {:>20}, {:>20}, {:>20}", num, size, friendly, unfriendly, ratio);
}

fn main() {
    println!("{:>5}, {:>10}, {:>20}, {:>20}, {:>20}", "#", "size", "friendly", "unfriendly", "unfriendly / friendly");
    for num in 1usize..10000 { test(num) }
}
