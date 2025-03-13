#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>



void OneTouch(ComplexRelation BaseRel, Relation LD, int Preprocessing = 1)
{
	ComplexRelation *BaseOut = new ComplexRelation;
	char item;
	int i;
	Relation R_Orig;

        //printKindRelInfo(BaseRel);
//disp=1;


	// print input relations
    if(!_SILENT)
        printRelations(BaseRel.R, 1);

	// extend to equal dimensions
	if(Preprocessing)
	BaseRel.R = NormalizeRel(BaseRel.R);
        if(disp)
            printf("\n%s", str(TopologyName(GetTopology(BaseRel))));



	// po normalizacji
	// print input relations

        if(disp)
        {
            printf("Po normalizacji\n");
            printRelations(BaseRel.R, 1);
        }


	if(BaseRel.R.length() > 1)
		R_Orig = globalUnion(BaseRel.R);
	else
		R_Orig = BaseRel.R[1];

	// correct statements and extend relations with dimension of statement
	//BaseRel = CorrectStatements(BaseRel);
        //Relation UDS_ = Difference(Domain(copy(R_Orig)), Range(copy(R_Orig)));
        //UDS_.simplify(2, 3);
        //UDS_.print();


        if(disp)
            printRelations(BaseRel.R, 1);

    if(Preprocessing)
	BaseRel = Ext_Base(BaseRel);
	//printRelations(BaseRel.R, 1);

	if(RETURN_R)
	{
	    Relation _RR = globalUnion(BaseRel.R);
	    _RR.print();
	    cout << "====" << endl;
	    _RR.print_with_subs();
	    exit(0);
	}




	Rel_Struct Sources;



	//try to reduce relations
        if(disp)
            printf("Try to reduce some relations\n");


// NOT IMPLEMENTED LINUX

	    BaseRel = PrepareRelations(BaseRel);


        if(disp)
            printRelations(BaseRel.R, 1);
        for(i=1; i<=BaseRel.R.length(); i++)
            BaseRel.R[i] = Repair_Relation(BaseRel.R[i]);

        if(_FS_FOR_TILING){
            for(i=1; i<=BaseRel.R.length(); i++){
                BaseRel.R[i] = NewDep(BaseRel.R[i]);
            }
        }

        /*
        Relation Z;
        Z = BaseRel.R[1];
        Z = Difference(copy(Z), Composition(Star(Z, 1), copy(Z)));
        Z.simplify();
        Z.print();

        BaseRel.R[1] = Z;

        Z = BaseRel.R[2];
        Z = Difference(copy(Z), Composition(Star(Z, 1), copy(Z)));
        Z.simplify();
        Z.print();

        BaseRel.R[2] = Z;
*/


        //exit(0);
    if(!_SILENT)
        printf("\n\nTopology: %s\n", str(TopologyName(GetTopology(BaseRel))));

       // exit(0);


        Relation R = globalUnion(BaseRel.R), Rs;

        std::string srel = Omega2Barvinok(Str2string(R2String(R)));
        if(_RELPRINT){
            cout << srel;

            for(int yyy = 1; yyy<=BaseRel.R.length(); yyy++){
                printf("#%i", BaseRel.From[yyy]);
                printf("#%i", BaseRel.To[yyy]);
            }
            if(_NOSOURCES)
                exit(0);
        }
        //std::ofstream os("tmp/rel.txt");
        //if (!os) { std::cerr<<"Error writing to ..."<<std::endl; } else {
        //    os << srel;
        //}
        //os.close();

/*
R.simplify();

R.print_with_subs();
printf("\n==\n");


R.print();

Relation Z1 = TransitiveClosure(copy(R));


//zmierzyc czas
double begin = gettime();
    Rs = Star(copy(R), 0);
double end = gettime();
printf("\n\--------> Czas obliczenia R*: %d\n", (int)((end - begin) * 1000.0));
// ---


    Rs.print_with_subs();
 //   Rs.simplify(2, 4);
  //  Rs = SimplifyNumConjuncts(Rs);
  //  Rs = InteSymp(Rs);
//exit(0);
Rs.print_with_subs();


printf("\n\n*** %i ***\n\n", Rs.number_of_conjuncts());
  //  R.print()
*/


/*
	BaseRel = readSCC(petitLoopfilename, BaseRel);

	for(i=1; i<=BaseRel.R.length(); i++)
		printf("Relation %i SCC %i,  From %i To %i\n", i, BaseRel.SCC[i], BaseRel.From[i-1], BaseRel.To[i-1]);

*/

	//independent statements
	String IND_LOOP = " "; //GenerateINDLoop(LD, R_Orig);
//exit(0);
    //NewDep(BaseRel.R[1]);
    if(!_SILENT){
	printf("\n-------------------------------------------------------------------------------------\n");
	printf("Sources of Slices\n\n");
    }

	//calculate sources of slices
	if(1)
{
// zmierzyc czas
//double begin2 = gettime();
	Sources = CalcSources(BaseRel, 1);


    Relation Srepr = globalUnion(Sources.R);

    FILE *f = fopen("sources_of_slices.txt", "w");
    //Srepr.print(f);
    fprintf(f, "%s", Omega2Barvinok(Str2string(R2String(Srepr))).c_str());
    fclose(f);

    f = fopen("rucs.txt", "w");
    Relation Rucs = globalUnion(Sources.R_UCS_list);
    fprintf(f, "%s", Omega2Barvinok(Str2string(R2String(Rucs))).c_str());
    fclose(f);

    if(_RELPRINT){
        exit(0);
    }



	if(Sources.R.length() == 1) // && _SILENT)
	{
	    std::string s(str(Sources.Loops[1]));
	    string str2 ("for");
	    size_t found=s.find(str2);
        if (found==string::npos)   //tu powinna byc flaga
            item = '0' + _SCHEDULE_TYPE;

	}

	if(_FS_FOR_TILING == 2)
	{
	    item = '0' + _SCHEDULE_TYPE;
	}



//double end2 = gettime();
// printf("\n--------> Czas obliczenia poczatkow: %d\n", (int)((end2 - begin2) * 1000.0));
// !!!!

}
	else
	{
	Relation RRR  = BaseRel.R[1];

	RRR.simplify();
	RRR.print();
	for(i=2; i<=BaseRel.R.length(); i++)
		RRR = Union(copy(RRR), copy(BaseRel.R[i]));


	Relation SOUR = Difference(Domain(copy(RRR)), Range(copy(RRR)));
	SOUR = ReduceSet(SOUR);


	Sources.R.append(SOUR);
	Sources.Loops.append(LoopCodeGen(SOUR, 0));
	RRR = Difference(copy(RRR), copy(RRR));
	RRR.simplify();
	Sources.R_UCS_list.append(RRR);
	printf("\n%s", str(Sources.Loops[1]));
	SOUR.simplify();
	SOUR.print();
	//exit(0);




	}

     //   exit(0);
        if(!_NOMENU){
	printf("\n-------------------------------------------------------------------------------------\n");
	printf("Generate parallel code - menu\n\n");

	printf("0. Slices with codegen\n\n");
	printf("1. Chain - while\n\n");
	printf("2. Tree - while\n\n");
	printf("3. Graph - while\n\n");
	printf("4. Graph 2 Tree - while, try to reduce graph to tree \n\n");
	printf("5. Graph/Tree 2 Chains - while, try to reduce graph/tree to chain (R' algorithm)\n\n");
	printf("6. Synchronization (codegen) - exmperimentally\n\n");
	printf("7. Synchronization (codegen) with aggl. - exmperimentally\n\n");
        printf("8. Free Sheduling without Rk (new)\n\n");
        printf("9. Free Sheduling with Rk (new)\n\n");


	scanf("%c", &item);
        }
        else
        {
            if(item != '8' && item != '9') item = '0';
        }


	switch(item)
	{

		case '0' :
			{
				Tuple<String> Loops;
				GenCodeScanSlices(Sources, BaseRel, IND_LOOP, true, &Loops, false);

                double end2 = gettime();
                if(!_SILENT)
                    printf("\n--------> Czas obliczenia poczatkow: %.2f\n", (double)((end2 - begin2)));

                FILE *_file = fopen("pseudocode.txt", "w");
				for(i=1; i<=Sources.R.length(); i++)
                {
					if(!_SILENT)
                        printf("Parallel loop for affine dependences :\n\n%s\n", str(Loops[i]));
                    fprintf(_file, str(Loops[i]));

                }
		fclose(_file);
		ParseOutput();


				break;
			}
		case '1' : // chain
			{

				for(i=1; i<=Sources.R.length(); i++)
                                {
					GenerateChainsWhileLoopFromSourcesOfSlices(BaseRel.R, Sources.R[i], false);
                                      //  GenerateChainsWhileLoopFromSourcesOfSlices(BaseRel.R, Sources.R[i], false);
                                }
				break;
			}
		case '2' : //tree
			{
				for(i=1; i<=Sources.R.length(); i++)
					GenerateTreeWhileLoop(BaseRel, Sources.R[i], "", false );
				break;
			}
		case '3' : //graph
			{
				for(i=1; i<=Sources.R.length(); i++)
					GenerateGraphWhileLoop(BaseRel, false, "", Sources.Loops[i]);
				  double end2 = gettime();
				  if(!_SILENT)
                                printf("\n--------> Czas obliczenia poczatkow: %.2f\n", (double)((end2 - begin2)));


                                break;
			}
		case '4' :
			{

			//	if(GetTopology(BaseRel) = 2)
			//	{
					printRelations(BaseRel.R, 1);


					BaseOut = new ComplexRelation;
					algorytm2c(BaseRel, BaseOut, false);
					BaseRel = *BaseOut;

					printRelations(BaseRel.R, 1);

					BaseOut = new ComplexRelation;
                                        printf("%i", Sources.R.length() );

					Relation GlobSour = Sources.R[1];
					for (i=2; i<=Sources.R.length(); i++)
						GlobSour = Union(copy(GlobSour), copy(Sources.R[i]));

					printf("\nAfter algoritm 1...\n %s", str(TopologyName(GetTopology(BaseRel))));

					if(GetTopology(BaseRel) == 2)
					{
						BaseRel = algorytm2d(BaseRel, BaseOut, GlobSour, true);


						if(GetTopology(BaseRel) == 1)
						{
							printRelations(BaseRel.R, 1);

							for(i=1; i<=Sources.R.length(); i++)
								GenerateTreeWhileLoop(BaseRel, Sources.R[i], "", false );
						}
						else
						{
							printf("\nIt is not tree, but %s sorry...", TopologyName(GetTopology(BaseRel)));
							printRelations(BaseRel.R, 1);
						}
					}

				//}
				//else
				//	printf("\nIt is not graph , sorry...");

				break;
			}

		case '5' :
			{
				if(GetTopology(BaseRel) >= 1)
				{
					GenCodeScanSlices(Sources, BaseRel, "", false);
				}
				else
				{
					printf("\nIt is chain, sorry...");
				}
				break;
			}

		case '6' :
			{
				Synch(BaseRel, "", 0);
				break;
			}
		case '7' :
			{
				Synch(BaseRel, "", 1);
				break;
			}
            case '8' :
                        {

                            Relation Ru = globalUnion(BaseRel.R);

                            WriteVars(Domain(copy(Ru)));

                          //  Ru = SimplifyNumConjuncts(Ru, 1);
                            Ru.simplify(2, 5);
                            Ru.print();


                            String Loop = GetFS(Ru, 0, Sources);
                            PrintString(Loop);
                            FILE *_file = fopen("pseudocode.txt", "w");
                            fprintf(_file, str(Loop));
                            fclose(_file);
                            ParseOutput(1);
                            break;
                        }

            case '9' :
                        {

                            Relation Ru = globalUnion(BaseRel.R);
                            Relation Z = Ru;
                            WriteVars(Domain(copy(Ru)));
                          //  Ru = SimplifyNumConjuncts(Ru, 1);
                            Ru = Repair_Relation(Ru);
                            Ru.copy_names(Z);
                            Ru.simplify(2, 5);
                            Ru.print();


                            Rk_FS(Ru);
                            ParseOutput(0);
                            double end2 = gettime();
                            printf("\n--------> Czas całkowity liczenia FS: %.2f\n", (double)((end2 - begin2)));

                            break;
                        }

		default :
			{
				printf("\nNot yet implemented\n");
			}
	}

	//	if(strcmp(IND_LOOP, "FALSE\n") != 0)
	//	printf("\nIND_LOOP\n%s", str(IND_LOOP));



	exit(0);
}




