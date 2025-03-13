void Gen_Code_Scan_Slices(ComplexRelation BaseRel)
{
	Tuple<Relation> *R_UCS_list = new Tuple<Relation>;
	Rel_Struct Sources = FindSourcesOfSlices(BaseRel, R_UCS_list, 0);

	printRelations(*R_UCS_list, 0);

}


Relation GET_S_Slice(Relation R, Relation R_UCS, Relation I, bool with_iterations = true, bool display = false)
{
	Relation S_Slice;
	Relation R_s, R_UCS_s, RSUCSI;
	int i;



	R = RepairNameVar(R);
	//R.print();
	R = Repair_Relation(R);

	R_s = Star(copy(R));

	if(R_s.is_inexact())
		R_s = Upper_Bound(copy(R_s));


	//R_s.print();

	/* eksperymentalnie */
	//R_s = Try;
	/* ---------------- */

//R = Repair_Relation(R);
//printf("\n****\n");
//	R_UCS.print();
    R_UCS.simplify();

	if(R_UCS.number_of_conjuncts() < 1)
		R_UCS_s = R_UCS;
	else
		R_UCS_s = Star(copy(R_UCS));
	//if(display)

	//R_UCS_s.print();

	if(R_UCS.number_of_conjuncts() < 1)
		RSUCSI = I;
	else
	{
		RSUCSI = Range(Restrict_Domain(copy(R_UCS_s), copy(I)));
		if(display)
		{
		printf("RSUCSI");
		RSUCSI.print();
		}
		RSUCSI.simplify();
	}

	if(display)
	{
		printf("Poczatki pozostale : \n");
		PrintString(LoopCodeGen(RSUCSI, 0));

	}
	if(with_iterations)
	{
		S_Slice = Range(Restrict_Domain(copy(R_s), copy(RSUCSI)));
		//RSUCSI.print();
		//printf("!!!!!");
		//R_s.print();
		//S_Slice.print();
	}
	else
		S_Slice = RSUCSI;

	S_Slice = RepairNameVar(S_Slice);
	//printf("\nS_SLICE");

	//S_Slice.print();

	S_Slice.simplify();
	if(display)
		S_Slice.print();
	for(i=1; i<=S_Slice.n_inp(); i++)
	{
		Variable_ID vv = S_Slice.set_var(i);
		String nazwa = vv->name();
		if(strcmp(nazwa, "v'")==0)
			S_Slice.name_set_var(i, "v");
	}

	if(display)
		printf("\nS_Slice\n");
	S_Slice.simplify();
	S_Slice = SimplifyNumConjuncts(S_Slice);
	//S_Slice = InteSymp(S_Slice);

/*

	//wlasne ograniczenia

	F_And *fa = S_Slice.and_with_and();
	GEQ_Handle geq = fa->add_GEQ();
	Variable_ID vv1n = S_Slice.get_local(&vv1);
	geq.update_coef(vv1n, 1);
	geq.update_const(-1);
	geq = fa->add_GEQ();
	geq.update_coef(vv1n, -1);
	geq.update_const(2);

	// -----------

*/
	S_Slice.simplify();

	if(display)
		S_Slice.print();



	return S_Slice;

}

Relation GET_Rprim(Relation S_Slice)
{
	Relation Rprim;
	int i;
	String nazwa;

	Rprim = Cross_Product(copy(S_Slice), copy(S_Slice));


	F_And *fand = Rprim.and_with_and();
	Add_Lexographic_Order2(Rprim, fand);


	fand = Rprim.and_with_and();
	F_Not *fnot = fand->add_not();
	F_Exists *fex = fnot->add_exists();

	F_And *fex_and = fex->add_and();

	Variable_ID ex[10];	// to tablica zmiennych e''
	Tuple<Variable_ID> ex_tuple, in_tuple, out_tuple;

	// pobierz nazwy do exists e''
	for(i=1; i<=Rprim.n_inp(); i++)
	{
		nazwa =  Rprim.input_var(i)->name();
		nazwa += "''";
		ex[i-1] = fex->declare(nazwa);
		ex_tuple.append(ex[i-1]);
		in_tuple.append(Rprim.input_var(i));
		out_tuple.append(Rprim.output_var(i));
	}

	S_Add_Exist2(S_Slice, Rprim, fex_and, ex);

	Add_Lexographic_Order2(Rprim, fex_and, in_tuple, ex_tuple);
	Add_Lexographic_Order2(Rprim, fex_and, ex_tuple, out_tuple);

	printf("R' b\n");
	Rprim.print();

	Rprim.simplify();



	if(Rprim.number_of_conjuncts() > 100)
	{
		printf("R' is too complicated! %i ", Rprim.number_of_conjuncts());
		exit(0);
	}


	//Rprim.print();

	return Rprim;
}

