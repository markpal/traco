// Algorytmy z artykulu Krzyska

// Proba skasowania wlasnych relacji tranzytywnych
int algorytm0(ComplexRelation BaseRel, ComplexRelation *BaseOut, int disp)
{
	Relation R, Temp1, Temp2;
	int i;
	int a,b;

	BaseOut->From = BaseRel.From;
	BaseOut->To = BaseRel.To;

	for(i=1; i<=petitRelations.length(); i++)
	{

		R = TransitiveReduction(copy(BaseRel.R[i]));

		// Jesli mamy relacje tozsamosci to uzyskamy tu relacje FALSE, to dobra okazja by takie usunac
		if( R.number_of_conjuncts() ==0 )
			continue;


		// Sprawdz czy relacja jest taka sama po obliczeniu
		Temp1 = Difference(copy(R), copy(BaseRel.R[i]));
		Temp2 = Difference(copy(BaseRel.R[i]), copy(R));
		// jesli a i b = 0 to nic sie nie zmienilo

		a = Temp1.number_of_conjuncts();
		b = Temp2.number_of_conjuncts();
		// -----------------------------

		if(!R.is_unknown() && (a>0 || b>0) )
		{
			if(disp)
			{
			printf("Zamieniam: ");
			BaseRel.R[i].print();
			printf(" na ");
			R.print();
			printf("\n");
			}

			BaseOut->R.append(R);

			//Obliczenie wektora zaleznosci na nowo dla relacji
			BaseOut->DepVect.append(RelToDepVec(R));
			//BaseOut->VecType.append(BaseRel.VecType[i]);
			//Ponowne ustalenie typu wektora
			BaseOut->VecType.append(GetVecType(BaseOut->DepVect[i]));
		}
		else
		{
			BaseOut->R.append(BaseRel.R[i]);
			BaseOut->DepVect.append(BaseRel.DepVect[i]);
			BaseOut->VecType.append(BaseRel.VecType[i]);
		}
		BaseOut->From[i] = BaseRel.From[i];
		BaseOut->To[i] = BaseRel.To[i];
		BaseOut->SCC[i] = BaseRel.SCC[i];
	}

	return 0;
}

// Proba skasowania wlasnych relacji tranzytywnych wedlug artykulu Pugh
int algorytm02(ComplexRelation BaseRel, ComplexRelation *BaseOut, int disp)
{
	Relation globR, globRplus, globSS, globNEW, Ra, Rb;
	int i;

	globR = globalUnion(BaseRel.R);
       // printf("Star\n");
	globRplus = Star(copy(globR), 1);
	globSS = Composition(copy(globRplus), copy(globR));
	globSS.simplify();

	globR = Difference(copy(globR), copy(globSS));
	globR.simplify(2, 5);
        globR = Repair_Relation(globR);


    //    globR.print();



	//BaseOut->From = BaseRel.From;
	//BaseOut->To = BaseRel.To;

	for(i=1; i<=BaseRel.R.length(); i++)
	{
          //  int dodac = 1;
                BaseRel.R[i] = Repair_Relation(BaseRel.R[i]);
		//BaseRel.R[i].print();

                Relation W = Intersection(copy(BaseRel.R[i]), copy(globR));
                W = Repair_Relation(W);

		W.simplify(2, 5);
               // W.print();

		// Jesli mamy relacje tozsamosci to uzyskamy tu relacje FALSE, to dobra okazja by takie usunac
		if(W.number_of_conjuncts() ==0 )
			continue;


		BaseOut->R.append(BaseRel.R[i]);
		BaseOut->DepVect.append(BaseRel.DepVect[i]);
		BaseOut->VecType.append(BaseRel.VecType[i]);
                BaseOut->Type.append(BaseRel.Type[i]);
		BaseOut->From.append(BaseRel.From[i]);
		BaseOut->To.append(BaseRel.To[i]);
		BaseOut->SCC.append(BaseRel.SCC[i]);
		BaseOut->Var.append(BaseRel.Var[i]);
		BaseOut->Line.append(BaseRel.Line[i]);
	}

	//printf("\n!!!\n");
        Relation N = globalUnion(BaseOut->R);



       // printRelations(BaseOut->R, 1);
        N.simplify(2,5);
       // N.print();
     //   printf("Star\n");
	globNEW = Star(N, 1);
	Ra = Difference(copy(globRplus), copy(globNEW));
	Rb = Difference(copy(globNEW), copy(globRplus));
        Ra.simplify(); Rb.simplify();
        if(!_SILENT){
        if(Ra.number_of_conjuncts() ==0  && Ra.number_of_conjuncts() ==0)
           printf("OK\n");
        else
        {
           printf("Blad!\n");
           //exit(1);
        }
        }


    //sprawdz czy BaseOut i BaseRel + jest ten sam
	return 0;
}


// Proba skasowania wlasnych relacji tranzytywnych wedlug artykulu Pugh
int algorytm02a(ComplexRelation BaseRel, ComplexRelation *BaseOut, int disp)
{
		Relation Ra, Rb;
	int i,dodac;


	for(i=1; i<=BaseRel.R.length(); i++)
	{
  //  printf("%i",BaseOut->R.length());

          dodac=1;
                BaseRel.R[i] = Repair_Relation(BaseRel.R[i]);
		//BaseRel.R[i].print();

                for(int q = 1; q<=BaseOut->R.length(); q++)
                {
                    Ra = Difference(copy(BaseRel.R[i]), copy(BaseOut->R[q]));
                    Rb = Difference(copy(BaseOut->R[q]), copy(BaseRel.R[i]));
                    Ra.simplify(); Rb.simplify();
                    if(Ra.number_of_conjuncts() ==0  && Ra.number_of_conjuncts() ==0)
                        dodac = 0;
                }
                if(!dodac)
                    continue;


		BaseOut->R.append(BaseRel.R[i]);

		BaseOut->DepVect.append(BaseRel.DepVect[i]);
		BaseOut->VecType.append(BaseRel.VecType[i]);
        BaseOut->Type.append(BaseRel.Type[i]);

		BaseOut->From.append(BaseRel.From[i]);
		BaseOut->To.append(BaseRel.To[i]);

		BaseOut->SCC.append(BaseRel.SCC[i]);

        BaseOut->Var.append(BaseRel.Var[i]);
		BaseOut->Line.append(BaseRel.Line[i]);
	}

	return 0;
}

