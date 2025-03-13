

typedef boost::adjacency_matrix<boost::directedS> Graph;

//------------------- Interfaces.h
struct SFromTo {
	SFromTo() : from(0), to(0) {}
	SFromTo(unsigned int f, unsigned int t) : from(f), to(t) {}
	SFromTo(unsigned int f, unsigned int t, std::string relType) : from(f), to(t), relationType(relType) {}
	unsigned int from;
	unsigned int to;
	std::string relationType;  //rodzaj relacji : flow, anti, output, ...
};

struct SLessFromTo {
	bool operator () (const SFromTo &arg1, const SFromTo &arg2) const
	{
		if (arg1.from<arg2.from || (arg1.from==arg2.from && arg1.to<arg2.to) )
			return true;
		else
			return false;

		//if (arg2.from != 0 && arg2.to != 0)
		//{
		//	//porownujemy wzgledem from i to
		//	if (arg1.from<arg2.from || (arg1.from==arg2.from && arg1.to<arg2.to) )
		//		return true;
		//	else
		//		return false;
		//}
		//else if (arg2.from != 0 && arg2.to == 0)
		//{
		//	//porownujmey wzgledem from
		//	if (arg1.from<arg2.from)
		//		return true;
		//	else
		//		return false;
		//
		//}
		//else if (arg2.from == 0 && arg2.to != 0)
		//{
		//	//porownujemy wzgldem to
		//	if (arg1.to<arg2.to)
		//		return true;
		//	else
		//		return false;
		//}
	}
};


//struktura slazaca do przechowywania relacji wybierajacych zalezne iteracje
//oraz wektory zaleznosci przynaleznye do tej relacji
struct SRelationVector {
	SRelationVector(const Relation &rel, std::string relType, const Relation &vec, bool vecType,
					int arg1=-1, int arg2=-1) : selectingRel(rel), relationType(relType),
					distanceVec(vec), distanceVecType(vecType),
					from(arg1), to(arg2) {}
					SRelationVector(const Relation &rel, std::string relType, const Relation &vec,
					int arg1=-1, int arg2=-1);


	//	SRelationVector(const Relation &rel);
	unsigned int from;
	unsigned int to;
	Relation selectingRel;	//relacja wybierajaca
	Relation distanceVec;	//zbior wektorow zaleznosci dla powyzszej relacji
	bool distanceVecType;	//true - wektor zaleznosci staly,
									//false - wektor zaleznosci zmienny
	std::string relationType; //rodzaj relacji : flow, anti, output, ...
};

// Interfaces.cpp

SRelationVector::SRelationVector(const Relation &rel, std::string relType, const Relation &vec,
								 int arg1, int arg2) : selectingRel(rel), relationType(relType),
								 distanceVec(vec), from(arg1), to(arg2)
{
	coef_t upperBound,lowerBound;

	//ustalenie czy wektor dystansu dla relacji <selectingRel> jest staly
	for(int i=1;i<=distanceVec.n_set();i++) {
		distanceVec.query_variable_bounds(set_var(i),lowerBound,upperBound);
		if (lowerBound!=upperBound) {
			distanceVecType = false;
			break;
		}
		else {
			distanceVecType = true;
		}
	}
	//rodzaj wektora dystansu ustalony
}

// -----------------------------------
// Convert.h

Relation TPDS_ConstantVariable(const Relation &pInputRelation, int pInputVariableNumber, int pInputVariableValue, int pOutputVariableNumber = 0, int pOutputVariableValue = 0);
Relation TPDS_ConstantVariable(const Relation &pInputRelation, char *pVariableName, int pVariableValue);


int TPDS_ConvertTupleToVector_Relation(Tuple<Relation> &pTupleInput, std::vector<Relation> &pVectorOutput);
int TPDS_ConvertTupleToVector_Bool(Tuple<bool> &pTupleInput, std::vector<bool> &pVectorOutput);

int TPDS_Convert(std::vector<char *> &, std::vector<std::string> &);
int TPDS_Convert(std::vector<Relation> &, std::list<Relation> &);
int TPDS_Convert(std::vector<int> &, std::list<int> &);
int TPDS_Convert(std::list<Relation> &, std::vector<Relation> &);
int TPDS_Convert(std::list<int> &, std::vector<int> &);
int TPDS_Convert(std::map<SFromTo, std::vector<SRelationVector>, SLessFromTo> &,
				 std::vector<Relation> &, std::vector<char *> &, std::vector<int> &,
				 std::vector<int> &, std::vector<Relation> &, std::vector<bool> &);
int TPDS_Convert(std::map<SFromTo, Relation, SLessFromTo> &,
				 std::vector<Relation> &, std::vector<int> &, std::vector<int> &);
int TPDS_Convert(std::multimap<SFromTo, Relation, SLessFromTo> &,
				 std::vector<Relation> &, std::vector<int> &, std::vector<int> &);

int TPDS_Print(std::vector<Relation> &, const char *, char *out=NULL);
int TPDS_Print(std::map<int,Relation> &, const char *, char *out=NULL);
int TPDS_Print(std::map<int,int> &, const char *, char *out=NULL);
int TPDS_Print(std::map<int, std::map<SFromTo,Relation,SLessFromTo> > &, const char *, const char *, char *out=NULL);
int TPDS_Print(std::map<int, std::multimap<SFromTo,Relation,SLessFromTo> > &, const char *, const char *, char *out=NULL);
int TPDS_Print(std::map<SFromTo,Relation,SLessFromTo> &, const char *, char *out=NULL);
int TPDS_Print(std::multimap<SFromTo,Relation,SLessFromTo> &, const char *, char *out=NULL);
int TPDS_Print(std::map<int,String> &, const char *, const char *out=NULL);
int TPDS_Print(std::vector<Relation> &pRel, std::vector<int> &pFrom, std::vector<int> &pTo, const char *, char *out=NULL);
int TPDS_Print(std::map<SFromTo, std::vector<SRelationVector>, SLessFromTo> &, const char *, char *out=NULL);
int TPDS_Print(std::set<int> &, const char *, char *out=NULL);
int TPDS_Print(std::vector<Relation> & pLoopRelations, std::vector<std::string> & pLoopRelationsType,
			   std::vector<Relation> & pLoopRelationsDepVectors, std::vector<bool> & pLoopRelationsVecType,
			   std::vector<int> & pLoopRelationsFrom, std::vector<int> & pLoopRelationsTo, char *out=NULL);
int TPDS_Print_RawStat(std::vector<Relation> &pRelations, const char *pMessage, char *out);

int TPDS_DoubleDimensionSet(Relation &pSetInput, Relation &pSetOutput);
int TPDS_DoubleDimensionMapSets(std::map<int,Relation> &pMapSetsInput, std::map<int,Relation> &pMapSetsOutput);

int TPDS_ConvertToMap(std::vector<Relation> &, std::vector<int> &, std::vector<int> &, std::map<SFromTo,Relation,SLessFromTo> &pMapOutput);

int TPDS_GetMaximalDimension(std::map<SFromTo,Relation,SLessFromTo> &);

//tworzy relacje mapuj¹c¹ zbior [x,y] na [x,y,x,y] czyli relacja (dim=2) [x,y]->[x,y,x,y]
Relation TPDS_MakeMappingRelationDimTo2Dim(int pDim);
//tworzy relacje mapujaca z relacji wejciowj np. input - [x,y]->[i,j,k] output - [x,y]->[i,j,k,x,y]
Relation TPDS_MakeMappingRelationInputToOutputInput(Relation &pRelationInput);
//tworzy relacje przestawiajaca zmienne w zbiorze np. wywloanie (5,2,3) wygeneruja relacje
//[a,b,c,d,e]->[d,e,a,b,c]
Relation TPDS_MakeMappingRelationReverseSet(int pDim, int pFirst, int pSecend);
//[a,b]->[c,d] rozszerza do relacji [a,b,x,y]->[c,d,x,y]
Relation TPDS_MakeMappingRelation(Relation &pRelation, int pDim);
//tworzy relacje torzsamosciowa
Relation TPDS_MakeMappingRelation(int pDim);
//(pDim)->(pDim,pOut) np. pDim=2,pOut=3  [a,b]->[a,b,0,0,0]
Relation TPDS_MakeMappingRelation(int pDim, int pOut);

/***Funkcje zapo¿yczone z JDPC do redukcji nadmiarowych zale¿noci*************/
void TPDS_ExtendendReduction(std::vector<Relation> pInLoopRelations, std::vector<std::string> pInLoopRelationsType, std::vector<int> pInLoopRelationsFrom, std::vector<int> pInLoopRelationsTo, std::vector<Relation> pInLoopDepVector, std::vector<bool> pInLoopRelationsVecType,
							 std::vector<Relation> &pOutLoopRelations, std::vector<std::string> &pOutLoopRelationsType, std::vector<int> &pOutLoopRelationsFrom, std::vector<int> &pOutLoopRelationsTo, std::vector<Relation> &pOutLoopDepVector, std::vector<bool> &pOutLoopRelationsVecType);

void TPDS_SaveNonParNonRed(std::vector<SRelationVector> &selectingRel, Relation &rel, std::string relType,
						   Relation &depVector, bool vectorType, unsigned int from, unsigned int to);

int TPDS_ParallelVectors(Relation &arg1, Relation &arg2);

bool TPDS_VarDividedByConst(int constant, unsigned int varNumber, Relation &arg);

