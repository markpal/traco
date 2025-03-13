#include <math.h>
#include <string.h>
#include <sys/time.h>


struct tuple_world
{
	int **wsk;
	int liczba_wektorow;
	int constr_count;
};


struct noimp_vecs   // vi = nvk
{
	int rel_pos;
	int pos;
	noimp_vecs *next;
};


struct ComplexRelation
{
	Tuple<Relation> R;
	Tuple<Relation> DepVect;
	Tuple<bool> VecType;
	Tuple<int> SCC;
	Tuple<int> From;
	Tuple<int> To;
	Tuple<char *> Type;
	Tuple<std::string> Line;
	Tuple<char *> Var;
};

struct Rel_Struct
{
	Tuple<Relation> R;
	int I[100];
	Tuple<Relation> R_UCS_list;
	Tuple<String> Loops;
	Tuple<Relation> L_I[100];
	Tuple<Relation> Rprim[100];

};


double gettime()
{
   struct timeval tv ;
   gettimeofday ( & tv, NULL ) ;
   return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0 ;
}

Relation TransitiveClosure3(NOT_CONST Relation &r, NOT_CONST Relation &region);
Relation AdvancedIterateClosure(NOT_CONST Relation &r);

// ================================================================================
// R = R1 u R2 u R3 ...
// Oblicza unię relacji
Relation globalUnion(Tuple<Relation> R)
{
	Relation Ru;

	int i, n;

	n = R.length();

	Ru = R[1];
	for(i=2; i<=n; i++)
		Ru = Union(copy(Ru), copy(R[i]));

	Ru.simplify();

	return Ru;

}

// ================================================================
// ==============
// Print Relations[]
// ==============

int printRelations(Tuple<Relation> Relations, int upr=0)
{
	int i;

    if(!_SILENT)
	printf("\n_Number of relations %i.\n\n", 	Relations.length());

	for(i=1; i <= Relations.length(); i++)
	{
		if(!_SILENT)
            printf("%i.\t", i);

		if(_SILENT)
		{
		    FILE *f = fopen("/dev/null", "w");
		    Relations[i].print(f);
		    fclose(f);
		}

        else
        {
            if(upr == 1)
            {
                Relations[i].print_with_subs();

            }
            else
                Relations[i].print();
        }

		if(!_SILENT)
            printf("\n\n");
	}


};

String R2String(Relation R, int upr=0);
// =================
// Check if vectors are parallel V1 = nV2
// 1 - Yes, 0 - No
// =================

// ================================================================
void PrintString(String s)
{
   int i;
   for(i=0; i<s.length(); i++)
printf("%c", s[i]);

}

char* str(String s)
{
   int i;
   char *S = new char[s.length()+1];
   for(i=0; i<s.length()+1; i++)
   {
      S[i] = s[i];
     // printf("%c_" , S[i]);
   }

   return S;

}

std::string Str2string(String s)
{
   int i;
   char *S = new char[s.length()+1];
   for(i=0; i<s.length()+1; i++)
   {
      S[i] = s[i];
     // printf("%c_" , S[i]);
   }

    return std::string(S);

}

char* _str(String s)
{
   int i;
   char *S = new char[s.length()+2];
   S[0] = '\n';
   for(i=0; i<s.length()+1; i++)
   {
      S[i+1] = s[i];
     // printf("%c_" , S[i]);
   }

   return S;

}



void print_tuples(tuple_world tw)
{
	int i,j;

	for(i=0;i<tw.constr_count; i++)
	{
		for(j=0;j<tw.liczba_wektorow; j++)
			printf("%i\t", tw.wsk[j][i]);
		printf("\n");
	}


}


int is_vect_parallel(int *tab1, int *tab2, int vect_size)  //1 tak, 0 nie  -- tab1=n*tab2
{

	int vect_parallel = 1;
	int ktory = -1;
	int dzielnik;
	int m,d,i;
	int zerowy=0;



	// Sprawdzenie zerowych
	for(i=0; i<vect_size; i++)
		if(tab1[i]!=0)
			zerowy = 1;
	if (zerowy==0)
		return 1;  //bo wektor [0..0]

	zerowy=0;
	for(i=0; i<vect_size; i++)
		if(tab2[i]!=0)
			zerowy = 1;

	if (zerowy==0)
		return 1;  //bo wektor [0..0]



	for(i=0; i<vect_size; i++)
	{

		if ((*tab1==0 && *tab2!=0) || (*tab1!=0 && *tab2==0)) //nie sa rownolegle
		{
			vect_parallel = 0;
			break;
		}
		if (*tab1 == 0 && *tab2 == 0)
		{
			tab1++;
			tab2++;
			continue;
		}

		d = *tab1;
		m = *tab2;


		if (ktory == -1)
		{

			// ustal dzielnik
			if (d%m==0)
			{
				dzielnik = d / m;
				ktory = 0;
			}
			else
			{
				//liczby sa niepodzielne
				vect_parallel = 0;
				break;
			}
		}
		else if(dzielnik != (d/m) || d%m!=0)
			{
				//dzielnik jest inny lub sa niepodzielne
				vect_parallel = 0;
				break;
			}


		tab1++;
		tab2++;
	}  //jak przejdzie cala petle to vect_parallel == 1

return vect_parallel;
}


// ================================================================
// ================================================================
// ================================================================
// ================================================================