// Proba skasowania wlasnych relacji tranzytywnych - nowy pomysl WB
//algroytm musi byc wykonany po algorytmie 02a, nie może byc identycznych relacji !!!!!!!!!!!!!
// inaczej jest niepoprawny bo wykasuje obie relacje
int algorytm02b(ComplexRelation BaseRel, ComplexRelation *BaseOut, int disp)
{
	Relation tmpRi, tmpRq, out;
	int i;

	for(i=1; i<=BaseRel.R.length(); i++)
	{
            int dodac = 1;

                tmpRi= Star(copy(BaseRel.R[i]), 1);

                for(int q = 1; q<=BaseRel.R.length(); q++)
                {
                    if(q!=i)
                    {
                        tmpRq= Star(copy(BaseRel.R[q]), 1);

                        out = Difference(copy(tmpRi), copy(tmpRq));
                        out.simplify();
                        if(out.number_of_conjuncts() ==0)
                            dodac = 0;
                    }
                }
                if(!dodac)
                    continue;


		BaseOut->R.append(BaseRel.R[i]);
		BaseOut->DepVect.append(BaseRel.DepVect[i]);
		BaseOut->VecType.append(BaseRel.VecType[i]);
		BaseOut->From.append(BaseRel.From[i]);
		BaseOut->To.append(BaseRel.To[i]);
		BaseOut->SCC.append(BaseRel.SCC[i]);

        BaseOut->Var.append(BaseRel.Var[i]);
		BaseOut->Line.append(BaseRel.Line[i]);

	}



    //sprawdz czy BaseOut i BaseRel + jest ten sam
	return 0;
}


// poprawiona wersja


// ALGORYTM 1

// Algorytm usuwania nadmiarowych zaleznosci

// Algorithm 1. Removing redundant dependences
// Removing the same depences except the only one

int algorytm1(ComplexRelation BaseRel, ComplexRelation *BaseOut, int disp)
{


	Tuple<Relation> petitRelations = BaseRel.R;

	int i = 0, liczba_par, i_R,j_R, j;
	Tuple<Relation> outputRelations;
	Tuple<Relation> tmpRelations = petitRelations;
	Tuple<bool> tmpRelationsVecType;
	Tuple<Relation> tmpDepVector;

	if(disp)
	{
		printf("\n\n===========================================================\n\n");
		printf("ALGORYTM 1\n");
	}

	// Struktura relacji i numerow relacji z jakich powstala
	struct RiRj
	{
		int i,j;
		Relation RiAndRj[1], Difij[1], Difji[1];
	};


	if (petitRelations.length() < 2)  //relacji mniej niz 2, wtedy aqlgorytm nic nie wykonuje
	{
		*BaseOut = BaseRel;

		if(disp)
		{
		printRelations(tmpRelations);
		printf("===========================================================\n");
		}

		return -1;
	}



	// =========================================================

	// Obliczenie liczby wszystkch par

	liczba_par = 1;
	for(i = 3; i<=petitRelations.length(); i++)
		liczba_par += i-1;

	if(disp)
		printf("Liczba par Ri, Rj = %i.\n\n", liczba_par);



	// ===========================================================
	// Krok 1. Rij = Ri and Rj dla kazdej pary Ri Rj gdzie i<>j

	RiRj *Relacje;   //Relacje wspolnej czesci  Ri/\Rj
	Relacje = new RiRj[liczba_par+1];
	//int do_skasowania[100]; // liczyc od jednego

	int *do_skasowania;
	do_skasowania = new int[petitRelations.length()+1];

	for(i=0; i<petitRelations.length()+1; i++)
		do_skasowania[i]=0;

	i = 1;

	for(i_R=1; i_R<=petitRelations.length()-1; i_R++)
		for(j_R=i_R+1; j_R<=petitRelations.length(); j_R++)
		{
			Relacje[i].RiAndRj[0] = Intersection(copy(petitRelations[i_R]), copy(petitRelations[j_R]));
			Relacje[i].i = i_R;
		    Relacje[i].j = j_R;
		//	printf("\nR%i/\\R%i = ",Relacje[i].i, Relacje[i].j);
	//		printf("%i:.\t", i);
			//Relacje[i].RiAndRj[0].print_with_subs();

			// W tablicy Relacje[liczby_par] mamy pary Ri /\ Rj
			// =========================================================

			// Krok 2. Roznice Difij i Difji


			if(Relacje[i].RiAndRj[0].number_of_conjuncts()>0)
			{
				Relacje[i].Difij[0] = Difference(copy(petitRelations[i_R]), copy(petitRelations[j_R])); // Difij = Ri - Rj;
				Relacje[i].Difji[0] = Difference(copy(petitRelations[j_R]), copy(petitRelations[i_R])); // Difij = Rj - Ri;

				if(Relacje[i].Difij[0].number_of_conjuncts()==0 && Relacje[i].Difji[0].number_of_conjuncts() > 0) //If Difij = FALSE Remove Ri
					do_skasowania[i_R]=1;
				if((Relacje[i].Difji[0].number_of_conjuncts()==0 && Relacje[i].Difij[0].number_of_conjuncts() > 0)
					|| (Relacje[i].Difji[0].number_of_conjuncts()==0 && Relacje[i].Difij[0].number_of_conjuncts()==0)) //If Difji = FALSE  OR Difij = Difji = False Remove Rj
					do_skasowania[j_R]=1;

				// Krok 3. Difij i Difji <> FALSE
				if((Relacje[i].Difij[0].number_of_conjuncts()>0) && (Relacje[i].Difji[0].number_of_conjuncts()>0))
					tmpRelations[i_R] = Difference(copy(tmpRelations[i_R]), copy(Relacje[i].RiAndRj[0]));
			}
			i++;
		}



    printf("ppp\n");
	// Przygotuj dane wyjsciowe

	j=1;
	for(i=1; i<=petitRelations.length(); i++)
	{
		if(do_skasowania[i]==0 && tmpRelations[i].number_of_conjuncts() > 0)
		{
                printf("ppp\n");
			BaseOut->R.append(tmpRelations[i]);
			//BaseOut->DepVect.append(BaseRel.DepVect[i]);
			//Obliczenie wektora zaleznosci na nowo dla relacji
			BaseOut->DepVect.append(RelToDepVec(tmpRelations[i]));

			//BaseOut->VecType.append(BaseRel.VecType[i]);
			// LINUX -wektor powinmien zostac na nowo obliczony, funkcja do poprawy
			// ponizsza linia kodu w komentarzu docelowo powinna zastapic powyzsza
			//Ponowne ustalenie typu wektora
		//	BaseOut->VecType.append(GetVecType(BaseOut->DepVect[j]));



			BaseOut->From.append(BaseRel.From[i]);
			BaseOut->To.append(BaseRel.To[i]);
			BaseOut->SCC.append(BaseRel.SCC[i]);
			j++;

		}

	}

	if(disp)
	{
	printRelations(BaseOut->R);
	printf("========================================================\n");
	}

	delete do_skasowania;
printf("========================================================\n");
	return 0;

}


