const BUFFER_SIZE: usize = 1920*1080*4;

// Tests
fn test_initialize() {
	let buf = vec![0u8;BUFFER_SIZE];
	eprintln!("Buffer length: {}", buf.len());	// Avoid optimization removes payload
}
fn test_initialize_and_memset() {
	let buf = vec![255u8;BUFFER_SIZE];
	eprintln!("Buffer length: {}", buf.len());	// Avoid optimization removes payload
}
fn test_initialize_and_assign() {
	let mut buf = vec![0u8;BUFFER_SIZE];
	for v in &mut buf {*v = 255u8}
	eprintln!("Buffer length: {}", buf.len());	// Avoid optimization removes payload
}
fn test_initialize_and_assign_different() {
	let mut buf = vec![0u8;BUFFER_SIZE];
	let mut buf_value = 0u8;
	for v in &mut buf {*v = buf_value; buf_value = !buf_value}
	eprintln!("Buffer length: {}", buf.len());	// Avoid optimization removes payload
}

// Benchmark
fn benchmark(name: &str, test_func: &Fn()) {
	let now = std::time::SystemTime::now();
	let mut runs = 0u32;
	while now.elapsed().map(|elapsed| elapsed.as_secs() < 2 ).unwrap() {
		test_func();
		runs += 1;
	}
	let elapsed = now.elapsed().unwrap();
	println!("Test: {}\nTotal seconds: {}\nRuns: {}\nAverage milliseconds: {}\n", name, elapsed.as_secs(), runs, elapsed.as_millis() as f64 / runs as f64);
}

// Test suite
fn main() {
	benchmark("Initialize", &test_initialize);
	benchmark("Initialize and memset", &test_initialize_and_memset);
	benchmark("Initialize and assign", &test_initialize_and_assign);
	benchmark("Initialize and assign different", &test_initialize_and_assign_different);
}