bool TPDS_ConstVector(Relation &vector);
/****************/

int TPDS_RemoveRelationsByType(std::vector<std::string> pRelationTypeToRemove,
							   std::vector<Relation> & pLoopRelations, std::vector<std::string> & pLoopRelationsType,
							   std::vector<Relation> & pLoopRelationsDepVectors, std::vector<bool> & pLoopRelationsVecType,
							   std::vector<int> & pLoopRelationsFrom, std::vector<int> & pLoopRelationsTo);

int TPDS_RelationsWithoutCommonEnd(std::vector<Relation> pInRelations, std::vector<int> pInFrom, std::vector<int> pInTo,
								   std::vector<Relation> & pOutRelations, std::vector<int> & pOutFrom, std::vector<int> & pOutTo);

// ----------------------------------------
// Convert.cpp


Relation TPDS_ConstantVariable(const Relation &pInputRelation, int pInputVariableNumber, int pInputVariableValue, int pOutputVariableNumber, int pOutputVariableValue)
{
	Relation _RetValue = copy(pInputRelation);

	if (pInputVariableNumber > 0 || pOutputVariableNumber > 0)
	{
		F_And *and = _RetValue.and_with_and();
		EQ_Handle eq;

		if (pInputVariableNumber > 0)
		{
			eq = and->add_EQ();
			eq.update_coef(_RetValue.input_var(pInputVariableNumber),-1);
			eq.update_const(pInputVariableValue);
		}
		if (pOutputVariableNumber > 0)
		{
			eq = and->add_EQ();
			eq.update_coef(_RetValue.output_var(pOutputVariableNumber),-1);
			eq.update_const(pOutputVariableValue);
		}
	}

	_RetValue.simplify(2,4);

	return _RetValue;
}

Relation TPDS_ConstantVariable(const Relation &pInputRelation, char *pVariableName, int pVariableValue)
{
	Relation _RetValue = copy(pInputRelation);

	Variable_ID _wskVar;

	//search input variable with name 'pVariableName'
	for(int i = 1; i <= _RetValue.n_inp(); i++)
	{
		_wskVar = _RetValue.input_var(i);

		if ( strcmp(_wskVar->char_name(),pVariableName) == 0 )
		{
			F_And *and = _RetValue.and_with_and();
			EQ_Handle eq;

			eq = and->add_EQ();
			eq.update_coef(_RetValue.input_var(i),-1);
			eq.update_const(pVariableValue);
		}
	}

	//search output variable with name 'pVariableName'
	//????

	_RetValue.simplify(2,4);

	return _RetValue;
}


int TPDS_Convert(std::map<SFromTo, Relation, SLessFromTo> &pMap,
				 std::vector<Relation> &pRelations, std::vector<int> &pFrom, std::vector<int> &pTo)
{
	int _RetValue = 0;

	std::map<SFromTo, Relation, SLessFromTo>::iterator _itMap;

	pRelations.clear();
	pFrom.clear();
	pTo.clear();

	for(_itMap = pMap.begin(); _itMap != pMap.end(); _itMap++)
	{
		pRelations.push_back(_itMap->second);
		pFrom.push_back((_itMap->first).from);
		pTo.push_back((_itMap->first).to);
	}

    return _RetValue;
}

int TPDS_Convert(std::multimap<SFromTo, Relation, SLessFromTo> &pMap,
				 std::vector<Relation> &pRelations, std::vector<int> &pFrom, std::vector<int> &pTo)
{
	int _RetValue = 0;

	std::multimap<SFromTo, Relation, SLessFromTo>::iterator _itMap;

	pRelations.clear();
	pFrom.clear();
	pTo.clear();

	for(_itMap = pMap.begin(); _itMap != pMap.end(); _itMap++)
	{
		pRelations.push_back(_itMap->second);
		pFrom.push_back((_itMap->first).from);
		pTo.push_back((_itMap->first).to);
	}

    return _RetValue;
}



int TPDS_Convert(std::map<SFromTo, std::vector<SRelationVector>, SLessFromTo> &pMap,
				 std::vector<Relation> &pRelation, std::vector<std::string> &pRelationType, std::vector<int> &pFrom,
				 std::vector<int> &pTo, std::vector<Relation> &pRelationDepVec, std::vector<bool> &pVecType)
{
	int _RetValue = 0;

	std::map<SFromTo, std::vector<SRelationVector>, SLessFromTo>::iterator _itOuter;
	std::vector<SRelationVector>::iterator _itInner;

	pRelation.clear();
	pRelationType.clear();
	pFrom.clear();
	pTo.clear();
	pRelationDepVec.clear();
	pVecType.clear();

	for(_itOuter = pMap.begin(); _itOuter != pMap.end(); _itOuter++)
	{
		for(_itInner = (_itOuter->second).begin(); _itInner != (_itOuter->second).end(); _itInner++)
		{
			pRelation.push_back(copy(_itInner->selectingRel));
			pRelationType.push_back((_itInner->relationType).c_str());
			pFrom.push_back(_itInner->from);
			pTo.push_back(_itInner->to);
			pRelationDepVec.push_back(_itInner->distanceVec);
			pVecType.push_back(_itInner->distanceVecType);
		}
	}



	return _RetValue;
}


int TPDS_Convert(std::vector<char *> &pVectorInput, std::vector<std::string> &pVectorOutput)
{
	int _RetValue = 0;

	for(std::vector<char *>::iterator _it = pVectorInput.begin(); _it != pVectorInput.end(); _it++)
	{
		pVectorOutput.push_back(std::string(*_it));
	}

	return _RetValue;
}


int TPDS_ConvertTupleToVector_Relation(Tuple<Relation> &pTupleInput, std::vector<Relation> &pVectorOutput)
{
	int _RetValue = 0;

	for(Tuple_Iterator<Relation> _it(pTupleInput); _it; _it++)
	{
		pVectorOutput.push_back(*_it);
	}

	return _RetValue;
}


int TPDS_ConvertTupleToVector_Bool(Tuple<bool> &pTupleInput, std::vector<bool> &pVectorOutput)
{
	int _RetValue = 0;

	for(Tuple_Iterator<bool> _it(pTupleInput); _it; _it++)
	{
		pVectorOutput.push_back(*_it);
	}

	return _RetValue;
}

int TPDS_Print_RawStat(std::vector<Relation> &pRelations, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	fprintf(output, " %s %d", pMessage, pRelations.size());

    if (out != NULL)
		fclose(output);

	return _RetValue;
}


