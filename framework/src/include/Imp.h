bool WhiteSpace(char arg)
{
	if (arg=='\n' || arg=='\t')
		return true;
	else
		return false;
}

//normalizacja zbiorow
Tuple<Relation> NormalizeSet(Tuple<Relation> R)
{
	int set_n=0, set_old=0;
	int i, diff, j;
	String set_names[10];

	int z = 1;


	for(i=1; i<=R.length(); i++)
	{
		if(R[i].n_set() > set_n)
		{
			set_old = set_n;
			set_n = R[i].n_set();
			for(j=set_old; j<set_n; j++)
			{
				set_names[j] = R[i].set_var(j+1)->name();
			}

		}
	}

	for(i=1; i<=R.length(); i++)
	{
		diff = set_n - R[i].n_set();

		if(diff > 0)
		{
			R[i] = Extend_Set(copy(R[i]), diff);
			for(j=set_n-diff+1; j<=set_n; j++)
			{
				F_And *and_con = R[i].and_with_and();
				Variable_ID vi = R[i].set_var(j);
				EQ_Handle tmp = and_con->add_EQ();
				tmp.update_coef(vi, 1);
				tmp.update_const(z);
				//R[i].simplify(2, 5);


			}

			for(j=0; j<set_n; j++)
				R[i].name_set_var(j+1,set_names[j]);

		}


		R[i].finalize();
		R[i].simplify();


	}

	return R;

}

Relation FindAllPerfectNestedLoop()
{
	std::string in_plik(petitLoopfilename);

	char tab[BUF]; //bufor
	unsigned int level=0;
	std::string strTemp;
	int stat[10], i;
	Tuple<std::string> nagl_for;
	Tuple<std::string> statements[10];
	Tuple<String> ploops;
	String nagl = "";
	Tuple<Relation> LD_SET;
	Relation LD;

	for(i=0; i<=9; i++)
		stat[i] = 0;

	ifstream input(in_plik.c_str(),ios::in);

	while (!input.eof()) {

		input.getline(tab,BUF,'\n');  //zczytanie lini
		//printf("%s\n", tab);
		strTemp.assign(tab);

		if ( strTemp.find("for ")!=std::string::npos )
		{

			level++;
			//printf("!!!! %i\n", level);
			if(level > nagl_for.length())
				nagl_for.append(strTemp);
			else
				nagl_for[level] = strTemp;

		}
		else if ( strTemp.find("endfor")!=std::string::npos )
		{
			//printf("::: %i\n", stat[level]);

			if(stat[level] > 0)  //petla ma instrukcje trzeba dodac
			{
				String petla = "";
				String tmp;

				petla = nagl + "\n";

				for(i=1; i<=level; i++)
				{
					tmp = nagl_for[i].c_str();
					petla = petla + tmp + "\n";
				}

				for(i=1; i<=statements[level].length(); i++)
				{
					tmp = statements[level][i].c_str();
					petla = petla + tmp + "\n";
				}

				for(i=1; i<=level; i++)
					petla = petla + "endfor\n";


				ploops.append(petla);
			}


			statements[level].clear();
			stat[level] = 0;
			level--;


		}
		else
		{
			std::remove_if(strTemp.begin(),strTemp.end(),WhiteSpace);


			if (strTemp.length()!=0) {
				if(level > 0)
				{
					stat[level] = 1;
					statements[level].append(strTemp);
					//printf("%s", strTemp.c_str());
				}
				else
				{
					String tmp;
					tmp = strTemp.c_str();
					nagl = nagl + tmp + "\n";
				}
			}


		}




	}




	for(i=1; i<=ploops.length(); i++)
	{
		FILE *tmp_plik;
		tmp_plik = fopen("tmp2.txt", "w");
		fprintf(tmp_plik, "%s", str(ploops[i]));
		fclose(tmp_plik);

		std::map<int,Relation> allIterations;
		CLoop *petla = new CLoop("tmp2.txt");
		allIterations = petla->CreateAllIterations();
		Relation LD = allIterations.begin()->second;

		LD = InteSymp(LD);

		LD_SET.append(copy(LD));

	}



	LD_SET = NormalizeSet(copy(LD_SET));

	LD = LD_SET[1];
	for(i=2; i<=LD_SET.length(); i++)
		LD = Union(copy(LD), copy(LD_SET[i]));

/* LINUX trzeba to zrobic w lib.h */
//	for(i=1; i<=ploops.length(); i++)
//		SymSimplify(&LD);

	LD.simplify(2, 4);
	LD = InteSymp(LD);


	//LD.print();



	return LD;


}