int algorytm2(ComplexRelation BaseRel, ComplexRelation *BaseOut, const int DISPL)
{

	Tuple<Relation> outputRelations = BaseRel.R;
	Tuple<bool> petitRelationsVecType = BaseRel.VecType;
	Tuple<Relation> petitDepVector = BaseRel.DepVect;
	BaseOut->From = BaseRel.From;
	BaseOut->To = BaseRel.To;


	if (petitRelations.length() < 2)  //relacji mniej niz 2, wtedy aqlgorytm nic nie wykonuje
	{
		*BaseOut = BaseRel;

		if(DISPL)
		{
		printf("\nALGORYTM 2\n");
		printRelations(outputRelations);
		printf("===========================================================\n");
		}

		return -1;
	}

	// Wersja tylko dla Uniform
	int i_R, j_R, i, j;
	Relation Temp, Test1, Test2;
	tuple_world tw1, tw2;
	Tuple<Relation> out2;

	int *do_skasowania;
	do_skasowania = new int[outputRelations.length()+1];

	for(i=0; i<outputRelations.length()+1; i++)
		do_skasowania[i]=0;

	if(DISPL)
	{
	printf("\n\n===========================================================\n\n");
	printf("ALGORYTM 2\n");

	printf("\nWektory zaleznosci\n");
	printRelations(petitDepVector);
	printf("===========================================================\n");
	}

	for(i_R=0; i_R<outputRelations.length(); i_R++)			//   ir od 0 i jr od 0
		for(j_R=0; j_R<outputRelations.length(); j_R++)		//   RAZEM liczba_par
		{
			if(i_R!=j_R && petitRelationsVecType[i_R+1]==1 && petitRelationsVecType[j_R+1]==1 && do_skasowania[i_R]==0 && do_skasowania[j_R]==0)   //staly
			{

				tw1 = SetToTupleTab(petitDepVector[i_R+1], DISPL);
				tw2 = SetToTupleTab(petitDepVector[j_R+1], DISPL);

				if( is_vect_parallel(tw1.wsk[0], tw2.wsk[0], tw1.constr_count) == 1)
				{

					Test1 = Difference(Domain(copy(outputRelations[i_R+1])), Domain(copy(outputRelations[i_R+1])));
					Test2 = Difference(Range(copy(outputRelations[i_R+1])), Range(copy(outputRelations[i_R+1])));

					Test1.simplify();
					Test2.simplify();

					if( Test1.number_of_conjuncts()==0 && Test2.number_of_conjuncts()==0 )
					{
						do_skasowania[i_R+1]=1;
					};
				}
			}
		}


	// Przygotuj dane wyjsciowe
	j=1;
	for(i=1; i<=outputRelations.length(); i++)
		if(do_skasowania[i]==0)
		{
			BaseOut->R.append(outputRelations[i]);
			//BaseOut->DepVect.append(BaseRel.DepVect[i]);
			//Obliczenie wektora zaleznosci na nowo dla relacji
			BaseOut->DepVect.append(RelToDepVec(outputRelations[i]));
			//BaseOut->VecType.append(BaseRel.VecType[i]);
			//Ponowne ustalenie typu wektora
			BaseOut->VecType.append(GetVecType(BaseOut->DepVect[j]));
			BaseOut->From[j] = BaseRel.From[i];
			BaseOut->To[j] = BaseRel.To[i];
			BaseOut->SCC[j] = BaseRel.SCC[i];
			j++;
		}


	if(DISPL)
		printRelations(BaseOut->R);

	delete do_skasowania;
	return 0;
}





// ===============================================================================
// ALGORYTM 2b - usuwanie relacji nadmiarowych, implementacja Krzyska Siedleckiego
// korzysta z funkcji ParallelVectors i VarDividedByConst
// ===============================================================================





