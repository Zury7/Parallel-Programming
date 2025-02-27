#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

const long double TRUE_PI = 3.141592653589793238462643383279502884L;
const int NUM_THREADS = 2;

struct ThreadData {
    long long start, end, insideCircle;
};

void* monteCarloThread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long inside = 0;
    
    for (long long i = data->start; i < data->end; i++) {
        long double x = (long double)rand() / RAND_MAX;
        long double y = (long double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) inside++;
    }

    data->insideCircle = inside;
    pthread_exit(nullptr);
}

long double monteCarloPi(long long samples, long long& insideCircle) {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    insideCircle = 0;

    long long chunkSize = samples / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].start = i * chunkSize;
        threadData[i].end = (i == NUM_THREADS - 1) ? samples : (i + 1) * chunkSize;
        pthread_create(&threads[i], nullptr, monteCarloThread, &threadData[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], nullptr);
        insideCircle += threadData[i].insideCircle;
    }

    return (4.0L * insideCircle) / samples;
}

long long getSamplesForPrecision(long double requiredPrecision) {
    long long samples = 1000;
    long long insideCircle;
    long double piEstimate, error;

    while (true) {
        piEstimate = monteCarloPi(samples, insideCircle);
        error = fabsl(piEstimate - TRUE_PI);

        if (error <= requiredPrecision) {
            return samples;
        }
        samples *= 2;
    }
}

int main() {

    long long samples[] = { static_cast<long long>(pow(2,24)), 
                            static_cast<long long>(pow(2,26)), 
                            static_cast<long long>(pow(2,28)) };

    // long double precisions[] = {1e-5L, 1e-10L, 1e-15L, 1e-20L};
    // int precisionLevels[] = {5, 10, 15, 20};

    for (int i = 0; i < 3; i++) {
        auto start = high_resolution_clock::now();
        long long requiredSamples = getSamplesForPrecision(samples[i]);
        long long insideCircle;
        long double estimatedPi = monteCarloPi(requiredSamples, insideCircle);
        cout << "Samples: " << samples[i] << "\n";
        cout << "Estimated Pi: " << estimatedPi << "\n";
        auto end = high_resolution_clock::now();
        double duration = duration_cast<milliseconds>(end - start).count() / 1000.0;
        cout << "Error: " << fabsl(estimatedPi - TRUE_PI) << "\n";
        cout << "Total Execution Time: " << duration << " seconds\n\n";
    }

    return 0;
}