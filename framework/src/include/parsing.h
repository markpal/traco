/* biblioteka oparta na BOOST REGEX */

// deklaracje
Free_Var_Decl* GetFVDByName(String name);
Tuple<String> s1GetVariables(Tuple<String> wektory);
int GetIdVar(Tuple<Variable_ID> zmienne, String nazwa);

//zwraca z petli wektory umieszczone w s1(....)
Tuple<String> GetLoop_s1_vectors(String petla1)
{
	Tuple<String> *wektory = new Tuple<String>;


	//char petla1[4048];
	//sprintf(petla1, "%s", LoopCodeGen(Sources.R[1], 0));

	std::string fb(petla1);

	// fb stores a fragment of html code, multiline;
	boost::regex pattern("(s1[^;]*\\))");
	//boost::cmatch res;
	boost::match_flag_type flags = boost::match_default;
	std::string::const_iterator s , e;
	s = fb.begin();
	e = fb.end();
	boost::match_results<std::string::const_iterator> res;


	while(boost::regex_search(s, e, res, pattern, flags))
	{
		std::string url(res[1].first, res[1].second);

		boost::regex pat("(s1\\()|(\\))");
		url = boost::regex_replace(url,  pat, "");

		url += ",";

		wektory->append(url.c_str());
		//printf("!!!!!!!!!!! %s", url.c_str());

		s = res[1].second;

	}

	return *wektory;
}



Relation String2Set(String input, Tuple<Variable_ID> symb_native, Relation Z)
{
	Tuple<String> poz_wekt;
	Tuple<String> names; names.append("i"); names.append("j"); names.append("k"); names.append("l"); names.append("m");
	Tuple<Variable_ID> symb;
	Tuple<String> own_var_symb;
	Tuple<String> inp_tmp;


	int j, iii;

	Relation R;

	inp_tmp.append(input);

	own_var_symb = s1GetVariables(inp_tmp);



	//wyparsuj pozycje wektora

	std::string fb(input);
	boost::regex pattern("([^,]*,)");
	int i=0, n;

	boost::match_results<std::string::const_iterator> res;
	boost::match_flag_type flags = boost::match_default;

	std::string::const_iterator s , e;
	s = fb.begin();
	e = fb.end();

	while(boost::regex_search(s, e, res, pattern, flags))
	{

		std::string url(res[1].first, res[1].second);

		poz_wekt.append(url.c_str());

		//printf("\n%s", url.c_str());
		i++;
		s = res[1].second;
	}

	//stworz relacje , na razie bez ograniczen
	n = i;
	R = Z;
	//R = Relation(n);
	for(i=1; i<=n; i++)
		R.name_set_var(i, names[i]);



	//dodaj zmienne symboliczne
	for(iii=1; iii<=own_var_symb.length(); iii++)
	{

        if(GetFVDByName(own_var_symb[iii]))
            symb.append(R.get_local(GetFVDByName(own_var_symb[iii])));
	}


        for(j=1; j<=symb_native.length(); j++)
            symb.append(symb_native[j]);
	for(iii=1; iii<=symb.length(); iii++)
		printf("\n%s", symb[iii]->char_name());


	F_And *fand = R.and_with_and();


	//dolaczanie ograniczen

	for(i=1; i<=n; i++)
	{
		F_And *fand2 = fand->add_and();
		EQ_Handle feq = fand2->add_EQ();
		feq.update_coef(R.set_var(i), -1);

		String el = poz_wekt[i];
		std::string fb(el);
		Tuple <String> skladniki;
		skladniki.clear();

		boost::regex pat1("([^(\\+|\\-|,)]+(\\+|\\-|,))");

		s = fb.begin();
		e = fb.end();

		boost::match_results<std::string::const_iterator>  res;


		while(boost::regex_search(s, e, res, pat1, flags))
		{
			std::string url(res[1].first, res[1].second);

			//printf("\n^ %s", url.c_str());
			skladniki.append(url.c_str());

			s = res[1].second;
		}

		int minus, curr_min;

		if(el[0] == '-')
			minus = -1;
		else
			minus = 1;

		boost::regex re("\\-");
		boost::regex alone_var("(t|c)\\d*$");
		boost::regex var("(((t|c)\\d*)|([a-zA-Z]))");
		boost::regex regcoef("(\\d*[a-z])");
		boost::regex pat_t("[a-z]");
		boost::regex is_num("^\\d*$");


		for(j=1; j<=skladniki.length(); j++)
		{
			String skl = skladniki[j];
			std::string tmp(skl);

			curr_min = minus;

			//printf("\n *********** %s", tmp.c_str());
			if (boost::regex_search(tmp, re))
			{
				minus = -1;
			}
			else
				minus = 1;




			boost::regex pat2("(\\*|\\+|\\-|,)");
			tmp = boost::regex_replace(tmp,  pat2, "");

			//

			s = tmp.begin();
			e = tmp.end();
			String tmp_symb = "";

			while(boost::regex_search(s, e, res, var, flags))
			{
                std::string url(res[1].first, res[1].second);

				tmp_symb = url.c_str();
				s = res[1].second;

			}



			if(tmp_symb.length()>0)
			{
				//printf("Jest zmienna %s", str(tmp_symb));

				s = tmp.begin();
				e = tmp.end();
				String var_coef = "";
				int cf = 1;

				while(boost::regex_search(s, e, res, regcoef, flags))
				{
					std::string url(res[1].first, res[1].second);

					url = boost::regex_replace(url,  pat_t, "");
					var_coef = url.c_str();
					s = res[1].second;

				}

				if(var_coef.length()>0)
					cf = atoi(var_coef);
				cf *= curr_min;

				//rintf(" z wspolczynnikiem  %i", cf);

                int idx_z = GetIdVar(symb, tmp_symb);
				feq.update_coef(symb[idx_z], cf);


			}
			else
			{
				if (boost::regex_match(tmp, is_num))
				{
					int cns = atoi(tmp.c_str());
					cns *= curr_min;
					//printf("stala %i", cns);

					feq.update_const(cns);
				}

			}


		}



	}

	R.simplify();

	//R.print();

	return R;


}



