#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

#include <iostream>
#include<bits/stdc++.h> 
using namespace std; 

#define index(i, j, colNum)  ((i)*(colNum)) + (j)
#define N 4 
int nn = 5;

void testFun (int A[N][N], int n);

template<class T> 
void display(T A[N][N]) { 

	for (int i=0; i<N; i++) { 
		for (int j=0; j<N; j++) 
			cout << A[i][j] << " "; 
		cout << endl; 
	} 
}
///////////////////////////////////////////////////////
void testArr(int arr[]) {
	arr[0] = -111;
}

int main() { 
	// int N = 4;
	// int A[N*N] = {5,-2,2,7, 1,0,0,3, -3,1,5,0, 3,-1,-9,4 };
	int A[N][N] = { {5, -2, 2, 7}, {1, 0, 0, 3}, {-3, 1, 5, 0}, {3, -1, -9, 4}}; 
	int B[] = {1, 2, 3};

	// testFun(A, 3);
	// display(A);
	// testArr(B);
	cout<<B[0]<<endl;
	cout<<"N->"<<N<<endl;
	return 0; 
}

void testFun (int A[N][N], int n) {
	A[0][0] = -111;
}