int TPDS_Print(std::map<SFromTo, std::vector<SRelationVector>, SLessFromTo> &pMap, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::map<SFromTo, std::vector<SRelationVector>, SLessFromTo>::iterator _itOuter;
	std::vector<SRelationVector>::iterator _itInner;

	fprintf(output,"\n%s\n",pMessage);
	for(_itOuter = pMap.begin(); _itOuter != pMap.end(); _itOuter++)
	{
		fprintf(output,"\n%d->%d\n",(_itOuter->first).from,(_itOuter->first).to);
		for(_itInner = (_itOuter->second).begin(); _itInner != (_itOuter->second).end(); _itInner++)
		{
			fprintf(output,"%d->%d (%s): ",_itInner->from,_itInner->to, (_itInner->relationType).c_str());
			(_itInner->selectingRel).print_with_subs(output);
		}
	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}

int TPDS_Print(std::vector<Relation> & pLoopRelations, std::vector<std::string> & pLoopRelationsType,
			   std::vector<Relation> & pLoopRelationsDepVectors, std::vector<bool> & pLoopRelationsVecType,
			   std::vector<int> & pLoopRelationsFrom, std::vector<int> & pLoopRelationsTo, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::vector<Relation>::iterator _itRel;
	std::vector<bool>::iterator _itRelVecType;
	std::vector<Relation>::iterator _itRelDepVec;
	std::vector<int>::iterator _itRelFrom;
	std::vector<int>::iterator _itRelTo;
	std::vector<std::string>::iterator _itRelType;

	fprintf(output,"Number fo relations : %d\n\n",pLoopRelations.size());

	for(_itRel = pLoopRelations.begin(), _itRelVecType = pLoopRelationsVecType.begin(), _itRelDepVec = pLoopRelationsDepVectors.begin(),
		_itRelFrom = pLoopRelationsFrom.begin(), _itRelTo = pLoopRelationsTo.begin(), _itRelType = pLoopRelationsType.begin();
		_itRel != pLoopRelations.end();
		_itRel++, _itRelVecType++, _itRelDepVec++, _itRelFrom++, _itRelTo++, _itRelType++)
	{
		fprintf(output,"%s  %i -> %i\n",_itRelType->c_str(),*_itRelFrom,*_itRelTo);
		_itRel->print_with_subs(output);

	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}



int TPDS_Print(std::vector<Relation> &pRel, std::vector<int> &pFrom, std::vector<int> &pTo, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	fprintf(output,"\n%s\n",pMessage);
	for (int i=0; i < pRel.size(); i++)
	{
		fprintf(output,"%i->%i : ",pFrom[i],pTo[i]);
		pRel[i].print_with_subs(output);
	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}

int TPDS_Print(std::set<int> &pSet, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::set<int>::iterator _itItem;

	fprintf(output,"%s",pMessage);
	for(_itItem = pSet.begin(); _itItem != pSet.end(); _itItem++)
	{
		fprintf(output," %d ",*_itItem);
	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}



int TPDS_Print(std::vector<Relation> &pVectorRelations, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::vector<Relation>::iterator _itItem;

	fprintf(output,"\n%s\n",pMessage);
	for(_itItem = pVectorRelations.begin(); _itItem != pVectorRelations.end(); _itItem++)
	{
		_itItem->print_with_subs(output);
	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}

int TPDS_Print(std::map<int,int> &pMapIntInt, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::map<int,int>::iterator _itItem;

	fprintf(output,"\n%s\n",pMessage);
	for(_itItem = pMapIntInt.begin(); _itItem != pMapIntInt.end(); _itItem++)
	{
		fprintf(output,"%d -> %d\n",_itItem->first, _itItem->second);
	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}


int TPDS_Print(std::map<int,Relation> &pMapIntRelations, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::map<int,Relation>::iterator _itItem;

	fprintf(output,"\n%s\n",pMessage);
	for(_itItem = pMapIntRelations.begin(); _itItem != pMapIntRelations.end(); _itItem++)
	{
		fprintf(output,"%d : ",_itItem->first);
		(_itItem->second).print_with_subs(output);
	}

	if (out != NULL)
		fclose(output);

	return _RetValue;
}

int TPDS_Print(std::multimap<SFromTo,Relation,SLessFromTo> &pSource, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::multimap<SFromTo,Relation,SLessFromTo>::iterator _itItem;

	fprintf(output,"\n%s\n",pMessage);
	for(_itItem = pSource.begin(); _itItem != pSource.end(); _itItem++)
	{
		fprintf(output,"%d,%d (%s): ",(_itItem->first).from, (_itItem->first).to, (_itItem->first).relationType.c_str());
		(_itItem->second).print_with_subs(output);
	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}


int TPDS_Print(std::map<SFromTo,Relation,SLessFromTo> &pSource, const char *pMessage, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::map<SFromTo,Relation,SLessFromTo>::iterator _itItem;

	fprintf(output,"\n%s\n",pMessage);
	for(_itItem = pSource.begin(); _itItem != pSource.end(); _itItem++)
	{
		fprintf(output,"%d,%d (%s): ",(_itItem->first).from, (_itItem->first).to, (_itItem->first).relationType.c_str());
		(_itItem->second).print_with_subs(output);
	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}

int TPDS_Print(std::map<int, std::multimap<SFromTo,Relation,SLessFromTo> > &pSource, const char *pMessage1, const char *pMessage2, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	char _Temp[10];
	std::string _MessageInner;
	std::map<int, std::multimap<SFromTo,Relation,SLessFromTo> >::iterator _itSource;
	//std::map<SFromTo,Relation,SLessFromTo>::iterator _itInner;

	fprintf(output,"\n%s\n",pMessage1);

	if (out != NULL)
		fclose(output);

	for(_itSource = pSource.begin(); _itSource != pSource.end(); _itSource++)
	{
		_MessageInner.erase();
		_itoa(_itSource->first,_Temp,10);
		_MessageInner += pMessage2;
		_MessageInner += _Temp;
		//fprintf(output,"   FairSources in statement %d :\n",_itSource->first);
		TPDS_Print(_itSource->second,_MessageInner.c_str(), out);
	}

	return _RetValue;
}

int TPDS_Print(std::map<int, std::map<SFromTo,Relation,SLessFromTo> > &pSource, const char *pMessage1, const char *pMessage2, char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	char _Temp[10];
	std::string _MessageInner;
	std::map<int, std::map<SFromTo,Relation,SLessFromTo> >::iterator _itSource;
	//std::map<SFromTo,Relation,SLessFromTo>::iterator _itInner;

	fprintf(output,"\n%s\n",pMessage1);

	if (out != NULL)
		fclose(output);

	for(_itSource = pSource.begin(); _itSource != pSource.end(); _itSource++)
	{
		_MessageInner.erase();
		_itoa(_itSource->first,_Temp,10);
		_MessageInner += pMessage2;
		_MessageInner += _Temp;
		//fprintf(output,"   FairSources in statement %d :\n",_itSource->first);
		TPDS_Print(_itSource->second,_MessageInner.c_str(), out);
	}

	return _RetValue;
}

int TPDS_Print(std::map<int,String> &pThreads, const char *pMessage, const char *out)
{
	int _RetValue = 0;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::map<int,String>::iterator _itThread;

	fprintf(output,"\n%s\n",pMessage);
	for(_itThread = pThreads.begin(); _itThread != pThreads.end(); _itThread++)
	{
		fprintf( output,"\n%d\n",_itThread->first );
		fprintf( output,"%s\n",(const char *)(_itThread->second) );
	}

    if (out != NULL)
		fclose(output);

	return _RetValue;
}

int TPDS_GetMaximalDimension(std::map<SFromTo,Relation,SLessFromTo> &pMap)
{
	int _RetValue = 0;

	std::map<SFromTo,Relation,SLessFromTo>::iterator _it;

	for(_it = pMap.begin(); _it != pMap.end(); _it++)
	{
		if ( (_it->second).n_set() > _RetValue )
		{
			_RetValue = (_it->second).n_set();
		}
	}

	return _RetValue;
}


Relation TPDS_MakeMappingRelationDimTo2Dim(int pDim)
{
	Relation _RetValue = Relation(pDim,2*pDim);
	F_And *and;
	EQ_Handle eq;
	//Variable_ID varIn,varOut;

	and = _RetValue.add_and();
	for(int i=1; i<=pDim; i++)
	{
		eq = and->add_EQ();
		eq.update_coef(_RetValue.input_var(i),1);
		eq.update_coef(_RetValue.output_var(i),-1);

		eq = and->add_EQ();
		eq.update_coef(_RetValue.input_var(i),1);
		eq.update_coef(_RetValue.output_var(pDim+i),-1);
	}

#ifdef _DEBUG_PRINT
	_RetValue.print_with_subs();
#endif

	return _RetValue;
}

Relation TPDS_MakeMappingRelationInputToOutputInput(Relation &pRelationInput)
{
	Relation _RetValue;

	F_And *root;
	EQ_Handle eq;

	int _DimInput = pRelationInput.n_inp();
	int _DimOutput = pRelationInput.n_out();

	_RetValue = copy(pRelationInput);
	Extend_Range(_RetValue,_DimInput);

	root = _RetValue.and_with_and();
	for(int i=1; i<=_DimInput;i++)
	{
		eq = root->add_EQ();

		eq.update_coef(input_var(i),-1);
		eq.update_coef(output_var(_DimInput+1),1);
	}

	_RetValue.simplify(2,4);

	return _RetValue;
}


//[a,b]->[c,d] rozszerza do relacji [a,b,x,y]->[c,d,x,y]
Relation TPDS_MakeMappingRelation(Relation &pRelation, int pDim)
{
	Relation _RetValue = copy(pRelation);

	F_And *root;
	EQ_Handle eq;

	int i;
	int _InputDim,_OutputDim;

	_InputDim = _RetValue.n_inp();
	_OutputDim = _RetValue.n_out();

	_RetValue = Extend_Domain(_RetValue,pDim);
	_RetValue = Extend_Range(_RetValue,pDim);

	root = _RetValue.and_with_and();
	for (i=1;i<=pDim;i++)
	{
		eq = root->add_EQ();

		eq.update_coef( input_var(_InputDim+i),-1 );
		eq.update_coef( output_var(_OutputDim+i),1 );
	}

	_RetValue.simplify(2,4);

#ifdef _DEBUG_PRINT
	_RetValue.print_with_subs();
#endif


	return _RetValue;
}


//tworzy relacje torzsamosciowa
Relation TPDS_MakeMappingRelation(int pDim)
{
	Relation _RetValue = Relation(pDim,pDim);

	int i;
	F_And *root;
	EQ_Handle eq;

	root = _RetValue.add_and();
	for(i=1;i<=pDim;i++)
	{
		eq = root->add_EQ();

		eq.update_coef(input_var(i),1);
		eq.update_coef(output_var(i),-1);
	}

	_RetValue.simplify(2,4);

#ifdef _DEBUG_PRINT
	_RetValue.print_with_subs();
#endif

	return _RetValue;
}


Relation TPDS_MakeMappingRelation(int pDim, int pOut)
{
	Relation _RetValue = Relation(pDim,pOut);

	F_And *root;
	EQ_Handle eq;

	int i;

	root = _RetValue.add_and();
	for (i=1;i<=pDim;i++)
	{
		eq = root->add_EQ();

		eq.update_coef(input_var(i),1);
		eq.update_coef(output_var(i),-1);
	}
	for (i=pDim+1;i<=pOut;i++)
	{
		eq = root->add_EQ();

		eq.update_coef(output_var(i),-1);
	}

	_RetValue.simplify(2,4);

//	_RetValue.print_with_subs();

	return _RetValue;
}




//[a,b,c,d,e]->[d,e,a,b,c]
Relation TPDS_MakeMappingRelationReverseSet(int pDim, int pFirst, int pSecond)
{
	Relation _RetValue = Relation(pDim,pDim);

	F_And *root;
	EQ_Handle eq;

	int i;

	root = _RetValue.add_and();
	for (i=1;i<=pFirst;i++)
	{
		eq = root->add_EQ();

		eq.update_coef(input_var(pSecond+i),1);
		eq.update_coef(output_var(i),-1);
	}
	for (i=1;i<=pSecond;i++)
	{
		eq = root->add_EQ();

		eq.update_coef(input_var(i),1);
		eq.update_coef(output_var(pFirst+i),-1);
	}

	_RetValue.simplify(2,4);

	return _RetValue;
}



int TPDS_DoubleDimensionSet(Relation &pSetInput, Relation &pSetOutput)
{
	int _RetValue = 0;

	Relation _SetInput = copy(pSetInput);
	Relation _MappingRelation = TPDS_MakeMappingRelationDimTo2Dim(_SetInput.n_set());

	pSetOutput = Restrict_Domain( copy(_MappingRelation), copy(_SetInput) );
	pSetOutput = Range(pSetOutput);

	pSetOutput.simplify(2,4);

	return _RetValue;
}


int TPDS_DoubleDimensionMapSets(std::map<int,Relation> &pMapSetsInput, std::map<int,Relation> &pMapSetsOutput)
{
	int _RetValue = 0;

	std::map<int,Relation>::iterator _itItem;
	Relation _SetTemp;

	for(_itItem = pMapSetsInput.begin(); _itItem != pMapSetsInput.end() && _RetValue == 0; _itItem++)
	{
		if ( (_RetValue = TPDS_DoubleDimensionSet(_itItem->second, _SetTemp)) == 0)
		{
			pMapSetsOutput.insert( std::make_pair(_itItem->first,_SetTemp) );
		}
	}

	return _RetValue;
}


int TPDS_ConvertToMap(std::vector<Relation> &pRel, std::vector<int> &pFrom, std::vector<int> &pTo, std::map<SFromTo,Relation,SLessFromTo> &pMapOutput)
{
	int _RetValue = 0;

	int i;


	for(i=0;i<pRel.size();i++)
	{
		pMapOutput.insert( std::make_pair(SFromTo(pFrom[i],pTo[i]),copy(pRel[i])) );
	}

	return _RetValue;
}

int TPDS_Convert(std::vector<Relation> &pInput, std::list<Relation> &pOutput)
{
	int _RetValue = 0;

	std::copy(pInput.begin(),pInput.end(),pOutput.begin());

	return _RetValue;
}


int TPDS_Convert(std::vector<int> &pInput, std::list<int> &pOutput)
{
	int _RetValue = 0;

	std::copy(pInput.begin(),pInput.end(),pOutput.begin());

	return _RetValue;
}


int TPDS_Convert(std::list<Relation> &pInput, std::vector<Relation> &pOutput)
{
	int _RetValue = 0;

	std::copy(pInput.begin(),pInput.end(),pOutput.begin());

	return _RetValue;

}


int TPDS_Convert(std::list<int> &pInput, std::vector<int> &pOutput)
{
	int _RetValue = 0;

	std::copy(pInput.begin(),pInput.end(),pOutput.begin());

	return _RetValue;
}


void TPDS_ExtendendReduction(std::vector<Relation> pInLoopRelations, std::vector<std::string> pInLoopRelationsType, std::vector<int> pInLoopRelationsFrom, std::vector<int> pInLoopRelationsTo, std::vector<Relation> pInLoopDepVector, std::vector<bool> pInLoopRelationsVecType,
							 std::vector<Relation> &pOutLoopRelations, std::vector<std::string> &pOutLoopRelationsType, std::vector<int> &pOutLoopRelationsFrom, std::vector<int> &pOutLoopRelationsTo, std::vector<Relation> &pOutLoopDepVector, std::vector<bool> &pOutLoopRelationsVecType)
{
	std::map<SFromTo, std::vector<SRelationVector>, SLessFromTo> petitMapRelations;
	std::map<SFromTo, std::vector<SRelationVector>, SLessFromTo>::iterator itPetitRel;
	std::vector<SRelationVector> relTupleTemp;
	SFromTo temp;

	for (int i = 0; i < pInLoopRelations.size();i++) {
		temp.from = pInLoopRelationsFrom[i];
		temp.to = pInLoopRelationsTo[i];

		itPetitRel = petitMapRelations.find(temp);
		pInLoopRelations[i].print_with_subs();

		if (itPetitRel == petitMapRelations.end()) {
			relTupleTemp.clear();
			relTupleTemp.push_back( SRelationVector(pInLoopRelations[i],pInLoopRelationsType[i], pInLoopDepVector[i],
												   pInLoopRelationsFrom[i], pInLoopRelationsTo[i]) );
			petitMapRelations.insert( std::make_pair( temp, relTupleTemp) );
		}
		else {
			TPDS_SaveNonParNonRed(itPetitRel->second, pInLoopRelations[i], pInLoopRelationsType[i], pInLoopDepVector[i],
								  TPDS_ConstVector(pInLoopDepVector[i]), pInLoopRelationsFrom[i],
								  pInLoopRelationsTo[i]);
		}

	}

	TPDS_Print(petitMapRelations,"Reduced relations");
	TPDS_Convert(petitMapRelations, pOutLoopRelations, pOutLoopRelationsType, pOutLoopRelationsFrom, pOutLoopRelationsTo, pOutLoopDepVector, pOutLoopRelationsVecType);
}




void TPDS_SaveNonParNonRed(std::vector<SRelationVector> &selectingRel,
						   Relation &rel, std::string relType, Relation &depVector, bool vectorType, unsigned int from, unsigned int to)
{
	coef_t upperBound1,lowerBound1;
	coef_t upperBound2,lowerBound2;
	std::vector<SRelationVector>::iterator it;
	int number; 	//numer zmiennej w zbiorze powodujacej rownoleglosc wektorow

	Relation temp1,temp2,temp3;

//	Relation distance;
//	distance = Deltas(copy(rel));
//	distance.simplify(2,2);

//	rel.print();
//	distance.print();

	bool vectorAdded=false;	//wartosc zmiennej zostanie zmieniona na true jesli relacja
	//	<rel> zostanie dodana do zbioru relacji wybierajacych

/***sprawdzamy czy trzeba dodac relacje <rel> ze stalym wektorem <distance> do juz***/
/****istniejacych relacji o stalych wektorach dystansu********************************/
	if (vectorType) {
		for(it=selectingRel.begin();it!=selectingRel.end();it++) {
			if (it->distanceVecType) {
				//oba wektory dystansu sa stale
				number = TPDS_ParallelVectors(it->distanceVec,depVector);

				if (number==0 && from==to) {
					//wektory identyczne, w taki przypadku nalezy sprawdzic zakres zakresy
					//relacji <it->selectingRel> z <rel> i wybrac ta z wiekszym zakresem
					temp1 = Difference(copy(it->selectingRel),copy(rel));
					temp2 = Difference(copy(rel),copy(it->selectingRel));
					temp1.simplify(2,2);
					temp2.simplify(2,2);

//					(it->selectingRel).print();
//					rel.print();
					//jesli dwie relacje nie sa puste to cos nie tak !!!
					assert(!(temp1.number_of_conjuncts() && temp2.number_of_conjuncts()));
					if (temp2.number_of_conjuncts()) {
						//czyli relacja <rel> ma wiekszy zakres od <it->selectingRel>
						//dlatego w miejsce wskazywane przez <it> wstawiamy <rel>
						*it = SRelationVector(rel,relType,depVector,vectorType,from,to);
					}
					//mozemy przerwac wyszukiwanie, gdyz nie powinno byc identycznych wekorow
					//jesli beda to blad !!
					return; /***********!!!!!!!!!!!!!!!!!!!!!*********************/
					break;
				}
				if (number>0) {
					//wektory rownolegle, a roznica w zmiennej o numerze <number>
					(it->distanceVec).query_variable_bounds(set_var(number),lowerBound1,upperBound1);
					depVector.query_variable_bounds(set_var(number),lowerBound2,upperBound2);

					if (lowerBound1 > lowerBound2) {
						//wektor <distance> jest mniejszy, wiec sprawdzamy czy jest dzielnikiem
						//wczesniej zapamietanego wektora dystansu, jesli tak to podmieniamy
						//relacje wybierajace - odrzucamy wczesniejsza relacje
						if (TPDS_VarDividedByConst(lowerBound2,number,it->distanceVec)) {
							*it = SRelationVector(rel,relType,depVector,vectorType,from,to);
							vectorAdded = true;
							break;	//przerwanie for'a
						}
					}
					else {
						//wektor <distance> jest wiekszy, wiec sprawdzamy czy wektor
						//<it->distanceVec> jest dzielnikiem wektora <distance>. Jesli tak to
						//wektor <distance> nie musi byc zapamietany i przerywamy przeszukiwanie,
						//w przeciwnym razie szukamy dalej
						if (TPDS_VarDividedByConst(lowerBound1,number,depVector)) {
							return; /***********!!!!!!!!!!!!!!!!!!!!!*********************/
						}
					}
				} // end if (number>0)
			}// end if (it->distanceVecType)

		}	//end for
/*
		if (it==selectingRel.end()) {
			//jesli doszlismy do konca for'a to znaczy ze relacje <agr1> o wektorze <distance>
			//musi byc wstawiona na koniec <selectingRel>
			selectingRel.push_back(SRelationVector(rel));
			vectorAdded = true;
		}
*/
	}
/**************************************************************************************/


/****Operacje majace na celu wyeliminowanie relacji o zmiennych wektorach zaleznosci***/
/****rownoleglych do stalych wektorow zaleznosci **************************************/
	if (vectorType) {
		//czyli relacja rel o stalym wektorze dystansu <distance>
		for(it=selectingRel.begin();it!=selectingRel.end();it++) {
			if (!it->distanceVecType) {
				//czyli wektor it->distanceVec jest wektorem zmiennym

				number = TPDS_ParallelVectors(it->distanceVec,depVector);

				if (number>0) {
					(it->distanceVec).query_variable_bounds(set_var(number),lowerBound1,upperBound1);
					depVector.query_variable_bounds(set_var(number),lowerBound2,upperBound2);

					//ponizej jesli <id->distanceVec> jest podzielny przez <distanse>
					//to jesli relacja <rel> zostala dodana to usuwamy element wskazywany
					//przez <it>, a jesli nie zostala dodana do zamieniamy elementy
					if (TPDS_VarDividedByConst(lowerBound2,number,it->distanceVec)) {
						if (vectorAdded) {
							//relacja juz zostala dodana, wiec usuwamy zbedna relacje
							it = selectingRel.erase(it);
							it--;
						}
						else {
							//relacja <rel> nie zostala dodana wiec podmieniamy relacje z <it>
							//na <rel>
							*it = SRelationVector(rel,relType,depVector,vectorType,from,to);
							vectorAdded = true;
						}
					}
				}//end if (number>0)

			}
		}	//end for
	}
	else {
		//wektor <distance> nie jest staly
		for(it=selectingRel.begin();it!=selectingRel.end();it++) {
			if (it->distanceVecType) {
				//czyli wektor <it->distanceVec> jest wektorem stalym a <distance> to wektor
				//zmienny
				number = TPDS_ParallelVectors(it->distanceVec,depVector);

				if (number>0) {
					(it->distanceVec).query_variable_bounds(set_var(number),lowerBound1,upperBound1);
					depVector.query_variable_bounds(set_var(number),lowerBound2,upperBound2);

					//ponizej jesli <distance> jest podzielny przez <it->distanseVec>
					//to nie musimy dodawac wektora i konczymy przeszukiwanie RETURN
					if (TPDS_VarDividedByConst(lowerBound1,number,depVector)) {
						return; /***********!!!!!!!!!!!!!!!!!!!!!*********************/
					}

				}	//end if (number>0)

			}
			else {
				//czyli wektory <distance> i <it->distanceVec> sa wektorami zmiennymi
				//jesli relacja <rel> jest identyczna lub zawiera sie w calosci w
				//<it->selectingRel> to odrzucamy <rel> i na odwrot, jesli istnieja wspolne
				//zaleznosci (ten sam poczatek i ten sam koniec) w relacjach to usuwamy je
				//z jednej relacji - nie ma znaczenia z ktorej
//				rel.print_with_subs();
//				(it->selectingRel).print_with_subs();
				temp1 = Intersection(copy(rel),copy(it->selectingRel));
				temp1.simplify(2,2);
//				temp1.print();
				if (temp1.number_of_conjuncts()) {
					//czyli sa jakies wspolne relacje miedzy <rel> a <it->selectingRel>
					temp2 = Difference(copy(rel),copy(temp1));
					temp2.simplify(2,2);
//					temp2.print();
					if (temp2.number_of_conjuncts()) {
						//czyli sa jakies relacje w temp2, wiec <rel> ma wiekszy zakres niz
						//<it->selectingRel> lub relacje nie sa identyczne
						//ponizej sprawdzamy czy <rel> ma wiekszy zakres niz <it->selectingRel>
						temp2 = Difference(copy(it->selectingRel),copy(temp1));
						temp2.simplify(2,2);
//						temp2.print();
						if (temp2.number_of_conjuncts()) {
							//w tym momencie wiadomo ze relacje maja wspolne zaleznosci ale zadna
							//nie zawiera sie w calosci w drugiej, wiec odejmujemy od
							//<it->SelectingRel> wspolne zaleznosci z <rel>,
							//a <rel> dodajemy w calosci
							it->selectingRel = Difference(it->selectingRel,copy(temp1));
							it->selectingRel.simplify(2,2);
//							(it->selectingRel).print();
							//po kilku takich roznicach relacja <it->selectingRel> moze stac sie
							//pusta, w taki przypadku mozemy w miejsce <it> wstawic <rel>
							if ( !(it->selectingRel).number_of_conjuncts() ) {
								*it = SRelationVector(rel,relType,depVector,vectorType,from,to);
								vectorAdded = true;
							}
						}
						else {
							//<it->selectingRel> zawiera sie w <rel>, na miejsce <it> wstawiamy
							//<rel>
							*it = SRelationVector(rel,relType,depVector,vectorType,from,to);
							vectorAdded = true;
						}
					}
					else {
						//relacje <rel> i <it->selectingRel> sa identyczne lub <rel> zawiera sie
						//w calosci w <it-selectingRel>, wiec nie dodajemy zadnej relacji
						//i przerywamy dalsze przeszukiwanie
						return; /***********!!!!!!!!!!!!!!!!!!!!!*********************/
					}
				} //end if(temp1.number_of_conjuncts())
			}

		}//end for()
	}


	/***Dodatkowe sprawdzenie dopisane na szybiekgo dla TPDS***/
	if (!vectorAdded)
	{
		for(it = selectingRel.begin(); it != selectingRel.end(); it++)
		{
			if (it->from == from && it->to == to)
			{
				temp1 = Intersection(copy(it->selectingRel),copy(rel));
				temp1.simplify(2,4);
//				temp1.print_with_subs();

				if (temp1.number_of_conjuncts() != 0)
				{
					temp2 = Difference(copy(rel),copy(temp1));
					temp2.simplify(2,4);
//					temp2.print_with_subs();
					temp3 = Difference(copy(it->selectingRel),copy(temp1));
					temp3.simplify(2,4);
//					temp3.print_with_subs();

					if (temp2.number_of_conjuncts() == 0)
					{
						//nie dodajemy relacji, gdy¿ istniejaca relacja zawiera w ca³oci now¹
						vectorAdded = true;
						break;
					}
					else if (temp3.number_of_conjuncts() == 0)
					{
						//podmieniamy istniej¹c¹ relacjê nowa, gdy¿ nowa zawiera istniej¹c¹
						(it->selectingRel) = copy(rel);
						(it->distanceVec) = copy(depVector);
						(it->distanceVecType) = vectorType;

						vectorAdded = true;
						break;
					}
				}
			}
		}
	}
	/***********************************************************/



	if (!vectorAdded)
		selectingRel.push_back(SRelationVector(rel,relType,depVector,vectorType,from,to));

}



int TPDS_ParallelVectors(Relation &arg1, Relation &arg2)
{
	coef_t upperBound1,lowerBound1;
	coef_t upperBound2,lowerBound2;
	bool diference = false;
	int dimension;
	int number = 0;	//numer zmiennej w zbiorze powodujacej rownoleglosc wektorow

	//sprawdzenie czy wektory sa o jednakowych wymiarach
	if ( arg1.n_set()!=arg2.n_set() )
		return -1;

	dimension = arg1.n_set();
	for(int i=1;i<=dimension;i++) {
		arg1.query_variable_bounds(arg1.set_var(i),lowerBound1,upperBound1);
		//ponizej sprawdzenie czy wektor zaleznosci dla arg1 jest wektorem stalym
//		if (lowerBound1!=upperBound1)
//			return -1;

		//ponizej sprawdzenie czy wektor zaleznosci dla arg2 jest wektorem stalym
		arg2.query_variable_bounds(arg1.set_var(i),lowerBound2,upperBound2);
//		if (lowerBound2!=upperBound2)
//			return -1;


		//ponizej sprawdzenie czy koordynaty wektorow roznia sie tylko w jednym miejscu
		if (lowerBound1 != lowerBound2 || upperBound1 != upperBound2) {
			if (diference == true)
				return -1;
			else {
				diference = true;
				number = i;	//zapamietanie numeru zmiennej powodujacej rownoleglosc
			}
		}

	}

	return number;
}


bool TPDS_VarDividedByConst(int constant, unsigned int varNumber, Relation &arg)
{
	Relation rel;
	Relation temp,temp1,temp2;

	rel = arg;

	F_And *and = rel.and_with_and();
	F_Exists *exists = and->add_exists();
	Variable_ID var = exists->declare("n");

	and = exists->add_and();

	EQ_Handle eq = and->add_EQ();
	eq.update_coef(var,constant);
	eq.update_coef(rel.set_var(varNumber),-1);

	GEQ_Handle geq = and->add_GEQ();
	geq.update_coef(var,1);
	geq.update_const(-1);

//	arg.print();
//	rel.print();
//	rel.simplify(2,2);
//	rel.print();

	temp = Difference(copy(arg),copy(rel));
	temp.simplify(2,2);
//	temp.print();

	if (temp.number_of_conjuncts()) {
		//poniewaz roznica zbiorow nie jest pusta, wiec stala nie jest dzielnikiem dla <arg>
		return false;
	}
	else
		return true;

}

bool TPDS_ConstVector(Relation &vector)
{
	coef_t upperBound,lowerBound;

	for(int i=1;i<=vector.n_set();i++) {
		vector.query_variable_bounds(set_var(i),lowerBound,upperBound);
		if (lowerBound!=upperBound)
			return false;
	}
	return true;
}

int TPDS_RemoveRelationsByType(std::vector<std::string> pRelationTypeToRemove,
							   std::vector<Relation> & pLoopRelations, std::vector<std::string> & pLoopRelationsType,
							   std::vector<Relation> & pLoopRelationsDepVectors, std::vector<bool> & pLoopRelationsVecType,
							   std::vector<int> & pLoopRelationsFrom, std::vector<int> & pLoopRelationsTo)
{
	int _RetValue = 0;

	std::vector<Relation>::iterator _itRel;
	std::vector<bool>::iterator _itRelVecType;
	std::vector<Relation>::iterator _itRelDepVec;
	std::vector<int>::iterator _itRelFrom;
	std::vector<int>::iterator _itRelTo;
	std::vector<std::string>::iterator _itRelType;

START:
	for(_itRel = pLoopRelations.begin(), _itRelVecType = pLoopRelationsVecType.begin(), _itRelDepVec = pLoopRelationsDepVectors.begin(),
		_itRelFrom = pLoopRelationsFrom.begin(), _itRelTo = pLoopRelationsTo.begin(), _itRelType = pLoopRelationsType.begin();
		_itRelType != pLoopRelationsType.end();
		_itRel++, _itRelVecType++, _itRelDepVec++, _itRelFrom++, _itRelTo++, _itRelType++)
	{
		//printf("\n%s",_itRelType->c_str());

		//jesli ponizszy warynek jest spelniony to relacja jest do usuniecia
		if ( std::find(pRelationTypeToRemove.begin(),pRelationTypeToRemove.end(),*_itRelType) != pRelationTypeToRemove.end() )
		{
			//(*_itRel).print_with_subs();
			pLoopRelations.erase(_itRel);
			pLoopRelationsType.erase(_itRelType);
			pLoopRelationsVecType.erase(_itRelVecType);
			pLoopRelationsDepVectors.erase(_itRelDepVec);
			pLoopRelationsFrom.erase(_itRelFrom);
			pLoopRelationsTo.erase(_itRelTo);

			goto START;
		}
	}

	return _RetValue;
}

int TPDS_RelationsWithoutCommonEnd(std::vector<Relation> pInRelations, std::vector<int> pInFrom, std::vector<int> pInTo,
								   std::vector<Relation> & pOutRelations, std::vector<int> & pOutFrom, std::vector<int> & pOutTo)
{
	int _RetValue = 0;

	std::vector<Relation>::iterator _itRel;
	std::vector<int>::iterator _itFrom,_itTo,_itToInner;

	pOutFrom.clear();
	pOutTo.clear();
	pOutRelations.clear();

	for(_itRel = pInRelations.begin(), _itFrom = pInFrom.begin(), _itTo = pInTo.begin(); _itRel != pInRelations.end(); _itRel++, _itFrom++, _itTo++)
	{
		for(_itToInner = pInTo.begin(); _itToInner != pInTo.end(); _itToInner++)
		{
			if (*_itTo == *_itToInner && _itTo != _itToInner)
				break;
		}
		if (_itToInner == pInTo.end())
		{
			pOutRelations.push_back(copy(*_itRel));
			pOutFrom.push_back(*_itFrom);
			pOutTo.push_back(*_itTo);
		}
	}



	return _RetValue;
}

// ----------------------------------------



class CGraphRDG
{
public:
	CGraphRDG(std::vector<Relation> &pDepRel, std::vector<std::string> &pDepReltype,
			  std::vector<int> &pFrom, std::vector<int> &pTo);
	~CGraphRDG();



	//funkcja zwraca wszytskie koñce po³aczone z zadanym poczatkiem
	int GetConnectedEnds(int pFairSource, int pSource, std::vector<int> &pEnds, bool pIsRecurrent);

	void PrintMappingRowToVertex(char *output = NULL);
	void PrintGraph(char *output = NULL);
	void PrintIncidenceMatrix(char *output = NULL);
	void PrintVertices(char *output = NULL);
	void PrintEdges(char *output = NULL);

	void PrintBoostVertices(char *output = NULL);
	void PrintBoostEdges(char *output = NULL);
	void PrintBoostGraph(char *output = NULL);
	void PrintBoostSCC(char *output = NULL);
	void PrintSCCRelations(char *output = NULL);
	void PrintNotSCCRelations(char  *output = NULL);
	void PrintFreeSCCRelations(char  *output = NULL);
	//Zlicza i drukuje ile i jakie zale¿noci znajduj¹ siê w k¹zdym SCC
	void PrintStatistics(char *output = NULL);
	void PrintRawStat(char *out = NULL);
	std::map<int, std::multimap<SFromTo, Relation, SLessFromTo> > GetSCC() { return mSCCRelations; }
	std::multimap<SFromTo, Relation, SLessFromTo> GetFreeSCC() { return mFreeSCCRelations; }
	std::multimap<SFromTo, Relation, SLessFromTo> GetNotSCC() { return mNotSCCRelations; }
	int GetVertexNumber(int pIndex);

	//czy wierzcho³ek o numerze pTo jest osi¹galny z pFrom
	//DO IMPLEMENTACJI:)
	bool IsVertexReachable(int pFrom, int pTo);

protected:
	int CountVertices() { return mVertices.size(); }
	int CountEdges() { return mDependenceRelations.size(); }

	int BuildIncidenceMatrix();
	int BuildBoostGraph();
	int BuildSCCRelations();
	//Tworzy zbior relacji nie nalezacy do Strongly Connected Component
	int BuildNotSCCRelations();
	//Tworzy zbior relacji nie nalezacy do Strongly Connected Component oraz
	//nie majacych bezposredniego polaczenia polaczenie z SCC
	int BuildFreeRelation();
	int CalculateStatistics();

private:
	Graph *mGraph;
	int mNumberSCC; //ilosc komonentow ??
	std::vector<int> mSCC; //strongly connected components
	std::map<int, std::multimap<SFromTo, Relation, SLessFromTo> > mSCCRelations;
	std::multimap<SFromTo, Relation, SLessFromTo> mNotSCCRelations;
	std::multimap<SFromTo, Relation, SLessFromTo> mFreeSCCRelations;
	//
	std::map<int, std::map<std::string,int> > mSCCRelationTypeStatistics;


	std::multimap<SFromTo, Relation, SLessFromTo> mDependenceRelations;

	std::set<int> mVertices;

	std::vector< std::vector<int> > *mIncidenceMatrix;

	std::map<int,int> mMappingRowToVertex;
	std::map<int,int> mMappingVertexToRow;

	char* name;


};


// ---------------------------
// GraphRDG.cpp

CGraphRDG::CGraphRDG(std::vector<Relation> &pDepRel, std::vector<std::string> &pDepRelType,
					 std::vector<int> &pVectorFrom, std::vector<int> &pVectorTo)
{
	SFromTo _FromTo;

	//int i,j;
	std::vector<Relation>::iterator _itRel;
	std::vector<int>::iterator _itFrom,_itTo;
	std::vector<std::string>::iterator _itRelType;

	name = "ABCDEFGHIJKLMNOPRSTUVWXYZ0123456789";

	mDependenceRelations.clear();
	for(_itRel = pDepRel.begin(), _itRelType = pDepRelType.begin(),
		_itFrom = pVectorFrom.begin(), _itTo = pVectorTo.begin();
		_itRel != pDepRel.end(); _itRel++,_itRelType++,_itFrom++,_itTo++)
	{
		mDependenceRelations.insert( std::make_pair( SFromTo(*_itFrom,*_itTo,*_itRelType),copy(*_itRel) ) );
		TPDS_Print(mDependenceRelations,"");
		printf("\n%i %i\n",*_itFrom,*_itTo);
		(*_itRel).print_with_subs();


		mVertices.insert( *_itFrom );
		mVertices.insert( *_itTo );
	}

	BuildIncidenceMatrix();
	BuildBoostGraph();
	BuildSCCRelations();
	BuildNotSCCRelations();
	BuildFreeRelation();
	//SetMappingRowToVertex();

	CalculateStatistics();
}


int CGraphRDG::GetVertexNumber(int pIndex)
{
	int _RetValue = 0;

	std::map<int,int>::iterator _itVertex;

	_itVertex = mMappingRowToVertex.find( pIndex );

	_RetValue = _itVertex != mMappingRowToVertex.end() ? _itVertex->second : -1;

	return _RetValue;
}

int CGraphRDG::BuildBoostGraph()
{
	std::multimap<SFromTo,Relation,SLessFromTo>::iterator _itRel;
	std::map<int,int>::iterator _itFrom,_itTo;
	int _RetValue = 0;

    mGraph = new Graph(mVertices.size());

    for(_itRel = mDependenceRelations.begin(); _itRel != mDependenceRelations.end(); _itRel++)
	{
		_itFrom = mMappingVertexToRow.find((_itRel->first).from);
		_itTo = mMappingVertexToRow.find((_itRel->first).to);

		boost::add_edge(_itFrom->second,_itTo->second, *mGraph);
	}

	mSCC = std::vector<int>(boost::num_vertices(*mGraph));

	mNumberSCC = boost::strong_components(*mGraph,&mSCC[0]);

	return _RetValue;
}

int CGraphRDG::BuildSCCRelations()
{
	int _RetValue = 0;

	//std::vector<int>::size_type i;
	std::map<int, std::multimap<SFromTo, Relation, SLessFromTo> >::iterator _itSCCRel;
	std::multimap<SFromTo, Relation, SLessFromTo>::iterator _itRel;
	std::multimap<SFromTo, Relation, SLessFromTo> _Temp;

	int _From,_To;
	int _VertexFrom,_VertexTo;
	//int _SCC;

	for(_itRel = mDependenceRelations.begin(); _itRel != mDependenceRelations.end(); _itRel++)
	{
		_From = (_itRel->first).from;
		_To = (_itRel->first).to;

		_VertexFrom = mMappingVertexToRow.find(_From)->second;
		_VertexTo = mMappingVertexToRow.find(_To)->second;


		//jeli ponizszy warunek spelniony to oznacza ze relacja znajduje sie w jednym strongly connected component
		if ( mSCC[_VertexFrom] == mSCC[_VertexTo] )
		{
			_itSCCRel = mSCCRelations.find(mSCC[_VertexFrom]);
			//_itSCCRel = mSCCRelations.find(mSCC[_VertexTo]);

			if ( _itSCCRel != mSCCRelations.end() )
			{
				(_itSCCRel->second).insert( *_itRel );
			}
			else
			{
				_Temp.clear();
				_Temp.insert( *_itRel );

				mSCCRelations.insert( std::make_pair(mSCC[_VertexFrom],_Temp) );
			}
		}
	}

	return _RetValue;
}



int CGraphRDG::BuildFreeRelation()
{
	int _RetValue = 0;

	std::map<int, std::multimap<SFromTo, Relation, SLessFromTo> >::iterator _itSCCRel;
	std::multimap<SFromTo, Relation, SLessFromTo>::iterator _itMapRel, _itFreeSCC;

	int _From, _To;

	mFreeSCCRelations = mNotSCCRelations;

	for(_itSCCRel = mSCCRelations.begin(); _itSCCRel != mSCCRelations.end(); _itSCCRel++)
	{
		for(_itMapRel = (_itSCCRel->second).begin(); _itMapRel != (_itSCCRel->second).end(); _itMapRel++)
		{
			_From = (_itMapRel->first).from;
			_To = (_itMapRel->first).to;

S:
			for(_itFreeSCC = mFreeSCCRelations.begin(); _itFreeSCC != mFreeSCCRelations.end(); _itFreeSCC++)
			{
				if ( (_itFreeSCC->first).from == _From || (_itFreeSCC->first).from == _To ||
					 (_itFreeSCC->first).to == _From || (_itFreeSCC->first).to == _To)
				{
					mFreeSCCRelations.erase(_itFreeSCC);
					goto S; // :)
				}
			}


			/****** eliminujemy relacje majace polaczenie z poczatkami relacji nalezacymi do SCC ******
			_itFreeSCC = mFreeSCCRelations.find( SFromTo(_From, 0) );
			if (_itFreeSCC != mFreeSCCRelations.end())
			{
				_From = 10;
			}
			_itFreeSCC = mFreeSCCRelations.find( SFromTo(0, _From) );
			if (_itFreeSCC != mFreeSCCRelations.end())
			{
				_From = 10;
			}
			/******************************************************************************************/

			/****** eliminujemy relacje majace polaczenie z koncami relacji nalezacymi do SCC *********
			_itFreeSCC = mFreeSCCRelations.find( SFromTo(_To, 0) );
			if (_itFreeSCC != mFreeSCCRelations.end())
			{
				_To = 10;
			}
			_itFreeSCC = mFreeSCCRelations.find( SFromTo(0, _To) );
			if (_itFreeSCC != mFreeSCCRelations.end())
			{
				_To = 10;
			}
			/******************************************************************************************/

		}
	}




	return _RetValue;
}


int CGraphRDG::BuildNotSCCRelations()
{
	int _RetValue = 0;

	//int _From,_To;

	std::map<int, std::multimap<SFromTo, Relation, SLessFromTo> >::iterator _itSCCRel;
	std::multimap<SFromTo, Relation, SLessFromTo>::iterator _itMapRel, _itDepRel;

	mNotSCCRelations = mDependenceRelations;

	for(_itSCCRel = mSCCRelations.begin(); _itSCCRel != mSCCRelations.end(); _itSCCRel++)
	{
		for(_itMapRel = (_itSCCRel->second).begin(); _itMapRel != (_itSCCRel->second).end(); _itMapRel++)
		{
			//_From = (_itMapRel->first).from;
			//_To = (_itMapRel->first).to;
			_itDepRel = mNotSCCRelations.find(_itMapRel->first);

			if (_itDepRel != mNotSCCRelations.end())
			{
				mNotSCCRelations.erase(_itDepRel);
			}
			//mSCCRelations.erase();
		}
	}

	return _RetValue;
}




//int CGraphRDG::BuildSequenceRelations()
//{
//	int _RetValue = 0;
//
//	std::map<int,int> _MapUnique;
//	std::map<int,int>::iterator _itMapUnique;
//
//	std::vector<int>::iterator _itSCC;
//	//int _Component;
//
//	for(_itSCC = mSCC.begin(); _itSCC != mSCC.end(); _itSCC++)
//	{
//		_itMapUnique = _MapUnique.find(*_itSCC);
//		if ( _itMapUnique == _MapUnique.end() )
//			_MapUnique.insert( std::make_pair(*_itSCC,1) );
//		else
//			_itMapUnique->second = _itMapUnique->second + 1;
//	}
//
//
//	//usuwamy z mapy wszytskie componenty wystepujace wiecej niz jeden raz
//S:
//	for(_itMapUnique = _MapUnique.begin(); _itMapUnique != _MapUnique.end(); _itMapUnique++)
//	{
//		if (_itMapUnique->second > 1)
//		{
//			_MapUnique.erase(_itMapUnique);
//			goto S; // zabawne co :)
//		}
//	}
//
//	int _Vertex
//	for(_itMapUnique = _MapUnique.begin(); _itMapUnique != _MapUnique.end(); _itMapUnique++)
//	{
//       //_Vertex = mM
//	}
//
//
//
//
//	TPDS_Print(_MapUnique,"Test");
//
////	std::vector<int> mSCCCopy;
////
////	std::copy(mSCC.begin(),mSCC.end(),mSCC.begin());
//
//	//Usuwamy wszytskie strongly connected componnets zawieraj¹ce conajmniej dwa wierzcho³ki
//
//
//
//
//	return _RetValue;
//}



bool CGraphRDG::IsVertexReachable(int pFrom, int pTo)
{
	bool _RetValue = false;

	std::multimap<SFromTo, Relation, SLessFromTo> _DependenceRelations;
	std::multimap<SFromTo, Relation, SLessFromTo>::iterator _itDepRel;
	std::set<int> _VisitedVertex;
	std::set<int>::iterator _itVertex;
	int _From, _To;

	_DependenceRelations = copy(mDependenceRelations);
	_VisitedVertex.insert(pFrom);


START:
	for(_itVertex = _VisitedVertex.begin(); _itVertex != _VisitedVertex.end(); _itVertex++)
	{
		for(_itDepRel = _DependenceRelations.begin(); _itDepRel != _DependenceRelations.end(); _itDepRel++)
		{
			_From = (_itDepRel->first).from;
            if ( *_itVertex == _From )
			{
				_To = (_itDepRel->first).to;
				_VisitedVertex.insert( _To );

				_DependenceRelations.erase(_itDepRel);
				goto START;
			}
		}
	}

	_itVertex = _VisitedVertex.find(pTo);
	if (_itVertex != _VisitedVertex.end() )
	{
		_RetValue = true;
	}

	return _RetValue;
}



int CGraphRDG::BuildIncidenceMatrix()
{
	int _RetValue = 0;
	int i;
	std::set<int>::iterator _itVertex;
	std::multimap<SFromTo,Relation,SLessFromTo>::iterator _itRel;

	mIncidenceMatrix = new std::vector< std::vector<int> > (mVertices.size());
	for(std::vector< std::vector<int> >::iterator _it = mIncidenceMatrix->begin(); _it != mIncidenceMatrix->end(); _it++)
	{
		*_it = std::vector<int>(mVertices.size());
	}

	/**** Tworzymy mapowanie wierszy na wierzcho³ki ****/
	for(_itVertex = mVertices.begin(),i=0; _itVertex != mVertices.end(); _itVertex++,i++)
	{
		mMappingRowToVertex.insert( std::make_pair(i,*_itVertex) );
		mMappingVertexToRow.insert( std::make_pair(*_itVertex,i) );
	}

	int _Row = 0, _Column = 0;
	std::map<int,int>::iterator _itRowNumber,_itColNumber;
	for(_itRel = mDependenceRelations.begin(); _itRel != mDependenceRelations.end(); _itRel++)
	{
		_itRowNumber = mMappingVertexToRow.find( (_itRel->first).from );
		_itColNumber = mMappingVertexToRow.find( (_itRel->first).to );
		if (_itRowNumber != mMappingVertexToRow.end() && _itColNumber != mMappingVertexToRow.end())
		{
			_Row = _itRowNumber->second;
			_Column = _itColNumber->second;

			(*mIncidenceMatrix)[_Row][_Column] = 1;
		}
		else
			printf("ERROR - CGraphRDG::SetMappingRowToVertex()");
	}

	return _RetValue;
}



void CGraphRDG::PrintVertices(char *out)
{
	TPDS_Print(mVertices,"\nVertices in RDG : ",out);
}


void CGraphRDG::PrintNotSCCRelations(char *out)
{
    TPDS_Print(mNotSCCRelations,"Remaining Relations (not included in SCC)",out);
}

void CGraphRDG::PrintFreeSCCRelations(char *out)
{
	TPDS_Print(mFreeSCCRelations,"Relations Not Connected To SCC", out);
}


void CGraphRDG::PrintEdges(char *out)
{
	std::vector< std::vector<int> >::iterator _itRow;
	std::vector<int>::iterator _itEdge;
	std::map<int,int>::iterator _itFrom,_itTo;

	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	int _Row=0,_Column=0;

	fprintf(output, "\nEdges in RDG : ");
	for(_itRow = mIncidenceMatrix->begin(),_Row=0; _itRow != mIncidenceMatrix->end(); _itRow++,_Row++)
	{
		for(_itEdge = _itRow->begin(),_Column=0; _itEdge != _itRow->end(); _itEdge++,_Column++)
		{
			if (*_itEdge == 1)
			{
				_itFrom = mMappingRowToVertex.find(_Row);
				_itTo = mMappingRowToVertex.find(_Column);

				if (_itFrom != mMappingRowToVertex.end() && _itTo != mMappingRowToVertex.end())
				{
					fprintf(output,"%d->%d ",_itFrom->second,_itTo->second);
				}
				else
					fprintf(output,"ERORR, row %d or column %d does not have a vertex representation",_Row,_Column);
			}
		}
	}

    if (out != NULL)
		fclose(output);


}


void CGraphRDG::PrintMappingRowToVertex(char *output)
{
	TPDS_Print(mMappingVertexToRow,"Mapping row (in loop) -> edge (in graph)",output);
}

void CGraphRDG::PrintIncidenceMatrix(char *out)
{
	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	fprintf(output,"TO DO !!");

	if (out != NULL)
		fclose(output);

}

void CGraphRDG::PrintBoostVertices(char *out)
{
	std::filebuf _FileOutput;
	std::streambuf *_wskSTDOutput;

  	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out != NULL)
	{
		_wskSTDOutput = std::cout.rdbuf();

		_FileOutput.open(out, std::ios::app | std::ios::out);
		std::cout.rdbuf(&_FileOutput);
	}

	std::cout << "Vertices in GRAPH" << std::endl;
	boost::print_vertices(*mGraph,name);
	std::cout << std::endl << std::flush;

	if (out != NULL)
	{
		_FileOutput.close();
		std::cout.rdbuf(_wskSTDOutput);
	}
}

void CGraphRDG::PrintBoostEdges(char *out)
{
	std::filebuf _FileOutput;
	std::streambuf *_wskSTDOutput;

  	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out != NULL)
	{
		_wskSTDOutput = std::cout.rdbuf();

		_FileOutput.open(out, std::ios::app | std::ios::out);
		std::cout.rdbuf(&_FileOutput);
	}

	std::cout << "Edges in GRAPH" << std::endl;
	boost::print_edges(*mGraph,name);
	std::cout << std::endl << std::flush;

	if (out != NULL)
	{
		_FileOutput.close();
		std::cout.rdbuf(_wskSTDOutput);
	}
}

void CGraphRDG::PrintBoostGraph(char *out)
{
	std::filebuf _FileOutput;
	std::streambuf *_wskSTDOutput;

  	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out != NULL)
	{
		_wskSTDOutput = std::cout.rdbuf();

		_FileOutput.open(out, std::ios::app | std::ios::out);
		std::cout.rdbuf(&_FileOutput);
	}

	std::cout << "GRAPH" << std::endl;
	boost::print_graph(*mGraph, name);
	std::cout << std::endl << std::flush;

	if (out != NULL)
	{
		_FileOutput.close();
		std::cout.rdbuf(_wskSTDOutput);
	}
}

void CGraphRDG::PrintRawStat(char *out)
{
	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	fprintf(output," %s %d","TotalNumberOfSCC",mNumberSCC);

    if (out != NULL)
		fclose(output);
}


void CGraphRDG::PrintBoostSCC(char *out)
{
	std::filebuf _FileOutput;
	std::streambuf *_wskSTDOutput;

  	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out != NULL)
	{
		_wskSTDOutput = std::cout.rdbuf();

		_FileOutput.open(out, std::ios::app | std::ios::out);
		std::cout.rdbuf(&_FileOutput);
	}

	std::cout << "Total number of components: " << mNumberSCC << std::endl;
	std::vector<int>::size_type i;

	for (i = 0; i != mSCC.size(); ++i)
		std::cout << "Vertex " << name[i] <<" is in component " << mSCC[i] << std::endl;

	if (out != NULL)
	{
		_FileOutput.close();
		std::cout.rdbuf(_wskSTDOutput);
	}
}

void CGraphRDG::PrintSCCRelations(char *out)
{
	TPDS_Print(mSCCRelations,"Strongly connected component as relations","Component nr : ",out);
}


int CGraphRDG::CalculateStatistics()
{
    int _RetValue = 0;

	std::map<int, std::multimap<SFromTo, Relation, SLessFromTo> >::iterator _itSCC;
	std::multimap<SFromTo, Relation, SLessFromTo>::iterator _itInner;
	std::pair< std::map<int, std::map<std::string,int> >::iterator, bool > _pair;
	std::map<std::string,int>::iterator _itRelType;



	mSCCRelationTypeStatistics.clear();
	for(_itSCC = mSCCRelations.begin(); _itSCC != mSCCRelations.end(); _itSCC++)
	{
		_pair = mSCCRelationTypeStatistics.insert( std::make_pair(_itSCC->first,std::map<std::string,int>()) );

        for(_itInner = (_itSCC->second).begin(); _itInner != (_itSCC->second).end(); _itInner++)
		{
			//szukamy czy rodzaj zale¿noci dla danego SCC zosta³ juz zliczony
			_itRelType = ((_pair.first)->second).find( (_itInner->first).relationType );

			//jeli tak to zwiekszamy indeks o 1, jeli nei to dodajemy wpis dla nowego tpu zaleznoci
			if (_itRelType != ((_pair.first)->second).end())
			{
				_itRelType->second ++;
			}
			else
			{
				((_pair.first)->second).insert(std::make_pair((_itInner->first).relationType,1));
			}
		}
	}

	return _RetValue;
}

void CGraphRDG::PrintStatistics(char *out)
{
	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	std::map<int, std::map<std::string,int> >::iterator _itOuter;
	std::map<std::string,int>::iterator _itInner;

	fprintf(output,"\nGraph SCC statistics : ");
	for(_itOuter = mSCCRelationTypeStatistics.begin(); _itOuter != mSCCRelationTypeStatistics.end(); _itOuter++)
	{
		fprintf(output,"\nSCC nr. %i - Dependences :", _itOuter->first);
		for (_itInner = _itOuter->second.begin(); _itInner != _itOuter->second.end(); _itInner++)
		{
			fprintf(output," %s = %i", _itInner->first.c_str(), _itInner->second);
		}
	}
	fprintf(output,"\n");

    if (out != NULL)
		fclose(output);
}





void CGraphRDG::PrintGraph(char *out)
{
	FILE *output;
	//Jesli out==NULL to drukujemy na stdout jesli nie to do pliku o nazwie <out>
	if (out==NULL) output = stdout;
	else output = fopen(out,"a+");

	int _Row=0,_Column=0;
	std::vector< std::vector<int> >::iterator _itRow;
	std::vector<int>::iterator _itColumn;
	std::map<int,int>::iterator _itVertex;

	fprintf(output,"\nIncidenceMatrix\n");
	for(_itRow = mIncidenceMatrix->begin(),_Row=0; _itRow != mIncidenceMatrix->end(); _itRow++,_Row++)
	{
		_itVertex = mMappingRowToVertex.find(_Row);
		if (_itVertex != mMappingRowToVertex.end())
			fprintf(output,"\n%d -> ",_itVertex->second);
		else
			fprintf(output,"ERORR, row %d does not have a vertex representation",_Row);
		for(_itColumn = _itRow->begin(),_Column=0; _itColumn != _itRow->end(); _itColumn++,_Column++)
		{
			if (*_itColumn == 1)
			{
				_itVertex = mMappingRowToVertex.find(_Column);
				if (_itVertex != mMappingRowToVertex.end())
					fprintf(output,"%d,",_itVertex->second);
				else
					fprintf(output,"ERORR, column %d does not have a vertex representation",_Column);
			}
		}
	}

	fprintf(output,"\n");

    if (out != NULL)
		fclose(output);

}




int CGraphRDG::GetConnectedEnds(int pFairSource, int pSource, std::vector<int> &pEnds, bool pIsRecurrent)
{
	int _RetValue = 0;

	int i;
	std::map<int,int>::iterator _itVertex;

	_itVertex = mMappingVertexToRow.find(pSource);
	if (_itVertex != mMappingVertexToRow.end())
	{
		int _Row = _itVertex->second;
		for(i=0;i<CountEdges();i++)
		{

		}
	}
	else
		printf("ERROR - CGraphRDG::GetConnectedEnds()");

	return _RetValue;
}



CGraphRDG::~CGraphRDG()
{
	std::vector< std::vector<int> >::iterator _itExtern;
	std::vector<int>::iterator _itInner;

	for(_itExtern = mIncidenceMatrix->begin(); _itExtern != mIncidenceMatrix->end(); _itExtern++)
	{
		delete &(*_itExtern);
	}

}
