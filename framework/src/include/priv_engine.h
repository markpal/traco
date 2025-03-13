ComplexRelation Sslice, PrivCand;
std::vector<std::string> all_vars;
std::vector<int> priv_levels;


bool OneCellMemory(ComplexRelation BaseRel, std::string var);
int findMinVar(ComplexRelation BaseRel, std::string var);

bool CheckPrivatization(ComplexRelation BaseRel, std::string var);
int CheckPrivLevel(ComplexRelation BaseRel, std::string var);
std::vector<std::string> GetPrivVariables(ComplexRelation BaseRel);

void CopyComplexRel(ComplexRelation BaseRel, ComplexRelation *BaseOut, int i);
ComplexRelation RemoveComplexRel(ComplexRelation BaseRel, int i);
ComplexRelation CalcSetX(ComplexRelation BaseRel, std::string var, int i);
ComplexRelation JoinComplexRel(ComplexRelation BaseRel, ComplexRelation BaseRel2);

Relation Ch_Relation(Relation I, int n);
Relation _Ch_Relation(Relation I, int n);

void DivideRelSet(ComplexRelation BaseRel)
{
 //   BaseRel.R[5].print();
 if(!_SILENT)
 cout << "*******************S" << endl;
    double begin3a = gettime();

    BaseRel.R = NormalizeRel(BaseRel.R);
    BaseRel = Ext_Base(BaseRel);


    std::vector<std::string> priv_vars = GetPrivVariables(BaseRel);

    for(int i=0; i<priv_vars.size(); i++)
        cout << "Priv var: " <<  priv_vars[i];



    for(int i=1; i<=BaseRel.R.length(); i++)
    {
        if(std::find(priv_vars.begin(), priv_vars.end(), std::string(BaseRel.Var[i]))!=priv_vars.end())
        {
            CopyComplexRel(BaseRel, &PrivCand, i);
         //   cout << "p" << i << endl;
        }
        else
        {
            CopyComplexRel(BaseRel, &Sslice, i);
           // cout << "s" << i << endl;
        }


    }



   // cout << Sslice.R.length();



int b = 0;


    Rel_Struct SOUR_SSLICE;
    Relation T1;

    if(b)
    {
        SOUR_SSLICE = CalcSources(Sslice, 0);
        cout << Card(SOUR_SSLICE.R[1]);
        T1 = SOUR_SSLICE.R[1];
    }






    ComplexRelation SetX;

    for(int i=0; i<priv_vars.size(); i++)
    {
       ComplexRelation _SetX = CalcSetX(PrivCand, priv_vars[i], priv_levels[i]);
       SetX = JoinComplexRel(_SetX, SetX);
    }

   // for(int i=1; i<=SetX.R.length(); i++)
   //     SetX.R[i].print();


    Sslice = JoinComplexRel(Sslice, SetX);
cout << endl << endl << "przed:" << BaseRel.R.length();
cout << "po:" << Sslice.R.length();

//exit(0);

    SOUR_SSLICE = CalcSources2(Sslice, Sslice.R[1], 0);
    if(b)
    cout << Card(SOUR_SSLICE.R[1]);


    Relation T2 = SOUR_SSLICE.R[1];


   // cout << "sources" << endl;
if(b && !_SILENT){
    if(CardCompare(T1, T2))
        cout << "OK" << endl;
    else
    {
        cout << "BAD" << endl;
        exit(0);
    }
}

    Gen_affine(SOUR_SSLICE, Sslice);

    double end3a = gettime();
    printf("\n--------> Analiza: %.2f\n", (double)((end3a - begin3a)));

/*

P := [n] -> { n : n >= 2 };
R := [n] -> { n : n >= 2 };
P-R;
R-P;


*/

}

void CopyComplexRel(ComplexRelation BaseRel, ComplexRelation *BaseOut, int i)
{
        BaseOut->R.append(BaseRel.R[i]);
		BaseOut->DepVect.append(BaseRel.DepVect[i]);
		BaseOut->VecType.append(BaseRel.VecType[i]);
        BaseOut->Type.append(BaseRel.Type[i]);
		BaseOut->From.append(BaseRel.From[i]);
		BaseOut->To.append(BaseRel.To[i]);
		BaseOut->SCC.append(BaseRel.SCC[i]);
		BaseOut->Var.append(BaseRel.Var[i]);
		BaseOut->Line.append(BaseRel.Line[i]);
}

ComplexRelation RemoveComplexRel(ComplexRelation BaseRel, int i)
{
        ComplexRelation BaseOut;
        for(int j=1; j<=BaseRel.R.length() && j != i; j++)
        {
            CopyComplexRel(BaseRel, &BaseOut, j);
        }

        return BaseOut;

}

ComplexRelation JoinComplexRel(ComplexRelation BaseRel, ComplexRelation BaseRel2)
{
        ComplexRelation BaseOut;
        for(int j=1; j<=BaseRel.R.length(); j++)
        {
            CopyComplexRel(BaseRel, &BaseOut, j);
        }

        for(int j=1; j<=BaseRel2.R.length(); j++)
        {
            CopyComplexRel(BaseRel2, &BaseOut, j);
        }

        return BaseOut;

}