tuple_world SetToTupleTab(Relation Wektor, int dis_pl)
{

	int i = 0, j, k, l;
	int pos = 0;
	int val;
	int liczba_wekt = 0;
	int indeks_komb;
	int range;

	tuple_world out;

	struct constraint
	{
		int kind;   //0 - eq, 1 - geq
		int eq;
		int geq1;
		int geq2;
		int geq_visited;  //by wiedzial czy updatowac geq1 czy geq2
		int diff;
	};

	int constr_count=0, flag=0;

	for(DNF_Iterator di0(Wektor.query_DNF()); di0; di0++)
	{
		for(EQ_Iterator ei = (*di0)->EQs(); ei; ei++)
			constr_count++;
		for(GEQ_Iterator gi = (*di0)->GEQs(); gi; gi++)
			if (!flag)
			{
			constr_count++;
			flag = 1;
			}
			else
				flag = 0;
	}

	//constr_count = Wektor.nuy1` .number_of_conjuncts();

	constraint *tab_ogr;
	tab_ogr = new constraint[constr_count];   //count from 0

	for(i=0; i<constr_count; i++)
		tab_ogr[i].geq_visited = 0;


    for(DNF_Iterator di(Wektor.query_DNF()); di; di++)
        {

        for(EQ_Iterator ei = (*di)->EQs(); ei; ei++)
		{

			val = (*ei).get_const();

            for(Constr_Vars_Iter cvi(*ei); cvi; cvi++)
                pos = (*cvi).var->get_position();


			tab_ogr[pos-1].kind = 0;
			tab_ogr[pos-1].eq = val;



            }
        for(GEQ_Iterator gi = (*di)->GEQs(); gi; gi++)
            {

			val = (*gi).get_const();

            for(Constr_Vars_Iter cvi(*gi); cvi; cvi++)
				pos = (*cvi).var->get_position();

			if (tab_ogr[pos-1].geq_visited)
			{
				tab_ogr[pos-1].geq2 = val;
				tab_ogr[pos-1].diff = tab_ogr[pos-1].geq2 + tab_ogr[pos-1].geq1;
			}
			else
			{
				tab_ogr[pos-1].kind = 1;
				tab_ogr[pos-1].geq_visited = true;
				tab_ogr[pos-1].geq1 = val;

			}


            }

		//i++;
		}

	for(i=0; i<constr_count; i++)
		if (dis_pl)
			printf("Struktua %d o rodzaju %d ma wartosc eq %d geq %d geq %d\n", i, tab_ogr[i].kind, tab_ogr[i].eq, tab_ogr[i].geq1, tab_ogr[i].geq2 );


	// Szerokosc wektora dyktuje liczba constr_count bo dla kazdej zmiee\nnej jest jedno ograniczenie

	// Liczba wektorow wynosi suma(geq2i + geq1i) -> bo geq1 jest ujemny a eq nic nie wnosi

	for(i=0; i<constr_count; i++)
		if(tab_ogr[i].kind==1)   //kind = 1 geq
			liczba_wekt += (tab_ogr[i].geq1 + tab_ogr[i].geq2 + 1)/tab_ogr[i].diff;

	if(liczba_wekt==0)  //same eq
		liczba_wekt=1;

	if(dis_pl)
		printf("Liczba kombinacji : %d \n", liczba_wekt);

	//Tablica liczba_wekt x constr_count

	// Stworzenie tablicy-0 i spadamy z tej funkcji ;)

	int **wektory;

	wektory =  (int **) new int*[liczba_wekt];

	for(i=0; i<liczba_wekt; i++)
	{
		wektory[i] = new int[constr_count];
	}


	indeks_komb = 1;

	//wypelnia tablice np
	// 121212
	// 123123

	float g;

	for(i=0; i<constr_count; i++)
	{
		if(tab_ogr[i].kind==0) //eq
			for(j=0; j<liczba_wekt; j++)
				wektory[j][i]=tab_ogr[i].eq;

		else
		{

			range = tab_ogr[i].geq1 + tab_ogr[i].geq2 + 1;
			g = (float)liczba_wekt/((float)range*(float)indeks_komb);

			for(j=0; j<(int)g; j++)
				for(l=0; l<range; l++)
					for(k=0; k<indeks_komb; k++)
						wektory[j*range*indeks_komb+l*indeks_komb+k][i]=(tab_ogr[i].geq2*(-1)) + l*tab_ogr[i].diff;
			indeks_komb *=range;

		}


	}

	delete tab_ogr;

	out.constr_count=constr_count;
	out.liczba_wektorow=liczba_wekt;
	out.wsk=wektory;

	i=j=0;

	if(dis_pl)
	for(i=0; i<out.constr_count; i++)
	{
		for(j=0; j<out.liczba_wektorow; j++)
			printf("%i\t", out.wsk[j][i]);
		printf("\n");
	}

	return out;
}
// ================================================================
// ================================================================





// ================================================================
// ================================================================
// Wektor (wskaznik na tablice) -> Relacja

Relation VectToRelation(int *wsk, int dl)  // vector must be uniform
{
	int i;
	Relation R(dl, dl);
	Variable_ID *in, *out;

	in = new Variable_ID[dl];
	out = new Variable_ID[dl];

	for(i=0; i<dl; i++)
	{
		in[i] = R.input_var(i+1);   // bo w R(... liczy sie od 1
		out[i] = R.output_var(i+1);

	}


	F_And *R_root = R.add_and();

	for(i=0; i<dl; i++)
	{
		EQ_Handle ogr = R_root->add_EQ();
		ogr.update_coef(in[i], 1);      // j' = j+1
		ogr.update_coef(out[i], -1);
		ogr.update_const(wsk[i]);
		if (i<dl-2)
			R_root = R_root->add_and();

	}


	R.simplify();
	R.simplify();
	//R.print();

	return R;
}

// ================================================================
// ================================================================
// Typ relacji
// UNSTABLE

int VectType(Relation R)  // 1 zmienny 0 staly
{
	int constr_count = 0;

	for(DNF_Iterator di0(R.query_DNF()); di0; di0++)
		for(GEQ_Iterator gi = (*di0)->GEQs(); gi; gi++)
			constr_count++;

	if (constr_count == 0 /*|| di0 == 1    ale wczesniej simplify*/)
		return 0;  //staly
	else
		return 1;	//zmienny

}


// Inna realizacja Sample Solution	 i odjac od relacji, pusta oznaza stala
// ================================================================
// ================================================================


// ================================================================
// ================================================================

// ================================================================
// ================================================================

// ================================================================
// ================================================================


// Funkcje do algorytmu 4


Relation DoubleDim(Relation in_set)    // ITD = {IT, IT}   works only with SET
{
	int set_var_count, i;

	Variable_ID j,jprim;

	set_var_count = in_set.n_set();
	Relation out_set(2*set_var_count);
	out_set = Extend_Set(in_set, set_var_count);
	//out_set.print();

	F_And *extra_constr;     // i=i' , j=j'

	for(i=0; i<set_var_count; i++)   //dla kazdej zmiennej
	{

		j = out_set.set_var(i+1);
		jprim = out_set.set_var(set_var_count+i+1);

		extra_constr = out_set.and_with_and();


		EQ_Handle econstr = extra_constr->add_EQ();
		econstr.update_coef(j, 1);
		econstr.update_coef(jprim, -1);
	}

	//out_set.simplify(2, 4);
	return out_set;

}


//input must be a set  .. dodaje tyle co jest juz zmiennych
// przepisuje pierwsze zmienne do ostatnich i dodaje tyle samo przed z ograniczeniem TRUE bo jest bardziej
// przydatne do Cross Product


Relation Extend_Set_OnBegin(Relation in_set)

{
	int i;
	Variable_ID j,jprim;
	int set_var_count = in_set.n_set();
	in_set = Extend_Set(in_set, set_var_count);
	Relation out_set(2*set_var_count);
	Relation R(2*set_var_count,2*set_var_count);
	out_set = out_set.True(2*set_var_count);
	R = Cross_Product(in_set, out_set);
	R.simplify();
	//R.print();
	F_And *extra_constr;

	//zmienmy kolejnosc


	for(i=0; i<set_var_count; i++)   //dla kazdej zmiennej
	{

		j = R.input_var(i+1);
		jprim = R.output_var(set_var_count+i+1);

		extra_constr = R.and_with_and();


		EQ_Handle econstr = extra_constr->add_EQ();
		econstr.update_coef(j, 1);
		econstr.update_coef(jprim, -1);
	}

	//R.print();
	out_set = Range(copy(R));
	out_set.simplify(2, 4);

	return out_set;

}