//void CLoopAnalysisPerfect::SaveNonParNonRed(Relation &arg1, Relation &vecDep, bool vectorType, unsigned int from,
//														  unsigned int to)
int algorytm2b(ComplexRelation BaseRel, ComplexRelation *BaseOut, const int DISPL)
{
	int i, j, k;  // i - index dodawanej relacji, j - badanej relacji
	int number; //numer zmiennej w zbiorze powodujacej rownoleglosc wektorow
	int reldrop = 0;

	// zadeklarowanie tablic
	BaseOut->From = BaseRel.From;
	BaseOut->To = BaseRel.To;
	// -------------------- ok, mozna to zrobic lepiej ale tak najlatwiej :)

	coef_t upperBound1,lowerBound1;
	coef_t upperBound2,lowerBound2;


	bool vectorAdded=false;	//wartosc zmiennej zostanie zmieniona na true jesli relacja
	//	<arg1> zostanie dodana do zbioru relacji wybierajacych


	Relation temp1,temp2,temp3;


	for(i=1; i<=BaseRel.R.length(); i++)
	{

		reldrop = 0;

		/***sprawdzamy czy trzeba dodac relacje <arg1> ze stalym wektorem <distance> do juz***/
		/****istniejacych relacji o stalych wektorach dystansu********************************/
		// dodawanie wektora stalego do dodanych stalych
		if(BaseRel.VecType[i])
			for(j=1; j<=BaseOut->R.length(); j++)
				if(BaseOut->VecType[j])
				{
					number = ParallelVectors(BaseOut->DepVect[j], BaseRel.DepVect[i]);

					if (number==0)
					{
						//wektory identyczne, w taki przypadku nalezy sprawdzic zakres zakresy
						//relacji <it->selectingRel> z <arg1> i wybrac ta z wiekszym zakresem
						temp1 = Difference(copy(BaseOut->R[j]),copy(BaseRel.R[i]));
						temp2 = Difference(copy(BaseRel.R[i]),copy(BaseOut->R[j]));
						temp1.simplify(2,2);
						temp2.simplify(2,2);
						//jesli dwie relacje nie sa puste to cos nie tak !!!
						assert(!(temp1.number_of_conjuncts() && temp2.number_of_conjuncts()));
						if (temp2.number_of_conjuncts())
						{
							//czyli relacja <arg1> ma wiekszy zakres od <it->selectingRel>
							//dlatego w miejsce wskazywane przez <it> wstawiamy <arg1>
							//*it = SRelationVector(arg1,vecDep,vectorType,from,to);

							BaseOut->R[j] = BaseRel.R[i];
							BaseOut->DepVect[j] = BaseRel.DepVect[i];
							BaseOut->VecType[j] = BaseRel.VecType[i];
							BaseOut->From[j] = BaseRel.From[i];
							BaseOut->To[j] = BaseRel.To[i];
							BaseOut->SCC[j] = BaseRel.SCC[i];


						}
					//mozemy przerwac wyszukiwanie, gdyz nie powinno byc identycznych wekorow
					//jesli beda to blad !!
					//return 0; /***********!!!!!!!!!!!!!!!!!!!!!*********************/
					reldrop = 1;
					break;
					}

					if (number>0)
					{
						//wektory rownolegle, a roznica w zmiennej o numerze <number>
						BaseOut->DepVect[j].query_variable_bounds(set_var(number),lowerBound1,upperBound1);
						BaseRel.DepVect[i].query_variable_bounds(set_var(number),lowerBound2,upperBound2);


						if (lowerBound1 > lowerBound2)
						{
							//wektor <distance> jest mniejszy, wiec sprawdzamy czy jest dzielnikiem
							//wczesniej zapamietanego wektora dystansu, jesli tak to podmieniamy
							//relacje wybierajace - odrzucamy wczesniejsza relacje
							if (VarDividedByConst(lowerBound2,number,BaseOut->DepVect[j]))
							{

								BaseOut->R[j] = BaseRel.R[i];
								BaseOut->DepVect[j] = BaseRel.DepVect[i];
								BaseOut->VecType[j] = BaseRel.VecType[i];
								BaseOut->From[j] = BaseRel.From[i];
								BaseOut->To[j] = BaseRel.To[i];
								BaseOut->SCC[j] = BaseRel.SCC[i];
								vectorAdded = true;
								break;	//przerwanie for'a
							}

						}
						else
						{
						//wektor <distance> jest wiekszy, wiec sprawdzamy czy wektor
						//<it->distanceVec> jest dzielnikiem wektora <distance>. Jesli tak to
						//wektor <distance> nie musi byc zapamietany i przerywamy przeszukiwanie,
						//w przeciwnym razie szukamy dalej
							if (VarDividedByConst(lowerBound1,number,BaseRel.DepVect[i]))
							{
								//return 0; /***********!!!!!!!!!!!!!!!!!!!!!*********************/
								reldrop = 1;
								break;
							}
						}

					}
				}

		/**************************************************************************************/
		// Pomiñ BaseRel[i] jesli reldrop=1
		if(reldrop)
			continue;

		/****Operacje majace na celu wyeliminowanie relacji o zmiennych wektorach zaleznosci***/
		/****rownoleglych do stalych wektorow zaleznosci **************************************/
		if(BaseRel.VecType[i])
			//czyli relacja arg1 o stalym wektorze dystansu <distance>
			for(j=1; j<=BaseOut->R.length(); j++)
				if(!BaseOut->VecType[j])
				{
					//czyli wektor it->distanceVec jest wektorem zmiennym
					number = ParallelVectors(BaseOut->DepVect[j], BaseRel.DepVect[i]);

					if (number>0)
					{
						BaseOut->DepVect[j].query_variable_bounds(set_var(number),lowerBound1,upperBound1);
						BaseRel.DepVect[i].query_variable_bounds(set_var(number),lowerBound2,upperBound2);

						//ponizej jesli <id->distanceVec> jest podzielny przez <distanse>
						//to jesli relacja <arg1> zostala dodana to usuwamy element wskazywany
						//przez <it>, a jesli nie zostala dodana do zamieniamy elementy
						if (VarDividedByConst(lowerBound2,number,BaseOut->DepVect[j]))
						{
							if (vectorAdded)
							{
								//Usuwamy BaseOut[j]
								//relacja juz zostala dodana, wiec usuwamy zbedna relacje
								for(k=j+1; k<=BaseOut->R.length(); k++)
								{
									BaseOut->R[k-1] = BaseOut->R[k];
									BaseOut->DepVect[k-1] = BaseOut->DepVect[k];
									BaseOut->VecType[k-1] = BaseOut->VecType[k];
									BaseOut->From[k-1] = BaseOut->From[k];
									BaseOut->To[k-1] = BaseOut->To[k];
								}

								BaseOut->R.delete_last();
								BaseOut->DepVect.delete_last();
								BaseOut->VecType.delete_last();

								j--;

							}
							else
							{
								BaseOut->R[j] = BaseRel.R[i];
								BaseOut->DepVect[j] = BaseRel.DepVect[i];
								BaseOut->VecType[j] = BaseRel.VecType[i];
								BaseOut->From[j] = BaseRel.From[i];
								BaseOut->To[j] = BaseRel.To[i];
								vectorAdded = true;
							}
						}

					}
				}

		else
		//wektor <distance> nie jest staly
		{
			for(j=1; j<=BaseOut->R.length(); j++)
				if(BaseOut->VecType[j])
				{
				//czyli wektor <it->distanceVec> jest wektorem stalym a <distance> to wektor
				//zmienny
					number = ParallelVectors(BaseOut->DepVect[j], BaseRel.DepVect[i]);

					if(number>0)
					{
						BaseOut->DepVect[j].query_variable_bounds(set_var(number),lowerBound1,upperBound1);
						BaseRel.DepVect[i].query_variable_bounds(set_var(number),lowerBound2,upperBound2);

						//ponizej jesli <distance> jest podzielny przez <it->distanseVec>
						//to nie musimy dodawac wektora i konczymy przeszukiwanie RETURN

						if (VarDividedByConst(lowerBound1,number,BaseRel.DepVect[i]))
						{
							//	return 0; /***********!!!!!!!!!!!!!!!!!!!!!*********************/
							reldrop = 1;
							break;
						}


					}


				}
				else
				{
					//czyli wektory <distance> i <it->distanceVec> sa wektorami zmiennymi
					//jesli relacja <arg1> jest identyczna lub zawiera sie w calosci w
					//<it->selectingRel> to odrzucamy <arg1> i na odwrot, jesli istnieja wspolne
					//zaleznosci (ten sam poczatek i ten sam koniec) w relacjach to usuwamy je
					//z jednej relacji - nie ma znaczenia z ktorej
					temp1 = Intersection(copy(BaseRel.R[i]), copy(BaseOut->R[j]));
					temp1.simplify(2,2);

					if (temp1.number_of_conjuncts())
					{
						//czyli sa jakies wspolne relacje miedzy <arg1> a <it->selectingRel>
						temp2 = Difference(copy(BaseRel.R[i]),copy(temp1));
						temp2.simplify(2,2);

						if (temp2.number_of_conjuncts())
						{
							//czyli sa jakies relacje w temp2, wiec <arg1> ma wiekszy zakres niz
							//<it->selectingRel> lub relacje nie sa identyczne
							//ponizej sprawdzamy czy <arg1> ma wiekszy zakres niz <it->selectingRel>
							temp2 = Difference(copy(BaseOut->R[j]),copy(temp1));
							temp2.simplify(2,2);

							if (temp2.number_of_conjuncts())
							{
								//w tym momencie wiadomo ze relacje maja wspolne zaleznosci ale zadna
								//nie zawiera sie w calosci w drugiej, wiec odejmujemy od
								//<it->SelectingRel> wspolne zaleznosci z <arg1>,
								//a <arg1> dodajemy w calosci
								// !!!!!
								BaseOut->R[j] = Difference(copy(BaseOut->R[j]), copy(temp1));
								BaseOut->R[j].simplify(2,2);
//								(it->selectingRel).print();
								//po kilku takich roznicach relacja <it->selectingRel> moze stac sie
								//pusta, w taki przypadku mozemy w miejsce <it> wstawic <arg1>
								if ( !(BaseOut->R[j]).number_of_conjuncts() )
								{
									BaseOut->R[j] = BaseRel.R[i];
									BaseOut->DepVect[j] = BaseRel.DepVect[i];
									BaseOut->VecType[j] = BaseRel.VecType[i];
									BaseOut->From[j] = BaseRel.From[i];
									BaseOut->To[j] = BaseRel.To[i];
									vectorAdded = true;
								}
							}
							else
								//<it->selectingRel> zawiera sie w <arg1>, na miejsce <it> wstawiamy
								//<arg1>
							{
								BaseOut->R[j] = BaseRel.R[i];
								BaseOut->DepVect[j] = BaseRel.DepVect[i];
								BaseOut->VecType[j] = BaseRel.VecType[i];
								BaseOut->From[j] = BaseRel.From[i];
								BaseOut->To[j] = BaseRel.To[i];
								vectorAdded = true;
							}
						}
					}
					else
					{
						// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						//return 0;
						reldrop = 1;
						break;
					}//end if(temp1.number_of_conjuncts())
				}
			//for
		}  //else

		// Pomiñ BaseRel[i] jesli reldrop=1
		if(reldrop)
			continue;

		if(!vectorAdded)
		{

			BaseOut->R.append(BaseRel.R[i]);
			BaseOut->DepVect.append(BaseRel.DepVect[i]);
			BaseOut->VecType.append(BaseRel.VecType[i]);
			BaseOut->From[BaseOut->R.length()] = BaseOut->From[i];
			BaseOut->To[BaseOut->R.length()] = BaseOut->To[i];
			// j+1 powinno byc

			if (DISPL && j+1!=BaseOut->R.length())
				printf("Blad w indeksacji !!! \n");
			//break;
		}

	} //for BaseRel

	return 0;

}




