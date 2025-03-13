typedef boost::adjacency_matrix<boost::directedS> Graph;

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
	//Zlicza i drukuje ile i jakie zale¿noœci znajduj¹ siê w k¹zdym SCC
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
		//printf("\n%i %i\n",*_itFrom,*_itTo);
		//(*_itRel).print_with_subs();


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


		//jeœli ponizszy warunek spelniony to oznacza ze relacja znajduje sie w jednym strongly connected component
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


			/* ***** eliminujemy relacje majace polaczenie z poczatkami relacji nalezacymi do SCC ******
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


			***** eliminujemy relacje majace polaczenie z koncami relacji nalezacymi do SCC *********
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
			******************************************************************************************/

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

	//fprintf(output, "\nEdges in RDG : ");
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
					//fprintf(output,"%d->%d ",_itFrom->second,_itTo->second);
				}
				else
				{}	//fprintf(output,"ERORR, row %d or column %d does not have a vertex representation",_Row,_Column);
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

	//fprintf(output,"TO DO !!");

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

	//fprintf(output," %s %d","TotalNumberOfSCC",mNumberSCC);

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
			//szukamy czy rodzaj zale¿noœci dla danego SCC zosta³ juz zliczony
			_itRelType = ((_pair.first)->second).find( (_itInner->first).relationType );

			//jeœli tak to zwiekszamy indeks o 1, jeœli nei to dodajemy wpis dla nowego tpu zaleznoœci
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

	//fprintf(output,"\nGraph SCC statistics : ");
	for(_itOuter = mSCCRelationTypeStatistics.begin(); _itOuter != mSCCRelationTypeStatistics.end(); _itOuter++)
	{
		//fprintf(output,"\nSCC nr. %i - Dependences :", _itOuter->first);
		for (_itInner = _itOuter->second.begin(); _itInner != _itOuter->second.end(); _itInner++)
		{
			//fprintf(output," %s = %i", _itInner->first.c_str(), _itInner->second);
		}
	}
	//fprintf(output,"\n");

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

	//fprintf(output,"\nIncidenceMatrix\n");
	for(_itRow = mIncidenceMatrix->begin(),_Row=0; _itRow != mIncidenceMatrix->end(); _itRow++,_Row++)
	{
		_itVertex = mMappingRowToVertex.find(_Row);
		if (_itVertex != mMappingRowToVertex.end())
			{}//fprintf(output,"\n%d -> ",_itVertex->second);
		else
			{}//fprintf(output,"ERORR, row %d does not have a vertex representation",_Row);
		for(_itColumn = _itRow->begin(),_Column=0; _itColumn != _itRow->end(); _itColumn++,_Column++)
		{
			if (*_itColumn == 1)
			{
				_itVertex = mMappingRowToVertex.find(_Column);
				if (_itVertex != mMappingRowToVertex.end())
					{}//fprintf(output,"%d,",_itVertex->second);
				else
					{}//fprintf(output,"ERORR, column %d does not have a vertex representation",_Column);
			}
		}
	}

	//fprintf(output,"\n");

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
	//	int _Row = _itVertex->second;
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
