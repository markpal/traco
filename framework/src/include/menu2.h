void OneTouch(ComplexRelation BaseRel, Relation LD)
{
	ComplexRelation *BaseOut = new ComplexRelation;
	char item;
	int i;
	Relation R_Orig;
        
	// print input relations
	printRelations(BaseRel.R, 1);
     
	// extend to equal dimensions
	BaseRel.R = NormalizeRel(BaseRel.R);
printf("\n%s", str(TopologyName(GetTopology(BaseRel))));


	// po normalizacji
	// print input relations
	printf("Po normalizacji\n");
	printRelations(BaseRel.R, 1);
     

	if(BaseRel.R.length() > 1)
		R_Orig = globalUnion(BaseRel.R);
	else
		R_Orig = BaseRel.R[1];

	// correct statements and extend relations with dimension of statement
	//BaseRel = CorrectStatements(BaseRel);
	printRelations(BaseRel.R, 1);


	//BaseRel = Ext_Base(BaseRel);
	//printRelations(BaseRel.R, 1);



	Rel_Struct Sources;

	//try to reduce relations
	printf("Try to reduce some relations\n");


// NOT IMPLEMENTED LINUX
	BaseRel = PrepareRelations(BaseRel);

	printRelations(BaseRel.R, 1);

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

	printf("\n\nTopology: %s\n", str(TopologyName(GetTopology(BaseRel))));

       // exit(0);
Relation R = globalUnion(BaseRel.R), Rs;
R.simplify();

R.print_with_subs();
printf("\n==\n");


//zmierzyc czas
    Rs = Star(copy(R), 1);
// ---


    Rs.print_with_subs();
 //   Rs.simplify(2, 4);
  //  Rs = SimplifyNumConjuncts(Rs);
  //  Rs = InteSymp(Rs);
//exit(0);
Rs.print_with_subs();

  //
printf("\n\n*** %i ***\n\n", Rs.number_of_conjuncts());
  //  R.print()



/*
	BaseRel = readSCC(petitLoopfilename, BaseRel);

	for(i=1; i<=BaseRel.R.length(); i++)
		printf("Relation %i SCC %i,  From %i To %i\n", i, BaseRel.SCC[i], BaseRel.From[i-1], BaseRel.To[i-1]);

*/

	//independent statements
	String IND_LOOP = " "; //GenerateINDLoop(LD, R_Orig);
//exit(0);


	printf("\n-------------------------------------------------------------------------------------\n");
	printf("Sources of Slices\n\n");

	//calculate sources of slices
	if(1)

// zmierzyc czas
	Sources = CalcSources(BaseRel, 1);
// !!!!


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

        exit(0);

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


	scanf("%c", &item);

	switch(item)
	{

		case '0' :
			{
				Tuple<String> Loops;
				GenCodeScanSlices(Sources, BaseRel, IND_LOOP, true, &Loops);

				for(i=1; i<=Sources.R.length(); i++)
					printf("Parallel loop for affine dependences :\n\n%s\n", str(Loops[i]));

				break;
			}
		case '1' : // chain
			{

				for(i=1; i<=Sources.R.length(); i++)
					GenerateChainsWhileLoopFromSourcesOfSlices(BaseRel.R, Sources.R[i], false);
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
			
		default :
			{
				printf("\nNot yet implemented\n");
			}
	}

	//	if(strcmp(IND_LOOP, "FALSE\n") != 0)
	//	printf("\nIND_LOOP\n%s", str(IND_LOOP));

	exit(0);
}
