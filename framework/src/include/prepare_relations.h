ComplexRelation PrepareRelations(ComplexRelation BaseRel, int only_extend=0)
{

	//ComplexRelation *BaseOut = new ComplexRelation;


	//int DISPLAY = 0;

        if(disp)
	printf("\n%s\n", str(TopologyName(GetTopology(BaseRel))));

	//step 1. - normalize


	//step 2. - extend by additional variable of statement

	//BaseRel = Ext_Base(BaseRel);

	//if(only_extend)
	//	return BaseRel;
	//step 3. - transitive reduction
       // Relation Z = globalUnion(BaseRel.R);
      //  Z.simplify();
      //  Z.print_with_subs();
       // exit(0);
       // if(DISPLAY)

printRelations(BaseRel.R, 1);

//algorytm1(BaseRel, BaseOut, DISPLAY);   //usuwaj relacje z false, pozbedziemy sie tez tozsamosci

//BaseRel = *BaseOut;
//BaseOut = new ComplexRelation;

	//step 4. - krzysiek's algorithms
//printRelations(BaseRel.R, 1);

//printf("R-\n");



	//algorytm02a(BaseRel, BaseOut, true);
	//BaseRel = *BaseOut;
	//BaseOut = new ComplexRelation;
//printRelations(BaseRel.R, 1);

 //printKindRelInfo(BaseRel);

	//algorytm02(BaseRel, BaseOut, true);
	//BaseRel = *BaseOut;
	//BaseOut = new ComplexRelation;
	if(!_SILENT)
printRelations(BaseRel.R, 1);
//exit(0);

      //  printKindRelInfo(BaseRel);

//	algorytm02b(BaseRel, BaseOut, true);
//	BaseRel = *BaseOut;
//	BaseOut = new ComplexRelation;
//printRelations(BaseRel.R, 1);

// !!!!!!!!!!!!!!!!!!
//exit(0);
	//printf("\n%s\n", str(TopologyName(GetTopology(BaseRel))));

	//printRelations(BaseRel.R, 1);





	//	algorytm2(BaseRel, BaseOut, DISPLAY);
	// *****************

	//	BaseRel = *BaseOut;  // w BaseRel jest wszystko
		//BaseOut = new ComplexRelation;


//	algorytm2(BaseRel, BaseOut, DISPLAY);  //cos z j+1 indeksacja

//	BaseRel = *BaseOut;  // w BaseRel jest wszystko
//dble(i) * dnxm1	BaseOut = new ComplexRelation;

	// *****************

	//transitive reduction by 2

//	algorytm5(BaseRel, BaseOut, DISPLAY, 1);
//	BaseRel = *BaseOut;
	/*
	print_Relations(BaseRel.R, 1);


	Relation Z = Union(copy(BaseRel.R[3]), copy(BaseRel.R[4]));
	Z = Union(copy(Z), copy(BaseRel.R[5]));
	Z = Union(copy(Z), copy(BaseRel.R[6]));

	Z = Hull(copy(Z));
	Z.simplify();

	Relation Zb = Union(copy(BaseRel.R[7]), copy(BaseRel.R[8]));
	Zb= Union(copy(Zb), copy(BaseRel.R[9]));
	Zb = Union(copy(Zb), copy(BaseRel.R[10]));
	Zb = Hull(copy(Zb));
	Zb.simplify();

	Relation Za = Union(copy(BaseRel.R[1]), copy(BaseRel.R[2]));
	Za = Hull(copy(Za));
	Z.simplify();

	Zb = Union(copy(Z), copy(Zb));
	Zb = Hull(copy(Zb));
	Zb.simplify();

	BaseOut = new ComplexRelation;
	BaseRel = *BaseOut;
	BaseRel.R.append(copy(Za));
	BaseRel.R.append(copy(Zb));


 */


	//RemoveRedundant(BaseRel, BaseOut, false);



      //  BaseRel = *BaseOut;
      //  BaseOut = new ComplexRelation;

       // printRelations(BaseRel.R, 1);

	//BaseRel.R =  SimplifyNumRels(BaseRel.R, true);

	return BaseRel;

}



