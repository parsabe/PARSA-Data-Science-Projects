#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

// the function inside task pdf file
void process_slow(double* a, double* b, double* processed, int N) {
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            double v = sqrt(pow(a[i], 2) + pow(b[i], 2));
            processed[i] = (v > 10.0) ? v : 0.0;
        } else {
            processed[i] = 0.0;
        }
    }
}

// the new optimization
void process_fast(double* a, double* b, double* processed, int N) {
    // Initialize result array separately
    for (int i = 0; i < N; i++) {
        processed[i] = 0.0; 
    }

    // a loop with not pow(), strided and no such branch required. 
    // (v > 10.0) ? v : 0.0; in here since V is either 100 or 10 squared, 
    // we can directly compare v_sq with 100.0 without needing to compute the square root, 
    // which is a costly operation.
    for (int i = 0; i < N; i += 2) {
        double v_sq = (a[i] * a[i]) + (b[i] * b[i]); 
        if (v_sq > 100.0) {
            processed[i] = sqrt(v_sq);
        }
    }
}

int main() {
 
    int N = 10000000; 

    double* a = new double[N];
    double* b = new double[N];
    double* result = new double[N];

    // initating date
    for(int i = 0; i < N; i++) {
        a[i] = 10.0;
        b[i] = 20.0;
    }


    clock_t start = clock();
    process_slow(a, b, result, N);
    clock_t end = clock();
    cout << "Slow Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;


    start = clock();
    process_fast(a, b, result, N);
    end = clock();
    cout << "Fast Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    delete[] a;
    delete[] b;
    delete[] result;

    return 0;
}