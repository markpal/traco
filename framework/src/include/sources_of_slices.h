// *****************************************************************************************
// funkcje Sources of Slices


#include "r_ucs.h"
#include "r_ucs_2.h"
int v_name = 0;

Rel_Struct FindSourcesOfSlices(ComplexRelation BaseRel, Tuple<Relation> *R_UCS_list, int);

//funkcje pomocnicze
Relation Create_R_UCS(Relation R, Relation UDS, Relation UDSi, Relation Rstar, int display);

ComplexRelation CalcRelations(ComplexRelation BaseRel);
Relation Extend_Relation(Relation R, int From, int To, int kk);

ComplexRelation Ext_Base(ComplexRelation BR);
ComplexRelation Init_Base(ComplexRelation BaseRel);  //nieuzywana


// ------------------------------------------------------------------------------------------------------
//szukanie poczatkow - funkcja glowna
Rel_Struct FindSourcesOfSlices(ComplexRelation BaseRel, Tuple<Relation> *R_UCS_list, int display)
{

	display = 1; display = !_SILENT;
	Relation R, Tmp, Tmp2, All_UDS, R_UCS, R_UCSi;
	Rel_Struct Dom, Ran, UDS, Sources;
	ComplexRelation BaseRel2;


	int n, i,j, added, v;

	Tmp = Tmp2 = BaseRel.R[1];

	/*
	{Ri,j |   i, j?[1,q] of dependence relations representing an SCC, where each Ri,j denotes the union
	of all relations describing dependences between statements si and sj,  and q is the number of vertices in the SCC. */

	//print_Relations(BaseRel.R);
	//printf("\nRi,j denotes the union of all relations describing dependences between statements si and sj\n");
	//BaseRel = CalcRelations(BaseRel);
	//print_Relations(BaseRel.R);

	/*
	foreach relation Ri,j ? S do
	extend the tuples of Ri,j with additional objects representing identifiers of statements i and j, i.e., transform Ri,j := {[e]?[e']} into Ri,j :={[e,i]?[e',j]}.
	*/

	/*
	printf("Relacje po dodaniu zmiennej: extend the tuples of Ri,j with additional objects representing identifiers of statements i and j\n");
	BaseRel = Ext_Base(BaseRel);
	print_Relations(BaseRel.R);
	*/


	// ------------------------------------------------------------------------------------------

	// 2. Form relation R

	//R = GlobalUnion(BaseRel);
	//printf("@@@@@@@@@@@");
	R = BaseRel.R[1];
	for(i=2; i<=BaseRel.R.length(); i++)
		R = Union(copy(R), copy(BaseRel.R[i]));

//	R = RepairNameVar(R);

	R.simplify();

	//R.print();


	// --------


	/*
	printf("\nR: ");
	R.print();
	R = Complement(copy(R));
	R.simplify();
	printf("\n-R: ");
	R = Complement(copy(R));
	R.simplify();
	R.print();
*/


	n = BaseRel.R.length();

	//oblicz R

	// obliczanie UDS start

	//stworz Domain Rij i Range Rij

	for(i=1; i<=n; i++)
	{

		added = 0;
		// szukaj Dom
		for(j=1; j<=Dom.R.length(); j++)
		{

			if(BaseRel.From[i] == Dom.I[j-1])
			{
				Dom.R[j] = Union(copy(Dom.R[j]), Domain(copy(BaseRel.R[i])));
				Dom.R[j].simplify(2, 5);
				added = 1;
				break;
			}


		}


		if(added == 0)
		{

			Dom.R.append(Domain(copy(BaseRel.R[i])));
			Dom.I[Dom.R.length()-1] = BaseRel.From[i];

		}


		//teraz Ran

		added = 0;
		// szukaj Dom
		for(j=1; j<=Ran.R.length(); j++)
		{

			if(BaseRel.To[i] == Ran.I[j-1])
			{
				Ran.R[j] = Union(copy(Ran.R[j]), Range(copy(BaseRel.R[i])));
				Ran.R[j].simplify(2, 5);
				added = 1;
				break;
			}

		}

		if(added == 0)
		{
			Ran.R.append(Range(copy(BaseRel.R[i])));
			Ran.I[Ran.R.length()-1] = BaseRel.To[i];
		}


	}


	for(i=1; i<=Dom.R.length(); i++)
	{
	//	printf("Dom[I] %i", Dom.I[i-1]);
	//	Dom.R[i].print();
	}

	for(i=1; i<=Ran.R.length(); i++){
	//	printf("Ran[I] %i", Ran.I[i-1]);
	//	Ran.R[i].print();
	}

	//Oblicz UDS

	for(i=1; i<=Dom.R.length(); i++)
	{
		v = Dom.I[i-1];


		Tmp = Dom.R[i];
		Tmp2 = Difference(copy(Tmp), copy(Tmp));
		Tmp2.simplify(2, 5);



		for(j=1; j<=Ran.R.length(); j++)
			if(v == Ran.I[j-1])
				Tmp2 = Union(copy(Tmp2), copy(Ran.R[j]));


		if(Tmp.number_of_conjuncts() > 0)   //jesli jest dom Rik to trzeba dodac UDS(i), inaczej nie ma poczatkow dla si
		{

			Relation UDS_tmp;

		    if(Tmp2.number_of_conjuncts() > 0)
			  UDS_tmp = Difference(copy(Tmp), copy(Tmp2));
			else
			  UDS_tmp = Tmp;
			UDS_tmp.simplify();

			if(UDS_tmp.number_of_conjuncts() > 0)
			{
				UDS.R.append(UDS_tmp);
				UDS.R[UDS.R.length()].simplify();
				UDS.I[UDS.R.length()-1] = v;

			}
		}






	}

	for(i=1; i<=UDS.R.length(); i++){
	//	printf("UDS[I] %i", UDS.I[i-1]);
		//UDS.R[i].print();
	}



	for(i=1; i<=UDS.R.length(); i++)
	{
		if(v_name)
		UDS.R[i].name_set_var(UDS.R[i].n_set(), "v");
		if(!_SILENT)
		if(display)
		{
		printf("\n%i. UDS(%i) : ", i, UDS.I[i-1]);
		UDS.R[i].print();
		printf("\n");
		}
	}


	if(BaseRel.R.length() == 1)
	{
		Sources.R.append(UDS.R[1]);
		Sources.I[0] = UDS.I[0];
		Tmp = Difference(copy(BaseRel.R[1]), copy(BaseRel.R[1]));
		Tmp.simplify();
		R_UCS_list->append(Tmp);   //dodaj puste R_UCS
		return Sources;
	}

	//oblicz cale UDS


	All_UDS = UDS.R[1];

	for(i=2; i<=UDS.R.length(); i++)
		All_UDS = Union(copy(All_UDS), copy(UDS.R[i]));

	All_UDS.simplify(2, 5);

    if(v_name)
	All_UDS.name_set_var(All_UDS.n_set(), "v");
	if(display)
	{
	printf("\nUDS:\n");
	All_UDS.print();
	}




	// obliczanie UDS koniec


	//obliczanie R_UCS i koncowych source

	n = UDS.R.length();
	if(display)
		R.print();

	//printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");


	//R = Repair_Relation(R);
    R.simplify();
	//R.print();
		R = SimplifyNumConjuncts(R);                     // LINUX @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//exit(0);
		R = ReduceSet(R);

                double b6 = gettime();
	Relation Rstar = Star(copy(R));
                           double e6 = gettime();
                           if(!_SILENT)
                                printf("\n--------> Czas obliczenia R*: %.2f\n", (double)((e6 - b6)));

	//printf("*\n");
	//Rstar.print();

	Rstar.simplify(2, 4);
	if(display)
	{
	printf("\nR* : ");

	Rstar = SimplifyNumConjuncts(Rstar);
		Rstar = ReduceSet(Rstar);

		//Rstar.print();
	}

	if(!Rstar.is_exact())
	{
		if(!_SILENT)
            printf("\nR* (laczenie relacji) has UNKNOWN constraints\n");
		Rstar = Upper_Bound(copy(Rstar));
		if(!_SILENT)
		if(display)
		Rstar.print();
		//exit(1);
	}
	//printf("\n\n");

	Tuple<Relation> R_UCS_kopia = *R_UCS_list;
    Relation Tmp_Range;
	for(i=1; i<=n; i++)
	{
		/*
		int skok = 0;
		for(int rp = 1 ; rp < i; rp++)
		{
			Relation Testuj = Difference(copy(R_UCS_kopia[rp]), copy(UDS.R[i]));
			printf("************************");

			Testuj.print();
			Testuj.simplify();
			if(Testuj.number_of_conjuncts() == 0)
				skok = 1;
		}
		if(skok)
			continue;
*/
	//	if(i > 1)
	//		continue;

		R_UCS = Create_R_UCS(R, All_UDS,  UDS.R[i], Rstar, display);

		if(R_UCS.number_of_conjuncts() > 0)
		{
		//R_UCS = Repair_Relation(R_UCS, ginstr, goutstr, 0);
		//R_UCS = SimplifyNumConjuncts(R_UCS);
		}



		//printf("UDSi : ");
		//UDS.R[i].print();

		Tmp.simplify(2, 5);
		//if(display)
		//printf("\n\nR_UCS(%i) : ",i);

		Tmp = Range(copy(R_UCS));
		Tmp.simplify();
		Tmp = SimplifyNumConjuncts(Tmp);

        if(i>1)
            Tmp = Union(copy(Tmp), copy(Tmp_Range));
        Tmp_Range = Tmp;


		R_UCS.simplify(1, 1);

		if(!_SILENT)
		if(display)
		{
		printf("R_UCS");
		R_UCS.print();
		printf("\n");
		}
		R_UCS_list->append(copy(R_UCS));

        if(!_SILENT)
		if(display)
		{printf("\nRange R_UCS "); Tmp.print();}


		R_UCSi = Difference(copy(UDS.R[i]), Tmp);

		// ³atka na UNKNOWN
		Relation TMP_R = Intersection(copy(UDS.R[i]), Range(copy(R_UCS)));

		//printf("TMP_R\n");
		TMP_R.simplify();
		//TMP_R.print();
		//UDS.R[i].print();

		//R_UCSi = Intersection(copy(UDS.R[i]), copy(TMP_R));


		R_UCSi.simplify(2, 5);

		if(R_UCSi.number_of_conjuncts()){

            for(int u=1; u<=UDS.R[i].n_set(); u++)
                R_UCSi.name_set_var(u, UDS.R[i].set_var(u)->char_name());


            Sources.R.append(R_UCSi);
            int bb = Sources.R.length();
            Sources.I[bb-1] = UDS.I[bb-1];
		}




	}


	return Sources;

}

