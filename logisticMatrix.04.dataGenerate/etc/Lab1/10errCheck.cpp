void gRawDefineAusedSymVec();
void errCHKdefinedNotUsed();
void printPassOneErrMessage();
void errCHKduplicatedDefineSym();
void errCHKexceedModuleSize();
////////////////////////////////////////////////////
void errCHKgetDefineVec() {
	gRawDefineAusedSymVec();

	errCHKduplicatedDefineSym();

	errCHKdefinedNotUsed();

	errCHKexceedModuleSize();
}
////////////////////////////////
void errCHKexceedModuleSize() {
	DefineClass *defC;
	int moduleSize = -1;
	for(int i = 0; i < defineVec.size(); i++) {
		defC = &defineVec[i];
		moduleSize = moduleVec[defC->module].programVec.size();

		if(defC->relaAddre > moduleSize) {
			defC->relaAddre = 0;
			int iModule = defC->module;
			std::stringstream ss;
			ss<<iModule;
			string moduleStr = ss.str();
			string errMessStr = "Error: In module "+moduleStr+ " the def of "+defC->symbol+" exceeds the module size; zero (relative) used.";

			DefineClass nDef = defineVec[i];
			nDef.errMess = errMessStr;

			tailErrMessDefineVec.push_back(nDef);
		}
	}
}
//-------------------------------------------
void errCHKduplicatedDefineSym() {
	int dupNumArr[rawDefineVec.size()];
	int duplicatedInt;
	std::vector<DefineClass> tempDefVec, dupDefVec;
	DefineClass outDC, inDC;
	for(int i = rawDefineVec.size()-1; i >= 1; i--) {
		duplicatedInt = 0;
		outDC = rawDefineVec[i];
		for(int j = i -1 ; j >=0;  j--) {			
			inDC = rawDefineVec[j];

			if(outDC.symbol == inDC.symbol) {
				duplicatedInt ++;			
			}
		}

		dupNumArr[i] = duplicatedInt;
	}
	dupNumArr[0] = 0;

	DefineClass dfC;
	for(int i = 0; i < rawDefineVec.size(); i++) {
		dfC = rawDefineVec[i];
		if(dupNumArr[i] == 0 ) {
			tempDefVec.push_back(dfC);
		}	
		else {
			dupDefVec.push_back(dfC);
		} 
	}

	//mark duplicated on DefineClass
	for(int i = 0; i < tempDefVec.size(); i++ ) {
		outDC = tempDefVec[i];
		for(int j = 0; j < dupDefVec.size(); j++) {
			inDC = dupDefVec[i];
			if(outDC.symbol == inDC.symbol ) tempDefVec[i].qDuplicated = 1;
		}
	}

	defineVec = tempDefVec;

}
//------------------------------
void errCHKdefinedNotUsed() {
	string definedSym;
	int symUsed, actualModule;
	for(int i = 0; i < rawDefineVec.size(); i++) {
		symUsed = 0;

		definedSym = rawDefineVec[i].symbol;
		for(int j = 0; j < useSymVec.size(); j++) {
			if(definedSym == useSymVec[j]) {
				symUsed = 1;
			}	
		}

		if(symUsed == 0) {
			int iDefinedModule = rawDefineVec[i].module;
			std::stringstream ss;
			ss<<iDefinedModule;
			string iDefinedModuleStr = ss.str();
			string warnMess = "Warning: "+rawDefineVec[i].symbol+" was defined in module "
				+ iDefinedModuleStr+" but never used.";

			rawDefineVec[i].warnMess = warnMess;
			rawDefineVec[i].errKind = 0;
			warnMessDefineVec.push_back(rawDefineVec[i]);
		}	
	}
}
//---
void gRawDefineAusedSymVec() {
	std::vector<DefineClass> cDVec;
	for(int i = 0;i < moduleVec.size(); i++) {

		cDVec = moduleVec[i].defineVec;
		for(int j = 0; j < cDVec.size(); j++) {
			rawDefineVec.push_back(cDVec[j]);
		}

		for(int j = 0; j < moduleVec[i].useVec.size(); j++) {
			useSymVec.push_back(moduleVec[i].useVec[j]);
		}

	}
}