Rel_Struct CalcSources2(ComplexRelation BaseRel, Relation LD, int Preprocessing = 1)
{
	//ComplexRelation *BaseOut = new ComplexRelation;
	//char item;
	int i;
	Relation R_Orig;
disp = 0;


	// extend to equal dimensions
	if(Preprocessing)
	BaseRel.R = NormalizeRel(BaseRel.R);
        if(disp)
            printf("\n%s", str(TopologyName(GetTopology(BaseRel))));



	// po normalizacji
	// print input relations

        if(disp)
        {
            printf("Po normalizacji\n");
            printRelations(BaseRel.R, 1);
        }


	if(BaseRel.R.length() > 1)
		R_Orig = globalUnion(BaseRel.R);
	else
		R_Orig = BaseRel.R[1];

	// correct statements and extend relations with dimension of statement
	//BaseRel = CorrectStatements(BaseRel);

        if(disp)
            printRelations(BaseRel.R, 1);

    if(Preprocessing)
	BaseRel = Ext_Base(BaseRel);
	//printRelations(BaseRel.R, 1);



	Rel_Struct Sources;

	//try to reduce relations
        if(disp)
            printf("Try to reduce some relations\n");


// NOT IMPLEMENTED LINUX
	    BaseRel = PrepareRelations(BaseRel);

        if(disp)
            printRelations(BaseRel.R, 1);
        for(i=1; i<=BaseRel.R.length(); i++)
            BaseRel.R[i] = Repair_Relation(BaseRel.R[i]);

        //exit(0);

	printf("\n\nTopology: %s\n", str(TopologyName(GetTopology(BaseRel))));

       // exit(0);


Relation R = globalUnion(BaseRel.R), Rs;


	//independent statements
	String IND_LOOP = " ";



	printf("\n-------------------------------------------------------------------------------------\n");
	printf("Sources of Slices\n\n");

	return Sources = CalcSources(BaseRel, 1);



}



void Gen_affine(Rel_Struct Sources, ComplexRelation BaseRel)
{
                BaseRel = PrepareRelations(BaseRel);

                Tuple<String> Loops;
				GenCodeScanSlices(Sources, BaseRel, "", true, &Loops, false);
               // double end2 = gettime();
                //printf("\n--------> Czas obliczenia poczatkow: %.2f\n", (double)((end2 - begin2)));

				for(int i=1; i<=Sources.R.length(); i++)
                {
					printf("Parallel loop for affine dependences :\n\n%s\n", str(Loops[i]));
                }


}
