# Makefile
# Use this flag to change the opimisation level, integer values between 0 and 3, or fast
OPTIM=3

all: naive auto amul

naive: mat_mult_naive.cpp 
	g++ -O${OPTIM} -o mat_mult_naive.exe mat_mult_naive.cpp

auto: mat_mult_auto.cpp
	g++ -O${OPTIM} -o mat_mult_auto.exe mat_mult_auto.cpp

aadd: avx_add.cpp
	g++ -mavx${AVX} -O${OPTIM} -o avx_add.exe avx_add.cpp

amul: avx_mat_mul.cpp
	g++ -mavx${AVX} -O${OPTIM} -o avx_mat_mul.exe avx_mat_mul.cpp

run: mat_mult_naive.exe mat_mult_auto.exe avx_mat_mul.exe
	${TIME} mat_mult_naive.exe ${SIZE}
	${TIME} mat_mult_auto.exe ${SIZE}
	${TIME} avx_mat_mul.exe ${SIZE}

clean: 
	rm *.exe