// funkcje wspomagajaca obliczanie exists w R_UCS
#define POPRAWA_MINUSA 0
#define zm_nazwa "D"

Relation Com_Add_Exists(Relation r2, Relation IS, Relation R, int);
//funkcje pomocnicza
void Diff_Add_Exist2(Relation r2, F_And *fex_and, Variable_ID ex[10]);
void Diff_Add_Exist2(Relation r2, F_And *fex_and, Variable_ID ex[10], Variable_ID ex2[10], int);
void Add_Lexographic_Order2(Relation r2, F_And *fex_and);
void S_Add_Exist2(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10]);
void R_Add_Exist2(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10], int, int to_out = 1, int offset = 0, int unik = 0, int offset_out = 0);

Relation ReInitRel(Relation Z);
Relation RepairNameVar(Relation R);


// ------------------------------------------------------------------------------------------------------

Relation Com_Add_Exists(Relation r2, Relation IS, Relation R, int display)
{

	F_And *r2_and = r2.and_with_and();
	F_Exists *fex = r2_and->add_exists();
	F_And *fex_and = fex->add_and();

	String nazwa;
	String name_tab[10];   // tablica nazw zmiennych e''
	Variable_ID ex[10];	// to tablica zmiennych e''



	int i;
	String s = r2.print_with_subs_to_string();
	// pobierz nazwy do exists e''
	for(i=1; i<=r2.n_inp(); i++)
	{
		nazwa =  r2.input_var(i)->name();
		nazwa += "''";
		name_tab[i-1] = nazwa;
		ex[i-1] = fex->declare(nazwa);

	}



	Diff_Add_Exist2(r2, fex_and, ex);

	Add_Lexographic_Order2(r2, fex_and);

//UDSi
// do nowego includa
	S_Add_Exist2(IS, r2, fex_and, ex);


// input 1 , ex na ouputa, podmianka na symboliczne
	R_Add_Exist2(R, r2, fex_and, ex, 1);


	R_Add_Exist2(R, r2, fex_and, ex, 0);


	if(display)
	{
		printf("R_UCS przed uproszczeniem: \n");
		r2.print();
	}


	r2.simplify();


//	r2 = SimplifyNumConjuncts(r2);
//	r2 = ReduceSet(r2);
	r2.print();


	return r2;
}


// ------------------------------------------------------------------------------------------------------
// cuda z R*

// funkcja dla poczatkow
// in_out : 1 -input
//			0 -output
//			2 -set
// to_out   1 = out, 0 = in

// Z offset na input
// ZZ od ktorej zmiennej input kopiowac ograniczenia
// ZO offset na output
// !!!!!!!!!!!!!!!!!!
// trzeba zmienic !!!!!!! jak w dodawaniu zbioru dodawanie exists i symb z uwzglednianiem powtorzen


void R_Add_Exist2(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10], int in_out, int to_out, int Z, int ZZ, int ZO)
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
                                           // printf("%i\n", j);
                                            sym[j] = vv;

						j++;
					}

		}

	}
