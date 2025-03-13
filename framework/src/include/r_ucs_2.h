void S_Add_Exist2(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10], Tuple<Variable_ID> Sym);

Relation Create_New_R_UCS(Relation R, Relation UDS, Relation UDSi, Relation Rstar, int display)
{
    int n = UDS.n_set();

    Relation S(n);
    S = SymbolicTuple(n);
    S.simplify();
  //  S.print();
    if(display)
        S.print_with_subs();

    R.simplify(2, 4);

    UDSi.simplify(2, 4);
   // UDSi.print_with_subs();

    Relation Sx = Intersection(copy(S), copy(UDSi));
    Sx.simplify(2, 4);

    Relation Rs = Rstar;
    Rs.simplify(2, 4);

    Relation S1 = Range(Restrict_Domain(copy(Rs), copy(Sx)));
    S1.simplify(2, 4);

    Relation Ris = Inverse(copy(Rs));
    Ris.simplify(2, 4);

    Relation S2 = Intersection(Range(Restrict_Domain(copy(Ris), copy(S1))), copy(UDS));   // All_UDS?
    S2.simplify(2, 4);

    Relation RUCS = Cross_Product(copy(Sx), copy(S2));
    RUCS.simplify(2, 4);

    F_And *rucs_and = RUCS.and_with_and();
    Add_Lexographic_Order2(RUCS, rucs_and);

    RUCS.simplify(2, 4);

    for(int y=1; y<=n; y++)
        RUCS = Project(copy(RUCS), xi[y]);

/*
    RUCS = Project(copy(RUCS), &x1);
    if(n>=2)
    RUCS = Project(copy(RUCS), &x2);
    if(n>=3)
    RUCS = Project(copy(RUCS), &x3);
    if(n>=4)
    RUCS = Project(copy(RUCS), &x4);
    if(n>=5)
    RUCS = Project(copy(RUCS), &x5);
*/
   // RUCS.print_with_subs();

    return RUCS;


}





// ----------------------------------------------------------------------------------------------------------------

