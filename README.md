# Matrix Multiplication: AVX

This set of files will try to multiply matrices and see how the compiler can optimise it. 
1. [mat_mult_naive.cpp](./mat_mult_naive.cpp) runs the naive matrix multiplication on square matrices of size (`N` x `N`) with random floating point entries. This is not optimal or cache-friendly.
2. [mat_mult_auto.cpp](./mat_mult_auto.cpp) switches the inner loops to make the program more cache-friendly; in particular, it turns the loop order from _i-j-k_ to _i-k-j_, in order to re-use matrix data that has already been stored in the cache. This is so that the compiler can auto-vectorize this code.
3. [avx_mat_mul.cpp](./avx_mat_mul.cpp) vectorizes the load and multply operations in an attempt to process 8 computations per cycle, but retains the _i-j-k_ loop for simplicity.

## First Build ...

You can build all the codes to executables using make 

```bash
make OPTIM=<optim_level> AVX=<avx_ver>
```
where the flags are optional, and will take default values `OPTIM=3` (`-O3`) and `AVX` will be empty i.e. the build will default to `AVX`, not `AVX2` or `AVX512f`. 

```latex
[FLAG] AVX :Supply `2` for `AVX2` and `512f` for `AVX512f`. 
[FLAG] OPTIM: Supply integer values between 0 and 3, or fast to get the desired g++ optimisation level.
```

Building the naive, auto-vectorised and AVX-based code can be achieved with the `naive`, `auto` and `amul` targets, respectively, with the same flags as before.

## Then Run!  

Run the whole suite using 

```bash
make run SIZE=<your_size_here> TIME=<time_command>
```

where `time_command` is your time measuring command of choice. On Windows system, using UNIX `time` is tricky, so I recommend [ptime](https://community.chocolatey.org/packages/ptime), installed via the `choco` package manager. Otherwise, if you have access to GNU `time` or want to use your own tools, go forth! 

## And When You're Done ...

Run

```bash
make clean 
```

to remove all executables.