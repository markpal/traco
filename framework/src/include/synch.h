
ComplexRelation S1_R;
Rel_Struct S1_Sources;

//zwraca numery relacji nalezacych do s1
class S1S2
{
	public :
		Tuple<int> s1;
		Tuple<int> s2;
};

//zawiera wszystko niezbedne do wygenerowania kodu
class Synchr_Combo
{
	public:
		Tuple<String> loops_slice;
		//int I[100];  //z ktorej wychodza instrukcje jest w S1_Sources
		String IND_LOOP;
		Tuple<Relation> Rki[255];  //a moze potem tyablica dla roznych sources [255]
		Tuple<Relation> IRki[255];

		Tuple<Relation> Loop_vec[255]; //wektory w petli w sliceach

		Tuple<String> BackVec[20][20]; //wektory tablica pierwszy wymiar slice, drugi s1
		Tuple<String> ForwVec[20]; //send
		Tuple<String> SupForwVec[20][20]; //wektory tablica pierwszy wymiar slice, drugi s1
		Relation S_S2;

};




S1S2 FormS1(ComplexRelation BaseRel, int display, int sort)
{
	int n = BaseRel.R.length();
	int i;
	S1S2 zbiory;
	Rel_Struct Sources;
	ComplexRelation Tmp;
	Tmp.From = BaseRel.From; Tmp.To = BaseRel.To;
	Tuple<int> relacje;
	Tuple<int> zostalo;

	//posortuj relacje wedlug zawierania
	if(sort)
		relacje = SortRelations(BaseRel.R);
	else
		for(i=1; i<=n; i++)
			relacje.append(i);


	for(i=1; i<=n; i++)
	{
		//printf("-----------------------------%i\n", relacje[i]);
		Relation R = BaseRel.R[relacje[i]];

		//sprawdz czy wciaz mamy wiecej niz 1 slice, oblicz w tym celu sources

		Tmp.R.append(copy(R));
		int y = Tmp.R.length();
		Tmp.From[y] = BaseRel.From[relacje[i]];
		Tmp.To[y] = BaseRel.To[relacje[i]];
		Tmp.DepVect.append(BaseRel.DepVect[relacje[i]]);
		Tmp.VecType.append(BaseRel.VecType[relacje[i]]);


		// tu trzeba wyciagnac I !!!!


		Sources = CalcSources(Tmp, 0);



		if(Sources.R.length() == 1 && GetVecType(Sources.R[1]))
		{
			 // 1 slice tylko

			Tmp.R.delete_last();
			Tmp.DepVect.delete_last();
			Tmp.VecType.delete_last();



			if(zbiory.s1.length() > 0)
			{
				zbiory.s2.append(relacje[i]);
				if(display)
					printf("\nRelacja nr %i zostaje odrzucona do S2\n", i);
			}
			else
				zostalo.append(relacje[i]);

		}
		else
		{
			zbiory.s1.append(relacje[i]);
			if(display)
				printf("\nRelacja nr %i zostaje dołšczona do S1\n", i);
		}

	}


	for(i=zostalo.length(); i>=1; i--)
	{
		//printf("-----------------------------%i\n", relacje[i]);
		Relation R = BaseRel.R[zostalo[i]];

		//sprawdz czy wciaz mamy wiecej niz 1 slice, oblicz w tym celu sources

		Tmp.R.append(copy(R));
		int y = Tmp.R.length();
		Tmp.From[y] = BaseRel.From[zostalo[i]];
		Tmp.To[y] = BaseRel.To[zostalo[i]];
		Tmp.DepVect.append(BaseRel.DepVect[zostalo[i]]);
		Tmp.VecType.append(BaseRel.VecType[zostalo[i]]);


		// tu trzeba wyciagnac I !!!!


		Sources = CalcSources(Tmp, 0);
		//Sources.R[1].print();


		if(Sources.R.length() == 1 && GetVecType(Sources.R[1]))
		{
			 // 1 slice tylko

			Tmp.R.delete_last();
			Tmp.DepVect.delete_last();
			Tmp.VecType.delete_last();

			if(display)
				printf("\nRelacja nr %i zostaje odrzucona do S2\n", i);

			zbiory.s2.append(zostalo[i]);

		}
		else
		{
			zbiory.s1.append(zostalo[i]);
			if(display)
				printf("\nRelacja nr %i zostaje dołšczona do S1\n", i);
		}
	}




	S1_R = Tmp;
	S1_Sources = CalcSources(Tmp, 0);

	if(display)
	{
		printf("\nS1 ");
		if(zbiory.s1.length() > 0)
		for(i=1; i<=zbiory.s1.length(); i++)
			printf("%i ", zbiory.s1[i]);
		printf("\nS2 ");
		if(zbiory.s2.length() > 0)
		for(i=1; i<=zbiory.s2.length(); i++)
			printf("%i ", zbiory.s2[i]);
	}

	return zbiory;
}