// ------------------------------------------------------------------------------------------------------

// dodaje ograniczenia
// liczba zmiennych wejsciowych musi byc rowna wyjsciowym


// nie uzywana, zastapiona w r_ucs.h


Relation Add_Lexographic_Order(Relation Rt, int con = 0)
{
	Relation R(Rt.n_inp(), Rt.n_inp());
	F_And *Lex = R.add_and();
	int n = R.n_inp(), j, k;
	Variable_ID i = R.input_var(1);
	Variable_ID ip = R.output_var(1);
	F_Or *or_con;

	if(n == 1)
	{
		GEQ_Handle constr = Lex->add_GEQ();
		constr.update_coef(ip, 1);
		constr.update_coef(i, -1);
		constr.update_const(-1);
	}
	else
	{

		or_con = Lex->add_or();
		for(j=1; j<=n; j++)
		{




			F_And *and_con = or_con->add_and();

			if(j > 1)
			{
				for(k=1; k<=j-1; k++)
				{
					//if(k>1)
					//	F_And *and_con = or_con->add_and();


					Variable_ID i = R.input_var(k);
					Variable_ID ip = R.output_var(k);

					EQ_Handle tmp = and_con->add_EQ();
					tmp.update_coef(i, 1);
					tmp.update_coef(ip, -1);

					if(k == j-1)
					{
						Variable_ID i = R.input_var(k+1);
						Variable_ID ip = R.output_var(k+1);

						GEQ_Handle tmp2 = and_con->add_GEQ();
						tmp2.update_coef(ip, 1);
						tmp2.update_coef(i, -1);
						tmp2.update_const(-1);
					}

				}


			}
			else
			{

				Variable_ID i = R.input_var(1);
				Variable_ID ip = R.output_var(1);

				GEQ_Handle tmp3 = and_con->add_GEQ();
				tmp3.update_coef(ip, 1);
				tmp3.update_coef(i, -1);
				tmp3.update_const(-1);
			}



		}


	}

	if(con)
		return R;

	R = Intersection(copy(R), copy(Rt));

	R.simplify(2, 4);

	return R;
}
// ------------------------------------------------------------------------------------------------------