// ==============================================================
// ALGORYTM 3 - Finding sources of threads (version without applying transitive closure)
// ==============================================================
// Output = out_Relations modified Relations, IT set of sources independent threads




int algorytm3(int wersja, Tuple<Relation> inputRelations, Relation *out_IT, Relation *out_DT, Tuple<Relation> *out_Relations, int disp, Relation *In_FS)
{
	int i, i_R, j_R, odnowa;
	int ilosc_iteracji=0;

	Relation R, IR, _CI, Temp1, Temp2, Temp, FS, IT, DT, DT1, t, Runion, ztemp;

	R = R.False(inputRelations[1].n_inp(), inputRelations[1].n_inp());

	printf("\n===========================================================\n\nALGORYTM 3\n");

	for(i=1; i<=inputRelations.length(); i++)   // R = R1 \/ R2 \/ ...
		R = Union(copy(R), copy(inputRelations[i]));


	R.simplify(1, 1);

	if(disp)
	{
		printf("R: \n");
		R.print();
	}

	ztemp = Domain(copy(R));
	if(disp)
	{
	printf("Domain R: ");
	ztemp.print();
	}
	ztemp = Range(copy(R));
	if(disp)
	{
	printf("Range R: ");
	ztemp.print();
	}



	IR = Inverse(copy(R));
	//Relation TEMP = TransitiveClosure(copy(IR));
	//printf("===");
	//TEMP.print();

	IR.simplify(2, 4);

	if(disp)
	{
		printf("IR: \n");
		IR.print();
	}


	Relation CI;
	CI = CI.False(R.n_inp());

	if(disp)
	{
		printf("CI :");
		CI.print();
	}


	// Obliczenie liczby wszystkch par



	odnowa=0;

	//step 2

	do{
	odnowa=0;
	CI = CI.False(R.n_inp());
	for(i_R=1; i_R<=inputRelations.length()-1; i_R++)
		if (odnowa==0)
		{
		for(j_R=i_R+1; j_R<=inputRelations.length(); j_R++)
		{

			odnowa=0;
			//2.1
			_CI = _CI.False(R.n_inp());   // _CI:=FALSE

			Temp1 = Union(Domain(copy(inputRelations[i_R])), Range(copy(inputRelations[i_R]))); // All iterations represented by Ri
			Temp2 = Union(Domain(copy(inputRelations[j_R])), Range(copy(inputRelations[j_R]))); // All iterations represented by Ri


			_CI = Intersection(copy(Temp1), copy(Temp2)); //_CI represents common iterations

			_CI.simplify();

			//2.2
			Temp1 = Difference(Domain(copy(inputRelations[i_R])), Range(copy(inputRelations[i_R]))); // fair depence sources originated by Ri
			Temp2 = Difference(Range(copy(inputRelations[j_R])), Domain(copy(inputRelations[j_R]))); // fair depence destinations originated by Rj

			Temp = Intersection(copy(Temp1), copy(Temp2));
			_CI = Difference(copy(_CI), copy(Temp)); //_CI represents common iterations


			if (Temp.number_of_conjuncts() > 0)
			{
				Runion = Union(copy(inputRelations[i_R]), copy(inputRelations[j_R]));
				Runion.simplify(2, 4);
				inputRelations[i_R] = Runion;
				for(i=j_R; i<inputRelations.length(); i++)
					inputRelations[i]=inputRelations[i+1];
				inputRelations.delete_last();
				odnowa=1;
				break;  //go to to step 2
			}

			//2.3
			Temp1 = Difference(Range(copy(inputRelations[i_R])), Domain(copy(inputRelations[i_R]))); // fair depence destinations originated by Ri
			Temp2 = Difference(Domain(copy(inputRelations[j_R])), Range(copy(inputRelations[j_R]))); // fair depence sources originated by Rj

			Temp = Intersection(copy(Temp1), copy(Temp2));
			_CI = Difference(copy(_CI), copy(Temp)); //_CI represents common iterations

			if (Temp.number_of_conjuncts() > 0)
			{
				Runion = Union(copy(inputRelations[i_R]), copy(inputRelations[j_R]));
				Runion.simplify(2, 4);
				inputRelations[i_R] = Runion;
				for(i=j_R; i<inputRelations.length(); i++)
					inputRelations[i]=inputRelations[i+1];
				inputRelations.delete_last();
				odnowa=1;
				break;  //go to to step 2
			}

			//2.4
			CI = Union(copy(CI), copy(_CI));
			CI.simplify(2, 4);

			if(disp)
				CI.print();

		}
		}
		else break;
	}while(odnowa==1);

	//3. Find  depence sources

	FS = Difference(Domain(copy(R)), Range(copy(R)));

	printf("\nFS: ");
	FS.simplify(2, 4);
	FS.print();

	//4. Find DT and IT

	if(CI.number_of_conjuncts() < 1)
	{
		IT = FS;
		DT = DT.False(Range(copy(R)));
	}
	else
	{
		CI.simplify(2, 4);
		// 5. without applying transitive closure

		Temp = CI;
		DT1 = CI;

		if(disp)
		{
			CI.print();
			printf("!!!");
		}

		// find a set of depence sources belonging to dependent threads TEMP as applying IR to set Temp

		// wesja 5a i 5 b , output DT1
		if (wersja==0)
		{
			Relation IRplus = TransitiveClosure(copy(IR));
			DT1 = Range(Restrict_Domain(copy(IRplus), copy(CI)));
		}

		// 5b without applying transitive closure
		else
		{

			DT1.simplify(2, 4);
			Temp.simplify(2, 4);

			do
			{
				ilosc_iteracji++;

				if(disp)
				{
					Temp.print();
					printf("DT1");
					DT1.print();
				}

				Temp = Range(Restrict_Domain(copy(IR), copy(Temp)));
				Temp.simplify(1, 1);
				if (Temp.number_of_conjuncts() > 0)
					DT1 = Union(copy(DT1), copy(Temp));
				DT1.simplify(1, 1);
			}
			while(Temp.number_of_conjuncts() > 0);
		}
		// ====================================



		// 6. Dependent threads
		DT = Intersection(copy(DT1), copy(FS));
		IT = Difference(copy(FS), copy(DT));


		FS.simplify(2, 4);

		if(disp)
		{
		printf("FS ");
		FS.print();
		}

	}

	IT.simplify(2, 4);
	//IT.simplify(1,1);
	IT=MaxSimplify(IT);  //1111111111111111111
	DT.simplify(2, 4);

	*(out_IT) = IT;
	*(out_DT) = DT;
	*(out_Relations) = inputRelations;

	printf("IT: ");
	IT.print();
	printf("DT: ");
	DT.print();
	printf("\nIlosc_Iteracji: %i", ilosc_iteracji);
	printf("\n\n===========================================================\n\n");

	*In_FS = FS;

	return 0;
}



