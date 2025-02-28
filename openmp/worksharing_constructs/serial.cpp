#include <iostream>
#include <vector>
#include <chrono>

#define N 1000000 // Size of the array

int main() {
    std::vector<int> a(N, 1), b(N, 2); // Initialize arrays with some values

    auto start_time = std::chrono::high_resolution_clock::now(); // Start time measurement

    for (int i = 0; i < N; i++) {
        a[i] = a[i] + b[i];
    }
    
    auto end_time = std::chrono::high_resolution_clock::now(); // End time measurement
    std::chrono::duration<double> elapsed = end_time - start_time;
    
    std::cout << "Execution Time: " << elapsed.count() << " seconds" << std::endl;
    return 0;
}