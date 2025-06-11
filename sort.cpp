#include "sort.h"

#include <stdexcept>

/**
 * Parallel Radix Sort implementation.
 * 
 * Sorts `vector_to_sort` in-place using the given `mapping_function` to map characters
 * to alphabet positions. All strings are assumed to have the same length (`str_size`).
 * The alphabet has `alphabet_size` distinct symbols.
 */
void radix_par(std::vector<std::string*>& vector_to_sort,
               MappingFunction mapping_function,
               size_t alphabet_size,
               size_t str_size) {

    // Your implementation goes here
    throw std::runtime_error("Not implemented.");

    // Notes:
    // - The alphabet order is determined by `mapping_function`.
    //   For example: mapping_function((*some_string).at(position))
    //
    // - You should create buckets representing characters from the alphabet
    //
    // - All strings are guaranteed to have the same length (str_size),
    //   so you don't need to handle varying-length edge cases
    //
    // - After this function, `vector_to_sort` must be sorted in lexicographical order
}
