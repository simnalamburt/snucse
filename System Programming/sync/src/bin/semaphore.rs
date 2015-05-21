#![feature(std_misc)]

use std::sync::{Arc, Semaphore};
use std::thread;

static mut var: i32 = 0;

fn main() {
    let sem = Arc::new(Semaphore::new(1));

    let n = 8;

    let mut threads = Vec::new();
    for _ in 0..n {
        let sem = sem.clone();
        threads.push(thread::spawn(move || {
            for _ in 0..100_0000/n {
                let _guard = sem.access();
                unsafe { var += 1 }
            }
        }))
    }

    for thread in threads.into_iter() {
        let _ = thread.join();
    }

    unsafe {
        println!("var : {}", var);
    }
}
