//#pragma warning(disable:4786)

#include <fstream>
#include <algorithm>
#include <string>
#include <stdlib.h>

CLoop::CLoop(std::string in)
{
	unsigned int line=0; //numer czytanej lini
	char tab[BUF]; //bufor
	unsigned int level=0;
	std::string strTemp; //traktowany jako bufor
	std::string strIntNames; //nazwy zmiennych calkowitych
	std::string::size_type pos;
	std::map<unsigned int, CStatement *>::iterator itStat;
//	CFor * wskCFor;
//	std::string::size_type begin,end;
//	std::string::iterator itString;
//	CStatement *statement;

	std::string strTemp1;

	ifstream input(in.c_str(),ios::in);

	while (!input.eof()) {

		line++;
		input.getline(tab,BUF,'\n');  //zczytanie lini
		strTemp.assign(tab);


		if ( strTemp.find("endfor")!=std::string::npos ) {
			//koniec petli
			statementMap.insert(std::make_pair(line,CreateEndFor(str("endfor"),level--)));
		}
                else if ( strTemp.find("for ")!=std::string::npos && strTemp[0] != '!' ) {
			//poczatek pêtli for
			itStat = (statementMap.insert(std::make_pair(line,CreateFor(tab,++level)))).first;

		}
		else if ( (pos = strTemp.find("integer "))!=std::string::npos ) {
			//deklaracja zmiennych integer integer
			pos += 8;
			if ( strIntegers.length() ) {
				strIntegers.append(",");
			}
			strIntegers.append(strTemp,pos,strTemp.length()-pos);
		}
		else if ( level>0 ) {
			//wyrazenie arytmetyczne lub linia pusta
			std::remove_if(strTemp.begin(),strTemp.end(),WhiteSpace);

			if (strTemp.length()!=0) {
				//wyrazenie arytmetyczne
				statementMap.insert(std::make_pair(line,CreateStatement(tab,level)));
			}
		}


	}

	input.close();

	//zapamietanie zmiennych ideksowych dla poszczeglnych petli
	for(itStat=statementMap.begin();itStat!=statementMap.end();itStat++) {
		if (itStat->second->ReturnType()=="for") {
			loopIndexNames.insert(std::make_pair(itStat->first,itStat->second->IndexVarName()));
		}
	}


}



int CLoop::LoopType()
{
	bool forStatement=true;

	std::map<unsigned int, CStatement *>::iterator itStatement;

	for(itStatement=statementMap.begin();itStatement!=statementMap.end();itStatement++) {
		//Jesli forStatement==true i znajdziemy wyrazenie bedace poczatkiem petli
		//to znaczy ze petla jest nie idealnie zagniezdzona
		if (itStatement->second->ReturnType()=="for") {
			if (forStatement==false)
				return 1;
		}
		else
			forStatement=false;
	}

	return 0;
}



void CLoop::CreateLoopForFreeIterations(char *out)
{
	std::map<unsigned int, CStatement *>::iterator itStatementMap;
	std::string declarationVar; //deklaracje
	std::string loopBody; //cialo petli juz z nowymi wyrazeniami
	unsigned int line=2;	//numer wiersza w ktorym zapisujemy
	char temp[20];
	bool arithmetical = true;
//	int i;


	//jesli sa deklaracje zmiennych calkowitych to nalezy je uwzglednic
	if ( strIntegers.length() ) {
		line++;
		loopBody += "integer " + strIntegers + "\n";
	}


	declarationVar += "real ";
	for (itStatementMap=statementMap.begin();itStatementMap!=statementMap.end();itStatementMap++) {
		//petla dba aby numer wiersza byl taki sam jak w orginalnej petli
	//for(line;line<itStatementMap->first;line++)
	//		loopBody += "\n";



		if (itStatementMap->second->ReturnType()=="for") {
			loopBody += itStatementMap->second->ReturnBody() + "\n";
			line++;
		}
		else if (itStatementMap->second->ReturnType()=="arithmetical") {
			if (LoopType() || (!LoopType() && arithmetical) ) {
				//itoa(itStatementMap->first,temp,10);
				sprintf(temp, "%i", itStatementMap->first);
				loopBody += "l";
				loopBody += temp;
				loopBody += " = l";
				loopBody += temp;
				loopBody += "\n";
				line++;

				declarationVar += "l";
				declarationVar += temp;
				declarationVar += ",";

				arithmetical = false;
			}
		}
		else if (itStatementMap->second->ReturnType()=="endfor") {
			loopBody += itStatementMap->second->ReturnBody() + "\n";
			line++;
		}
	}
	declarationVar += "l\n";

	FILE * output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"w");

	fprintf(output,declarationVar.c_str());
	fprintf(output,loopBody.c_str());

