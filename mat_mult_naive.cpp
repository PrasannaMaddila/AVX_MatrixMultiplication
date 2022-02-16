#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;

int main(int argc, char **argv)
{
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

            // cout << a[i + N * j] << " " << b[i + N * j] << endl;
        }

    // Multiplying matrix a and b and storing in array mult.
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            for (k = 0; k < N; ++k)
            {
                mult[i + N * j] += a[i + N * k] * b[k + N * j];
            }

    cout << "MATMULT_NAIVE: Done " << mult[N * N] << endl;
    // // Displaying the multiplication of two matrix.
    // cout << endl
    //      << "Output Matrix: " << endl;
    // for (i = 0; i < N; ++i)
    // {
    //     for (j = 0; j < N; ++j)
    //     {
    //         cout << " " << mult[i + N * j];
    //     }
    //     cout << endl;
    // }
    delete[] a;
    delete[] b;
    delete[] mult;
    return 0;
}