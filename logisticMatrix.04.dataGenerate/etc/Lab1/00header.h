std::vector<string> strDataVec;
std::vector<string> useSymVec;

int totalModule;
////////////////////////////////////////////
class DefineClass {
public:
	string symbol;
	int relaAddre;
	int absoAddre;
	int qDuplicated;
	int qFirst;
	int module;
	int errKind;

	string warnMess;
	string errMess;

	DefineClass(){
		qDuplicated = 0; qFirst = 1;
	}		
};
std::vector<DefineClass> rawDefineVec, warnMessDefineVec , defineVec, tailErrMessDefineVec; 
//---
class ProgramClass{
public:
	string addreType;
	int instruction;
	int newWord;
	int module;
	string errMess;
	string symUsed;

	ProgramClass(){
		instruction = -1; newWord = -1; module = -1;
		symUsed = "NA";
	}
};
std::vector<ProgramClass> programVec, actuallyUsedPrgVec;
//---
class StateClass {
public:
	int moduleInt;
	string stateStr;//define, use, program
	int numUnit;
	
	std::vector<DefineClass> defineVec;
	std::vector<string> useVec;
	std::vector<ProgramClass> programVec;

	StateClass() {
		moduleInt = -1;
		stateStr = "NA";
		numUnit = -1;
	}	
};

std::vector<StateClass> StateVec;
/////////////////////////////////////
class ModuleClass {
public:
	std::vector<DefineClass> defineVec;
	std::vector<string> useVec;
	std::vector<ProgramClass> programVec;
	ModuleClass(){}
	
};

std::vector<ModuleClass> moduleVec;
////////////////////////////////////

void printPassOneErrMessage() {
	DefineClass dfC;

	for(int i = 0; i < warnMessDefineVec.size(); i++) {
		dfC = warnMessDefineVec[i];
		cout<<dfC.warnMess<<endl;
		if(i + 1 < warnMessDefineVec.size() && dfC.errKind == warnMessDefineVec[i+1].errKind) {
		} else {
			cout<<""<<endl;
		}
	}

	for(int i = 0; i < tailErrMessDefineVec.size(); i++) {
		cout<<tailErrMessDefineVec[i].errMess<<endl;
	}

}
//---
void printDefineVec(string fSt, std::vector<DefineClass> dfVec, string rSt) {
	DefineClass dfC;
	cout<<fSt<<dfVec.size()<<" "<<endl;
	for(int j = 0; j < dfVec.size(); j ++) {
		dfC = dfVec[j];
		cout<<dfC.symbol<<" "<<dfC.relaAddre<<" "<<" Duplicated="<<dfC.qDuplicated <<"<-module="<<dfC.module<<endl;
	}
	cout<<rSt<<endl;
}


void printUseVec(string fSt, std::vector<string> useVec, string rSt){
	string cSt;
	cout<<fSt<<useVec.size()<<" ";

	for(int i = 0; i < useVec.size();i++) {
		cSt = useVec[i];
		cout<<cSt<<" ";
	}
	cout<<rSt<<endl;
}
//--
void printProgramVec(string fSt, std::vector<ProgramClass> pgVec, string rSt) {
	ProgramClass cProgC;
	cout<<fSt<<pgVec.size()<<" ";
	for(int j = 0; j < pgVec.size(); j++){
		cProgC = pgVec[j];
		cout<<cProgC.addreType<<" "<<cProgC.instruction<<" ";		
	}	
	cout<<rSt<<endl;
}
//---
void printFinalProVec (string fSt, std::vector<ProgramClass> pgVec, string rSt) {
	ProgramClass cProgC;
	cout<<fSt;

	for(int i = 0; i < pgVec.size(); i++){
		cProgC = pgVec[i];

		std::stringstream ss;
		ss<<i<<":";
		std::string stI = ss.str();

		cout.width(3);
		cout<<std::left<<stI;
		cout<<cProgC.addreType<<" "<<cProgC.newWord<<" "<<cProgC.errMess<<endl;		
	}	
	cout<<rSt<<endl;	
}
//---
void printModuleVec() {
	DefineClass dfC;
	string symSt;
	ProgramClass pgC;

	std::vector<DefineClass> dfVec;
	std::vector<string> useVec;
	std::vector<ProgramClass> pgVec;

	ModuleClass mdC;
	for(int i = 0; i < moduleVec.size(); i++) {
		mdC = moduleVec[i];
		dfVec = mdC.defineVec;
		useVec = mdC.useVec;
		pgVec = mdC.programVec;
		
		printDefineVec("", dfVec, "");
		printUseVec("", useVec, "");
		printProgramVec("", pgVec, "");
		cout<<endl;
	}
}
//---
void printStateVec() {
	StateClass cSC;
	DefineClass cDefC;
	ProgramClass cProgC;
	string useSym;

	for(int i = 0; i < StateVec.size(); i++) {
		cSC =StateVec[i];
		if(cSC.stateStr == "define") {
			if(cSC.defineVec.size() == 0) {
				cout<<"define; Zero"<<endl;
			}
			for(int j = 0; j < cSC.defineVec.size(); j ++) {
				cDefC = cSC.defineVec[j];
				cout<<"define; "<<cDefC.symbol<<" "<<cDefC.relaAddre<<" module="<<cSC.moduleInt<<endl;
			}
			//cout<<" "<<endl;
		} 
		else if (cSC.stateStr == "use") {
			printUseVec("", cSC.useVec, "");		
			cout<<" "<<"modue="<<cSC.moduleInt <<endl;
		}
		else if (cSC.stateStr == "program"){
			if(cSC.programVec.size() == 0) {
				cout<<"program; Zero"<<endl;
			}
			for(int j = 0; j < cSC.programVec.size(); j++){
				cProgC = cSC.programVec[j];
				cout<<"program; "<<cProgC.addreType<<" "<<cProgC.instruction<<" module="
				<<cSC.moduleInt<<endl;
				
			}
			cout<<"--------------->modue="<<cSC.moduleInt<<" end"<<endl;
		}

		cout<<" "<<endl;
	}	
}