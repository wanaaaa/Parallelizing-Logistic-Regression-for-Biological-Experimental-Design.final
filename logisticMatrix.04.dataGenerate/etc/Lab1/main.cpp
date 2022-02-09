#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm> 

#include <fstream> 
#include <vector>
#include <cstdlib>
#include <list>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

#include "00header.h"
#include "05parser.cpp"
#include "10errCheck.cpp"
#include "20passOne.cpp"
#include "50passTwo.cpp"


int main(int argc, char *argv[]) {
	
	parser(argv[1]);
	passOne();
	passTwo();
	
	return 0;
}