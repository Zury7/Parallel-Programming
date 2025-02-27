#include <iostream>
#include <ctime> // Include for clock()

static long num_steps = 100000;
double step;

int main() {
    int i;
    double x, pi, sum = 0.0;

    // Start the clock
    clock_t start_time = clock();

    step = 1.0 / (double) num_steps;

    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    // Stop the clock
    clock_t end_time = clock();
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    std::cout << "Estimated value of Pi: " << pi << std::endl;
    //3.14159
    //0.00095 seconds
    std::cout << "Execution time: " << execution_time << " seconds" << std::endl;

    return 0;
}