/*
Relation RD_make_relation(Relation IT, Relation R)
{
	IT = Extend_Set(IT, IT.n_set());
	//IT.print();
	Relation RTemp1 = Cross_Product(copy(IT), copy(IT));
//	RTemp1 = RTemp1.True(IT.n_set(), IT.n_set());
	Relation S1, S2;
	S1 = Extend_Set_OnBegin(Domain(copy(R)));
	S2 = Extend_Set_OnBegin(Range(copy(R)));
	Relation RTemp2 = Cross_Product(copy(S1), copy(S2));

	Relation RD = Intersection(RTemp1, RTemp2);

	return RD;
*/
//}
/*
liczba_par = 1;
	for(i = 3; i<=inputRelations.length(); i++)
		liczba_par += i-1;
	*/


Relation MirrorSet(Relation InputSet)   // T = [i, j]   ->   T = [j, i]
{
	int dim = InputSet.n_set();

	int i;
	Variable_ID j,jprim;

	Relation R(dim, dim), OutSet(dim);

	F_And *root = R.add_and();

	for(i=0; i<dim; i++)   //dla kazdej zmiennej
	{

		j = R.input_var(i+1);
		jprim = R.output_var(((i+int(dim/2))%dim)+1);

		EQ_Handle econstr = root->add_EQ();
		econstr.update_coef(j, 1);
		econstr.update_coef(jprim, -1);

		if (i<dim-1)
			root = root->add_and();
	}

	OutSet = Range(Restrict_Domain(copy(R), copy(InputSet)));
	OutSet.simplify(2, 4);

	return OutSet;

}


Relation RD_make_relation(Relation IT, Relation R)
{
	int dim = IT.n_set();
	int i;
	Variable_ID j,jprim;

	R = Extend_Domain(copy(R), dim);
	R = Extend_Range(copy(R), dim);


	IT = Extend_Set_OnBegin(IT);

	Relation R_tozs(dim*2 , dim*2), Rtemp(dim*2, dim*2), OUT(2*dim, 2*dim);

	F_And *root = R_tozs.add_and();

	for(i=0; i<dim*2; i++)   //dla kazdej zmiennej
	{

		j = R_tozs.input_var(i+1);
		jprim = R_tozs.output_var(i+1);

		EQ_Handle econstr = root->add_EQ();
		econstr.update_coef(j, 1);
		econstr.update_coef(jprim, -1);

		if (i<2*dim-1)
			root = root->add_and();
	}

	Rtemp = Restrict_Domain(copy(R_tozs), copy(IT));
	Rtemp = Cross_Product(copy(IT), copy(IT));


	F_And *root3 = Rtemp.and_with_and();

	for(i=dim; i<dim*2; i++)   //dla kazdej zmiennej
	{

		j = Rtemp.input_var(i+1);
		jprim = Rtemp.output_var(i+1);

		EQ_Handle econstr = root3->add_EQ();
		econstr.update_coef(j, 1);
		econstr.update_coef(jprim, -1);

	//	if (i<2*dim-1)
	//		F_And *root3 = Rtemp.and_with_and();
	}



	//Rtemp.print();
	//R.print();

	OUT = Intersection(copy(Rtemp), copy(R));


	F_And *root2 = OUT.and_with_and();

	for(i=dim; i<dim*2; i++)   //dla kazdej zmiennej
	{

		j = OUT.input_var(i+1);
		jprim = OUT.output_var(i+1);

		EQ_Handle econstr = root2->add_EQ();
		econstr.update_coef(j, 1);
		econstr.update_coef(jprim, -1);

	//	if (i<2*dim-1)
	//		F_And *root2 = OUT.and_with_and();
	}


	root2 = NULL;
	root3 = NULL;

	OUT.simplify(2, 4);
	return OUT;


}


// ===================================

// Generowanie zbioru iteracji DT

// 1. Usun z S pierwsza polowe zmiennych
// 2. Stworz zbior Fill wszystkich iteracji
// 3. DTSET = Fill - S

Relation GenerateDTSet(Relation S, Relation LD)
{
	int i, dim = S.n_set();
	Relation DTSet, R(dim, (int)(dim/2));

	Variable_ID var1, var2;

	F_And *root = R.add_and();

	EQ_Handle econstr;
	GEQ_Handle econstr1;

	// Zamiana S dwuwymiarowego do jednowymaiarowego = obciecie pierwszych zmiennych
	for(i=(int)(dim/2)+1; i<=dim; i++)   //dla kazdej zmiennej
	{

		var1 = R.input_var(i);
		var2 = R.output_var(i-(int)(dim/2));

		econstr = root->add_EQ();
		econstr.update_coef(var1, 1);
		econstr.update_coef(var2, -1);

		if (i<dim-1)
			root = root->add_and();
	}

	DTSet = Range(Restrict_Domain(copy(R), copy(S)));
	DTSet.simplify(2, 4);

	LD.print();
	printf("LD\n\n");
	DTSet.print();

	DTSet = Difference(copy(LD), copy(DTSet));
	DTSet.simplify(2, 4);

	return DTSet;

}


// =====================================================================
// Funkcje do algorytmu 4 w wersji a z transitive closure

// Funkcja RelationToSet
// Input: Relation R
// Output: Set S
// S = {[In(R), Out(R)]:constraints(R)}
// Uwagi: dim(S) = 2*dim(In(R)),   dim(In(R))=dim(Out(R))


Relation RelationToSet(Relation R)
{
	Relation S;
	int dim, i;

	Variable_ID var1, var2;
	dim = R.n_inp();

	R = Extend_Domain(copy(R), dim);
	F_And *root = R.and_with_and();

	root = root->add_and();

	for(i=1; i<=dim; i++)
	{
		var1 = R.input_var(i+dim);
		var2 = R.output_var(i);

		EQ_Handle econstr = root->add_EQ();
		econstr.update_coef(var1, 1);
		econstr.update_coef(var2, -1);

		root = root->add_and();
	}

	S = Domain(R);
	S.simplify(2,4);

	return S;
}


// Funkcja ExtendSetByTrue
// Input: S1
// Output: S2
// S2 = S1(i,j,In1,In2):constraints(i,j)&&TRUE(In1, In2)
// Uwagi:
// TRUE by In = In
// dim(S2) = 2*dim(S1)

Relation ExtendSetByTrue(Relation S1)
{
	Relation S2;
	int dim, i;
	EQ_Handle econstr;
	Variable_ID var1, var2;

	dim = S1.n_set();

	S2 = Extend_Set(copy(S1), dim);

	F_And *root = S2.and_with_and();

	for(i=1; i<=dim; i++)
	{
		var1 = S2.set_var(i+dim);
		var2 = S2.set_var(i+dim);

		econstr = root->add_EQ();
		econstr.update_coef(var1, 1);
		econstr.update_coef(var2, -1);

		root = S2.and_with_and();
	}

	S2.simplify(2,4);
	return S2;
}

// Funkcja IdentityRelation
// Input: n
// Output: I
// I = {[i,j]->[i',j']:i=i'&&j=j'}
// Uwagi: dim(I) = n
// dim(I) = dim(In(I)) = dim(Out(I))

