#include <cuda_runtime.h>
#include <curand_kernel.h>
#include <iostream>
#include <chrono>
#include <iomanip>

// CUDA kernel for initializing random number generators
__global__ void init_rand_kernel(curandState *state, unsigned long long seed) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    curand_init(seed, idx, 0, &state[idx]);
}

// CUDA kernel for Monte Carlo PI estimation
__global__ void monte_carlo_kernel(curandState *state, unsigned long long *points_inside, 
                                 unsigned long long points_per_thread) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    curandState localState = state[idx];
    unsigned long long local_count = 0;

    for (unsigned long long i = 0; i < points_per_thread; i++) {
        float x = 2.0f * curand_uniform(&localState) - 1.0f;
        float y = 2.0f * curand_uniform(&localState) - 1.0f;
        if (x*x + y*y <= 1.0f) {
            local_count++;
        }
    }

    atomicAdd(points_inside, local_count);
    state[idx] = localState;
}

class CudaPiEstimator {
private:
    curandState *d_states;
    unsigned long long *d_points_inside;
    unsigned long long *h_points_inside;
    int num_blocks;
    int threads_per_block;

    void checkCudaError(cudaError_t error, const char *message) {
        if (error != cudaSuccess) {
            std::cerr << "CUDA Error: " << message << " - " 
                      << cudaGetErrorString(error) << std::endl;
            exit(-1);
        }
    }

public:
    CudaPiEstimator() : threads_per_block(256) {
        cudaDeviceProp prop;
        cudaGetDeviceProperties(&prop, 0);
        num_blocks = prop.multiProcessorCount * 8;

        checkCudaError(cudaMalloc(&d_states, num_blocks * threads_per_block * sizeof(curandState)), 
        "Failed to allocate device memory for random states");
        checkCudaError(cudaMalloc(&d_points_inside, sizeof(unsigned long long)), 
        "Failed to allocate device memory for points counter");
        h_points_inside = new unsigned long long;
    }

    ~CudaPiEstimator() {
        cudaFree(d_states);
        cudaFree(d_points_inside);
        delete h_points_inside;
    }

    double estimate_pi(unsigned long long total_points) {
        auto start = std::chrono::high_resolution_clock::now();
        unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        init_rand_kernel<<<num_blocks, threads_per_block>>>(d_states, seed);
        checkCudaError(cudaGetLastError(), "Failed to launch init kernel");

        int total_threads = num_blocks * threads_per_block;
        unsigned long long points_per_thread = total_points / total_threads;

        *h_points_inside = 0;
        checkCudaError(cudaMemcpy(d_points_inside, h_points_inside, sizeof(unsigned long long), 
        cudaMemcpyHostToDevice), "Failed to copy points counter to device");

        monte_carlo_kernel<<<num_blocks, threads_per_block>>>(d_states, d_points_inside, points_per_thread);
        checkCudaError(cudaGetLastError(), "Failed to launch Monte Carlo kernel");

        checkCudaError(cudaMemcpy(h_points_inside, d_points_inside, sizeof(unsigned long long), 
        cudaMemcpyDeviceToHost), "Failed to copy results from device");

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "CUDA implementation took " << duration.count() << " milliseconds" << std::endl;
        return 4.0 * (*h_points_inside) / static_cast<double>(total_points);
    }
};

int main() {
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, 0);
    std::cout << "GPU: " << prop.name << std::endl;

    try {
        CudaPiEstimator estimator;

        std::vector<unsigned long long> points_needed = {1ULL << 24, 1ULL << 26, 1ULL << 28};

        for (auto points : points_needed) {
            std::cout << "\nTesting for " << points << " trials..." << std::endl;
            double pi = estimator.estimate_pi(points);
            std::cout << "PI (CUDA): " << std::fixed << std::setprecision(10) << pi << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}