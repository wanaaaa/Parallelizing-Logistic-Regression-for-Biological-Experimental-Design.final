int gRaddress(ProgramClass pgC, ProgramClass * ppgC);
int gEaddress (ProgramClass iPGC, ProgramClass *ppgC); 
void errCHKinUseListNotActuallyUse();
int qActuallyUsed(string iSym, int moduleInt) ;
///////////////////////////
void passTwo() {

	ProgramClass pgC;
	ProgramClass *ppgC;
	string pType;

	cout<<"Memory Map"<<endl;
	for(int i = 0; i < moduleVec.size(); i++) {
		for(int j = 0; j < moduleVec[i].programVec.size(); j++) {
			ProgramClass nPGC;

			pgC = moduleVec[i].programVec[j];
			pType = pgC.addreType;

			if(pType == "A" || pType == "I") {
				if(pType == "A" && (pgC.instruction % 1000 > 200)) {
					nPGC.errMess = "Error: Absolute address exceeds machine size; zero used.";
					nPGC.newWord = pgC.instruction - (pgC.instruction % 1000);
				} else {
					nPGC.newWord = pgC.instruction;					
				}
			} else if (pType == "R") {
				///////////////////////////////
				nPGC.newWord = gRaddress(pgC, &nPGC);

			} else {// pType = "E"
				nPGC.newWord = gEaddress(pgC, &nPGC);
			}

			programVec.push_back(nPGC);
		}
	}

	errCHKinUseListNotActuallyUse();
	
	printFinalProVec("", programVec, ""); 
	printPassOneErrMessage();

}
//---
void errCHKinUseListNotActuallyUse() {
	ModuleClass mC;
	string symSt;
	for(int i = 0; i < moduleVec.size();i++) {
		mC = moduleVec[i];
		for(int j = 0; j < mC.useVec.size(); j++) {
			symSt = mC.useVec[j];
			if( qActuallyUsed(symSt, i) == 0  ) {
				DefineClass dfC;
				dfC.symbol = symSt;
				dfC.module = i;
				///////////////////////////////////////////
				int iModuleNum = i;
				std::stringstream ss;
				ss<<"Warning: In module "<<iModuleNum<<" "<<symSt
					<<" appeared in the use list but was not actually used.";
				std::string warnMess = ss.str();
				///////////////////////////////////////////
				dfC.warnMess = warnMess;
				dfC.errKind = 1;

				warnMessDefineVec.insert(warnMessDefineVec.begin(), dfC);
			}
		}	
	}
}
//---
int qActuallyUsed(string iSym, int moduleInt) {
	int hitInt = 0;
	ProgramClass cPGC;
	string symUsed;
	for(int i = 0; i < actuallyUsedPrgVec.size(); i++) {
		cPGC = actuallyUsedPrgVec[i];
		symUsed = cPGC.symUsed;
		if(iSym == symUsed && moduleInt == cPGC.module) {
			hitInt = 1;
			break;
		}
	}

	return hitInt;
}
//////////////////////////////////////////////////////////////
int gEaddress (ProgramClass iPGC, ProgramClass *ppgC) {
	int nEaddress = -777;

	int useListInt = moduleVec[iPGC.module].useVec.size();
	
	if((iPGC.instruction % 1000) > useListInt) {
		ppgC->errMess = "External address exceeds length of use list; treated as immediate.";
		nEaddress = iPGC.instruction;
	} else {
		string symbol = moduleVec[iPGC.module].useVec[iPGC.instruction % 1000];

		iPGC.symUsed = symbol;
		
		for(int i = 0; i < defineVec.size(); i ++) {
			if(defineVec[i].symbol == symbol) {

				nEaddress = iPGC.instruction - (iPGC.instruction % 1000) + defineVec[i].absoAddre;
			}
		}

		if(nEaddress == -777) {

			string errStr = "Error: "+symbol+ " is not defined; zero used.";
			ppgC->errMess = errStr;
			nEaddress = iPGC.instruction - (iPGC.instruction % 1000);
		}
	}

	actuallyUsedPrgVec.push_back(iPGC);
	return nEaddress;
}
//////////////////////////////////////////////////////////////
int gRaddress(ProgramClass iPGC, ProgramClass *ppgC) {
	int numInsturction = 0;
	int maxModuleSize = 0;
	int nRaddress;
	for(int i = 0; i < iPGC.module; i++) {
		numInsturction += moduleVec[i].programVec.size();
	}
	
	maxModuleSize = numInsturction + moduleVec[iPGC.module].programVec.size();			

	nRaddress = numInsturction + iPGC.instruction;

	if(iPGC.instruction % 1000 > maxModuleSize) {
		nRaddress = iPGC.instruction - (iPGC.instruction % 1000);
		ppgC->errMess = "Error: Relative address exceeds module size; zero used.";
	}
	
	return nRaddress;
}