// ALGORYTM 4
// Finding iterations belonging to independent threads and code generation
// LD - przestrzen iteracji petli

int algorytm4(int wersja, Relation IT, Tuple<Relation> inputRelations, Relation LD, char *plik, int disp, int disp1, Relation In_FS)
{


	Relation R = R.False(inputRelations[1].n_inp(), inputRelations[1].n_out());  // R:=False
	Relation DD1;
	int i = 1, ilosc_iteracji=0;
	printf("===========================================================\n\nALGORYTM 4\n");
	printf("\nRelacje\n");
	printRelations(inputRelations);


	Relation Ri, RD, S, Temp, ITD, Ri_IT;

	Tuple<naming_info *> name_func;
	String out_loop;

	name_func.append(new default_stmt_info(1));

	for (i=1; i<=inputRelations.length(); i++)
	{
		Ri = inputRelations[i];
		Ri.simplify(2, 4);
		Ri_IT = Range(Restrict_Domain(copy(Ri), copy(IT)));

		if (Ri_IT.number_of_conjuncts()>0)
			R = Union(copy(R), copy(Ri));

		if(disp)
		{
		printf("Ri_IT: ");
		Ri_IT.print();
		}


	}

	R.simplify(2, 4);

	if(disp)
	{
		printf("R");
		R.print();
	}


	if(wersja==0)
	// 2a. with applying transitive closure
	{


		Relation Rel_Vec = RelToDepVec(R);

		// upraszczanie !!! - nowy kod

		// {[i,j,In_3,In_4] j = 1 && i = 1 && In_3 <= 10 && In_4 <= 10 and exists ( n : ( In_3 = A*n+i && In_4 = A*n+j && 0 <= n )) }

		if(GetVecType(Rel_Vec))   //jest jednorodny
		{

			int t;
			omega::coef_t ub, lb;
			F_And *ogr;


			Relation LD_Rel = Union(Domain(copy(R)), Range(copy(R)));

			int fs_dim = In_FS.n_set();
			In_FS = Extend_Set(copy(In_FS), fs_dim);


			for(t=1; t<=fs_dim; t++)
			{
				ogr = In_FS.and_with_and();

				Variable_ID v = In_FS.set_var(fs_dim+t);

				LD_Rel.query_variable_bounds(set_var(t), lb, ub);

				GEQ_Handle gh = ogr->add_GEQ();
				gh.update_coef(v, -1);
				gh.update_const(ub);

			}

			ogr = In_FS.and_with_and();

			F_Exists *fe = ogr->add_exists();

			Variable_ID n = fe->declare("n");

			F_And *fe_ogr = fe->add_and();
			F_And *ogr2;

			for(t=1; t<=fs_dim; t++)
			{
				Rel_Vec.query_variable_bounds(set_var(t), lb, ub);

				if(t<fs_dim)
					ogr2 = fe_ogr->add_and();

				EQ_Handle eq1 = ogr2->add_EQ();
				eq1.update_coef(set_var(fs_dim+t), 1);  //In_FS. ??
				eq1.update_coef(n, -ub);
				eq1.update_coef(set_var(t), -1);

			}

			GEQ_Handle gh2 = fe_ogr->add_GEQ();
			gh2.update_coef(n, 1);

			S = In_FS;

		}
		else
		{

			Relation Rplus, Rstar;
			Rplus = TransitiveClosure(copy(R));
			Rplus.simplify(2,4);
			Rstar = Union(copy(Rplus), IdentityRelation(R.n_inp()));
			Rstar.simplify(2,4);
			printf("rstar");
			Rstar.print();

			Relation S1, S2;
			S1 = RelationToSet(Rstar);
			S2 = ExtendSetByTrue(copy(IT));

			S = Intersection(S1, S2);
		}



		S.simplify(2,4);
		S.print();
		//S = MaxSimplify(S);
	//	S.simplify(1, 1);
		ilosc_iteracji++;

	}
	else
	// 2b. without applying transitive closure
	{

		ITD = DoubleDim(IT); // ITD = { IT, IT}


		RD = RD_make_relation(IT, R);  //RD = {[In(IT), In(R)] -> [In(IT), Out(R)] : constr(IT) && constr(R) }
		RD.simplify(2, 4);

		if (disp)
		{
			printf("\n----\n-----RD:");
			RD.print();
		}

		S = ITD;

		Temp = ITD;

		//Relation GG = MirrorSet(ITD);

		if(disp)
		{
		printf("\n\n===");
		//GG.print();
		printf("S: ");
		S.print();
		}



		do
		{

			ilosc_iteracji++;
			Temp = MirrorSet(Temp);
			Temp = Range(Restrict_Domain(copy(RD), copy(Temp)));

			if(disp)
			{
			printf("\n\nRD(Temp):");
			Temp.print();
			}

			Temp = MirrorSet(Temp);
			Temp = Difference(copy(Temp), copy(S));
			Temp.simplify(2, 4);

			if(disp)
			{
				printf("\n\nRD(Temp) -S:");
				Temp.print();
			}

			if (Temp.number_of_conjuncts() > 0)
				S = Union(copy(S), copy(Temp));

			S.simplify(1, 1);
			S.simplify(2, 4);

			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//	if (S.number_of_conjuncts() < 10)
			S=MaxSimplify(copy(S));

			Temp.simplify(1, 1);

			if(disp)
			{
			printf("S: ");
			S.print();
			printf("Temp:");
			Temp.print();    //kod niezaleznego watka
			}
		}
		while(Temp.number_of_conjuncts() > 0);
	}

	// =============================================
	// Simplifuj S -> dla lepszej postaci petli
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	S=MaxSimplify(copy(S));

	S.simplify(2,4);

	if(disp)
	{
	printf("S:");
	S.print();
	}


	//Tworz relacje tozsamosci
	Relation R_transform = IdentityRelation(S.n_set());

	Tuple<Relation> R_t_coll, S_coll;
	R.simplify(2, 4);

	if(disp)
		R_transform.print();

//	S = Complement(copy(S));
//	S = Difference(Relation::True(S.n_set()), copy(S));

	R_t_coll.append(R_transform);
	S_coll.append(S);

	if(disp)
	{
	printf("R");
	R.print();
	printf("S");
	}

	//S = Intersection(Relation::True(S.n_set()), copy(S));
	S.simplify(2,4);
	S.simplify(1,2);
	//RZR = Relation::True(S.n_set());
//	Relation DD = Difference(copy(RZR), copy(S));

	if(disp)
		printf("=====================");

//	DD.simplify(2, 4);
//	S = Difference(copy(RZR), copy(DD));
//	S.simplify(4, 1);
//	if(disp)

	printf("======\n======\n");
	S = Complement(S);
		S = Complement(S);
	S.simplify(1,1);
	S.print();

	printf("Ilosc iteracji: %i\n\n\n", ilosc_iteracji);
		printf("\n\nPETLA WYJSCIOWA\n");

	//generowanie petli
	out_loop = LoopCodeGen(S, 0);
	//out_loop = MMGenerateCode(R_t_coll, S_coll, name_func, Relation::True(S.n_set()),3);

	printf("%s ====", str(out_loop));




	//obcinanie zmiennych dodatkowych parserem .NET - mozna teraz sprobowac Java

	if (disp1){
	FILE *f;
	f = fopen("petla.txt ", "w");
	fprintf(f, "%s", str(out_loop));
	fclose(f);

    //parseloop(str(plik), "petla.txt");
	printf("\n");
	}



//	if (disp1){
	//printf("Petla IT (par):\n\n%s", out_loop);


// GENEROWANIE PETLI DT

	Relation S11 = GenerateDTSet(S, LD);


	S11.print();

	if (S11.number_of_conjuncts() > 0)
	{
		S_coll.delete_last();
		S_coll.append(S11);



		Relation R_DT = IdentityRelation(S11.n_set());

		R_DT.simplify(2, 4);
		R_t_coll.delete_last();
		R_t_coll.append(R_DT);


        out_loop = LoopCodeGen(S11, 0);
		//out_loop = MMGenerateCode(R_t_coll, S_coll, name_func, Relation::True(S11.n_set()));



		printf("\nPetla DT:\n\n***===***\n\n%s\n\n***===***\n\n", str(out_loop));

		if (disp1){
		printf("\n\n===========================================================\n");
		S11.print();
		}

		return 0;
	}
	else
	{
	printf("\nPetla DT nie zawiera iteracji");
	printf("\n\n===========================================================");
	}




	return 0;


}





