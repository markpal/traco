void GenerateTreeWhileLoop(ComplexRelation BaseRel, Relation UDS, String INDLOOP, bool disp_details )
{
    int i;

    String outloopUDS, outloopIND;

    CodeEngine::TreeWhile *tw  = new CodeEngine::TreeWhile();

    Tuple<Relation> Rels = BaseRel.R;

	Relation R = Rels[1];

	for(i=1; i<=Rels.length(); i++)
	{
		R = Union(copy(R), copy(Rels[i]));
	}

	Relation Sources = UDS;


	// **********************************************************************************************************

    //petla UDS
	outloopUDS = LoopCodeGen(Sources, 0);

	outloopIND = "FALSE\n";

    tw->_AddElement(std::string("#Relacja"), Str2string(R2String(R)));
    tw->_AddElement(std::string("#Loop_UDS"), Str2string(outloopUDS));
    tw->_AddElement(std::string("#Loop_IND"), Str2string(outloopIND));

	for(i=1; i<=Rels.length(); i++)
	{
		Relation TMP = Rels[i];

        tw->_AddElement(std::string("#R_i"), Str2string(R2String(TMP)));

		TMP = Domain(copy(TMP));
		TMP.simplify(2, 4);

        tw->_AddElement(std::string("#Domain_i"), Str2string(R2String(TMP)));

	}

	if(disp_details)
	{
		printf("Relacja R: \n");
		R.print();
		printf("Poczatki wlasciwe UDS: \n");
		Sources.print();
		printf("\n\n");
		PrintString(outloopUDS);
		printf("Iterache niezalezne IND:");
		PrintString(outloopIND);
		printf("\n\n**************************************************************************\n\n");
		printf("\n\n");
	}

    std::string petla = tw->_OneRun();
    cout << endl << endl << petla;

}
