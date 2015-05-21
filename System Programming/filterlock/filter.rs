use std::thread;
use std::thread::yield_now;
use std::sync::atomic::fence;
use std::sync::atomic::Ordering::*;
use std::marker::Sync;

static mut var: i32 = 0;

fn main() {
    let n = 8;
    let filter = Filter::new(n);
    let addr = &filter as *const Filter as usize;

    let mut threads = Vec::new();
    for id in 0..n {
        threads.push(thread::spawn(move || {
            let filter = unsafe { &mut *(addr as *mut Filter) };
            for _ in 0..1000_0000/n {
                filter.lock(id);
                unsafe { var += 1 }
                filter.unlock(id);
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

/// Slow starvation-free binary semaphore
struct Filter {
    thread_count: usize,
    levels: Vec<usize>,
    victims: Vec<usize>
}

impl Filter {
    fn new(thread_count: usize) -> Self {
        Filter {
            thread_count: thread_count,
            levels:  vec![0; thread_count],
            victims: vec![0; thread_count]
        }
    }

    fn lock(&mut self, id: usize) {
        for level in 1..self.thread_count {
            self.levels[id] = level;
            self.victims[level] = id;
            fence(SeqCst);

            let cond1 = || {
                for other in 0..self.thread_count {
                    if id == other { continue; }

                    fence(SeqCst);
                    if self.levels[other] >= level { return true; }
                }
                false
            };

            let cond2 = || { fence(SeqCst); self.victims[level] == id };

            while cond1() && cond2() { yield_now(); }
        }
    }

    fn unlock(&mut self, id: usize) {
        self.levels[id] = 0;
        fence(SeqCst);
    }
}

unsafe impl Sync for Filter {}