ComplexRelation CalcSetX(ComplexRelation BaseRel, std::string var, int i)
{
    ComplexRelation Tmp = BaseRel, BaseOut;

    for(int j=1; j<=Tmp.R.length(); j++)
    {
        if(strcmp(Tmp.Var[j], var.c_str())==0)
        {
            Tmp.R[j] = _Ch_Relation(Tmp.R[j], i);

            if(Tmp.R[j].number_of_conjuncts() > 0)
                CopyComplexRel(Tmp, &BaseOut, j);
        }
    }

    return BaseOut;


}

std::vector<std::string> GetPrivVariables(ComplexRelation BaseRel)
{

    std::vector<std::string> priv_vars;

    for(int i=1; i<=BaseRel.R.length(); i++)
    {

        if(std::find(all_vars.begin(), all_vars.end(), std::string(BaseRel.Var[i]))==all_vars.end())
        {
            all_vars.push_back(std::string(BaseRel.Var[i]));
        }

    }

    for(int i=0; i<all_vars.size(); i++)
    {
        //cout << all_vars[i] << endl;
        if(OneCellMemory(BaseRel, all_vars[i]))
        {

         //   cout << all_vars[i] << " " << findMinVar(BaseRel, all_vars[i]) << endl;
            if(CheckPrivatization(BaseRel, all_vars[i]))
            {
               // cout <<  "OK!" << endl;

         //     cout << CheckPrivLevel(BaseRel, all_vars[i]) << endl;
              priv_vars.push_back(all_vars[i]);
              priv_levels.push_back(CheckPrivLevel(BaseRel, all_vars[i]));

            }

        }

    }

    return priv_vars;
}

bool OneCellMemory(ComplexRelation BaseRel, std::string var)
{
    std::string temp = "";
    for(int i=1; i<=BaseRel.R.length(); i++)
    {
        //cout << "!!!!!" << var;
        if(var == std::string(BaseRel.Var[i]))
        {
            //cout << std::string(BaseRel.Line[i]);
            std::vector<std::string> tab;
            std::string linia = std::string(BaseRel.Line[i]);
            boost::split(tab, linia, boost::is_any_of(" "), boost::algorithm::token_compress_on);
            //for(int j=0; j<tab.size(); j++)
            //   cout << j << tab[j] << endl;

            if(temp == "")
               temp = tab[2];

            if(tab[2] != temp || tab[5] != temp)   //np a[m] i a[m+1]
                return false;

        }

    }

    return true;

}

bool CheckPrivatization(ComplexRelation BaseRel, std::string var)
{
    int min = findMinVar(BaseRel, var);

    if(var == "square")
        return false;
//cout << min;
    for(int i=1; i<=BaseRel.R.length(); i++)
    {
        if(strcmp(BaseRel.Type[i], "anti") == 0 && BaseRel.From[i] == min && strcmp(BaseRel.Var[i], var.c_str()) == 0 )
            return false;
    }

    return true;
}

int findMinVar(ComplexRelation BaseRel, std::string var)
{
    int min = std::numeric_limits<int>::max();

    for(int i=1; i<=BaseRel.R.length(); i++)
    {
        if(strcmp(BaseRel.Var[i],var.c_str())==0)
        {


        if(BaseRel.From[i] < min)
          min = BaseRel.From[i];

        if(BaseRel.To[i] < min)
          min = BaseRel.To[i];
        }
    }

    return min;
}

int CheckPrivLevel(ComplexRelation BaseRel, std::string var)
{
    int z = 10;

    for(int i=1; i<=BaseRel.R.length(); i++)
       if (strcmp(BaseRel.Var[i], var.c_str()) == 0)
       {
            std::vector<std::string> tab;
            std::string linia = std::string(BaseRel.Line[i]);
            boost::split(tab, linia, boost::is_any_of(" "), boost::algorithm::token_compress_on);
            boost::regex reg(",");
            int temp = Count_Captures(tab[6], reg);

            if(temp <= z)
                z = temp;
       }
    return z+1;
}

Relation _Ch_Relation(Relation I, int n)
{
    int i;
    for(i=1; i<=n; i++)
        I = Ch_Relation(I, i);
    return I;

}


Relation Ch_Relation(Relation I, int q)
{
	int i;

	Variable_ID var1, var2;
	F_And *root = I.and_with_and();

	for(i=q; i<=q; i++)
	{
		var1 = I.input_var(i);
		var2 = I.output_var(i);

		EQ_Handle econstr = root->add_EQ();
		econstr.update_coef(var1, 1);
		econstr.update_coef(var2, -1);

	//	if(i<n) root = root->add_and();
	}

  //  I.print();
	I.simplify(2,4);
	//I.print();

	return I;
}
