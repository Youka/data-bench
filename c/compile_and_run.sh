# Compile C to Assember
gcc main.c -o main.asm -Wall -O3 -S
# Compile C to executable
gcc main.c -o main -Wall -O3
# Run output
./main 2>/dev/null

# Wait for input to exit script
read -n1 -r -p "Press any key..."