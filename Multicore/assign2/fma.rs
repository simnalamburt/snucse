fn main() {
    let size = 1024;

    let mut mem = vec![(0.0f32, 0.0f32, 0.0f32, 0.0f32); size];

    let mut i = 0.0;
    let constant = 1000.0;
    for elem in mem.iter_mut() {
        elem.1 = i;
        elem.2 = i + constant;
        elem.3 = i + constant*2.0;

        i += 1.0;
    }

    // begin

    for elem in mem.iter_mut() {
        elem.0 = elem.1 * elem.2 + elem.3
    }

    // end

    for elem in mem.into_iter() {
        println!("{}", elem.0);
    }
}