void S_Add_Exist2(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10], Variable_ID symx[10])
{

	Variable_ID sym[1000];	// tablica symboli w r1
	Variable_ID r1ex[1000];  // to tablica zmiennych w r1 w ograniczeniach exists
	Tuple<String> r1_ex_s;

	int i, pos, cn, j=0, k=0, ii, add_ok;  //j - ile symb w r1, k ile zmiennych exists w r1



	// odczytaj zmienne symboliczne w r1
	for(DNF_Iterator di2(r1.query_DNF()); di2; di2++)    // r1 !!!!!!
	{

		for(Variable_Iterator vi(*(*di2)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd == Global_Var)
					{
						add_ok = 1;
						for(i=0; i<j; i++)
							if(strcmp(sym[i]->char_name(), vv->char_name())==0)
								add_ok = 0;

						if(add_ok)
						{
							sym[j] = vv;
							j++;
						}
					}

		}

	}



	// odczytaj zmienne exists w r1
	for(DNF_Iterator di3(r1.query_DNF()); di3; di3++)
	{

		for(Variable_Iterator vi(*(*di3)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd != Input_Var && vd != Output_Var && vd != Set_Var && vd != Global_Var)
					{

							add_ok = 1;

							for(i=0; i<k; i++)
								if(strcmp(r1ex[i]->char_name(), vv->char_name())==0)
									add_ok = 0;

							if(add_ok)
							{
								r1ex[k] = vv;
								r1_ex_s.append(vv->name());
								k++;
								printf("**********************8!!!!!");
							}

					}

		}

	}




	//F_And *f_main = fex_and->add_and();
	F_Or *f_mainor = fex_and->add_or();

	for(DNF_Iterator di(r1.query_DNF()); di; di++)
	{
		F_Exists *f_in_ex;	// jesli sa exists to bedzie uzyte
		F_And *fand;
		F_Or *f_or;

		f_or = f_mainor->add_or();


		//sprawdz czy nie jest exists
		String s = (*di)->print_to_string(1);

		if(strstr(s, "Exists"))
		{
			f_in_ex = f_or->add_exists();
			fand = f_in_ex->add_and();
		}
		else
			fand = f_or->add_and();

		Variable_ID exists_var[10];
		int exists_var_count=0;
		String exists_var_s[50];


		// dodaj wszystkie rownosci EQ
		for(EQ_Iterator ei = (*di)->EQs(); ei; ei++)
		{

			EQ_Handle feq = fand->add_EQ();

			for(Constr_Vars_Iter cvi(*ei); cvi; cvi++)
			{


				//Var_Kind vd = (*cvi).var->kind();



				pos = -1;	// -1 oznacza ze nie jest to zmienna zbioru
				for(i=0; i<r1.n_set(); i++)
				{
					Variable_ID temp = r1.set_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
						pos = i+1;
				}


				if(pos > 0)
				{

					feq.update_coef(ex[pos-1], (*cvi).coef);

				}
				else
				{


					for(i=0; i<j; i++)
					{
						if(strcmp((*cvi).var->char_name(), "x1") ==0)
						{
						    feq.update_coef(symx[0], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x2") ==0)
						{
						    feq.update_coef(symx[1], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x3") ==0)
						{
						    feq.update_coef(symx[2], (*cvi).coef);
						    break;
						}

						if(strcmp((*cvi).var->char_name(), "x4") ==0)
						{
						    feq.update_coef(symx[3], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x5") ==0)
						{
						    feq.update_coef(symx[4], (*cvi).coef);
						    break;
						}

						if(strcmp(sym[i]->char_name(), (*cvi).var->char_name()) ==0)
						{
							Variable_ID vsymb = sym[i];
							feq.update_coef(vsymb, (*cvi).coef);

							break;
						}
					}

					for(i=1; i<=r1_ex_s.length(); i++)
					{

						if(strcmp(r1_ex_s[i], (*cvi).var->char_name()) ==0)
						{

							int added = 0;
							Variable_ID tmp_ex;

							// sprawdz czy juz wczesniej jej nie bylo
							for(ii=0; ii<exists_var_count; ii++)
								if(strcmp((*cvi).var->char_name(), exists_var_s[ii]) == 0)
								{
									added = 1; //juz dodana
									tmp_ex = exists_var[ii];
									break;
								}


							if(!added)
							{
								// dodaj do tablicy
								tmp_ex = f_in_ex->declare((*cvi).var->char_name());
								exists_var[exists_var_count] = tmp_ex;
								exists_var_s[exists_var_count] = r1_ex_s[i];
								exists_var_count++;
							//	printf("hola");
							}


							feq.update_coef(tmp_ex, (*cvi).coef);
						//	printf("|| %i %s _%i_ ||", (*cvi).coef, (*cvi).var->char_name(), r1_ex_s.length()) ;

						}
					}



				}



			}
			// dodaj stala
			cn = (*ei).get_const();

			if(cn != 0)
				feq.update_const(cn);




		}




		// dodaj wszystkie rownosci GEQ
		for(GEQ_Iterator gi = (*di)->GEQs(); gi; gi++)
		{

			GEQ_Handle fgeq = fand->add_GEQ();

			for(Constr_Vars_Iter cvi(*gi); cvi; cvi++)
			{
				//Var_Kind vd = (*cvi).var->kind();

				pos = -1;   // -1 oznacza ze nie jest to zmienna zbioru
				for(i=0; i<r1.n_set(); i++)
				{
					Variable_ID temp = r1.set_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
						pos = i+1;


				}

				if(pos > 0)
					fgeq.update_coef(ex[pos-1], (*cvi).coef);
				else
				{
					// zmeinna symb lub jakiegos exists

					for(i=0; i<j; i++)
					{
						if(strcmp((*cvi).var->char_name(), "x1") ==0)
						{
						    fgeq.update_coef(symx[0], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x2") ==0)
						{
						    fgeq.update_coef(symx[1], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x3") ==0)
						{
						    fgeq.update_coef(symx[2], (*cvi).coef);
						    break;
						}

						if(strcmp((*cvi).var->char_name(), "x4") ==0)
						{
						    fgeq.update_coef(symx[3], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x5") ==0)
						{
						    fgeq.update_coef(symx[4], (*cvi).coef);
						    break;
						}

						if(strcmp(sym[i]->char_name(), (*cvi).var->char_name()) ==0)
						{
							Variable_ID vsymb = sym[i];
							fgeq.update_coef(vsymb,(*cvi).coef);
							break;
						}
					}

					for(i=1; i<=r1_ex_s.length(); i++)
					{



						if(strcmp(r1_ex_s[i], (*cvi).var->char_name()) ==0)
						{
							// sprawdz czy juz wczesniej jej nie bylo


							int added = 0;
							Variable_ID tmp_ex;


							// sprawdz czy juz wczesniej jej nie bylo
							for(ii=0; ii<exists_var_count; ii++)
							if(strcmp((*cvi).var->char_name(), exists_var_s[ii]) == 0)
							{
								added = 1; //juz dodana
								tmp_ex = exists_var[ii];
								break;
							}

							if(!added)
							{
								// dodaj do tablicy
								tmp_ex = f_in_ex->declare((*cvi).var->char_name());
								exists_var[exists_var_count] = tmp_ex;
								exists_var_s[exists_var_count] = r1_ex_s[i];
								exists_var_count++;
							}


							fgeq.update_coef(tmp_ex, (*cvi).coef);

						}

					}



				}

			}

			// dodaj stala
			cn = (*gi).get_const();
			if(cn != 0)
				fgeq.update_const(cn);

		}




	}


}




// ------------------------------------------------------------------------------------------------------



void R_Add_Exist2(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10], int in_out, int to_out, Variable_ID symx[10])
{
	Variable_ID sym[1000];	// tablica symboli w r1
	//Variable_ID r1ex[1000];  // to tablica zmiennych w r1 w ograniczeniach exists
	Tuple<String> r1_ex_s;

	int i, ii, pos, cn, j=0, k=0;  //j - ile symb w r1, k ile zmiennych exists w r1
	int kind_var; //0 - input, 1 - output


	// odczytaj zmienne exists w r1
	for(DNF_Iterator di3(r1.query_DNF()); di3; di3++)
	{

		for(Variable_Iterator vi(*(*di3)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd != Input_Var && vd != Output_Var && vd != Set_Var && vd != Global_Var)
					{
						r1_ex_s.append(vv->name());
						//r1ex[k] = vv;
						k++;
					}

		}

	}


// tu porzelacz miedzy s1 i s2
	// odczytaj zmienne symboliczne w r1
	for(DNF_Iterator di2(r1.query_DNF()); di2; di2++)
	{

		for(Variable_Iterator vi(*(*di2)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd == Global_Var)
					{
						sym[j] = vv;
						j++;
					}

		}

	}





	//F_And *f_main = fex_and->add_and();
	F_Or *f_mainor = fex_and->add_or();


	for(DNF_Iterator di(r1.query_DNF()); di; di++)
	{


		F_Exists *f_in_ex;	// jesli sa exists to bedzie uzyte
		F_And *fand;
		F_Or *f_or;

		//sprawdz czy nie jest exists
		String s = (*di)->print_to_string(1);

		f_or = f_mainor->add_or();



		if(strstr(s, "Exists"))
		{
			f_in_ex = f_or->add_exists();
			fand = f_in_ex->add_and();
		}
		else
		{
			fand = f_or->add_and();
		}

		Variable_ID exists_var[50];
		String exists_var_s[50];
		int exists_var_count=0;



		// dodaj wszystkie rownosci EQ
		for(EQ_Iterator ei = (*di)->EQs(); ei; ei++)
		{
			EQ_Handle feq = fand->add_EQ();




			for(Constr_Vars_Iter cvi(*ei); cvi; cvi++)
			{

				//Var_Kind vd = (*cvi).var->kind();

				pos = -1;	// -1 oznacza ze nie jest to zmienna zbioru

				for(i=0; i<r1.n_inp(); i++)
				{
					Variable_ID temp = r1.input_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i+1;
						kind_var = !to_out;
					}
				}

				for(i=0; i<r1.n_out(); i++)
				{
					Variable_ID temp = r1.output_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i+1;
						kind_var = to_out;
					}
				}




				if(pos > 0)
				{
					if(kind_var)
						feq.update_coef(ex[pos-1], (*cvi).coef);
					else
					{
						if(in_out == 2)
							feq.update_coef(r2.set_var(pos), (*cvi).coef);
						else if(in_out==1)
							feq.update_coef(r2.input_var(pos), (*cvi).coef);
						else
							feq.update_coef(r2.output_var(pos), (*cvi).coef);
					}
				}
				else
				{

					// zmeinna symb lub jakiegos exists
                    for(i=0; i<j; i++)
					{

						if(strcmp((*cvi).var->char_name(), "x1") ==0)
						{
						    feq.update_coef(symx[0], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x2") ==0)
						{
						    feq.update_coef(symx[1], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x3") ==0)
						{
						    feq.update_coef(symx[2], (*cvi).coef);
						    break;
						}

						if(strcmp((*cvi).var->char_name(), "x4") ==0)
						{
						    feq.update_coef(symx[3], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x5") ==0)
						{
						    feq.update_coef(symx[4], (*cvi).coef);
						    break;
						}

						if(strcmp(sym[i]->char_name(), (*cvi).var->char_name()) ==0)
						{
							Variable_ID vsymb = sym[i];
							feq.update_coef(vsymb, (*cvi).coef);

							break;
						}



						if(strcmp(sym[i]->char_name(), (*cvi).var->char_name()) ==0)
						{
							Variable_ID vsymb = sym[i];
							feq.update_coef(vsymb, (*cvi).coef);
							break;
						}
					}


					for(i=1; i<=r1_ex_s.length(); i++)
					{



						if(strcmp(r1_ex_s[i], (*cvi).var->char_name()) ==0)
						{
							int added = 0;
							Variable_ID tmp_ex;

							// sprawdz czy juz wczesniej jej nie bylo
							for(ii=0; ii<exists_var_count; ii++)
							{

								if(strcmp((*cvi).var->char_name(), exists_var_s[ii]) == 0)
								{
									added = 1; //juz dodana
									tmp_ex = exists_var[ii];

									break;
								}
							}
							if(!added)
							{
								// dodaj do tablicy

								tmp_ex = f_in_ex->declare((*cvi).var->char_name());
								exists_var[exists_var_count] = tmp_ex;
								exists_var_s[exists_var_count] = r1_ex_s[i];

								exists_var_count++;
							}


							feq.update_coef(tmp_ex, (*cvi).coef);

							break;

						}
					}



				}
			}
			// dodaj stala
			cn = (*ei).get_const();

			if(cn != 0)
				feq.update_const(cn);



		}



		// dodaj wszystkie rownosci GEQ
		for(GEQ_Iterator gi = (*di)->GEQs(); gi; gi++)
		{

			GEQ_Handle fgeq = fand->add_GEQ();

			for(Constr_Vars_Iter cvi(*gi); cvi; cvi++)
			{
				//Var_Kind vd = (*cvi).var->kind();
				pos = -1;

				for(i=0; i<r1.n_inp(); i++)
				{
					Variable_ID temp = r1.input_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i+1;
						kind_var = !to_out;
					}
				}

				for(i=0; i<r1.n_out(); i++)
				{
					Variable_ID temp = r1.output_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i+1;
						kind_var = to_out;
					}
				}




				if(pos > 0)
				{
					if(kind_var)
						fgeq.update_coef(ex[pos-1], (*cvi).coef);
					else
					{
						if(in_out == 2)
							fgeq.update_coef(r2.set_var(pos), (*cvi).coef);
						else if(in_out==1)
							fgeq.update_coef(r2.input_var(pos), (*cvi).coef);
						else
							fgeq.update_coef(r2.output_var(pos), (*cvi).coef);
					}

				}
				else
				{
					// zmeinna symb lub jakiegos exists

					for(i=0; i<j; i++)
					{

                        if(strcmp((*cvi).var->char_name(), "x1") ==0)
						{
						    fgeq.update_coef(symx[0], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x2") ==0)
						{
						    fgeq.update_coef(symx[1], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x3") ==0)
						{
						    fgeq.update_coef(symx[2], (*cvi).coef);
						    break;
						}

						if(strcmp((*cvi).var->char_name(), "x4") ==0)
						{
						    fgeq.update_coef(symx[3], (*cvi).coef);
						    break;
						}
						if(strcmp((*cvi).var->char_name(), "x5") ==0)
						{
						    fgeq.update_coef(symx[4], (*cvi).coef);
						    break;
						}



						if(strcmp(sym[i]->char_name(), (*cvi).var->char_name()) ==0)
						{
							Variable_ID vsymb = sym[i];
							fgeq.update_coef(vsymb, (*cvi).coef);
							break;
						}
					}

					for(i=1; i<=r1_ex_s.length(); i++)
					{

						if(strcmp(r1_ex_s[i], (*cvi).var->char_name()) ==0)
						{
							int added = 0;
							Variable_ID tmp_ex;

							// sprawdz czy juz wczesniej jej nie bylo
							for(ii=0; ii<exists_var_count; ii++)
							{

								if(strcmp((*cvi).var->char_name(), exists_var_s[ii]) == 0)
								{
									added = 1; //juz dodana
									tmp_ex = exists_var[ii];

									break;
								}
							}
							if(!added)
							{
								// dodaj do tablicy

								tmp_ex = f_in_ex->declare((*cvi).var->char_name());
								exists_var[exists_var_count] = tmp_ex;
								exists_var_s[exists_var_count] = r1_ex_s[i];

								exists_var_count++;
							}

							fgeq.update_coef(tmp_ex, (*cvi).coef);
							break;

						}
					}


				}
			}

			// dodaj stala
			cn = (*gi).get_const();
			if(cn != 0)
				fgeq.update_const(cn);

		}



	}



}



/*


Relation Create_New_R_UCS(Relation R, Relation UDS, Relation UDSi, Relation Rstar, int display)
{
    int n = UDS.n_set();

    Relation S(n);
    S = SymbolicTuple(n);
    S.simplify();
    S.print();
    if(display)
        S.print_with_subs();
    // ---------------------------------------------------

    R.simplify(2, 4);
    //R.print_with_subs();

    UDSi.simplify(2, 4);
    UDSi.print_with_subs();

    Relation Sx = Intersection(copy(S), copy(UDSi));
    Sx.simplify(2, 4);
    //Sx.print_with_subs();

    Relation Rs = Rstar;
    Rs.simplify(2, 4);

    //Rs.print_with_subs();

    Relation S1 = Range(Restrict_Domain(copy(Rs), copy(Sx)));
    S1.simplify(2, 4);
    //S1.print_with_subs();

    Relation Ris = Inverse(copy(Rs));
    Ris.simplify(2, 4);

    Relation S2 = Intersection(Range(Restrict_Domain(copy(Ris), copy(S1))), copy(UDS));   // All_UDS?
    S2.simplify(2, 4);
    //S2.print_with_subs();

   // S2 = Difference(copy(S2), copy(S1));
    S2.simplify(2, 4);

    //S2.print_with_subs();


    Relation RUCS = Cross_Product(copy(Sx), copy(S2));
    RUCS.simplify(2, 4);

    F_And *rucs_and = RUCS.and_with_and();
    Add_Lexographic_Order2(RUCS, rucs_and);

    RUCS.simplify(2, 4);

    if(display)
    {
        printf("RUCS\n");
        RUCS.print();
    }

    Relation W = Range(copy(RUCS));
    W.simplify(2, 4);

    W.print_with_subs();

    Relation Z(n);

    Z = W;
    Z = Difference(copy(Z), copy(W));
    Z = Complement(Z);
    Z.simplify();

    F_And *Z_and = Z.and_with_and();
	F_Exists *fex = Z_and->add_exists();
	F_And *fex_and = fex->add_and();

    Variable_ID ex[10];
    ex[0] = fex->declare("fx1");
    if(n>=2)
    ex[1] = fex->declare("fx2");
    if(n>=3)
    ex[2] = fex->declare("fx3");
    if(n>=4)
    ex[3] = fex->declare("fx4");
    if(n>=5)
    ex[4] = fex->declare("fx5");
    Variable_ID sv[10];
    sv[0] = Z.set_var(1);
    if(n>=2)
    sv[1] = Z.set_var(2);
    if(n>=3)
    sv[2] = Z.set_var(3);
    if(n>=4)
    sv[3] = Z.set_var(4);
    if(n>=5)
    sv[4] = Z.set_var(5);


    S_Add_Exist2(W, Z, fex_and, sv, ex);
    S_Add_Exist2(UDSi, Z, fex_and, ex);

    Z.simplify();

    if(display)
        Z.print();

    Relation SS = Difference(copy(UDSi), copy(Z));
    SS.simplify();
    SS.print_with_subs();

    // R_UCS = UDS -> W : e < e'

    Relation _RUCS = Difference(copy(RUCS), copy(RUCS));
    _RUCS = Complement(_RUCS);
    _RUCS.simplify();

    F_And *_RUCS_and = _RUCS.and_with_and();
	fex = _RUCS_and->add_exists();
	fex_and = fex->add_and();

    ex[0] = fex->declare("fx1");
    if(n>=2)
    ex[1] = fex->declare("fx2");
    if(n>=3)
    ex[2] = fex->declare("fx3");
    if(n>=4)
    ex[3] = fex->declare("fx4");
    if(n>=5)
    ex[4] = fex->declare("fx5");
    sv[0] = _RUCS.output_var(1);
    if(n>=2)
    sv[1] = _RUCS.output_var(2);
    if(n>=3)
    sv[2] = _RUCS.output_var(3);
    if(n>=4)
    sv[3] = _RUCS.output_var(4);
    if(n>=5)
    sv[4] = _RUCS.output_var(5);


    R_Add_Exist2(RUCS, _RUCS, fex_and, sv, 1, 1, ex);

   // Variable_ID _x1 = RUCS.get_local(&x1);

    RUCS = Project(copy(RUCS), &x1);
    if(n>=2)
    RUCS = Project(copy(RUCS), &x2);
    if(n>=3)
    RUCS = Project(copy(RUCS), &x3);
    if(n>=4)
    RUCS = Project(copy(RUCS), &x4);
    if(n>=5)
    RUCS = Project(copy(RUCS), &x5);
    //RUCS = Project(copy(RUCS), x2.get_global_var());

    if(display)
        _RUCS.print();
        RUCS.print();

RUCS.simplify();
    S_Add_Exist2(UDSi, _RUCS, fex_and, ex);

    printf("RUCS new method\n");
    _RUCS.simplify();
    _RUCS.print_with_subs();

RUCS.print_with_subs();
//exit(0);

    W = Range(copy(_RUCS));
    W.simplify(2, 4);

    if(display)
        W.print_with_subs();

    SS = Difference(copy(UDSi), copy(W));
    SS.simplify();
    SS.print_with_subs();

// return _RUCS;
    return RUCS;



}
*/
// wywal n' na potrzeby IND
Relation SymSimplify2(Relation R)
{
    Tuple<Variable_ID> Sym, Symprim;
    int i;
    Relation Rnowe = R;

    //zbierz zmienne symboliczne
    for(DNF_Iterator di2(Rnowe.query_DNF()); di2; di2++)
    {

        for(Variable_Iterator vi(*(*di2)->variables()); vi; vi++)
        {
            Variable_ID vv = (*vi);
            Var_Kind vd = vv->kind();
            if(vd == Global_Var)
            {
                int dodac=1;

                if(strchr(vv->char_name(), '\''))
                {
                    dodac = 0;
                   // printf("%s", vv->char_name());
                    int add = 1;

                    for(i=1; i<=Symprim.length(); i++)
                    {
                        if(strcmp(vv->char_name(), Symprim[i]->char_name())==0)
                            add = 0;
                    }

                    if(add)
                        Symprim.append(vv);


                }


                for(i=1; i<=Sym.length(); i++)
                {
                    if(strcmp(vv->char_name(), replace(Sym[i]->char_name(), "'", ""))==0)
                        dodac = 0;
                }

                if(dodac)
                {
                    Sym.append(vv);
                 //   printf("%s\n", vv->char_name());
                }
            }
        }

    }

    Variable_ID ex[10];	// to tablica zmiennych e''

    for(i=1; i<=R.n_set(); i++)
        ex[i-1] = R.set_var(i);

    Rnowe = Difference(copy(Rnowe), copy(Rnowe));
    Rnowe = Complement(copy(Rnowe));
    Rnowe.simplify();
    F_And *fex_and = Rnowe.and_with_and();

    S_Add_Exist2(R, Rnowe, fex_and, ex, Sym);
 //   Rnowe.print();
    for(i=1; i<=Symprim.length(); i++)
    {
        Rnowe = Project(copy(Rnowe), Symprim[i]->get_global_var());
      //  printf("%s", Symprim[i]->char_name());
    }
    Rnowe.simplify();
    return Rnowe;


}

int GetVarSym(Tuple<Variable_ID> Sym, const char * nazwa)
{
    nazwa = replace(nazwa, "'", "");

    for(int i=1; i<=Sym.length(); i++)
    {
        if(strcmp(nazwa, Sym[i]->char_name())==0)
            return i;
    }
    return -1;
}


void S_Add_Exist2(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10], Tuple<Variable_ID> Sym)
{

	Variable_ID sym[1000];	// tablica symboli w r1
	Variable_ID r1ex[1000];  // to tablica zmiennych w r1 w ograniczeniach exists
	Tuple<String> r1_ex_s;

	int i, pos, cn, j=0, k=0, ii, add_ok;  //j - ile symb w r1, k ile zmiennych exists w r1



	// odczytaj zmienne symboliczne w r1
	for(DNF_Iterator di2(r1.query_DNF()); di2; di2++)    // r1 !!!!!!
	{

		for(Variable_Iterator vi(*(*di2)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd == Global_Var)
					{
						add_ok = 1;
						for(i=0; i<j; i++)
							if(strcmp(sym[i]->char_name(), vv->char_name())==0)
								add_ok = 0;

						if(add_ok)
						{
							sym[j] = vv;
							j++;
						}
					}

		}

	}



	// odczytaj zmienne exists w r1
	for(DNF_Iterator di3(r1.query_DNF()); di3; di3++)
	{

		for(Variable_Iterator vi(*(*di3)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd != Input_Var && vd != Output_Var && vd != Set_Var && vd != Global_Var)
					{

							add_ok = 1;

							for(i=0; i<k; i++)
								if(strcmp(r1ex[i]->char_name(), vv->char_name())==0)
									add_ok = 0;

							if(add_ok)
							{
								r1ex[k] = vv;
								r1_ex_s.append(vv->name());
								k++;

							}

					}

		}

	}




	//F_And *f_main = fex_and->add_and();
	F_Or *f_mainor = fex_and->add_or();

	for(DNF_Iterator di(r1.query_DNF()); di; di++)
	{
		F_Exists *f_in_ex;	// jesli sa exists to bedzie uzyte
		F_And *fand;
		F_Or *f_or;

		f_or = f_mainor->add_or();


		//sprawdz czy nie jest exists
		String s = (*di)->print_to_string(1);

		if(strstr(s, "Exists"))
		{
			f_in_ex = f_or->add_exists();
			fand = f_in_ex->add_and();
		}
		else
			fand = f_or->add_and();

		Variable_ID exists_var[10];
		int exists_var_count=0;
		String exists_var_s[50];


		// dodaj wszystkie rownosci EQ
		for(EQ_Iterator ei = (*di)->EQs(); ei; ei++)
		{

			EQ_Handle feq = fand->add_EQ();

			for(Constr_Vars_Iter cvi(*ei); cvi; cvi++)
			{


				//Var_Kind vd = (*cvi).var->kind();



				pos = -1;	// -1 oznacza ze nie jest to zmienna zbioru
				for(i=0; i<r1.n_set(); i++)
				{
					Variable_ID temp = r1.set_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
						pos = i+1;
				}


				if(pos > 0)
				{

					feq.update_coef(ex[pos-1], (*cvi).coef);

				}
				else
				{

                                    int indsym = GetVarSym(Sym, (*cvi).var->char_name());
                                    if(indsym > 0)
                                    {
                                        feq.update_coef(Sym[indsym], (*cvi).coef);
                                    }



                                       /* for(i=0; i<j; i++)
					{
						if(strcmp(sym[i]->char_name(), ) ==0)
						{
							//Variable_ID vsymb = sym[i];

							feq.update_coef(vsymb, (*cvi).coef);

							break;
						}
					}*/

					for(i=1; i<=r1_ex_s.length(); i++)
					{

						if(strcmp(r1_ex_s[i], (*cvi).var->char_name()) ==0)
						{

							int added = 0;
							Variable_ID tmp_ex;

							// sprawdz czy juz wczesniej jej nie bylo
							for(ii=0; ii<exists_var_count; ii++)
								if(strcmp((*cvi).var->char_name(), exists_var_s[ii]) == 0)
								{
									added = 1; //juz dodana
									tmp_ex = exists_var[ii];
									break;
								}


							if(!added)
							{
								// dodaj do tablicy
								tmp_ex = f_in_ex->declare((*cvi).var->char_name());
								exists_var[exists_var_count] = tmp_ex;
								exists_var_s[exists_var_count] = r1_ex_s[i];
								exists_var_count++;
							//	printf("hola");
							}


							feq.update_coef(tmp_ex, (*cvi).coef);
						//	printf("|| %i %s _%i_ ||", (*cvi).coef, (*cvi).var->char_name(), r1_ex_s.length()) ;

						}
					}



				}



			}
			// dodaj stala
			cn = (*ei).get_const();

			if(cn != 0)
				feq.update_const(cn);




		}




		// dodaj wszystkie rownosci GEQ
		for(GEQ_Iterator gi = (*di)->GEQs(); gi; gi++)
		{

			GEQ_Handle fgeq = fand->add_GEQ();

			for(Constr_Vars_Iter cvi(*gi); cvi; cvi++)
			{
				//Var_Kind vd = (*cvi).var->kind();

				pos = -1;   // -1 oznacza ze nie jest to zmienna zbioru
				for(i=0; i<r1.n_set(); i++)
				{
					Variable_ID temp = r1.set_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
						pos = i+1;


				}

				if(pos > 0)
					fgeq.update_coef(ex[pos-1], (*cvi).coef);
				else
				{
					// zmeinna symb lub jakiegos exists
                                       int indsym = GetVarSym(Sym, (*cvi).var->char_name());
                                       if(indsym > 0)
                                       {
                                           fgeq.update_coef(Sym[indsym], (*cvi).coef);
                                       }

                                        /*
					for(i=0; i<j; i++)
					{
						if(strcmp(sym[i]->char_name(), (*cvi).var->char_name()) ==0)
						{
							Variable_ID vsymb = sym[i];
							fgeq.update_coef(vsymb,(*cvi).coef);
							break;
						}
					}*/

					for(i=1; i<=r1_ex_s.length(); i++)
					{



						if(strcmp(r1_ex_s[i], (*cvi).var->char_name()) ==0)
						{
							// sprawdz czy juz wczesniej jej nie bylo


							int added = 0;
							Variable_ID tmp_ex;


							// sprawdz czy juz wczesniej jej nie bylo
							for(ii=0; ii<exists_var_count; ii++)
							if(strcmp((*cvi).var->char_name(), exists_var_s[ii]) == 0)
							{
								added = 1; //juz dodana
								tmp_ex = exists_var[ii];
								break;
							}

							if(!added)
							{
								// dodaj do tablicy
								tmp_ex = f_in_ex->declare((*cvi).var->char_name());
								exists_var[exists_var_count] = tmp_ex;
								exists_var_s[exists_var_count] = r1_ex_s[i];
								exists_var_count++;
							}


							fgeq.update_coef(tmp_ex, (*cvi).coef);

						}

					}



				}

			}

			// dodaj stala
			cn = (*gi).get_const();
			if(cn != 0)
				fgeq.update_const(cn);

		}




	}


}