//dodaje zmienna do instrukcji From To
Relation Extend_Relation(Relation R, int From, int To, int kk = 0)
{
	int n_in = R.n_inp();
	int n_out = R.n_out();

	Variable_ID k, kp;

	R = Extend_Domain(copy(R));
	R = Extend_Range(copy(R));

	k = R.input_var(n_in+1);
	kp = R.output_var(n_out+1);

	//R.name_input_var(n_in+1, "v");
	//R.name_output_var(n_out+1, "v'");

	F_And *Ext = R.and_with_and();

	EQ_Handle constr = Ext->add_EQ();
	constr.update_coef(k, 1);
	constr.update_const(-From);

	EQ_Handle constr2 = Ext->add_EQ();
	constr2.update_coef(kp, 1);
	constr2.update_const(-To);


//	if(kk!=1)
//	R = Repair_Relation(R);

	R.simplify();

    if(v_name)
    {
	R.name_input_var(n_in+1, "v");
	R.name_output_var(n_out+1, "v'");
    }


	return R;
}

// ------------------------------------------------------------------------------------------------------

// poprawia From To
ComplexRelation Init_Base(ComplexRelation BaseRel)
{
	int i;
	//int z = 10-BaseRel.R.length();
	int z =0;

	for(i=1; i<=BaseRel.R.length(); i++)
	{
		BaseRel.From[i]-=z;
		BaseRel.To[i]-=z;
	}

	return BaseRel;
}