//dla slicow
int algorytm2c(ComplexRelation BaseRel, ComplexRelation *BaseOut, int disp)
{
	int n = BaseRel.R.length();
	int i, j, l=0;
	Relation R(2,2), Sprim, S, Rstar, Rk, Rk_inv, Sbis, Result, D;

	if(n < 2)
	{
		*BaseOut = BaseRel;
		return 0;
	}

	BaseOut->To = BaseRel.To;
	BaseOut->From = BaseRel.From;

/*
	R = BaseRel.R[1];
	for(i=2; i<=n; i++)
		R = Union(copy(R), copy(BaseRel.R[i]));


	S = Difference(Domain(copy(R)), Range(copy(R)));
	S.simplify(2, 5);
		printf("S");
	S.print();
*/
	for(i=1; i<=n; i++)
	{
		l =0;
		R = Difference(copy(BaseRel.R[1]), copy(BaseRel.R[1]));
		for(j=1; j<=n; j++)
		{
			if(i != j && l == 1)
			{
				R = Union(copy(R), copy(BaseRel.R[j]));
			}
			else if(i==j)
			{
				Rk = BaseRel.R[j];
				D = Domain(copy(Rk));
				Rk_inv = Inverse(copy(Rk));
			}
			else
			{
				R = BaseRel.R[j];
				l = 1;
			}
		}

		Result = Difference(Range(Restrict_Domain(copy(Rk), copy(D))), Range(Restrict_Domain(TransitiveClosure(copy(R)), copy(D))));

		if(!Result.is_exact())
			{
				printf("\nR* has UNKNOWN constraints\n");
				exit(1);
			}



		if(Result.number_of_conjuncts() > 0)  // S'' nie zawiera sie w S' dodaj Rk
		{
			BaseOut->R.append(BaseRel.R[i]);
			int ww = BaseOut->R.length();
			BaseOut->From[ww] = BaseRel.From[i];
			BaseOut->To[ww] = BaseRel.To[i];

		}

	}

	if(disp)
		printRelations(BaseOut->R);

	return 0;

}

//redukcja grafow do drzew
ComplexRelation algorytm2d(ComplexRelation BaseRel, ComplexRelation *BaseOut, Relation S, int disp)
{
	int n = BaseRel.R.length();

	int i, j;

        Relation Ri, Riprim, Di, CI, TMP, tmp2, tmp3, R, RSet, RprimSet, Tmp_A, Tmp_B;
	ComplexRelation TmpRel;
printf("?!!!");

	if(n < 2)
		return BaseRel;

	BaseOut = new ComplexRelation;

	BaseOut->To = BaseRel.To;
	BaseOut->From = BaseRel.From;
        printf("!!!!\n");

//	BaseOut->R = BaseRel.R;

	if(GetTopology(BaseRel) < 2) //nie jest to graf
	{
		printf("\nIt is not graph, exiting...");
		return BaseRel;
	}

	if(disp)
	{
	printf("\nSources set: ");
	S.print();
	}

// oblicz sources of slices, mozna potem to podmienic na parametr
	R = BaseRel.R[1];
	for(i=2; i<=n; i++)
		R = Union(copy(R), copy(BaseRel.R[i]));


	//S = Difference(Domain(copy(R)), Range(copy(R)));
	S.simplify(2, 5);
	if(disp)
	S.print();



	// ---

	for(i=1; i<=n; i++)
	{

		Di = Range(copy(BaseRel.R[i]));

		CI = Difference(copy(Di), copy(Di));
		CI.simplify();

		if(disp)
		for(j=1; j<=n; j++)
			BaseRel.R[j].print();


		for(j=1; j<=n; j++)
			if(j!=i)
			{
				CI = Union(copy(CI), Intersection(copy(Di), Range(copy(BaseRel.R[j]))));
			}

if(disp)
		printf("\n_Ci  ");
if(disp)
		CI.print();

		Di = Difference(copy(Di), copy(CI));

		Di.simplify();
		if(disp)
		printf("\nDi  ");
		if(disp)
		Di.print();


		Riprim = Restrict_Range(copy(BaseRel.R[i]), copy(Di));

		Riprim.simplify();
		if(disp)
		printf("\nRi  ");
		if(disp)
		Riprim.print();


		tmp2 = Difference(copy(BaseRel.R[i]), copy(Riprim));
		tmp3 = Difference(copy(Riprim), copy(BaseRel.R[i]));

		if(tmp2.is_unknown() || tmp3.is_unknown())
			{
				printf("\nFailure: Some relations has UNKNOWN constraints\n");
				exit(1);
			}

		if((tmp2.number_of_conjuncts() <= 0) && (tmp3.number_of_conjuncts() <= 0))
		{

			printf("***");
			BaseOut->R.append(BaseRel.R[i]);
			int ww = BaseOut->R.length();
			BaseOut->From[ww] = BaseRel.From[i];
			BaseOut->To[ww] = BaseRel.To[i];
			continue;
		}

		for(j=1; j<=n; j++)
			if(j!=i)
				TmpRel.R.append(BaseRel.R[j]);
			else
				TmpRel.R.append(Riprim);


		//printf("\n========\n");
		//for(j=1; j<=n; j++)
		//	TmpRel.R[j].print();
		//printf("\n========\n");

		RSet = BaseRel.R[1];
	//	Tmp_B = TransitiveClosure(copy( BaseRel.R[1]));
		for(j=2; j<=n; j++)
		{
	//		Tmp_B = TransitiveClosure(copy( BaseRel.R[j]));
			RSet = Union(copy(RSet), copy(BaseRel.R[j]));
		}

		RprimSet = TmpRel.R[1];
		for(j=2; j<=n; j++)
			RprimSet = Union(copy(RprimSet), copy(TmpRel.R[j]));

		RSet.simplify(2, 4);
		RprimSet.simplify();

		Relation I1 = TransitiveClosure(copy(RSet));

if(disp)
		RprimSet.print();
		RprimSet.simplify(2, 4);
	//	RprimSet = SimplifyNumConjuncts(RprimSet);

		if(disp)
		RprimSet.print();
		Relation I2 = TransitiveClosure(copy(RprimSet));


		tmp2 = Difference(Range(Restrict_Domain(TransitiveClosure(copy(RSet)), copy(S))), Range(Restrict_Domain(TransitiveClosure(copy(RprimSet)), copy(S))));


		tmp3 = Difference(Range(Restrict_Domain(TransitiveClosure(copy(RprimSet)), copy(S))), Range(Restrict_Domain(TransitiveClosure(copy(RSet)), copy(S))));


		tmp2.simplify(2,5);
		tmp3.simplify(2,5);

		if(!(tmp2.is_exact() && tmp3.is_exact()))
			{
				printf("\nR* has UNKNOWN constraints\n");
				exit(1);
			}

		if(disp)
		tmp2.print();
		if(disp)
		tmp3.print();

		if((tmp2.number_of_conjuncts() <= 0) && (tmp3.number_of_conjuncts() <= 0))
		{
			BaseOut->R.append(Riprim);
			BaseRel.R[i] = Riprim;

			int ww = BaseOut->R.length();
			BaseOut->From[ww] = BaseRel.From[i];
			BaseOut->To[ww] = BaseRel.To[i];
		}
		else
			BaseOut->R.append(BaseRel.R[i]);

		for(j=1; j<=n; j++)
			TmpRel.R.delete_last();


	}


	if(disp)
		printRelations(BaseOut->R);

	if(GetTopology(BaseRel) < 2) //nie jest to graf
	{
		printf("\nGraph reduced... ");
		if(GetTopology(BaseRel)==1)
			printf("It is a tree");
		else
			printf(" ");
	}
	else
		printf("\nStill graph...");

	return *BaseOut;

}