Free_Var_Decl* GetFVDByInt(int i)
{
	switch(i)
	{

		case (1) : return &vv1;
		case (2) : return &vv2;
		case (3) : return &vv3;
		case (4) : return &vv4;
		case (5) : return &vv5;
		case (6) : return &vv6;
		case (7) : return &vv7;
		case (8) : return &vv8;
		case (9) : return &vv9;
		case (10) : return &vv10;

	}
	return &vv1;
}


Free_Var_Decl* GetFVDByName(String name)
{

	if(strcmp(NameFVD[1], name)==0)
		return &vv1;
	if(strcmp(NameFVD[2], name)==0)
		return &vv2;
	if(strcmp(NameFVD[3], name)==0)
		return &vv3;
	if(strcmp(NameFVD[4], name)==0)
		return &vv4;
	if(strcmp(NameFVD[5], name)==0)
		return &vv5;
	if(strcmp(NameFVD[6], name)==0)
		return &vv6;
	if(strcmp(NameFVD[7], name)==0)
		return &vv7;
	if(strcmp(NameFVD[8], name)==0)
		return &vv8;
	if(strcmp(NameFVD[9], name)==0)
		return &vv9;
	if(strcmp(NameFVD[10], name)==0)
		return &vv10;

	return NULL;
}

int GetIdVar(Tuple<Variable_ID> zmienne, String nazwa)
{
	int i;

	for(i=1; i<=zmienne.length(); i++)
		if(strcmp(nazwa, zmienne[i]->name())==0)
			return i;

	return -1;
}




Relation gluptok()
{

	Relation R(1);
	int g = 1;
	Variable_ID z1;

	vv2.set_base_name("t3");

	GetFVDByName("t1")->set_base_name("t5");


	if(10 > g)
	{
		z1 =  R.get_local(&vv1);
	}




	F_And *f = R.add_and();
	EQ_Handle eq = f->add_EQ();
	eq.update_coef(R.set_var(1), 1);
	eq.update_coef(z1, 1);

	Relation K = Union(copy(R), copy(R));


	return K;
}


