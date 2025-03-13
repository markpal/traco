void MakeR(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10],int n);

Relation NewDep(Relation R)
{
    //R.print();
    int n = (R.n_inp()-1)/2;

    Relation Dom = Domain(copy(R));
    Dom = Extend_Set(copy(Dom));
    Dom = RemoveHalf(Dom);

    Relation r2 = Cross_Product(copy(Dom), copy(Dom));
    r2 = Complement(Intersection(copy(r2), Complement(copy(r2))));
    r2.simplify();
    //r2.print();
    //Relation r2(n+1,n+1);
	F_And *r2_and = r2.and_with_and();
	F_Exists *fex = r2_and->add_exists();
	F_And *fex_and = fex->add_and();

	String nazwa;
	String name_tab[10];   // tablica nazw zmiennych e''
	Variable_ID ex[10];	// to tablica zmiennych e''



	int i,j=1;

	for(i=1; i<=n; i++)
	{
	    r2.name_input_var(i, R.input_var(i)->name());
	    r2.name_output_var(i, R.output_var(i)->name());

	}

	r2.name_input_var(n+1, R.input_var(n*2+1)->name());
    r2.name_output_var(n+1, R.output_var(n*2+1)->name());

	// pobierz nazwy do exists
	for(i=n+1; i<=n*2; i++)
	{
		nazwa =  R.input_var(i)->name();
		name_tab[j-1] = nazwa;
		ex[j-1] = fex->declare(nazwa);
		j++;
	}

	for(i=n+1; i<=n*2; i++)
	{
        nazwa =  R.output_var(i)->name();
		name_tab[j-1] = nazwa;
		ex[j-1] = fex->declare(nazwa);
		j++;

	}

	//EQ_Handle xvalue = fex_and->add_EQ();
	//xvalue.update_const(-1);
    //xvalue.update_coef(r2.input_var(1), 1);

   MakeR(R, r2, fex_and, ex,n);
   //r2.print();
    r2.simplify();

  //  r2.print();
   return r2;

    //R_Add_Exist2(R, r2, fex_and, ex, 0);


}
void MakeR(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10],int n)
{
	Variable_ID sym[1000];	// tablica symboli w r1
	//Variable_ID r1ex[1000];  // to tablica zmiennych w r1 w ograniczeniach exists
	Tuple<String> r1_ex_s;

    int i, ii, pos, cn, j=0, k=0;  //j - ile symb w r1, k ile zmiennych exists w r1
	int inp;


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

				pos = 0;	// -1 oznacza ze nie jest to zmienna zbioru

				for(i=1; i<=r1.n_inp(); i++)   // ominiecie
				{
					Variable_ID temp = r1.input_var(i);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i;
						inp = 1;

					}
				}

				for(i=1; i<=r1.n_out(); i++)
				{
					Variable_ID temp = r1.output_var(i);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i;
						inp = 0;
					}
				}




				if(pos > 0)
				{
					if(inp)
					{
					    if(pos>=n+1 && pos <=n*2)
                            feq.update_coef(ex[pos-1-n], (*cvi).coef);
                        else
                        {
                            pos = ((pos == 2*n+1) ? n+1 : pos);
                            feq.update_coef(r2.input_var(pos), (*cvi).coef);
                        }

					}
					else
					{
					    if(pos>=n+1 && pos <=n*2)
                            feq.update_coef(ex[pos-1], (*cvi).coef);
                        else
                        {
                            pos = ((pos == 2*n+1) ? n+1 : pos);
                            feq.update_coef(r2.output_var(pos), (*cvi).coef);
                        }

					}
				}
				else
				{

					// zmeinna symb lub jakiegos exists

					for(i=0; i<j; i++)
					{
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

				pos = 0;	// -1 oznacza ze nie jest to zmienna zbioru

				for(i=1; i<=r1.n_inp(); i++)   // ominiecie
				{
					Variable_ID temp = r1.input_var(i);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i;
						inp = 1;

					}
				}

				for(i=1; i<=r1.n_out(); i++)
				{
					Variable_ID temp = r1.output_var(i);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i;
						inp = 0;
					}
				}




				if(pos > 0)
				{
					if(inp)
					{
					    if(pos>=n+1 && pos <=n*2)
                            fgeq.update_coef(ex[pos-1-n], (*cvi).coef);
                        else
                        {
                            pos = ((pos == 2*n+1) ? n+1 : pos);
                            fgeq.update_coef(r2.input_var(pos), (*cvi).coef);
                        }

					}
					else
					{
					    if(pos>=n+1 && pos <=n*2)
                            fgeq.update_coef(ex[pos-1], (*cvi).coef);
                        else
                        {
                            pos = ((pos == 2*n+1) ? n+1 : pos);
                            fgeq.update_coef(r2.output_var(pos), (*cvi).coef);
                        }

					}
				}
				else
				{
					// zmeinna symb lub jakiegos exists

					for(i=0; i<j; i++)
					{
						if(strcmp(sym[i]->char_name(), (*cvi).var->char_name()) ==0)
						{
							//printf("%s\n", sym[i]->char_name());
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