//	fclose(output);
	if (out!=NULL) fclose(output);
}



CLoop::~CLoop()
{
	std::for_each(statementMap.begin(),statementMap.end(),DeleteSecondStatement);
}



CStatement * CLoop::CreateFor(char *str, unsigned int level)
{
	std::string strBuf;
	std::string strTemp;
	std::string::iterator itStrTemp;

	std::string varName;

	strBuf.assign(str);

	//przesuniêcie siê na literake "r" w slowie for
	for(itStrTemp = strBuf.begin();*itStrTemp!='r';itStrTemp++);
	itStrTemp+=1;  //teraz wskazuje na spacje

	while (*itStrTemp<='a' || *itStrTemp>='z')
		itStrTemp++;

	//ponizej zczytanie nazwy zmiennej
	while(*itStrTemp!=' ' && *itStrTemp!='\t' && *itStrTemp!='=') {
		varName.insert(varName.end(),*itStrTemp);
		itStrTemp++;
	}

	//tworzymy obiekt i odrazu zwracamy wskaznik
	return new CFor(str,"for",level,varName);
}



CStatement * CLoop::CreateStatement(char *str, unsigned int level)
{
	std::string strNonWhiteSpace;
	std::string::iterator itStrTemp;
	std::string strBuf(str);

	std::string::size_type index; //potrzebne do wyszukania znaku '='

	std::string leftSide, rightSide;
	unsigned int leftD=1, //lewy wymiar
					 rightD=1; //prawy wymiar

	//pozbycie sie spacji, tabulacji i nawiasow z calego wyrazenia,
	//nowe wyrazenie w stringu strNonWhiteSpace
	for(itStrTemp=strBuf.begin();itStrTemp!=strBuf.end();itStrTemp++) {
		if (*itStrTemp!=' ' && *itStrTemp!='\t')
			strNonWhiteSpace.insert(strNonWhiteSpace.end(),*itStrTemp);
	}

	index = strNonWhiteSpace.find('=');
	leftSide = strNonWhiteSpace.substr(0,index);
	rightSide = strNonWhiteSpace.substr(index+1);

	//zliczenie wymiaru lewej strony (policzeie przecinkow)
	for(itStrTemp=leftSide.begin();itStrTemp!=leftSide.end();itStrTemp++) {
		if (*itStrTemp==',')
			leftD++;
	}

	//zliczenie wymiaru prawej strony (policzeie przecinkow)
	for(itStrTemp=rightSide.begin();itStrTemp!=rightSide.end();itStrTemp++) {
		if (*itStrTemp==',')
			rightD++;
	}

	return new CArithmetic(str,"arithmetical",level,leftSide,rightSide,leftD,rightD);
}

CStatement * CLoop::CreateEndFor(char *str, unsigned int level)
{
	return new CStatement("endfor",std::string(str),level);
}


CStatement * CLoop::operator[] (unsigned int lineNr)
{
	std::map<unsigned int, CStatement *>::iterator itStatement;

	itStatement = statementMap.find(lineNr);

	if (itStatement!=statementMap.end())
		return itStatement->second;
	else
		return NULL;
}


CStatement * CLoop::Loop(unsigned int nr)
{
	std::map<unsigned int, CStatement *>::iterator itStatement;

	unsigned int nrTemp=1;
	if (nr<1 || nr>statementMap.size()) return NULL;

	for(itStatement=statementMap.begin();itStatement!=statementMap.end();itStatement++) {
		if (itStatement->second->ReturnType()=="for")
			if (nrTemp==nr)
				return itStatement->second;
			else
				nrTemp++;
		else if (nrTemp>nr)
			return NULL;
	}

	return NULL;
}