void Synch(ComplexRelation BaseRel, String IND_LOOP, int aggl)
{
	Synchr_Combo SCombo; //klasa zawierajaca dane niezbedne do wygenerowania kodu

	S1S2 s1s2_sets = FormS1(BaseRel, 1, 0);  // tu daj I z klasy Combo

	Relation S_S2;
	int i, j, k, n, to;
	int num_Rel; // numer relacji S2
	Relation Tmp;

	// Initialize COM.
       // void* args1[1];
       // void* args3[3];
       // void* args2[2];
       // MonoObject *obj = GetObject("SynchClass");
      //  MonoMethod *met = GetMethod("AddLoopSlice");
      //  MonoString *str1;

        CodeEngine::SynchClass *sc  = new CodeEngine::SynchClass();


	Relation S_Comm;
	n = s1s2_sets.s2.length();

	for(i=1; i<=n; i++)
	{
		if(i==1)
			S_Comm = BaseRel.R[s1s2_sets.s2[i]];
		else
			S_Comm = Union(copy(S_Comm), copy(BaseRel.R[s1s2_sets.s2[i]]));
	}

	Relation S1_set;

	for(i=1; i<=s1s2_sets.s1.length(); i++)
	{
		if(i==1)
			S1_set = BaseRel.R[s1s2_sets.s1[i]];
		else
			S1_set = Union(copy(S1_set), copy(BaseRel.R[s1s2_sets.s1[i]]));
	}
	S1_set = Union(Domain(copy(S1_set)), Range(copy(S1_set)));

	if(n >= 1)
	{
		S_S2 = Domain(copy(S_Comm));
		S_Comm = Union(Domain(copy(S_Comm)), Range(copy(S_Comm)));


		S_Comm = InteSymp(S_Comm);
		S_S2 = InteSymp(S_S2);

		//uprosc potem jeszcze extra zbor S_Comm, S_S2
		S_Comm.print();
		S_S2.print();

		S1_set = Intersection(copy(S1_set), copy(S_Comm));
		printf("\n\nMutex init \n%s\n\n", str(LoopCodeGen(S1_set, 0)));
	}


	// dla wszystkich relacji w S2
	for(i=1; i<=s1s2_sets.s2.length(); i++)
	{
		num_Rel = s1s2_sets.s2[i];
		to = BaseRel.To[num_Rel-1];

		for(j=1; j<=S1_Sources.R.length(); j++)
		{
			if(S1_Sources.I[j-1] == to)
			{

				//oblicz range , IR dodaj pod j
				Tmp = BaseRel.R[num_Rel];
				Tmp = InteSymp(Tmp);

				SCombo.Rki[j].append(Tmp);

				Tmp = Inverse(copy(BaseRel.R[num_Rel]));
				Tmp = InteSymp(Tmp);

				SCombo.IRki[j].append(Tmp);

				//SCombo.Ri[j].append(copy(BaseRel.R[num_Rel]));



			}
		}
	}

	//oblicz slice dla poczatkow i dodaj do klasy
	// dodaj indloop i s_s2
	SCombo.S_S2 = S_S2;

	ComplexRelation W;
	for(i=1;i<=s1s2_sets.s1.length(); i++)
	{

		W.R.append(BaseRel.R[s1s2_sets.s1[i]]);
		W.R[i].print();
	}

	printf("poczatki\n");
	for(i=1;i<=S1_Sources.R.length(); i++)
	{
		S1_Sources.R[i].print();
		printf("\n%s", str(S1_Sources.Loops[i]));

	}


	GenCodeScanSlices(S1_Sources, W, "", true, &SCombo.loops_slice, true);

	for(i=1; i<=SCombo.loops_slice.length(); i++)
        {
              //  str1 = mono_string_new (domain, str(SCombo.loops_slice[i])); args1[0] = str1;
              //  mono_runtime_invoke (met, obj, args1, NULL);

                sc->AddLoopSlice(Str2string(SCombo.loops_slice[i]));


        }


	// zczytaj wektory z petli

	for(i=1; i<=SCombo.loops_slice.length(); i++)
	{
		printf("\n\nESys: \n%s", str(SCombo.loops_slice[i]));

		SCombo.Loop_vec[i] = ExtractSetsFromLoop(SCombo.loops_slice[i]);

	}


	for(i=1; i<=SCombo.loops_slice.length(); i++)
		for(j=1; j<=SCombo.Loop_vec[i].length(); j++)
		{

			//SCombo.Loop_vec[i][j].print_with_subs();
		}



	//SCombo.IRki[1][1].print();

	//Relation Z = Range(Restrict_Domain(copy(SCombo.IRki[1][1]), copy(SCombo.Loop_vec[1][1])));



	if(S_S2.number_of_conjuncts() > 0)
	for(i=1; i<=SCombo.loops_slice.length(); i++)
		for(j=1; j<=SCombo.Loop_vec[i].length(); j++)
		{
			Relation Temp = Intersection(copy(S_S2), copy(SCombo.Loop_vec[i][j]));
			SCombo.ForwVec[i].append(Temp.print_with_subs_to_string());
			printf("$$$ %s", str(Temp.print_with_subs_to_string()));


                   //     met = GetMethod("AddForwVec");
                    //    str1 = mono_string_new (domain, str(SCombo.ForwVec[i][j]));
                    //    args2[0] = str1;
                   //     args2[1] = &i;
                   //     mono_runtime_invoke (met, obj, args2, NULL);
                   sc->AddForwVec(Str2string(SCombo.ForwVec[i][j]), i);

			for(k=1; k<=SCombo.IRki[i].length(); k++)
			{
				Temp = Range(Restrict_Domain(copy(SCombo.IRki[i][k]), copy(SCombo.Loop_vec[i][j])));
				SCombo.BackVec[i][j].append(Temp.print_with_subs_to_string());
				printf("!! %s", str(Temp.print_with_subs_to_string()));



                               // met = GetMethod("AddBackVec");
                               // str1 = mono_string_new (domain, str(SCombo.BackVec[i][j][k]));
                              //  args3[0] = str1;
                              //  args3[1] = &i;
                              //  args3[2] = &j;
                              //  mono_runtime_invoke (met, obj, args3, NULL);

                    sc->AddBackVec(Str2string(SCombo.BackVec[i][j][k]), i, j);

				//------
				Temp = Range(Restrict_Domain(copy(SCombo.Rki[i][k]), copy(SCombo.Loop_vec[i][j])));
				SCombo.SupForwVec[i][j].append(Temp.print_with_subs_to_string());

                              //  met = GetMethod("AddSupForwVec");
                               // str1 = mono_string_new (domain, str(SCombo.SupForwVec[i][j][k]));
                               // args3[0] = str1;
                               // args3[1] = &i;
                               // args3[2] = &j;
                               // mono_runtime_invoke (met, obj, args3, NULL);

                    sc->AddSupForwVec(Str2string(SCombo.SupForwVec[i][j][k]), i, j);

				printf("## %s",str(Temp.print_with_subs_to_string()));

			}
		}

	//printf("***********");



     //   met = GetMethod("SetIndLoop");
     //   str1 = mono_string_new (domain, str(IND_LOOP)); args1[0] = str1;
      //  mono_runtime_invoke (met, obj, args1, NULL);

        sc->SetIndLoop(Str2string(IND_LOOP));

	printf("*****************************************\n\n");


	String ag = aggl == 1 ? "1" : "0";


   //     met = GetMethod("Debug");
   //     str1 = mono_string_new (domain, ag); args1[0] = str1;
   //     mono_runtime_invoke (met, obj, args1, NULL);

	// MonoClear();

    std::string petla = sc->Debug(Str2string(ag));
    cout << endl << endl << petla;


}


Free_Var_Decl lb("lb");
Free_Var_Decl ub("ub");

Relation AddAgglomeration(Relation R)
{
	Variable_ID R_lb = R.get_local(&lb);
	Variable_ID R_ub = R.get_local(&ub);
	Variable_ID var = R.set_var(1);

	F_And *fa = R.and_with_and();
	GEQ_Handle geq = fa->add_GEQ();
	geq.update_coef(R_ub, -1);
	geq.update_coef(var, 1);

	geq = fa->add_GEQ();
	geq.update_coef(R_lb, 1);
	geq.update_coef(var, -1);


	return R;

}
