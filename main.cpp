/**
 * ===============================
 * Radix Sort Benchmark and Tester
 * ===============================
 *
 * This script benchmarks a custom parallel radix sort implementation against std::sort.
 * 
 * - All strings are fixed-length (STR_LENGTH).
 * - Alphabet is limited to specific uppercase letters (ALPHABET).
 * - Sorting is done by pointer for performance.
 * 
 * Two algorithms are evaluated:
 *   - Student's radix sort (`radix_par`)
 *   - Standard library sort (`std::sort`)
 * 
 * Execution time is measured and correctness is verified by comparing to std::sort.
 */

#include "sort.h"
#include "test.h"

#include <cstdint>
#include <cstddef>
#include <random>
#include <algorithm>
#include <chrono>

constexpr uint64_t SEED = 1;
std::mt19937 rng(SEED); // Mersenne-Twister RNG with fixed seed for reproducibility

constexpr size_t STR_COUNT = 10'000'000; // Number of strings
constexpr size_t STR_LENGTH = 3;         // Length of each string (uniform length)

const std::string ALPHABET = "ABCDE";    // Alphabet used to generate strings
const char alphabet_offset = ALPHABET.at(0);

// Maps a character to its bucket index based on alphabet
size_t get_bucket(char c) {
    return c - alphabet_offset;
}

// Generates uniformly random strings using characters from ALPHABET
std::vector<std::string> generate_strings(size_t count, size_t length) {
    std::uniform_int_distribution<size_t> dist(0, ALPHABET.size() - 1);
    std::vector<std::string> strings(count);
    for (size_t i = 0; i < count; ++i) {
        std::string s;
        s.reserve(length);
        for (size_t j = 0; j < length; ++j) {
            s.push_back(ALPHABET[dist(rng)]);
        }
        strings[i] = s;
    }
    return strings;
}

// Student's radix sort implementation wrapper
auto radix_sort = [](std::vector<std::string*>& vector_to_sort) {
    radix_par(vector_to_sort, get_bucket, ALPHABET.size(), STR_LENGTH);
};

// std::sort wrapper with proper pointer dereferencing
auto std_sort = [](std::vector<std::string*>& vector_to_sort) {
    std::sort(vector_to_sort.begin(), vector_to_sort.end(), [](std::string* a, std::string* b) {
        return *a < *b;
    });
};

// Runs and times a sorting algorithm, verifies result against std::sort
void eval(const char* test_name, std::vector<std::string>& data, auto sorting_algorithm) {
    SortingTest test{data, sorting_algorithm};

    try {
        auto begin = std::chrono::steady_clock::now();
        test.run_sort();
        auto end = std::chrono::steady_clock::now();

        if (!test.verify(data, std_sort)) {
            printf("%s       --- wrong result ---\n", test_name);
        } else {
            auto ms = duration_cast<std::chrono::milliseconds>(end - begin);
            printf("%s          %7ldms\n", test_name, ms.count());
        }
    } catch (...) {
        printf("%s      --- not implemented ---\n", test_name);
    }
}

int main() {
    auto data_to_sort = generate_strings(STR_COUNT, STR_LENGTH);

    eval("student's radix sort", data_to_sort, radix_sort);
    eval("std::sort", data_to_sort, std_sort);

    return 0;
}