// GLOWNA FUNKCJA
void GenCodeScanSlices(Rel_Struct Sources, ComplexRelation BaseRel, String IND_LOOP, bool codegen, Tuple<String> *petle = NULL, bool display = true)
{
	int i, j, n;
	n = Sources.Loops.length();
	   // printRelations(BaseRel.R, 1);
            Relation RRR = globalUnion(BaseRel.R);



	Relation Temp_S_Slice;

	for(i=1; i<=n; i++)
	{


		if(0)
            Sources.L_I[i] = ExtractSetsFromLoop(Sources.Loops[i]);
        else
            Sources.L_I[i] = ExtractSetsFromLoop_AndReduce(Sources.Loops[i], Sources.R[i]);


         //  printf("-%i-\n", Sources.L_I[i].length());

		if(display)
			printf("\n\nPetla 1:\n%s", str(Sources.Loops[i]));
		String TmpL = "";
		std::string fb(str(Sources.Loops[i]));

		boost::regex pattern("(^\\s*s1[^;]*\\);)");
		boost::match_results<std::string::const_iterator> res;
		boost::match_flag_type flags = boost::match_default;
		std::string::const_iterator s , e, _s, _e;
		s = fb.begin();
		e = fb.end();
		_s = s;


		std::string url1;
		std::string::const_iterator s1 , e1;



		for(j=1; j<=Sources.L_I[i].length(); j++)
		{

            if(display)
			{
				printf("\n%i: ", j);
				Sources.L_I[i][j].print();
	 		}

			// wlasciwa R'
            Relation RRR = globalUnion(BaseRel.R);
            if(!_SILENT)
            RRR.print();

           //  Sources.R_UCS_list[i].print();
            // Sources.L_I[i][j].print();
            //cout << Sources.L_I[i].length();


			Temp_S_Slice =  GET_S_Slice(RRR, Sources.R_UCS_list[i] , Sources.L_I[i][j] );



			Temp_S_Slice = ReduceSet(Temp_S_Slice);
			Temp_S_Slice = SimplifyNumConjuncts(Temp_S_Slice);
			Temp_S_Slice.simplify(2, 4);

            //printf("ooo");
			Relation X = Hull(copy(Temp_S_Slice));
			Relation _Z1 = Difference(copy(Temp_S_Slice), copy(X));
			Relation _Z2 = Difference(copy(X), copy(Temp_S_Slice));
			_Z1.simplify(); _Z2.simplify();
			if(_Z1.number_of_conjuncts() == 0 && _Z2.number_of_conjuncts() == 0)
               Temp_S_Slice = X;



			//Temp_S_Slice.print();

			if(codegen)
			{


                            String Tmpp;

				Relation CDG = copy(Temp_S_Slice);
				//CDG = SimplifyNumConjuncts(CDG);
				//if(display)
			//	printf("!!!!");
			if(!_SILENT)
				CDG.print();
               // Temp_S_Slice.print();

                                    FILE *_file;
                                    _file = fopen("names_info.txt", "w");
                                    for(int yy = 1; yy <= CDG.n_set(); yy++)
                                    {
                                        fprintf(_file, CDG.set_var(yy)->name());
                                        if( yy < CDG.n_set())
                                            fprintf(_file, ",");

                                    }
                                    fclose(_file);


double b6 = gettime();
                                //printf("\n--------> Czas obliczenia poczatkow: %.2f\n", (double)((end2 - begin2)));
if(!_SILENT)
printf("\n%s", str(LoopCodeGen(CDG, 0)));
				if(petle == NULL)
				{
                    if(!_SILENT)
					printf("\n%s", str(LoopCodeGen(CDG, 0)));

				}
				else
				{
					Tmpp = LoopCodeGen(CDG, 0);
					//petle->append(Tmpp);
				}
                                double e6 = gettime();
                                if(!_SILENT)
                                printf("\n--------> Czas obliczenia poczatkow: %.2f\n", (double)((e6 - b6)));


            //    printf("\n%s", str(LoopCodeGen(CDG, 0)));


				boost::regex_search(_s, e, res, pattern, flags);



				s1 = res[1].first;
				e1 = res[1].second;






				//std::string tab(s1, e1);
				boost::regex pattern2("(^\\s*[^s])");
				boost::match_results<std::string::const_iterator> res2;

				boost::regex_search(s1, e1, res2, pattern2, flags);

				std::string tab(res2[1].first, res2[1].second);
				String Tabb = tab.c_str();

                //przesun kod o tabulacje wciecia, funkcja replace z lib.h
				Tmpp = replace(Tmpp, "\n", "\n" + Tabb );




				//if(j==1)
					url1 = std::string(_s, s1);
				//else{
				//	url1 = std::string(res[j-1].second, s1);
				//}

				TmpL = TmpL + url1.c_str() +  Tabb + Tmpp;
				_s = e1;


			}
			else
			{

				Sources.Rprim[i].append(GET_Rprim(Temp_S_Slice));

				Sources.Rprim[i][j] = SimplifyNumConjuncts(Sources.Rprim[i][j]);
				Sources.Rprim[i][j] = ReduceSet(Sources.Rprim[i][j]);


				//printf("\nR' ----------------\n");
				Sources.Rprim[i][j].simplify();
				//Sources.Rprim[i][j].print_with_subs();


				Tuple <Relation> Rels = Divide_Relation(Sources.Rprim[i][j]);

				ComplexRelation Bas;
				//ComplexRelation *d = new ComplexRelation;
				Bas.R = Rels;
				//printRelations(Bas.R);

        // !!!! LINUX
        // DO IMPLEMENTACJI
				GenerateChainsSingleWhileLoop(Sources.Rprim[i][j], Sources.Loops[i], false);
			}

		}

		//dopisz for do generated.txt
		if(!codegen)
		{
			// !!!! LINUX
			// DO IMPLEMENTACJI
			All_GenerateChains(Sources.Loops[i], i, n, IND_LOOP);
		}

		if(codegen)
		{


                    //PrintString(TmpL);

                    url1 = std::string(e1, e);
			TmpL = TmpL + url1.c_str();
			if(petle != NULL)
				petle->append(TmpL);


		}


	}


}