CStatement * CLoop::Arithmetical(unsigned int nr)
{
	std::map<unsigned int, CStatement *>::iterator itStatement;

	unsigned int nrTemp=1;
	if (nr<1 || nr>statementMap.size()) return NULL;

	for(itStatement=statementMap.begin();itStatement!=statementMap.end();itStatement++) {
		if (itStatement->second->ReturnType()=="arithmetical")
			if (nrTemp==nr)
				return itStatement->second;
			else
				nrTemp++;
		else if (nrTemp>nr)
			return NULL;
	}

	return NULL;
}

CStatement * CLoop::Statement(unsigned int nr)
{
	std::map<unsigned int, CStatement *>::iterator itStatement;

	itStatement = statementMap.find(nr);

	if ( itStatement!=statementMap.end() )
		return itStatement->second;
	else
		return NULL;
}

unsigned int CLoop::StatementDimension(unsigned int nr)
{
	std::map<unsigned int, CStatement *>::iterator itLine;
	unsigned int dimension(0);
	unsigned int number(0);

	for(itLine=statementMap.begin();itLine!=statementMap.end();itLine++) {
		number++;
		if (number==nr)
			return dimension;

		if (itLine->second->ReturnType()=="for")
			dimension++;
		else if (itLine->second->ReturnType()=="endfor")
			dimension--;
	}


	return 0;
}


unsigned int CLoop::NumberOfLine(std::string str, unsigned int nr)
{
	std::map<unsigned int, CStatement *>::iterator itLine;
	unsigned int numberArith(0), numberFor(0);

	for(itLine=statementMap.begin();itLine!=statementMap.end();itLine++) {
		if (itLine->second->ReturnType()=="for") {
			numberFor++;
			if (numberFor==nr && str=="for")
				return itLine->first;
		}
		else if (itLine->second->ReturnType()=="arithmetical") {
			numberArith++;
			if (numberArith==nr && str=="arithmetical")
				return itLine->first;
		}
	}

	return 0;
}

unsigned int CLoop::NumberOfFor()
{
	std::map<unsigned int, CStatement *>::iterator itFor;
	unsigned int numberFor(0);

	for(itFor=statementMap.begin();itFor!=statementMap.end();itFor++) {
		if (itFor->second->ReturnType()=="for")
			numberFor++;
		else
			break;

	}

	assert(numberFor);

	return numberFor;
}


unsigned int CLoop::LoopNumber(std::string &str)
{
	unsigned int nr=1;
	std::map<unsigned int, CStatement *>::iterator itStatement;

	for(itStatement=statementMap.begin();itStatement!=statementMap.end();itStatement++) {
		if (itStatement->second->ReturnType()=="for") {
			if (itStatement->second->IndexVarName()==str)
				return nr;
			else
				nr++;
		}
	}

	return 0;
}