// Algorithm 5. Removing redundant dependences
// Consisted in other relations

int algorytm5(ComplexRelation BaseRel, ComplexRelation *BaseOut, int disp, int strength=0)
{


	Tuple<Relation> petitRelations = BaseRel.R;
	BaseOut->From = BaseRel.From;
	BaseOut->To = BaseRel.To;
	Relation RR;


	int i, j, k;

	for(k=1; k<=petitRelations.length(); k++)
	{
		for(i=1; i<=petitRelations.length(); i++)
			for(j=1; j<=petitRelations.length(); j++)
			{
				if(j != k && i!=k)
				{
					if(petitRelations[k].number_of_conjuncts() <= 0)
						continue;

					RR = Union(copy(petitRelations[i]), copy(petitRelations[j]));
					RR.simplify();


					if(RR.number_of_conjuncts() <= 0)
						continue;

					RR = TransitiveClosure(copy(RR));
					RR.simplify();




					if(RR.is_inexact())
						RR = Lower_Bound(copy(RR));

					if(RR.number_of_conjuncts() <= 0)
						continue;


					Relation CR = Intersection(copy(RR), copy(petitRelations[k]));

					Relation Diff = Difference(copy(petitRelations[k]), copy(CR));
					Diff.simplify();


					if(Diff.number_of_conjuncts() <= 0)
						petitRelations[k] = Diff;

					if(strength > 0 && Diff.number_of_conjuncts() > 0)
					{
						petitRelations[k] = Difference(copy(petitRelations[k]), copy(CR));
						petitRelations[k].simplify();
					}





				}

				if(i==k && strength == 1)
				{
					if(petitRelations[k].number_of_conjuncts() <= 0)
						continue;

					RR = Union(copy(petitRelations[i]), copy(petitRelations[j]));
					RR.simplify();


					if(RR.number_of_conjuncts() <= 0)
						continue;


					RR = TransitiveReduction(copy(RR));
					RR.simplify();
					petitRelations[k] = Intersection(copy(RR), petitRelations[k]);
					petitRelations[k].simplify();
					petitRelations[k] = SimplifyNumConjuncts(petitRelations[k]);
				}



			}
	}

	j=1;
	for(i=1; i<=petitRelations.length(); i++)
		if(petitRelations[i].number_of_conjuncts()>0)
		{

			BaseOut->R.append(petitRelations[i]);
			BaseOut->DepVect.append(BaseRel.DepVect[i]);
			BaseOut->VecType.append(BaseRel.VecType[i]);
			BaseOut->From[j] = BaseRel.From[i];
			BaseOut->To[j] = BaseRel.To[i];
			j++;
		}


	if(disp)
	printRelations(BaseOut->R);


	return 0;

}





// Proba skasowania wlasnych relacji tranzytywnych
int algorytm00(ComplexRelation BaseRel, ComplexRelation *BaseOut, int disp)
{
	Relation R, Temp1, Temp2;
	int i;

	BaseOut->From = BaseRel.From;
	BaseOut->To = BaseRel.To;
	BaseOut->Type = BaseRel.Type;
	printf("dodaje");
	for(i=1; i<=BaseRel.R.length(); i++)
	{

		if(strcmp(BaseRel.Type[i], "flow") == 0)
		{

			BaseOut->R.append(BaseRel.R[i]);
			BaseOut->DepVect.append(BaseRel.DepVect[i]);
			BaseOut->VecType.append(BaseRel.VecType[i]);
			int k = BaseOut->R.length();
			BaseOut->From[k] = BaseRel.From[i];
			BaseOut->To[k] = BaseRel.To[i];
			BaseOut->Type[k] = BaseRel.Type[i];
			BaseOut->SCC[k] = BaseRel.SCC[i];

		}
	}

	return 0;
}

// Wybieranie SCC
ComplexRelation chooseSCC(ComplexRelation BaseRel, int SCCnum, int disp)
{
	int i;

	ComplexRelation *BaseOut = new ComplexRelation;
	BaseOut = new ComplexRelation;

	for(i=1; i<=BaseRel.R.length(); i++)
	{

		if(BaseRel.SCC[i] == SCCnum)
		{

			BaseOut->R.append(BaseRel.R[i]);
			BaseOut->DepVect.append(BaseRel.DepVect[i]);
			BaseOut->VecType.append(BaseRel.VecType[i]);
			BaseOut->From.append(BaseRel.From[i]);
			BaseOut->To.append(BaseRel.To[i]);
			BaseOut->Type.append(BaseRel.Type[i]);
			BaseOut->SCC.append(BaseRel.SCC[i]);

		}
	}

	return *BaseOut;
}






