#pragma once

#include <string>
#include <vector>

/**
 * SortingTest class runs a given sorting algorithm on data
 * and verifies whether the result is sorted correctly.
 */
template <typename SortingAlgorithm>
class SortingTest {
public:
    std::vector<std::string*> sorted_data{};  // Sorted data (stored as pointers for speed)
    SortingAlgorithm sorting_algorithm;

    // Constructor — prepares data and stores the algorithm
    SortingTest(std::vector<std::string>& data, const SortingAlgorithm& algorithm) : sorting_algorithm{algorithm} {
        // Store data as pointers to speed up sorting
        for (auto& entry : data) {
            sorted_data.push_back(&entry);
        }
    }

    // Runs the sorting algorithm
    void run_sort() {
        sorting_algorithm(sorted_data);
    }

    // Verifies the sorting result using a reference comparator
    bool verify(std::vector<std::string>& data, auto verify_with) {
        if (data.size() != sorted_data.size()) {
            return false;
        }

        // Create a reference-sorted version of the input data (as pointers)
        std::vector<std::string*> reference;
        for (auto& entry : data) {
            reference.push_back(&entry);
        }

        // Sort the reference version using the given comparator
        verify_with(reference);

        // Compare values one-by-one
        for (size_t i = 0; i < data.size(); i++) {
            if ((*reference[i]) != (*sorted_data[i])) {
                return false;
            }
        }

        // No mismatches found — success
        return true;
    }
};