std::map<int,Relation> CLoop::CreateAllIterations(char *input)
{
	std::map<int,Relation> allIterations; //zbior wszystkich iteracji
	std::map<int,Relation>::iterator itAllIterations;
	int i;
        input = "temp";
        Relation Rs;
 ComplexRelation BaseRel; // *BaseOut = new ComplexRelation;
	CreateLoopForFreeIterations(input);

	char *argvGMaker[6] = {"petit","-b -4","-g", "-Fc", "-R./analysis/petit1.out"};

	switch (LoopType()) {
		case 0:
			//PETLA IDEALNIE ZAGNIEZDZONA
                        argvGMaker[5] = input;
			GMakerPetit(6,argvGMaker);
			////////////////////////////////////////////////////
                        // dodaj instrukcje



			for(i=1;i<=petitRelations.length();i++) {
				if (i==1) {
					allIterations.insert( std::make_pair(0,Union(Range(copy(petitRelations[i])),
																			   Domain(copy(petitRelations[i])))) );
				}
				else {
					allIterations.begin()->second = Union( allIterations.begin()->second,
																	   Union(Range(copy(petitRelations[i])),
																			   Domain(copy(petitRelations[i]))) );
				}
			}
			break;
		case 1:
			//PETLA NIEIDEALNIE ZAGNIEZDZONA, ELIMINUJEMY WPIS "-FC"
			argvGMaker[3] = argvGMaker[4];
			argvGMaker[4] = input;
			GMakerPetit(5,argvGMaker);
			///////////////////////////////////////////////////////

                        petitRelations = NormalizeRel(petitRelations);


    BaseRel.R = petitRelations;
    BaseRel.VecType = petitRelationsVecType;
    BaseRel.DepVect = petitDepVector;
    BaseRel.From = petitFrom;
    BaseRel.To = petitTo;
    BaseRel.Type = petitRelationsType;
    BaseRel.Line = petitLine;
    BaseRel.Var = petitVar;

                        BaseRel = Ext_Base(BaseRel);

                        petitRelations = BaseRel.R;

                        Rs = globalUnion(petitRelations);
                        Rs = Union(Domain(copy(Rs)), Range(copy(Rs)));
                        Rs.simplify(2, 2);
                        Rs = SimplifyNumConjuncts(Rs);


                        Rs.print();




			for(i=1;i<=petitRelations.length();i++) {
				itAllIterations = allIterations.find(petitFrom[i]); //dla Domain
				if (itAllIterations!=allIterations.end()) {
					//jest juz taki wpis
					itAllIterations->second = Union(itAllIterations->second, Domain(copy(petitRelations[i])));
					(itAllIterations->second).simplify();
				}
				else {
					//nie ma takiego jeszcze wpisu
					allIterations.insert(std::make_pair(petitFrom[i], Domain(copy(petitRelations[i]))) );
				}

				itAllIterations = allIterations.find(petitTo[i]); //dla Range
				if (itAllIterations!=allIterations.end()) {
					//jest juz taki wpis
					itAllIterations->second = Union(itAllIterations->second, Range(copy(petitRelations[i])));
					(itAllIterations->second).simplify();
				}
				else {
					//nie ma takiego jeszcze wspisu
					allIterations.insert(std::make_pair(petitFrom[i], Range(copy(petitRelations[i]))) );
				}

			}

                        allIterations.begin()->second = Rs;

			break;
		default:
			//blad
			assert(0);
			break;
	};

        //return Rs;
	return allIterations;
}


void CLoop::Print(char *out)
{
	std::map<unsigned int, CStatement *>::iterator itStatement;

	FILE * output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"w");

	fprintf(output,"Loop read : \n");
	for(itStatement=statementMap.begin();itStatement!=statementMap.end();itStatement++) {
		fprintf(output,"%u : %s\n",itStatement->first,itStatement->second->ReturnType().c_str());
	}
	fprintf(output,"\n\n");

	if (out!=NULL) fclose(output);
}

//funkcja zwarcajaca true jesli znak jest znakiem bialym no spacja tabulacja itp
bool CLoop::WhiteSpace(char arg)
{
	if (arg=='\n' || arg=='\t')
		return true;
	else
		return false;
}

//funkcja uzywana w destruktorze CLoop do kasowania obiektow CStatement
void CLoop::DeleteSecondStatement(std::pair<int,CStatement *> arg)
{
	delete arg.second;
}




bool CLoop::IsParameterized(int nrLoop)
{
	char tmp;
	CStatement *wskStat = Loop(nrLoop);
	std::string upperBound = wskStat->ReturnUpperBound();


	for(int i=0;i<=upperBound.size();i++) {
		tmp = upperBound[i];
		if ( (tmp>='A' && tmp<='Z') || (tmp>='a' && tmp<='z') ) {
			//czyli mamy jakas zmienna sparametryzowana
			return true;
		}
	}
	return false;
}



CFor::CFor(std::string b, std::string t, unsigned int lev, std::string var) :
			  CStatement(b,t,lev), indexVarName(var) {

	std::string::size_type begin,end;
        std::string s = body;

	//Dodajemy gorna granice dla petli
	begin = body.find(str("to"));
	begin += 3;

	end = body.find(str("do"));
	end--;

// printf("***%i %i %i\n", body.length(), end, begin);

	for(int i=begin;i<=end;i++) {
		if (body[i]!=' ') {
			upperBound.append(sizeof(char),body[i]);
		}
	}

	//wskCFor->upperBound = strTemp.substr(begin,end-begin);
//			printf((wskCFor->upperBound).c_str());
			///////////////////////////////////////


}
