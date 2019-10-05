#include <stdlib.h>	// malloc, free
#include <string.h>	// memset
#include <stdio.h>	// fprintf, printf
#include <time.h>	// clock

#define BUFFER_SIZE 1920*1080*4

// Tests
static void test_initialize() {
	unsigned char* const buf = malloc(BUFFER_SIZE);
	fprintf(stderr, "Buffer address: %p\n", buf);	// Avoid optimization removes payload
	free(buf);
}
static void test_initialize_and_memset() {
	unsigned char* const buf = malloc(BUFFER_SIZE);
	memset(buf, 255, BUFFER_SIZE);
	fprintf(stderr, "Buffer address: %p\n", buf);	// Avoid optimization removes payload
	free(buf);
}
static void test_initialize_and_assign() {
	unsigned char* buf = malloc(BUFFER_SIZE);
	for (unsigned char* buf_ptr = buf, *buf_ptr_end = buf + BUFFER_SIZE; buf_ptr < buf_ptr_end; buf_ptr++)
		*buf_ptr = 255;
	fprintf(stderr, "Buffer address: %p\n", buf);	// Avoid optimization removes payload
	free(buf);
}
static void test_initialize_and_assign_different() {
	unsigned char* buf = malloc(BUFFER_SIZE);
	unsigned char buf_value = 0;
	for (unsigned char* buf_ptr = buf, *buf_ptr_end = buf + BUFFER_SIZE; buf_ptr < buf_ptr_end; buf_ptr++, buf_value = ~buf_value)
		*buf_ptr = buf_value;
	fprintf(stderr, "Buffer address: %p\n", buf);	// Avoid optimization removes payload
	free(buf);
}

// Benchmark
static void benchmark(const char* const name, void(*test_func)()) {
	const clock_t start_time = clock(), end_time = start_time + 2 * CLOCKS_PER_SEC;
	unsigned int runs;
	for(runs = 0; clock() < end_time; runs++)
		test_func();
	const double total_seconds = ((double)(clock() - start_time)) / CLOCKS_PER_SEC;
	printf("Test: %s\nTotal seconds: %f\nRuns: %d\nAverage milliseconds: %f\n\n", name, total_seconds, runs, total_seconds * 1000 / runs);
}

// Test suite
int main() {
	benchmark("Initialize", &test_initialize);
	benchmark("Initialize and memset", &test_initialize_and_memset);
	benchmark("Initialize and assign", &test_initialize_and_assign);
	benchmark("Initialize and assign different", &test_initialize_and_assign_different);
	return 0;
}