// ------------------------------------------------------------------------------------------------------

//ostateczna wersja
ComplexRelation Ext_Base(ComplexRelation BR)
{
	int i, n = BR.R.length();
	//int diff = 0;
	//int tmp;


/*
	for(i=1; i<=n; i++)
	{
		if(i==1)
			tmp = BR.From[i];

		if(tmp != BR.From[i] || tmp != BR.To[i])
			diff = 1;
	}
*/
	//if(diff == 0)
	//	return BR;

	//BR = Init_Base(BR);



	for(i=1; i<=n; i++)
	{
			BR.R[i] = Extend_Relation(BR.R[i], BR.From[i], BR.To[i], 1);

			BR.R[i] = RepairNameVar(BR.R[i]);
			//printf("*********\n");
			//BR.R[i].print();
	}



	return BR;
}

// ------------------------------------------------------------------------------------------------------

// przeksztalc relacja wzgledem instrukcji From To
ComplexRelation CalcRelations(ComplexRelation BaseRel)
{
	ComplexRelation BaseOut;
	int i, j, added;

	BaseOut.From = BaseRel.From;
	BaseOut.To = BaseRel.To;


	for(j=1; j<=BaseRel.R.length(); j++)
	{
		added = 0;

		for(i=1; i<=BaseOut.R.length(); i++)
		{
			if(BaseRel.From[j] == BaseOut.From[i] && BaseRel.To[j] == BaseOut.To[i])
			{
				BaseOut.R[i] = Union(copy(BaseRel.R[j]), copy(BaseOut.R[i]));
				BaseOut.R[i].simplify(1, 5);
				added = 1;
				break;
			}
		}

		if(added == 0)
		{
			BaseOut.R.append(BaseRel.R[j]);
			BaseOut.From[BaseOut.R.length()] = BaseRel.From[j];
			BaseOut.To[BaseOut.R.length()] = BaseRel.To[j];
		}
	}



	return BaseOut;
}

// ------------------------------------------------------------------------------------------------------