Relation IdentityRelation(int n)
{
	Relation I(n,n);

	int i;

	Variable_ID var1, var2;
	F_And *root = I.add_and();

	for(i=1; i<=n; i++)
	{
		var1 = I.input_var(i);
		var2 = I.output_var(i);

		EQ_Handle econstr = root->add_EQ();
		econstr.update_coef(var1, 1);
		econstr.update_coef(var2, -1);

		root = root->add_and();
	}

	I.simplify(2,4);

	return I;
}


// Funkcja RollRelation
// Input: n
// Output: I
// I = {[k,i,j]->[i',j',k']:i=i'&&j=j'&k=k'}
// Uwagi: dim(I) = n
// dim(I) = dim(In(I)) = dim(Out(I))

Relation RollRelation(int n)
{
	Relation I(n,n);

	int i;

	Variable_ID var1, var2;
	F_And *root = I.add_and();

	for(i=1; i<=n; i++)
	{
		var1 = I.input_var((i%n)+1);
		var2 = I.output_var(i);

		EQ_Handle econstr = root->add_EQ();
		econstr.update_coef(var1, 1);
		econstr.update_coef(var2, -1);

		root = root->add_and();
	}

	I.simplify(2,4);

	return I;
}


// =======================================================

// Funkcja poprawiajaca kod
// Wykorzystanie: algorytm 4 po generowaniu S
// Dziala lepiej niz simplify
// Wada: jest wolniejsza niz simplify
// W zaleznosci od petli

Relation MaxSimplify(Relation S)
{

	Relation DD1, RZR;
	RZR = Relation::True(S.n_set());
	DD1= Difference(copy(RZR), copy(S));
	DD1.simplify(1,1);
	S = Difference(RZR, DD1);
	S.simplify(1,1);

	return S;
}

// =========================================================
// Funkcje do TRANSITIVE CLOSURE


//
// ----------
// Usuwanie koniunkcji za wyjatkiem k-tej
// Przyklad: R = 1 u 2 u 3   R = 2
// parametry: Relacja R, int k - numer koniunkcji ktora ma zostac
// przyklad wywolania
// R = ConjReduction(R, 3);

// Uwagi: dodac do klasy DNF w dziale public funkcje
//
//   void rmm_conjunct(Conjunct *c)
//   {
//		rm_conjunct(c);
//   }

Relation ConjReduction(Relation Rp, int k)
{
	int i;
	Conjunct *c;

	DNF *d = Rp.query_DNF();

	// Usuwanie zaleznosci z przodu
	for (i=1; i<k; i++)
		d->rm_first_conjunct();

	// Usuwanie zaleznosci z tylu
	while(Rp.number_of_conjuncts() > 1)
	{
		i=1;
		for (DNF_Iterator di(Rp.query_DNF()); di; di++)
		{
			if (i>1)
			{
				c = (*di);
				d->rmm_conjunct(c);  //specjalna funkcja dodana do DNF klasy
				break;
			}
		i++;
		}
	}

	return Rp;
};


Relation RealCopy(Relation R)
{
	Relation R2 = Complement(copy(R));
	R2 = Complement(copy(R2));
	R2.simplify();
	return R2;
}

