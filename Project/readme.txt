# GPUProject
Parallelizing logistic regression and comparing it to sequential version

*Compile on snappy3 for sequential code*
*Compile on cuda2 for CUDA code*

1. unzip all files in a same directory

2. generate random data:
g++ generateRanData.cpp -o ranData
./ranData 10 5 (it generates 10by5Matt.txt file. 10 rows by 5 variables)

3. compile sequential code:
g++ 02.regressMat.00.cpp -o regressSequen
./regressSequen 10 5

4. compile CUDA code
nvcc 01.regressMatCUDA.00.cu -o regressCUDA
./regressCUDA 10 5

________________________________________
For time: time ./cudareg 100 10
	  time ./regressSequen 10 5
For profiling: nvprof ./cudareg 100 10

