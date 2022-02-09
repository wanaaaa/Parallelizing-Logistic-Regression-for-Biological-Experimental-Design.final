#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <iostream>
// #include<bits/stdc++.h> 
#include <cstdlib>
#include <math.h>
#include <fstream>
#include<sstream>
#include<string.h>

using namespace std;
#define index(i, j, colNum)  ((i)*(colNum)) + (j)

#include "0header.h"
#include "0matrixCalculation.cpp"

int main(int argc, char *argv[]) {

	int rowNum = atoi(argv[1]);
	int colNum = atoi(argv[2]);

	float X[rowNum*colNum];
	float transposeX[colNum*rowNum];

	float Y[rowNum];
	readFile(X, Y, rowNum, colNum);

	for(int i = 0; i < rowNum; i++) {
		for(int j = 0; j < colNum; j++) {
			transposeX[index(j,i, rowNum)] = X[index(i,j, colNum)];	
		}
	}
	

	N = colNum;
///////////////////////////////////////////////////////
   double time_taken;
   clock_t start, end;

	float tranXmulxMat[colNum*colNum];
	matMultiplFloat(transposeX, colNum, rowNum, X, rowNum, colNum, tranXmulxMat);

	// display(tranXmulxMat, 3, 3);

	time_taken = ((double)(end - start))/ CLOCKS_PER_SEC;
	cout<<" single Core Taken->"<<time_taken<<endl;
///////////////////////////////////////////////////////////////////////////
	double time_takenTwo;
   clock_t startTwo, endTwo;

	float tranXmulxMatTwo[colNum*colNum];
	matMulitCoreMultiplFloat(transposeX, colNum, rowNum, X, rowNum, colNum, tranXmulxMatTwo);

	// display(tranXmulxMatTwo, colNum, colNum);

	time_takenTwo = ((double)(end - start))/ CLOCKS_PER_SEC;
	cout<<" multi Core Taken-->"<<time_takenTwo<<endl;

	return 0;
}
