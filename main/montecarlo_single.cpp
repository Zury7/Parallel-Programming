#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

const long double TRUE_PI = 3.141592653589793238462643383279502884L;

long double monteCarloPi(long long samples, long long& insideCircle) {
    insideCircle = 0;
    for (long long i = 0; i < samples; i++) {
        long double x = (long double)rand() / RAND_MAX;
        long double y = (long double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) insideCircle++;
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
    srand(time(0));
    auto start = high_resolution_clock::now();

    long double precisions[] = {1e-5L, 1e-10L, 1e-15L, 1e-20L};
    int precisionLevels[] = {5, 10, 15, 20};

    for (int i = 0; i < 4; i++) {
        long long requiredSamples = getSamplesForPrecision(precisions[i]);
        long long insideCircle;
        long double estimatedPi = monteCarloPi(requiredSamples, insideCircle);

        cout.precision(precisionLevels[i] + 2);
        cout << "Precision: " << precisionLevels[i] << " decimal places\n";
        cout << "Estimated Pi: " << estimatedPi << "\n";
        cout << "Required Samples: " << requiredSamples << "\n\n";
    }

    auto end = high_resolution_clock::now();
    double duration = duration_cast<milliseconds>(end - start).count() / 1000.0;
    cout << "Total Execution Time: " << duration << " seconds" << endl;

    return 0;
}
