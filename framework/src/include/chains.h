void GenerateChainsWhileLoopFromSourcesOfSlices(Tuple<Relation> Rels, Relation Sources, bool disp_details)
{
    String outloopUDS, outloopIND;
    unsigned int i=1;

    CodeEngine::ChainWhile *cw  = new CodeEngine::ChainWhile();


    //Wspolna relacja R
    Relation R = Rels[1];

    for(i=1; i<=Rels.length(); i++)
    {
            R = Union(copy(R), copy(Rels[i]));
    }

    R.simplify();

    //petla UDS
    outloopUDS = LoopCodeGen(Sources, 0);

    outloopIND = "FALSE\n";

    cw->_AddElement(std::string("#Relacja"), Str2string(R2String(R)));
    cw->_AddElement(std::string("#Loop_UDS"), Str2string(outloopUDS));
    cw->_AddElement(std::string("#Loop_IND"), Str2string(outloopIND));

    for(i=1; i<=Rels.length(); i++)
    {
        Relation TMP = Rels[i];

        cw->_AddElement(std::string("#R_i"), Str2string(R2String(TMP)));

        TMP = Domain(copy(TMP));
        TMP.simplify(2, 4);

        cw->_AddElement(std::string("#Domain_i"), Str2string(R2String(TMP)));

    }

    if(disp_details)
    {
            printf("Relacja R: \n");
            R.print();
            printf("Poczatki wlasciwe UDS: \n");
            Sources.print();
            printf("\n \n");
            PrintString(outloopUDS);
            printf("Iterache niezalezne IND: ");
            PrintString(outloopIND);
            printf("\n\n**************************************************************************\n\n");
            printf("\n\n");
    }

    std::string petla = cw->_OneRun();
    cout << endl << endl << petla;


}


void GenerateChainsSingleWhileLoop(Relation Rprim, String SourceLoop, bool disp_details)
{
	String outloopUDS;
	int i=1;

	CodeEngine::ChainWhile *cw  = new CodeEngine::ChainWhile();


	Tuple<Relation> R_SET;  // R' podzielone na OR
        //void* args [2];
       // MonoObject *obj = GetObject("ChainWhile");
       // MonoMethod *met = GetMethod("AddElement");
       // MonoString *str, *str2;



	R_SET = Divide_Relation(Rprim);

	//Wspolna relacja R
	Relation R = R_SET[1];

	for(i=2; i<=R_SET.length(); i++)
	{
		R = Union(copy(R), copy(R_SET[i]));
	}

	R.simplify();

/*
        str = mono_string_new (domain, "#Relacja"); args[0] = str;
        str2 = mono_string_new (domain, R2String(R)); args[1] = str2;
        mono_runtime_invoke (met, obj, args, NULL);


        str = mono_string_new (domain, "#Loop_UDS"); args[0] = str;
        str2 = mono_string_new (domain, outloopUDS); args[1] = str2;
        mono_runtime_invoke (met, obj, args, NULL);

*/
    cw->_AddElement(std::string("#Relacja"), Str2string(R2String(R)));
    cw->_AddElement(std::string("#Loop_UDS"), Str2string(outloopUDS));

	for(i=1; i<=R_SET.length(); i++)
	{
            Relation TMP = R_SET[i];

        //    str = mono_string_new (domain, "#R_i"); args[0] = str;
         //   str2 = mono_string_new (domain,  R2String(TMP)); args[1] = str2;
         //   mono_runtime_invoke (met, obj, args, NULL);

         cw->_AddElement(std::string("#R_i"), Str2string(R2String(TMP)));

            TMP = Domain(copy(TMP));
            TMP.simplify(2, 4);

       //     str = mono_string_new (domain, "#Domain_i"); args[0] = str;
       //     str2 = mono_string_new (domain,  R2String(TMP)); args[1] = str2;
       //     mono_runtime_invoke (met, obj, args, NULL);
       cw->_AddElement(std::string("#Domain_i"), Str2string(R2String(TMP)));
		//TMP.print();

	}

	if(disp_details)
	{
		printf("Relacja R: \n");
		R.print();
		printf("Poczatki wlasciwe UDS: \n");
		PrintString(outloopUDS);
//		printf("\n%s \n", str(outloopUDS));
	}

	printf("Generating code WhileLoop...");

      //  met = GetMethod("GenerateSingleWhileLoop");
      //  mono_runtime_invoke (met, obj, NULL, NULL);
      cw->GenerateSingleWhileLoop();

   //     MonoClear();



}


void All_GenerateChains(String SourceLoop, int current, int count, String IND)
{
    int first, last;
   // void* args [2];
  //  MonoObject *obj = GetObject("ChainWhile");
   // MonoMethod *met = GetMethod("AddElement");
   // MonoString *str, *str2;
   CodeEngine::ChainWhile *cw  = new CodeEngine::ChainWhile();


    if(current == 1)
            first = 1;
    else
            first = 0;

    if(current == count)
            last = 1;
    else
            last = 0;


   // str = mono_string_new (domain, "#Loop_UDS"); args[0] = str;
   // str2 = mono_string_new (domain, SourceLoop); args[1] = str2;
   // mono_runtime_invoke (met, obj, args, NULL);

   // str = mono_string_new (domain, "#Loop_IND"); args[0] = str;
    //str2 = mono_string_new (domain, IND); args[1] = str2;
    //mono_runtime_invoke (met, obj, args, NULL);

    cw->_AddElement(std::string("#Loop_UDS"), Str2string(SourceLoop));
    cw->_AddElement(std::string("#Loop_IND"), Str2string(IND));

   // args[0] = &first;
  //  args[1] = &last;

  //  met = GetMethod("GenerateAggregatedWhileLoop");
   // mono_runtime_invoke (met, obj, args, NULL);
    cw->GenerateAggregatedWhileLoop(first, last);


  //  MonoClear();

}