//Funkcja wyciagajaca z Tuple<String> zmienne symboliczne i zwraca tez w Tuple<String>
Tuple<String> s1GetVariables(Tuple<String> wektory)
{
	Tuple<String> zmienne;
	int i, j, added;
	String var;

	for(i=1; i<=wektory.length(); i++)
	{
		std::string fb(wektory[i]);

		boost::regex pattern("([a-z]\\d*)");
		boost::match_results<std::string::const_iterator> res;
		boost::match_flag_type flags = boost::match_default;

		std::string::const_iterator s , e;
		s = fb.begin();
		e = fb.end();

		while(boost::regex_search(s, e, res, pattern, flags))
		{
            std::string url(res[1].first, res[1].second);


			var = url.c_str();

			added = 0;
			for(j=1; j<=zmienne.length(); j++)
				if(strcmp(zmienne[j], var) == 0)
				{
					added = 1;
					break;
				}
			if(!added)
			{
				zmienne.append(var);
			}

			s = res[1].second;
		}
	}


	return zmienne;
}



void Init_FVD(Tuple<String> zmienne)
{
	int i, j, was=0;

	for(i=1; i<=zmienne.length(); i++)
	{
		was = 0;
		// tu powinno sie chyba sprawdzac czy juz dodano !!!
		for(j=1; j<=NameFVD.length(); j++)
			if(strcmp(NameFVD[j], zmienne[i])==0)
				was = 1;

		if(was)
			continue;


		GetFVDByInt(i)->set_base_name(zmienne[i]);
		NameFVD.append(zmienne[i]);

	}



}

// Wlasciwa funkcja
// Dostaje na wejsciu string petli i zwraca relacje zbiorow z wektorow

Tuple<Relation> ExtractSetsFromLoop(String petla)
{
	Tuple<String> wektory, zmienne_symb;
	Tuple<Relation> Sets;
	Tuple<Variable_ID> symb_native;
	int i;
	Relation R;

	//wyciagnij wektory
	wektory = GetLoop_s1_vectors(petla);

	//wyciagnij wszystkie zmienne symboliczne z wektorow
	zmienne_symb = s1GetVariables(wektory);

	//for(i=1; i<=zmienne_symb.length(); i++)
	//	printf("\n$$$ %s", zmienne_symb[i]);

	//zainicjuj FVD
	Init_FVD(zmienne_symb);


	for(i=1; i<=wektory.length(); i++)
	{
		Sets.append(String2Set(wektory[i], symb_native, R));

	}

//printf("!!!!!! %s", wektory[1]);
	return Sets;

}

Tuple<Relation> ExtractSetsFromLoop_AndReduce(String petla, Relation S)
{
	Tuple<String> wektory, zmienne_symb;
	Tuple<Relation> Sets;
	Tuple<Variable_ID> symb_native;
	int i;

	//wyciagnij wektory
	wektory = GetLoop_s1_vectors(petla);

	//wyciagnij wszystkie zmienne symboliczne z wektorow
	zmienne_symb = s1GetVariables(wektory);

    // odczytaj zmienne symboliczne w S
	for(DNF_Iterator di2(S.query_DNF()); di2; di2++)
	{

		for(Variable_Iterator vi(*(*di2)->variables()); vi; vi++)
		{
					Variable_ID vv = (*vi);
					Var_Kind vd = vv->kind();
					if(vd == Global_Var)
					{
                        symb_native.append(vv);
					}

		}

	}



	//zainicjuj FVD
	Init_FVD(zmienne_symb);

    Relation r2 = Difference(copy(S), copy(S));
    r2.simplify();
    r2.print();
    r2 = Complement(copy(r2));

    r2.simplify();
    r2.print();

	for(i=1; i<=wektory.length(); i++)
	{
		printf("%s p", str(wektory[i]));
		Relation Z = Intersection(copy(String2Set(wektory[i], symb_native, copy(r2))), copy(S));
		Z.print();
		Z.simplify();
        Z.print();

		Sets.append(Z);


	}

	NameFVD.clear();



	return Sets;

}
