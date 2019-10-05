# Assember output
cargo asm data_bench::main --no-color>data_bench.asm
echo>>data_bench.asm
cargo asm data_bench::benchmark --no-color>data_bench.asm
echo>>data_bench.asm
cargo asm data_bench::test_initialize_and_assign_different --no-color>data_bench.asm
# Compile Rust and run output
cargo run --release 2>/dev/null

# Wait for input to exit script
read -n1 -r -p "Press any key..."