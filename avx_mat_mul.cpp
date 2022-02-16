#include <iostream>
#include <stdlib.h>
#include <immintrin.h>
#include <random>
// #include <time.h>

using namespace std;

// 8 floats per vector, 16 ints per vector
const int BLOCKSIZE = 8;

int main(int argc, char **argv)
{
    // initialising the random number generator
    srand(0);
    random_device randdev;
    mt19937 generator(randdev());
    uniform_real_distribution<> distrib(-1, 1);

    cout << distrib(generator) << '\n';

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

    // getting slices to store parts of A, B
    // which we will use to vectorise the multiplications.
    __m256 slice_a = _mm256_setzero_ps(); //_mm256_load_si256((__m256i *)&a);
    __m256 slice_b = _mm256_setzero_ps(); //_mm256_load_si256((__m256i *)&b);
    __m256 slice_mult = _mm256_setzero_ps();

    // float temp_a[BLOCKSIZE], temp_b[BLOCKSIZE];
    // Multiplying matrix a and b and storing in array mult.
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            for (k = 0; k <= N / BLOCKSIZE; k += BLOCKSIZE)
            {
                // 1. Load 8 bytes from A, 8 from B into
                // AVX-compliant vectors,
                // temp_a = *(a + k + N * j);
                // temp_b = *(b + i + N * k);
                slice_a = _mm256_loadu_ps(&a[k + N * j]);
                slice_b = _mm256_loadu_ps(&b[i + N * k]); //(__m256 *)temp_b

                // 2. multiply and add them, store in appropriate
                // array meant for C
                slice_mult = _mm256_mul_ps(slice_a, slice_b);

                // 3. Assign the right elements to C.
                mult[i + N * j] += slice_mult[0] + slice_mult[1] + slice_mult[2] + slice_mult[3] +
                                   slice_mult[4] + slice_mult[5] + slice_mult[6] + slice_mult[7];
            }

    // Displaying the multiplication of two matrix.
    cout << "MATMULT_AVX: Done " << endl;
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