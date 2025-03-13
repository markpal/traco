/* 
 * File:   topology.h
 * Author: marek
 *
 * Created on 17 styczeń 2010, 21:14
 */

#ifndef _TOPOLOGY_H
#define	_TOPOLOGY_H

//jest jakis blad
// wyszukiwanie wspolnych poczatkow i koncow w relacji
Relation ExtractCommonSources(Relation R);

// wyszukiwanie wspolnych poczatkow i koncow w relacji
Relation ExtractCommonDestinations(Relation R);

// algorytm sprawdzajacy czy zbior relacji jest grafem, drzewem czy lancuchem
// 0 - lancuch
// 1 - drzewo
// 2 - graf
int GetTopology(ComplexRelation BaseRel)
{
	int i,j;
	int n = BaseRel.R.length();

	Relation CI, TMP;
        Relation R = globalUnion(BaseRel.R);

        

	if(n < 2)
		return 0;



	CI = Intersection(Range(copy(BaseRel.R[1])), Range(copy(BaseRel.R[2])));
        //exit(0);
/*	for(j=1; j<=n; j++)
		for(i=j+1; i<=n; i++)
		{
		printf("%i %i\n", i, j);
                    TMP = Intersection(Range(copy(BaseRel.R[i])), Range(copy(BaseRel.R[j])));
			CI = Union(copy(CI), copy(TMP));
			if(CI.number_of_conjuncts() > 0) //to jest graf
				return 2;
		}

*/
         

  //      CI = ExtractCommonDestinations(R);

	if(CI.number_of_conjuncts() > 0) //to jest graf
		return 2;



	CI = Intersection(Domain(copy(BaseRel.R[1])), Domain(copy(BaseRel.R[2])));

	for(j=1; j<=n; j++)
		for(i=j+1; i<=n; i++)
		{
			TMP = Intersection(Domain(copy(BaseRel.R[i])), Domain(copy(BaseRel.R[j])));
			CI = Union(copy(CI), TMP);
		}

     //   CI = ExtractCommonSources(R);

	if(CI.number_of_conjuncts() > 0) //to jest drzewo
		return 1;


	//lancuch
	return 0;


};


char * TopologyName(int topology)
{
	switch(topology)
	{
	case(0) : return "chain"; break;
	case(1) : return "tree"; break;
	case(2) : return "graph"; break;
	default: return "";
	}
}




// wyszukiwanie wspolnych poczatkow i koncow w relacji
Relation ExtractCommonSources(Relation R)
{
	Relation D = Domain(copy(R));
	int n = D.n_set();

	Relation CDS = Difference(copy(D), copy(D));
	CDS = Complement(copy(CDS));

	CDS.simplify();

	F_And *cds_and = CDS.and_with_and();
	F_Exists *fex = cds_and->add_exists();
	F_And *fex_and = fex->add_and();

	String nazwa;
	Variable_ID exprim[10];	// to tablica zmiennych e''
	Variable_ID exbis[10];	// to tablica zmiennych e''


	int i;

	// pobierz nazwy do exists e''
	for(i=1; i<=n; i++)
	{
		nazwa =  CDS.set_var(i)->name();
		nazwa += "'";
		exprim[i-1] = fex->declare(nazwa);
		nazwa += "'";
		exbis[i-1] = fex->declare(nazwa);
	}

	R_Add_Exist2(R, CDS, fex_and, exprim, 2, 1);
	R_Add_Exist2(R, CDS, fex_and, exbis, 2, 1);

	S_Add_Exist2(D, CDS, fex_and, exprim);
	S_Add_Exist2(D, CDS, fex_and, exbis);

	Diff_Add_Exist2(CDS, fex_and, exprim, exbis, n);

	CDS.simplify();

	return CDS;

}

// wyszukiwanie wspolnych poczatkow i koncow w relacji
Relation ExtractCommonDestinations(Relation R)
{
	Relation D = Range(copy(R));
	int n = D.n_set();

	Relation CDS = Difference(copy(D), copy(D));
	CDS = Complement(copy(CDS));

	CDS.simplify();

	F_And *cds_and = CDS.and_with_and();
	F_Exists *fex = cds_and->add_exists();
	F_And *fex_and = fex->add_and();

	String nazwa;
	Variable_ID exprim[10];	// to tablica zmiennych e''
	Variable_ID exbis[10];	// to tablica zmiennych e''


	int i;

	// pobierz nazwy do exists e''
	for(i=1; i<=n; i++)
	{
		nazwa =  CDS.set_var(i)->name();
		nazwa += "'";
		exprim[i-1] = fex->declare(nazwa);
		nazwa += "'";
		exbis[i-1] = fex->declare(nazwa);
	}

	R_Add_Exist2(R, CDS, fex_and, exprim, 2, 0);
	R_Add_Exist2(R, CDS, fex_and, exbis, 2, 0);

	S_Add_Exist2(D, CDS, fex_and, exprim);
	S_Add_Exist2(D, CDS, fex_and, exbis);

	Diff_Add_Exist2(CDS, fex_and, exprim, exbis, n);

	CDS.simplify();

	return CDS;

}


#endif	/* _TOPOLOGY_H */