// Funkcja zwracaja zbior relacji z unii
Tuple <Relation> Divide_Relation(Relation R)
{
	int i, n;
	n = R.number_of_conjuncts();
	Relation Tmp, Tmp2;
	Tuple <Relation> Rels;

	for(i=1; i<=n; i++)
	{
		Tmp = RealCopy(R);
		Tmp2 = ConjReduction(Tmp, i);
		Rels.append(Tmp2);

	}

	return Rels;
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------


Relation TransitiveReduction(Relation R)
{
	Relation Rc, Rt;

	Rt = TransitiveClosure(copy(R));

	Rc = Composition(copy(Rt), copy(R));

	R = Difference(copy(R), copy(Rc));

	return R;

}


// ---------------------------------------------------------------
// Uzyskanie wektora zaleznosci z relacji
// zalozenie n.inp = n.out

Relation RelToDepVec(Relation R)
{
	Relation depVec = Project_Sym(Deltas(copy(R), R.n_inp()));
	return depVec;
}

// -------------------------------------------------------------
// Ustalenie czy wektor jest jednorodny czy niejednorodny


// LINUX -do modyfikacji !!
// Naprawiono 2010.3.12 do synch
bool GetVecType(Relation S)
{

        Relation W = Cross_Product(copy(S), copy(S));
        W = Deltas(copy(W));
        String SS = R2String(W, 1);

        String SZ = "";
        for(int i=1; i<W.n_set(); i++)
            SZ += "0,";
        SZ += "0";
        //printf("@@@  %s", str(SZ));

        std::string sz = str(SZ);
        std::string ss = str(SS);
        int l = ss.find(sz);


        if(l > -1)
            return true;
        else
            return false;
}

// Czy wartosc jest liczba calkowita

bool Int(double x)
{
	long y = (long)floor(x);

	if(x - y == 0)
		return true;
	else
		return false;
}

// Usuwa pierwsze polowe zmiennych w zbiorze,
// Uwagi:  input_set musi miec parzysta liczbe zmiennych

Relation RemoveHalf(Relation Input_Set)
{
	int i, dim = Input_Set.n_set();

	Relation MR(dim, (int)dim/2), Output_Set((int)dim/2); // mapping relation

	F_And *root = MR.add_and();

	for(i=1; i<=(int)dim/2; i++)
	{
		if(i < (int)dim/2)
			root = root->add_and();

		EQ_Handle eq = root->add_EQ();

		Variable_ID t1 = MR.input_var((int)dim/2 + i);
		Variable_ID t2 = MR.output_var(i);

		eq.update_coef(t1, 1);
		eq.update_coef(t2, -1);

	}

	Output_Set = Range(Restrict_Domain(copy(MR), copy(Input_Set)));

	return Output_Set;

}




// Funkcja dzielaca relacje po koniunkcjach
// R = R1 u R2 u R3 ..... zwraca R1, R2, R3 w kolekcji relacji Tuple<Relation> *
// Input: Relation
// Output: Tuple<Relation> *


Tuple<Relation>* RelationSplit(Relation R)
{
	Tuple<Relation> *rels = new Tuple<Relation>;

	R.simplify(2, 4);

	for(DNF_Iterator di(R.query_DNF()); di; di++)
		rels->append(*(new Relation(R, (*di))));

	return rels;
}

// Przyklad uzycia


/*	// DEBUG
	Relation r1 = Union(copy(BaseRel.R[1]), copy(BaseRel.R[2]));
	r1.print();
	printf("Podzielona relacja\n");
	print_Relations(*(RelationSplit(r1)));


	// - DEBUG */

// ----------------

// Funkcja rozkladaja relacje na czynniki pierwsze
// ma podstawie manuala
// wejscie relacja R

void Print_Info(Relation r1)
{
	for(DNF_Iterator di(r1.query_DNF()); di; di++)
	{
		printf("In next conjunct,\n");

		for(Variable_Iterator vi(*(*di)->variables()); vi; vi++)
		{
			Variable_ID vv = (*vi);
			printf("	Variable: %s", str(vv->name()));
			Var_Kind vd = vv->kind();

			switch(vd)
			{
				case(Input_Var) :
				{
					printf("  Input [%d]\n", vv->get_position());
					break;
				}
				case(Output_Var) :
				{
					printf("  Output [%d]\n", vv->get_position());
					break;
				}
				case(Set_Var) :
				{
					printf("  Set [%d]\n", vv->get_position());
					break;
				}
				case(Global_Var) :
				{
					printf("  Global\n");
					break;
				}
				default :
				{
					printf("  Exists or another\n");
					break;
				}
			}

		}
		printf("\n");

		String s = (*di)->print_to_string(1);

		if(strstr(s, "Exists"))
			printf("	Exists constraint \n ");


		for(EQ_Iterator ei = (*di)->EQs(); ei; ei++)
		{
			printf("	In next equality constraint,\n");
			for(Constr_Vars_Iter cvi(*ei); cvi; cvi++)
				printf("	Variable %s has coefficient %d\n", (*cvi).var->char_name(), (int)(*cvi).coef);


			printf("	Const in constraint %d\n", (int)(*ei).get_const());
		}
		for(GEQ_Iterator gi = (*di)->GEQs(); gi; gi++)
		{
			printf("	In next inequality constraint,\n");
			for(Constr_Vars_Iter cvi(*gi); cvi; cvi++)
				printf("	Variable %s has coefficient %d\n", (*cvi).var->char_name(), (int)(*cvi).coef);

			printf("	Const in constraint %d\n", (int)(*gi).get_const());
		}
		printf("\n");
	}
}


// ----------------------------------------------------------------------------------------
Relation TransitiveC(Relation R)
{
   if(__TC == 0)
      return TransitiveClosure(copy(R));
   else if(__TC == 1)
      return IterateClosure(R, __TC_N);
   else if(__TC == 2)
      return IterateClosure(R, __TC_N);
   else if(__TC == 3)
      return AdvancedIterateClosure(R);

}

// R*
Relation Star(Relation R, int plus = 0)
{

        Relation Rstar = TransitiveC(copy(R));
	Rstar.simplify();
	if(plus == 0)
        Rstar =	Union(copy(Rstar), IdentityRelation(R.n_inp()));
	Rstar.simplify();




	if(!Rstar.is_exact())
	{
		printf("\nError! R* has UNKNOWN");
		//Rstar = Upper_Bound(copy(Rstar));

		//exit(0);
	}

	return Rstar;

}

//sposob uzycia: SymSimplify(&DT);
// ------------------------------------

Relation SymSimplify(Relation DT)
{
	Tuple<Variable_ID> Sym;
        Tuple<Global_Var_ID> Z;

    	for(DNF_Iterator di2(DT.query_DNF()); di2; di2++)
	{

		for(Variable_Iterator vi(*(*di2)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd == Global_Var)
					{
                                            Sym.append(vv);
                                            printf("%s", vv->char_name());
                                            Global_Var_ID z = vv->get_global_var();
                                            Z.append(z);
                                            if(Z.length() > 1)
                                                z = Z[Z.length()-1];

                                          //  printf("%i", &z);

					}

		}

	}

        for(int i=1; i<=Sym.length()/2; i++)
        {
        F_And *DTroot = DT.and_with_and();
			EQ_Handle eq = DTroot->add_EQ();

			eq.update_coef(Sym[i], 1);
			eq.update_coef(Sym[Sym.length()/2+i], -1);
                        DT.simplify();

        }

        for(int j=1; j<=Z.length(); j++)
            printf("%s", str(Z[j]->base_name()));
        return DT;
}




String R2String(Relation R, int upr)
{
	char buf[10];
	String r = "";
	FILE *f = fopen("tmp_r.txt", "w");

        if(upr == 1)
            R.print_with_subs(f);
        else
            R.print(f);
	fclose(f);

	f = fopen("tmp_r.txt", "r");

	while( fgets(buf,sizeof(buf), f) != NULL)
	{
		r += buf;
	}

	fclose(f);

	return r;

}


void RemoveRedundant(ComplexRelation BaseRel, ComplexRelation *BaseOut, bool other)
{
	int j, i, n, add;


	n = BaseRel.R.length();

        BaseOut = new ComplexRelation();

	//BaseOut->From = BaseRel.From;
	//BaseOut->To = BaseRel.To;

	for(i=1; i<=n; i++)
	{
		add = 1;

		for(j=1; j<=BaseOut->R.length(); j++)
		{

			String s1 = R2String(BaseRel.R[i]);
			String s2 = R2String(BaseOut->R[j]);

			if(other)
			{
				if((BaseRel.From[i] == BaseOut->From[j]) && (BaseRel.To[i] == BaseOut->To[j]) && (strcmp(s1, s2) == 0))
					add =0;
			}
			else
			{
				if(strcmp(s1, s2) == 0)
					add =0;
			}


		}

		if(add)
		{
			BaseOut->R.append(BaseRel.R[i]);
			BaseOut->DepVect.append(BaseRel.DepVect[i]);
		//	BaseOut->VecType.append(BaseRel.VecType[i]);
                        BaseOut->From.append(BaseRel.From[i]);
                        BaseOut->To.append(BaseRel.To[i]);
			//if(other)
			//{
			//	BaseOut->From[j] = BaseRel.From[i];
			//	BaseOut->To[j] = BaseRel.To[i];
			//}
		}
	}


        printRelations(BaseOut->R, 1);




}



Tuple <Relation> ReduceTR(Tuple <Relation> R_Set)
{
	for(int i=1; i<=R_Set.length(); i++)
	{
		R_Set[i].print();
		R_Set[i] = TransitiveReduction(R_Set[i]);

		R_Set[i].simplify();
		R_Set[i].print();
	}

	return R_Set;


}



Relation ReduceSet(Relation S)
{
	Tuple <Relation> Under_Sets = Divide_Relation(S);
	Tuple <Relation> Out_Sets;
	Relation Tmp, Tmp2;
	Relation R_OUT;

	int i, j, n = Under_Sets.length(), remove;



	for(i=1; i<=n; i++)
	{

		remove = 0;

		for(j=1; j<=Out_Sets.length(); j++)
		{
			Tmp =  Difference(copy(Under_Sets[i]), copy(Out_Sets[j]));
			Tmp2 = Difference(copy(Out_Sets[j]), copy(Under_Sets[i]));

			Tmp.simplify();
			Tmp2.simplify();

			//sa takie same nie dodawaj
			if(Tmp2.number_of_conjuncts() == 0 && Tmp.number_of_conjuncts() == 0)
			{
				remove = 1;
				break;
			}

			if(Tmp.number_of_conjuncts() == 0)
			{

				remove = 1;
				break;
			}

			if(Tmp2.number_of_conjuncts() == 0)
			{
				Out_Sets[j] = Under_Sets[i];
				remove = 1;
			}

		}

		if(remove == 0)
			Out_Sets.append(Under_Sets[i]);
	}


	Under_Sets = Out_Sets;
	n = Under_Sets .length();
	Out_Sets.clear();


	for(i=1; i<=n; i++)
	{

		remove = 0;

		for(j=1; j<=Out_Sets.length(); j++)
		{
			Tmp =  Difference(copy(Under_Sets[i]), copy(Out_Sets[j]));
			Tmp2 = Difference(copy(Out_Sets[j]), copy(Under_Sets[i]));

			Tmp.simplify();
			Tmp2.simplify();

			//sa takie same nie dodawaj
			if(Tmp2.number_of_conjuncts() == 0 && Tmp.number_of_conjuncts() == 0)
			{
				remove = 1;
				break;
			}


		}

		if(remove == 0)
			Out_Sets.append(Under_Sets[i]);
	}


	Under_Sets = Out_Sets;
	n = Under_Sets.length();

	R_OUT = Under_Sets[1];
	for(i=2; i<=n; i++)
		R_OUT = Union(copy(R_OUT), copy(Under_Sets[i]));

	R_OUT.simplify();

	Tmp =  Difference(copy(R_OUT), copy(S));
	Tmp2 = Difference(copy(S), copy(R_OUT));


//	Tmp.simplify();
	//Tmp2.simplify();

	if(Tmp.number_of_conjuncts() == 0 && Tmp2.number_of_conjuncts() == 0)
	{}//printf("Walidacja Alg2 OK\n");
	else
		printf("Blad w ReduceSet");


	return R_OUT;

}

//  Sortuje relacje, zwraca tablice numerow relacji, te ktore sie w sobie zawieraja sa skladane pozniej
Tuple<int> SortRelations(Tuple<Relation> R)
{
	int n = R.length(), i, j, all = 0, child = 0, count=0;
	int *lista = new int[n];
	int *added = new int[n];
	Tuple<int> sortlist;

	for(i=0; i<n; i++)
		added[i-1] = 0;

	while(all == 0)
	{
		all = 1;
		for(j=1; j<=n; j++)
		{


			if(added[j-1] != 1)
			{
				all = 0;
				child = 0;
				for(i=1; i<=n; i++)
				{
					if(i!=j && added[i-1] != 1)
					{
						Relation Si = Union(Domain(copy(R[i])), Range(copy(R[i])));
						Relation Sj = Union(Domain(copy(R[j])), Range(copy(R[j])));

						Relation Diff = Difference(copy(Si), copy(Sj));
						Relation Diff2 = Difference(copy(Sj), copy(Si));

						Diff.simplify();
						Diff2.simplify();
						if(Diff.number_of_conjuncts()>0 && Diff2.number_of_conjuncts() == 0) //Sj zawiera sie w Si, Rj nie moze byc teraz dodane
						{
							child = 1;
							break;
						}
					}
				}

				if(child == 0)
				{

					lista[count] = j;
					count++;
					added[j-1] = 1;

				}




			}


		}

	}

	for(i=0; i<n; i++)
	{
		printf("%i ", lista[i]);
		sortlist.append(lista[i]);
	}
	return sortlist;

}


ComplexRelation SortNow(ComplexRelation BaseRel)
{
	Tuple<int> lista = SortRelations(BaseRel.R);

	ComplexRelation BaseOut;

	BaseOut.From = BaseRel.From;
	BaseOut.To = BaseRel.To;

	int i;

	for(i=1; i<=lista.length(); i++)
	{
		BaseOut.R.append(BaseRel.R[lista[i]]);
		BaseOut.DepVect.append(BaseRel.DepVect[lista[i]]);
		BaseOut.VecType.append(BaseRel.VecType[lista[i]]);

		BaseOut.From[i] = BaseRel.From[lista[i]];
		BaseOut.To[i] = BaseRel.To[lista[i]];

	}

	return BaseOut;

}

char *replace(const char *s, const char *old, const char *_new)
{
char *ret, *sr;
size_t i, count = 0;
size_t newlen = strlen(_new);
size_t oldlen = strlen(old);

if (newlen != oldlen) {
for (i = 0; s[i] != '\0'; ) {
if (memcmp(&s[i], old, oldlen) == 0)
count++, i += oldlen;
else
i++;
}
} else
i = strlen(s);

ret = (char*)malloc(i + 1 + count * (newlen - oldlen));
if (ret == NULL)
return NULL;

sr = ret;
while (*s) {
if (memcmp(s, old, oldlen) == 0) {
memcpy(sr, _new, newlen);
sr += newlen;
s += oldlen;
} else
*sr++ = *s++;
}
*sr = '\0';

return ret;
}

/*
// szukaj relacje
int GetRelationId(String _rel, int _from, int _to)
{
	int i;
	for(i=1; i<=petitRelations.length(); i++)
	{
		String tmp = petitRelations[i].print_with_subs_to_string();
		if(strcmp(tmp, _rel) ==0 && _from == petitFrom[i-1] && _to == petitTo[i-1])
			return i;
	}
	return -1;
}
*/







ComplexRelation CorrectStatements(ComplexRelation BaseRel)
{
	Tuple<int> _old;
	Tuple<int> _new;

	int i, j, tmp;

	for(i=1; i<=BaseRel.R.length(); i++)
	{

		tmp = BaseRel.From[i];
		int dodaj = 1;
		for(j=1; j<=_old.length(); j++)
		{
			if(_old[j] == tmp)
			{
				dodaj = 0;
			}
		}

		if(dodaj)
			_old.append(tmp);

		tmp = BaseRel.To[i];
		dodaj = 1;
		for(j=1; j<=_old.length(); j++)
		{
			if(_old[j] == tmp)
			{
				dodaj = 0;
			}
		}

		if(dodaj)
			_old.append(tmp);


	}



//	for(i=1; i<=_old.length(); i++)
//		printf("\n%i ", _old[i]);


	for(i=1; i<=_old.length(); i++)
	{
		tmp = 0;

		for(j=1; j<=_old.length(); j++)
			if(i!=j && _old[i] > _old[j])
				tmp++;

		_new.append(tmp);
	}

//	for(i=1; i<=_new.length(); i++)
//		printf("\n%i ", _new[i]);


	for(i=1; i<=BaseRel.R.length(); i++)
	{
		tmp = BaseRel.From[i];

		for(j=1; j<=_old.length(); j++)
			if(_old[j] == tmp)
			{
				BaseRel.From[i] = _new[j];
				break;
			}

		tmp = BaseRel.To[i];

		for(j=1; j<=_old.length(); j++)
			if(_old[j] == tmp)
			{
				BaseRel.To[i] = _new[j];
				break;
			}

	}

	return BaseRel;
}

Variable_ID FindSym(Relation R, String nazwa)
{

	// odczytaj zmienne symboliczne w r1
	for(DNF_Iterator di2(R.query_DNF()); di2; di2++)
	{

		for(Variable_Iterator vi(*(*di2)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd == Global_Var)
					{
						if(strcmp(nazwa,  vv->char_name()) == 0)
							return vv;
					}

		}

	}

	return NULL;


}


char* _itoa( int value, char* result, int base ) {

	// check that the base if valid

	if (base < 2 || base > 16) { *result = 0; return result; }



	char* out = result;

	int quotient = value;



	do {

		*out = "0123456789abcdef"[ std::abs( quotient % base ) ];

		++out;

		quotient /= base;

	} while ( quotient );



	// Only apply negative sign for base 10

	if ( value < 0 && base == 10) *out++ = '-';



	std::reverse( result, out );

	*out = 0;

	return result;

}

/*

Relation SymbolicTuple2(int z)
{
    Relation S(z);



    Tuple<Variable_ID> Sx, Si;

    Sx.append(S.get_local(&x1));
    if(z>=2)
        Sx.append(S.get_local(&x2));
    if(z>=3)
        Sx.append(S.get_local(&x3));
    if(z>=4)
        Sx.append(S.get_local(&x4));
    if(z>=5)
        Sx.append(S.get_local(&x5));

    for(int i=1; i<=z; i++)
        Si.append(S.set_var(i));



    for(int i = 1; i<=z; i++)
    {
        F_And *Stmp;
        if(i == 1)
        {
        F_And *S_root = S.add_and();

        EQ_Handle Sx1 = S_root->add_EQ();
        Sx1.update_coef(Si[1], 1);
        Sx1.update_coef(Sx[1], -1);

        Stmp = S_root;

        }
        else
        {
            if(i<z)
            {

                F_And *S_node = Stmp->add_and();
                EQ_Handle Snodeeq = S_node->add_EQ();
                Snodeeq.update_coef(Si[i], 1);
                Snodeeq.update_coef(Sx[i], -1);

                Stmp = S_node;
            }
            else
            {
                EQ_Handle Snodeeq = Stmp->add_EQ();
                Snodeeq.update_coef(Si[i], 1);
                Snodeeq.update_coef(Sx[i], -1);
            }

       }
    }


    S.simplify();


    return S;





}

*/


Relation SymbolicTuple(int z)
{
    Relation S(z);
    Variable_ID *xTab;
    xTab = (Variable_ID*)calloc(z, sizeof(Variable_ID));
    char *tmp;
    Tuple<Variable_ID> Si;

    for(int i=0; i<z; i++)
    {
        asprintf(&tmp, "x%d", i+1);
        xi[i+1]->set_base_name(tmp);
        xTab[i] = S.get_local(xi[i+1]);
    }



    for(int i=1; i<=z; i++)
        Si.append(S.set_var(i));



    for(int i = 1; i<=z; i++)
    {
        F_And *Stmp;
        if(i == 1)
        {
        F_And *S_root = S.add_and();

        EQ_Handle Sx1 = S_root->add_EQ();
        Sx1.update_coef(Si[1], 1);
        Sx1.update_coef(xTab[0], -1);

        Stmp = S_root;

        }
        else
        {
            if(i<z)
            {
                F_And *S_node = Stmp->add_and();
                EQ_Handle Snodeeq = S_node->add_EQ();
                Snodeeq.update_coef(Si[i], 1);
                Snodeeq.update_coef(xTab[i-1], -1);

                Stmp = S_node;
            }
            else
            {
                EQ_Handle Snodeeq = Stmp->add_EQ();
                Snodeeq.update_coef(Si[i], 1);
                Snodeeq.update_coef(xTab[i-1], -1);
            }

       }

    }


    S.simplify();


    return S;





}

// char * PrintString


//LexForward Omega Console
Relation LexForward(int n) {
  Relation r(n,n);
  F_Or *f = r.add_or();
  for (int i=1; i <= n; i++) {
	F_And *g = f->add_and();
	for(int j=1;j<i;j++) {
	   EQ_Handle e = g->add_EQ();
	   e.update_coef(r.input_var(j),-1);
	   e.update_coef(r.output_var(j),1);
	   e.finalize();
	   }
	GEQ_Handle e = g->add_GEQ();
	e.update_coef(r.input_var(i),-1);
	e.update_coef(r.output_var(i),1);
	e.update_const(-1);
	e.finalize();
	}
  r.finalize();
  return r;
  }


Relation Maximize(Relation In)
{
    Relation Out;

    Out = Cross_Product(copy(In), copy(In));
    Out = Difference(copy(In), Domain(Intersection(copy(Out),LexForward(Out.n_inp()))));

    return Out;

}

Relation Minimize(Relation In)
{
    Relation Out;

    Out = Cross_Product(copy(In), copy(In));
    Out = Difference(copy(In), Range(Intersection(copy(Out),LexForward(Out.n_inp()))));

    return Out;

}





/************************************** */
/*  Calculate R* on a given region      */
/*										*/
/*  Tomasz Klimek 05-06-2010			*/
/************************************** */

// #define maxVars 256 /* original 56, increased by chun */

#define myMaxIterations 10
#define myMaxConjuncts 800
#define myMaxWildcards 12
#define myMaxGEQs 2048
#define myMaxEQs 512

/* Tomasz Klimek */
int iterateCondition( NOT_CONST Relation &rNew, NOT_CONST Relation &rOld, int nEQs, int nGEQs, \
		      int nConjuncts, int iters, int maxWildcards){

Relation r1 = consume_and_regurgitate(rNew);
Relation r2 = consume_and_regurgitate(rOld);

 // if (Must_Be_Subset(r1, r2)) return 0;
 // if ((nEQs >= myMaxEQs) || (nGEQs >= myMaxGEQs)) return -1;
  if (nConjuncts >= myMaxConjuncts) return -2;
  if (iters >= myMaxIterations) return -3;
  if (maxWildcards >= myMaxWildcards) return -4;

  return 1;

}


Relation checkExactness(NOT_CONST Relation &r, NOT_CONST Relation &rplus){

Relation s1 = consume_and_regurgitate(r);
Relation s2 = consume_and_regurgitate(rplus);
Relation R;


R = Composition(copy(s1), copy(s2));
R = Union(s1, R);


 if( Must_Be_Subset(copy(s2), copy(R)) && \
	    Must_Be_Subset(copy(R), copy(s2))) {
    R = Relation::Null();
    return s2;
 }

 R = Relation::Null();

 return Intersection(s2, Relation::Unknown(s2));

}


Relation TransitiveClosure3(NOT_CONST Relation &r, NOT_CONST Relation &region) {

Relation s = consume_and_regurgitate(r);
Relation reg = consume_and_regurgitate(region);
Relation R = Relation::False(s.n_inp(), s.n_out());
Relation tc = Relation::False(s.n_inp(), s.n_out());
Relation Rtmp, Rdelta, delta;


  for (DNF_Iterator c(s.query_DNF()); c; c++) {
	  delta = Deltas(Relation(s, c.curr()));
	  Rdelta = DeltasToRelation(copy(delta), s.n_inp(), s.n_out());
	  Rtmp = DeltasToRelation(Project_Sym(delta), s.n_inp(), s.n_out());

	  Rtmp = Restrict_Domain(Rtmp, Domain(copy(Rdelta)));
	  Rtmp = Restrict_Range(Rtmp, Range(Rdelta));

	  R = Union(R, TransitiveClosure(Rtmp, 1, Relation::Null()));
  }

  for (DNF_Iterator c(R.query_DNF()); c; c++) {
     Rtmp = Union(Identity(s.n_inp()), Relation(R, c.curr()));
     tc = Composition(Union(tc, Identity(s.n_inp())), Rtmp);
  }

  tc = Difference(tc, Identity(s.n_inp()));

  tc = Restrict_Domain(tc, copy(reg));
  tc = Restrict_Range( tc, reg );
  tc.simplify(2,4);

  return checkExactness(s, tc);

}


Relation TransitiveClosure2(NOT_CONST Relation &r){

Relation s = consume_and_regurgitate(r);
Relation region = Union(Domain(copy(s)),Range(copy(s)));

return TransitiveClosure3(s, region);

}



/* Tomasz Klimek */
static Relation composeN(NOT_CONST Relation &r, int &condition) {

  Relation R = consume_and_regurgitate(r);
  Relation Rplus,delta,deltaTmp,cHull,cHullTmp,tc;
  int i=1;

  R = Union(R, Identity(R.n_inp()));

  Rplus = delta = R;

  for(;;) {
    delta = Difference(Composition(copy(R), delta), copy(Rplus));

    if (Must_Be_Subset(copy(delta), copy(Rplus))) break;

    Rplus = Difference(Union(Rplus, copy(delta)), Identity(R.n_inp()));
    cHull = Hull(copy(Rplus),false,1,Null_Relation());
    cHullTmp = Difference(copy(cHull), copy(Rplus));
    cHull = Difference(cHull, cHullTmp);

    if (cHull.number_of_conjuncts() < Rplus.number_of_conjuncts()) {
	Rplus = Relation::Null();
	Rplus = Union(cHull, Identity(R.n_inp()));
    }
    else{
	cHull = Relation::Null();
    }

    Rplus = Union(Rplus, Identity(R.n_inp()));

    condition = iterateCondition(copy(delta), copy(Rplus), Rplus.n_EQs(), Rplus.n_GEQs(), \
				  Rplus.number_of_conjuncts(), i++, Rplus.get_max_wildcards_number());

    if (condition < 0){
      break;
    }

    deltaTmp = Identity(R.n_inp());

    for (DNF_Iterator c(delta.query_DNF()); c; c++) {
	  tc = TransitiveClosure(Relation(delta, c.curr()), 1,Relation::Null());
	  if (tc.is_inexact()) {
	    deltaTmp = Union(deltaTmp, Relation(delta, c.curr()));
	    continue;
	  }
	  deltaTmp = Union(deltaTmp, tc);
    }

    delta = deltaTmp;
    deltaTmp = Relation::Null();

  }

  delta = Relation::Null();
  return Rplus;


} /* composeN */





/************************************** */
/*  Calculate approximation of R*       */
/*										*/
/*  Tomasz Klimek 05-06-2010			*/
/************************************** */


Relation ApproxClosure(NOT_CONST Relation &r){

Relation s = consume_and_regurgitate(r);
Relation R = Relation::False(s.n_inp(), s.n_out());
Relation tc = Relation::False(s.n_inp(), s.n_out());
Relation cHull,cHullTmp,Rtmp;;

  for (DNF_Iterator c(s.query_DNF()); c; c++) {
      R = Union(R, TransitiveClosure(DeltasToRelation(Project_Sym(Deltas(Relation(s, c.curr()))),s.n_inp(),s.n_out()), \
			      1, Relation::Null()));
  }

  for (DNF_Iterator c(R.query_DNF()); c; c++) {
     Rtmp = Union(Identity(s.n_inp()), Relation(R, c.curr()));
     tc = Composition(Union(tc, Identity(s.n_inp())), Rtmp);

     tc = Difference(tc, Identity(s.n_inp()));
     cHull = Hull(copy(tc),false,1,Null_Relation());
     cHullTmp = Difference(copy(cHull), copy(tc));
     cHull = Difference(cHull, cHullTmp);

     if (cHull.number_of_conjuncts() < tc.number_of_conjuncts()) {
	tc = Relation::Null();
	tc = Union(cHull, Identity(s.n_inp()));
     }
     else{
	cHull = Relation::Null();
     }
  }

  tc = Difference(tc, Identity(s.n_inp()));
  tc = Restrict_Domain(tc,Domain(copy(s)));
  tc = Restrict_Range(tc,Range(s));
  tc = Intersection(tc, Relation::Unknown(tc));

 return tc;
}




/************************************** */
/*  Calculate R* in iterate procedure   */
/*										*/
/*  Tomasz Klimek 05-06-2010			*/
/************************************** */

Relation AdvancedIterateClosure(NOT_CONST Relation &r) {

Relation s = consume_and_regurgitate(r);
Relation R = Identity(s.n_inp());

Relation tc;
int condition=1;


 for (DNF_Iterator c(s.query_DNF()); c; c++) {
     tc = TransitiveClosure(Relation(s, c.curr()), 1,Relation::Null());
     if (tc.is_inexact()) {
       condition = -5;
       break;
     }
     R = Union(R, tc);
 }

 if (condition > 0) {
   tc = composeN(R, condition);
 }

 if ( condition < 0 ) {
   tc = Relation::Null();
   R = Relation::Null();
   tc = ApproxClosure(s);

   return tc;
 }

 tc = Difference(tc, Identity(s.n_inp()));

 return tc;

}


void printKindRelInfo(ComplexRelation BaseRel)
{
    int flow=0, anti=0, output=0;
    for(int i=1; i<=BaseRel.R.length(); i++)
    {
        if(strcmp(BaseRel.Type[i], "flow")==0)
            flow++;

        if(strcmp(BaseRel.Type[i],"anti")==0)
            anti++;

        if(strcmp(BaseRel.Type[i], "output")==0)
            output++;

        cout << BaseRel.Type[i];
    }

    cout << endl << "Flow:   " << flow;
    cout << endl << "Anti:   " << anti;
    cout << endl << "Output: " << output;



}


bool copyFile (const char SRC[], const char DEST[])
{
    std::ifstream src; // the source file
    std::ofstream dest; // the destination file

    src.open (SRC, std::ios::binary); // open in binary to prevent jargon at the end of the buffer
    dest.open (DEST, std::ios::binary); // same again, binary
    if (!src.is_open() || !dest.is_open())
        return false; // could not be copied

    dest << src.rdbuf (); // copy the content
    dest.close (); // close destination file
    src.close (); // close source file

    return true; // file copied successfully
}


void WriteVars(Relation CDG)
{
    FILE *_file;
    _file = fopen("names_info.txt", "w");
    for(int yy = 1; yy <= CDG.n_set(); yy++)
    {
        fprintf(_file, CDG.set_var(yy)->name());
        if( yy < CDG.n_set())
            fprintf(_file, ",");

    }
    fclose(_file);

}