//printf("zzzzz\n");



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

				for(i=ZZ; i<r1.n_inp(); i++)   // ominiecie
				{
					Variable_ID temp = r1.input_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i+1;
						kind_var = !to_out;
                                           //     printf("%i %s\n", pos, (*cvi).var->char_name());
                                              //  exit(0);
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
							feq.update_coef(r2.input_var(pos+Z-ZZ), (*cvi).coef);
						else
							feq.update_coef(r2.output_var(pos+ZO), (*cvi).coef);
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
				pos = -1;

				for(i=ZZ; i<r1.n_inp(); i++)   //ominiecie
				{
					Variable_ID temp = r1.input_var(i+1);
					if(strcmp(temp->char_name(), (*cvi).var->char_name()) == 0)
					{
						pos = i+1;
						kind_var = !to_out;
                                       //         printf("%i %s\n", pos, (*cvi).var->char_name());
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
							fgeq.update_coef(r2.input_var(pos+Z-ZZ), (*cvi).coef);
						else
							fgeq.update_coef(r2.output_var(pos+ZO), (*cvi).coef);
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







// ------------------------------------------------------------------------------------------------------
// e ' > e

void Add_Lexographic_Order2(Relation r2, F_And *fex_and)
{
	F_And *Lex = fex_and->add_and();
	int n = r2.n_inp(), j, k;
	Variable_ID i = r2.input_var(1);
	Variable_ID ip = r2.output_var(1);
	F_Or *or_con;

	if(n == 1)
	{
		GEQ_Handle constr = Lex->add_GEQ();
		constr.update_coef(ip, 1);
		constr.update_coef(i, -1);
		constr.update_const(-1);
	}
	else
	{

		or_con = Lex->add_or();
		for(j=1; j<=n; j++)
		{




			F_And *and_con = or_con->add_and();

			if(j > 1)
			{
				for(k=1; k<=j-1; k++)
				{
					//if(k>1)
					//	F_And *and_con = or_con->add_and();


					Variable_ID i = r2.input_var(k);
					Variable_ID ip = r2.output_var(k);

					EQ_Handle tmp = and_con->add_EQ();
					tmp.update_coef(i, 1);
					tmp.update_coef(ip, -1);

					if(k == j-1)
					{
						Variable_ID i = r2.input_var(k+1);
						Variable_ID ip = r2.output_var(k+1);

						GEQ_Handle tmp2 = and_con->add_GEQ();
						tmp2.update_coef(ip, 1);
						tmp2.update_coef(i, -1);
						tmp2.update_const(-1);
					}

				}


			}
			else
			{

				Variable_ID i = r2.input_var(1);
				Variable_ID ip = r2.output_var(1);

				GEQ_Handle tmp3 = and_con->add_GEQ();
				tmp3.update_coef(ip, 1);
				tmp3.update_coef(i, -1);
				tmp3.update_const(-1);
			}



		}


	}

}

// ------------------------------------------------------------------------------------------------------
// e'' nalezy do IS

void S_Add_Exist2(Relation r1, Relation r2, F_And *fex_and, Variable_ID ex[10])
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
				{
				    fgeq.update_coef(ex[pos-1], (*cvi).coef);
				}

				else
				{
					// zmeinna symb lub jakiegos exists

					for(i=0; i<j; i++)
					{
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

// e'' jest rozne od e i e;

void Diff_Add_Exist2(Relation r2, F_And *fex_and, Variable_ID ex[10])
{

	int i;

	F_And *fex_and1 = fex_and->add_and();
	F_And *fex_and2 = fex_and->add_and();


	F_Not *f_not = fex_and1->add_not();
	F_And *f_in = f_not->add_and();

	for(i=1; i<=r2.n_inp(); i++)
	{
		F_And *tmp = f_in->add_and();
		EQ_Handle feq = tmp->add_EQ();

		feq.update_coef(r2.input_var(i), 1);
		feq.update_coef(ex[i-1], -1);
	}


	f_not = fex_and2->add_not();
	f_in = f_not->add_and();


	for(i=1; i<=r2.n_out(); i++)
	{
		F_And *tmp = f_in->add_and();
		EQ_Handle feq = tmp->add_EQ();

		feq.update_coef(r2.output_var(i), 1);
		feq.update_coef(ex[i-1], -1);
	}


}

// -----------------------------------------------------------------------------------------------------

void Diff_Add_Exist2(Relation r2, F_And *fex_and, Variable_ID ex[10], Variable_ID ex2[10], int n)
{

	int i;

	F_And *fex_and1 = fex_and->add_and();

	F_Not *f_not = fex_and1->add_not();
	F_And *f_in = f_not->add_and();

	for(i=1; i<=n; i++)
	{
		F_And *tmp = f_in->add_and();
		EQ_Handle feq = tmp->add_EQ();

		feq.update_coef(ex[i-1], 1);
		feq.update_coef(ex2[i-1], -1);
	}
}

// -----------------------------------------------------------------------------------------------------

void Add_Lexographic_Order2(Relation r2, F_And *fex_and, Tuple<Variable_ID> left, Tuple<Variable_ID> right)
{
	F_And *Lex = fex_and->add_and();
	int n = r2.n_inp(), j, k;
	Variable_ID i = left[1];
	Variable_ID ip = right[1];
	F_Or *or_con;

	if(n == 1)
	{
		GEQ_Handle constr = Lex->add_GEQ();
		constr.update_coef(ip, 1);
		constr.update_coef(i, -1);
		constr.update_const(-1);
	}
	else
	{

		or_con = Lex->add_or();
		for(j=1; j<=n; j++)
		{




			F_And *and_con = or_con->add_and();

			if(j > 1)
			{
				for(k=1; k<=j-1; k++)
				{
					//if(k>1)
					//	F_And *and_con = or_con->add_and();


					Variable_ID i = left[k];
					Variable_ID ip = right[k];

					EQ_Handle tmp = and_con->add_EQ();
					tmp.update_coef(i, 1);
					tmp.update_coef(ip, -1);

					if(k == j-1)
					{
						Variable_ID i = left[k+1];
						Variable_ID ip = right[k+1];

						GEQ_Handle tmp2 = and_con->add_GEQ();
						tmp2.update_coef(ip, 1);
						tmp2.update_coef(i, -1);
						tmp2.update_const(-1);
					}

				}


			}
			else
			{

				Variable_ID i = left[1];
				Variable_ID ip = right[1];

				GEQ_Handle tmp3 = and_con->add_GEQ();
				tmp3.update_coef(ip, 1);
				tmp3.update_coef(i, -1);
				tmp3.update_const(-1);
			}



		}


	}

}


//repair relations


Relation Repair_Relation(Relation R, Tuple<String> instr, Tuple<String> outstr, int repair=1)
{
	int n1, n2, i;

	n1 = R.n_inp();
	n2 = R.n_out();

	Relation Rn(n1, n2);

	if(repair)
	{

		Rn = Cross_Product(Domain(copy(R)), Range(copy(R)));

		Rn = Inverse(copy(Rn));

		Variable_ID ex[10];	// to tablica zmiennych e''

		for(i=1; i<=n1; i++)
			ex[i-1] = Rn.input_var(i);


		F_And *fex_and = Rn.and_with_and();

		R_Add_Exist2(R, Rn, fex_and, ex, 0, 1);
		Rn = Inverse(copy(Rn));

		Rn.simplify();
	}
	else
		Rn = R;


	for(i=1; i<=n1; i++)
		Rn.name_input_var(i, instr[i]);


	for(i=1; i<=n2; i++)
		Rn.name_output_var(i, outstr[i]);


	Rn.simplify();

	return Rn;
}



//normalizacja relacji
Tuple<Relation> NormalizeRel(Tuple<Relation> R)
{
	int in_n=0;
	int out_n=0;
	int i, diff, j;
	String in_names[10];
	String out_names[10];
	Tuple<String> instr;
	Tuple<String> outstr;
	int z = 1;

	if(0)
	{
	R[3] = Union(copy(R[1]), copy(R[3]));
					R[3].print();
	}



	for(i=1; i<=R.length(); i++)
	{
		if(R[i].n_inp() > in_n)
		{
			int in_old = in_n;
			in_n = R[i].n_inp();
			for(j=in_old; j<in_n; j++)
			{
				in_names[j] = R[i].input_var(j+1)->name();
				instr.append(in_names[j]);
                                //printf("%i %s\n",j,str(in_names[j]));
			}

		}

		if(R[i].n_out() > out_n)
		{
			int out_old = out_n;
			out_n = R[i].n_out();
			for(j=out_old; j<out_n; j++)
			{
				out_names[j] = R[i].output_var(j+1)->name();
				outstr.append(out_names[j]);
			}

		}
	}



	if(in_n > out_n)
	{
		for(int w=out_n+1; w<=in_n; w++)
		    outstr.append(instr[w] + "'");

		out_n = in_n;


	}

	if(out_n > in_n)
	{
        for(int w=in_n+1; w<=out_n; w++)
		    outstr.append(outstr[w] + "'");


		in_n = out_n;


	}




	for(i=1; i<=R.length(); i++)
	{

		diff = in_n - R[i].n_inp();

		if(diff > 0)
		{




			R[i] = Extend_Domain(copy(R[i]), diff);
			for(j=in_n-diff+1; j<=in_n; j++)
			{
				F_And *and_con = R[i].and_with_and();
				Variable_ID vi = R[i].input_var(j);
				EQ_Handle tmp = and_con->add_EQ();

//				Variable_ID qq = R[i].get_local(&q);

				tmp.update_coef(vi, 1);
				tmp.update_const(z);
				//tmp.update_coef(qq, -1);

				R[i].simplify(2, 5);


			}
/*
			for(j=0; j<in_n; j++)
			{
				if(strcmp(in_names[j],"") == 0)
					R[i].name_input_var(j+1,out_names[j]);
				else
					R[i].name_input_var(j+1,in_names[j]);
			}
			*/

		}

		diff = out_n - R[i].n_out();

		if(diff > 0)
		{
			R[i] = Extend_Range(copy(R[i]), diff);

			for(j=in_n-diff+1; j<=out_n; j++)
			{
				F_And *and_con = R[i].and_with_and();
				Variable_ID vi = R[i].output_var(j);
				EQ_Handle tmp = and_con->add_EQ();



				// eksperymentalnie dla UTDSP
				if(POPRAWA_MINUSA)
				{

					Variable_ID b_n;


					   b_n = FindSym(R[1], zm_nazwa);



					tmp.update_coef(vi, 1);


					tmp.update_coef(b_n, -1);

					tmp.update_const(-1);


				}
				// ------------
				else
				{
					tmp.update_coef(vi, 1);
					tmp.update_const(z);
				}



				R[i].simplify(2, 5);

			}
/*
			for(j=0; j<out_n; j++)
			{
				if(strcmp(out_names[j],"") == 0)
					R[i].name_output_var(j+1,in_names[j]);
				else
					R[i].name_output_var(j+1,out_names[j]);
			}
			*/
		}

		//R[i].finalize();

		R[i].simplify();
	//	R[i] = ReInitRel(R[i]);

		//R[i].print();

	//	R[i] = Repair_Relation(R[i], instr, outstr, 1);

	}
//	exit(0);

	instr.append("v");

	outstr.append("v'");



	for(i=1; i<=instr.length(); i++)
	{
		ginstr.append(instr[i]);
               // printf("%s\n", str(instr[i]));
	}

	for(i=1; i<=outstr.length(); i++)
	{
		goutstr.append(outstr[i]);
               // printf("%s\n", str(outstr[i]));
	}





	return R;

}


Relation Repair_Relation(Relation R)
{
	int n1, n2, i;

	n1 = R.n_inp();
	n2 = R.n_out();

	Relation Rn(n1, n2);


		Rn = Cross_Product(Domain(copy(R)), Range(copy(R)));

		Rn = Inverse(copy(Rn));

		Variable_ID ex[10];	// to tablica zmiennych e''

		for(i=1; i<=n1; i++)
			ex[i-1] = Rn.input_var(i);

		F_And *fex_and = Rn.and_with_and();

		R_Add_Exist2(R, Rn, fex_and, ex, 0, 1);


		Rn = Inverse(copy(Rn));

		Rn.simplify();
/*
	for(i=1; i<=n1; i++)
		Rn.name_input_var(i, ginstr[i]);


	for(i=1; i<=n2; i++)
		Rn.name_output_var(i, goutstr[i]);
*/

	return Rn;
}

Relation RepairNameVar(Relation R)
{

	int i;

	if(!R.is_set())
	{

	for(i=1; i<=R.n_inp(); i++)
		R.name_input_var(i, ginstr[i]);


	for(i=1; i<=R.n_out(); i++)
		R.name_output_var(i, goutstr[i]);

	}
	else
	{
		for(i=1; i<=R.n_set(); i++)
			R.name_set_var(i, ginstr[i]);

	}

	return R;
}




Relation ReInitRel(Relation Z)
{
    Relation RX = Difference(copy(Z), copy(Z));
    RX = Complement(copy(RX));
    RX.simplify();
    F_And *fex_and = RX.and_with_and();
    Variable_ID ex[10];

    for(int u=1; u<=RX.n_inp(); u++)
        ex[u-1] = RX.input_var(u);

    R_Add_Exist2(Z, RX, fex_and, ex, 0, 0);

    RX.simplify();
    //RX.print();

    return RX;
}

