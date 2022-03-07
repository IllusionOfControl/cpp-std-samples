#include <stddef.h>
#include <stdio.h>
#include <algorithm>
#include <chrono>
#include <random>
#include <ratio>
#include <vector>
#include <execution>


const size_t testSize = 1'000'000;
const int iterationCount = 5;

void print_results(const char* const tag, 
                   const std::vector<double>& sorted,
                   std::chrono::high_resolution_clock::time_point startTime,
                   std::chrono::high_resolution_clock::time_point endTime) {
    printf("%s: Lowest: %g Highest: %g Time: %fms\n", 
           tag, sorted.front(), sorted.back(),
           std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count());
}

template<class T>
void execute_sort(T policy, std::vector<double>& doubles) {
    std::vector<double> sorted(doubles);
    const auto startTime = std::chrono::high_resolution_clock::now();
    sort(policy, sorted.begin(), sorted.end());
    const auto endTime = std::chrono::high_resolution_clock::now();
    print_results("Serial", sorted, startTime, endTime);
}

int main() {
    std::random_device rd;

    //gen random doubles
    std::vector<double> doubles(testSize);
    for (auto& d : doubles) {
        d = static_cast<double>(rd());
    }

    std::execution::seq;
    std::execution::par_unseq;
    std::execution::par;
    
    printf("Testing with %zu doubles...\n", testSize);

    // measure time
    for (int i = 0; i < iterationCount; ++i)
    {
        execute_sort(std::execution::seq, doubles);
    }

    printf("Testing with %zu doubles...\n", testSize);

    for (int i = 0; i < iterationCount; ++i)
    {
        execute_sort(std::execution::par_unseq, doubles);
    }

    printf("Testing with %zu doubles...\n", testSize);

    for (int i = 0; i < iterationCount; ++i)
    {
        execute_sort(std::execution::par, doubles);
    }
}