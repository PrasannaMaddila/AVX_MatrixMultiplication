#include <iostream>
#include <stdlib.h>
// #include <time.h>
#include <random>

using namespace std;

int main(int argc, char **argv)
{
    // initialising the random number generator
    srand(0);
    random_device randdev;
    mt19937 generator(randdev());
    uniform_real_distribution<> distrib(-1, 1);

    int N = atoi(argv[1]);
    float *a = new float[N * N];
    float *b = new float[N * N];
    float *mult = new float[N * N];
    int i, j, k, index;

    // Initializing elements of matrix mult to 0.
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
        {
            index = i + N * j;
            a[index] = distrib(generator);
            b[index] = distrib(generator);
            mult[index] = 0;
        }

    // Multiplying matrix a and b and storing in array mult.
    for (i = 0; i < N; ++i)
        for (k = 0; k < N; ++k)
            for (j = 0; j < N; ++j)
            {
                mult[i + N * j] += a[i + N * k] * b[k + N * j];
            }

    // Displaying the multiplication of two matrix.
    cout << "MATMULT_AUTO: Done " << mult[N * N];
    //      << "Output Matrix: " << endl;
    // for (i = 0; i < n; ++i)
    // {
    //     for (j = 0; j < n; ++j)
    //     {
    //         cout << " " << mult[i][j];
    //     }
    //     cout << endl;
    // }
    delete[] a;
    delete[] b;
    delete[] mult;
    return 0;
}