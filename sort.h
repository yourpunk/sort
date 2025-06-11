#include "sort.h"
#include <omp.h>
#include <vector>
#include <cstring>
#include <algorithm>
 
void radix_par(std::vector<std::string*>& vector_to_sort,
               MappingFunction mapping_function,
               size_t alphabet_size,
               size_t str_size) {
    size_t n = vector_to_sort.size();
    std::vector<std::string*> aux(n);
 
    for (int pos = static_cast<int>(str_size) - 1; pos >= 0; --pos) {
        int num_threads = 1;
        #pragma omp parallel
        {
            #pragma omp single
            {
                num_threads = omp_get_num_threads();
            }
        }
 
         
        std::vector<std::vector<size_t>> local_hist(num_threads, std::vector<size_t>(alphabet_size, 0));
 
        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            size_t chunk_size = (n + num_threads - 1) / num_threads;
            size_t start = tid * chunk_size;
            size_t end = std::min(start + chunk_size, n);
 
            for (size_t i = start; i < end; ++i) {
                size_t bucket = mapping_function((*vector_to_sort[i])[pos]);
                local_hist[tid][bucket]++;
            }
        }
 
         
        std::vector<size_t> global_hist(alphabet_size, 0);
        for (int t = 0; t < num_threads; ++t)
            for (size_t b = 0; b < alphabet_size; ++b)
                global_hist[b] += local_hist[t][b];
 
         
        std::vector<size_t> bucket_start(alphabet_size, 0);
        for (size_t i = 1; i < alphabet_size; ++i)
            bucket_start[i] = bucket_start[i - 1] + global_hist[i - 1];
 
         
        std::vector<std::vector<size_t>> thread_offsets(num_threads, std::vector<size_t>(alphabet_size, 0));
        for (size_t b = 0; b < alphabet_size; ++b) {
            size_t offset = bucket_start[b];
            for (int t = 0; t < num_threads; ++t) {
                thread_offsets[t][b] = offset;
                offset += local_hist[t][b];
            }
        }
 
         
        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            size_t chunk_size = (n + num_threads - 1) / num_threads;
            size_t start = tid * chunk_size;
            size_t end = std::min(start + chunk_size, n);
 
            std::vector<size_t> local_pos = thread_offsets[tid];
 
            for (size_t i = start; i < end; ++i) {
                size_t bucket = mapping_function((*vector_to_sort[i])[pos]);
                aux[local_pos[bucket]++] = vector_to_sort[i];
            }
        }
 
         
        std::swap(vector_to_sort, aux);
    }
}
