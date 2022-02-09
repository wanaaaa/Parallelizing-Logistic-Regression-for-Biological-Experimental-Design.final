int qDigitOrAlpha(char ch);
void classify();
void clearStateCVec(StateClass *iClass);
void makeModuleVec();
/////////////////////////////////////////////////////////
void parser(char fileName[]) {
	std::vector<char> strVec;
	
	if (FILE *fp = fopen(fileName, "r")) {
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp)){
			strVec.insert(strVec.end(), buf, buf + len);
		}
		fclose(fp);
	}  

	string tempStr = "";
	char tmpChar;
	int wasAlphDigit = 0;
	for(int i = 0; i < strVec.size(); i++) {
		tmpChar = strVec[i];

		if(qDigitOrAlpha(tmpChar) == 1) {
			tempStr += tmpChar;
			wasAlphDigit = 1;
		} else {
			if(tempStr != " ") {
				if(wasAlphDigit == 1) {
					strDataVec.push_back(tempStr);	

				}
				wasAlphDigit = 0;				
			}
			tempStr = "";
		}
	}

	totalModule = atoi(strDataVec[0].c_str());
	strDataVec.erase(strDataVec.begin());

	classify();

	makeModuleVec();
}

//---
int qDigitOrAlpha(char ch) {
	if(isalpha(ch) != 0 || isdigit(ch) == 1)
		return 1;	
	return 0;
}

void makeModuleVec() {
	StateClass cSC;
	ModuleClass moduleC;
	for(int i = 0; i< StateVec.size(); i ++) {
		cSC = StateVec[i];
		if(cSC.stateStr == "define") {
			moduleC.defineVec = cSC.defineVec;

		} else if(cSC.stateStr == "use") {
			moduleC.useVec = cSC.useVec;

		} else if(cSC.stateStr == "program") {
			moduleC.programVec = cSC.programVec;

			moduleVec.push_back(moduleC);

			ModuleClass nMC;
			moduleC = nMC;
		}
	}
}

void classify() {
	int stateInt = 0;
	int ithEleInState = 0;
	int expectedUnitNum;
	int moduleInt = 0;
	string stateStr;
	string cStr;

	StateClass cStatC;
	DefineClass cDefineC;
	ProgramClass cProgramC;

	for(int i = 0; i < strDataVec.size(); i++) {
		cStr = strDataVec[i];
		stateInt = stateInt % 3;

		if(stateInt == 0) {
			stateStr = "define";

		} else if(stateInt == 1) {
			stateStr = "use";
		} else {
			stateStr = "program";
		}

		cStatC.stateStr = stateStr;
		cStatC.moduleInt = moduleInt;

		if(ithEleInState == 0) {

			cStatC.numUnit = atoi(cStr.c_str());

			if(stateInt == 0 || stateInt == 2) {
				expectedUnitNum = atoi(cStr.c_str()) * 2;					
			} else {
				expectedUnitNum = atoi(cStr.c_str()) ;					
			}

			if (expectedUnitNum == 0) {

				ithEleInState = -1;
				stateInt ++;

				StateVec.push_back(cStatC);

				if (stateStr == "program") moduleInt ++;
			}					
		} else {

			if(stateInt == 0) {

				if(ithEleInState % 2 == 1) {
					cDefineC.symbol = cStr;
					cDefineC.module = moduleInt;

				} else {
					cDefineC.relaAddre = atoi(cStr.c_str());
					cStatC.defineVec.push_back(cDefineC);

					if(ithEleInState == expectedUnitNum) {
						StateVec.push_back(cStatC);
						clearStateCVec(&cStatC);
					}
				}
			} else if (stateInt == 1) {
				cStatC.useVec.push_back(cStr);
				if(ithEleInState == expectedUnitNum) {
					StateVec.push_back(cStatC);
					clearStateCVec(&cStatC);
				}

			} else if (stateInt == 2) {
				if(ithEleInState % 2 == 1) {
					cProgramC.addreType = cStr;
					cProgramC.module = moduleInt;
				} else {
					cProgramC.instruction = atoi(cStr.c_str());
					cStatC.programVec.push_back(cProgramC);

					if(ithEleInState == expectedUnitNum) {
						StateVec.push_back(cStatC);
						clearStateCVec(&cStatC);
					}
				}
			} 

			//end of line
			if(ithEleInState == expectedUnitNum) {
				ithEleInState = -1;
				stateInt ++;

				if (stateStr == "program") moduleInt ++;
			}
		}

		ithEleInState ++;

	}// end of big For

}
//---
void clearStateCVec(StateClass *iClass) {
	iClass->defineVec.clear();
	iClass->useVec.clear();
	iClass->programVec.clear();
}





























