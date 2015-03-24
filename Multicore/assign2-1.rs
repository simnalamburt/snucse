fn main() {
    let array = [0.001f32, 0.002, 0.003, 0.004, 0.005, 0.06, 0.9, 1.3, 2.5, 6.9, 10.5, 230.6, 1005.];
    println!("{:>12} : {}", "real", "1257.775");

    let mut sum = 0.0;
    for &num in array.iter() {
        sum += num;
    }
    println!("{:>12} : {}", "ascending", sum);

    let mut sum = 0.0;
    for &num in array.iter().rev() {
        sum += num;
    }
    println!("{:>12} : {}", "descending", sum);
}
