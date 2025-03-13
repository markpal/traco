//generowanie grafu


void GenerateGraphWhileLoop(ComplexRelation BaseRel, bool disp_details, String INDLOOP, String outloopUDS = "thread UDS")
{
	int i;

    CodeEngine::GraphWhile *gw  = new CodeEngine::GraphWhile();


	Relation R = BaseRel.R[1];

	if(BaseRel.R.length() > 1)
		for(i=2; i<=BaseRel.R.length(); i++)
			R = Union(copy(R), copy(BaseRel.R[i]));


	R.simplify();

	if(strcmp(outloopUDS, "thread UDS") == 0)
	{
		Relation UDS = Difference(Domain(copy(R)), Range(copy(R)));
		outloopUDS = LoopCodeGen(UDS, 0);
	}

    gw->_AddElement(std::string("#Relacja"), Str2string(R2String(R)));
    gw->_AddElement(std::string("#Loop_UDS"), Str2string(outloopUDS));

	// Zapisz wszystkie relacje

	for(i=1; i<=BaseRel.R.length(); i++)
	{
		Relation TMP = BaseRel.R[i], TMP2;

        gw->_AddElement(std::string("#R_i"), Str2string(R2String(TMP)));

		TMP2 = Domain(copy(TMP));
		TMP2.simplify(2,4);

        gw->_AddElement(std::string("#Domain_i"), Str2string(R2String(TMP2)));

		TMP2 = Range(copy(TMP));
		TMP2.simplify(2,4);

       gw->_AddElement(std::string("#Range_i"), Str2string(R2String(TMP2)));

	}

    gw->_AddElement(std::string("#Loop_IND"), Str2string(INDLOOP));


	if(disp_details)
	{
		printf("Relacja R: \n");
		R.print();

		for(i=1; i<=BaseRel.R.length(); i++)
		{
			Relation TMP = BaseRel.R[i];
			printf("Relacja R%i: \n",i);
			TMP.print();
		}

		// Zapisz wszystkie dziedziny
		for(i=1; i<=BaseRel.R.length(); i++)
		{
			Relation TMP = BaseRel.R[i];
			TMP = Domain(copy(TMP));
			TMP.simplify(2,4);
			printf("Domain_R%i: \n",i);
			TMP.print();
		}


		// Zapisz wszystkie range
		for(i=1; i<=BaseRel.R.length(); i++)
		{

			Relation TMP = BaseRel.R[i];
			TMP = Range(copy(TMP));
			TMP.simplify(2,4);
			printf("Range_R%i: \n",i);
			TMP.print();
		}

		printf("\nPetla IND:\n");
		PrintString(outloopUDS);
		printf("\nPetla IND:\n");
		PrintString(INDLOOP);

	}

    std::string petla = gw->_OneRun();
    cout << endl << endl << petla;



}