// obliczanie R_UCS, wymaga r_ucs.h
Relation Create_R_UCS(Relation R, Relation UDS, Relation UDSi, Relation Rstar, int display)
{

	if(_R_UCS)
	   return Create_New_R_UCS(R, UDS, UDSi, Rstar, display);

	R.simplify(2,4);
	Relation IS = Union(Domain(copy(R)), Range(copy(R)));
	Relation R_UCS = Cross_Product(copy(UDSi), copy(UDS));
	//R_UCS.simplify();
	IS.simplify();
	printf("==================");

	R_UCS = Com_Add_Exists(R_UCS, IS, Rstar, display);   // wymaga r_ucs.h

	R_UCS.simplify();
	//R_UCS.print();




	return R_UCS;
}



// ---------------------------------------------------------------------------------------------------------
// Funkcja do obliczania Sources
// FUNKCJA GLOWNA

char *replace_str(char *str, char *orig, char *rep)
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return str;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}

Rel_Struct CalcSources(ComplexRelation BaseRel, int display)
{
	int i, n;


	Tuple<Relation> *R_UCS_list = new Tuple<Relation>;

	Rel_Struct Sources = FindSourcesOfSlices(BaseRel, R_UCS_list, display);


	n = Sources.R.length();

	for(i=1; i<=n; i++)
	{

		if(0)
		{
			printf("Sources(%i) i=%i\n", i, Sources.I[i-1]);
			Sources.R[i].print_with_subs();
		}






		Sources.Loops.append(LoopCodeGen(Sources.R[i], 0));

if(PAR_SOURCES){
 //   Sources.Loops[i] = replace_str(str(Sources.Loops[i]), (const char*)"for", (const char*)"par for");

        // pragmy
        // przerobic by lapal wszystkie petle, liczyc klamry

        std::string p_loop(str(Sources.Loops[i]));
        std::vector<std::string> strs, strs2;
        boost::split(strs, p_loop, boost::is_any_of("\n"));
        boost::match_flag_type flags = boost::match_default;
		std::string::const_iterator _s, _e;

        size_t found;

        string str2 = str("for(");
        string _bopen = str("{");
        string _bclose = str("}");
        string priv_vars = "private(";


        int bylo = 0;
        int _br = 0;

        for(int _z=0; _z<strs.size(); _z++)
        {
            found=strs[_z].find(str2);
            if (found!=string::npos)
            {
                _s = strs[_z].begin();
                _e = strs[_z].end();

                boost::regex _pattern1("(for\\([A-Za-z_]+[A-Za-z_\\d]*)");
                boost::match_results<std::string::const_iterator> _res1;

				boost::regex_search(_s, _e, _res1, _pattern1, flags);

				std::string _var(_res1[1].first, _res1[1].second);

                boost::replace_all(_var, "for(", "");

				priv_vars += _var + ",";
            }
        }

        priv_vars[priv_vars.length()-1] = ')';

        for(int _z=0; _z<strs.size(); _z++)
        {
            string pragma = str("#pragma omp parallel for ");
            //pragma += priv_vars;


            // different member versions of find in the same order as above:
            found=strs[_z].find(str2);
            if (found!=string::npos && bylo == 0)
            {
                strs2.push_back(pragma);
                bylo = 1;
            }

            // nie pragmuj wewnetrznych petli
            if(bylo)
            {
                found=strs[_z].find(_bopen);
                if(found!=string::npos)
                    _br++;

                found=strs[_z].find(_bclose);
                if(found!=string::npos)
                    _br--;

                if(_br==0)
                    bylo = 0;
            }


            strs2.push_back(strs[_z]);

        }

        string out_loop = "";
        for(int _z=0; _z<strs2.size(); _z++)
            out_loop += strs2[_z] + "\n";

        out_loop = out_loop.substr(0, out_loop.size()-1);

        if(1)
            Sources.Loops[i] = out_loop.c_str();

        // --------------------


}
        if(!_SILENT)
		if(display)
		{
			printf("\n\nPetla 1:\n");
			PrintString(Sources.Loops[i]);
			printf("\n");
		}



		//GenerateChainsWhileLoopFromSourcesOfSlices(BaseRel.R, Sources.R[i], false);

	}

	Sources.R_UCS_list = *R_UCS_list;
	return Sources;
}
