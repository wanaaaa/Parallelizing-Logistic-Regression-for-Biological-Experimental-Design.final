void printModuleVec();
int gAbsoAddreFun(DefineClass *dfC);
void printSymTable();
///////////////////////////////////////////
void passOne() {
	cout<<" "<<endl;
	errCHKgetDefineVec();

	DefineClass *dfC;
	for(int i = 0; i < defineVec.size();i++) {
		dfC = &defineVec[i];
		dfC->absoAddre = gAbsoAddreFun(dfC);
	}

	////////////////////////
	printSymTable();

}
////////////////////////////////
void printSymTable() {
	cout<<"Symbol Table"<<endl;
	DefineClass dfC;
	for(int i = 0; i < defineVec.size(); i++) {
		dfC = defineVec[i];
		cout<<dfC.symbol<<"="<<dfC.absoAddre;
		if(dfC.qDuplicated == 1)
			cout<<" Error: This variable is multiply defined; first value used.";
		cout<<""<<endl;
	}

	cout<<" "<<endl;
}
////////////////////////////////
int gAbsoAddreFun(DefineClass *dfC) {
	int numInstruction = 0;
	for(int i = 0; i < dfC->module; i++) {
		numInstruction += moduleVec[i].programVec.size();
	}
	return numInstruction + dfC->relaAddre ;
}
