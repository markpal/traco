//Sk odwrocic mozna przez rollrelation
bool Legality(Relation R, Relation Sk);

void Test8(Relation Ru)
{
    Relation Sk = Rk_FS(Ru, 1);
    Sk.print();
    Relation Roll = RollRelation(Sk.n_set());
    Roll.print();
    Relation Sk1 = Range(Restrict_Domain(copy(Roll), copy(Sk)));


    for(int i=1; i<=Sk1.n_set(); i++)
    {
        Sk1.name_set_var(i, Sk.set_var((i%Sk1.n_set())+1)->name());
    }

    Sk1.simplify(2,4);
    Sk1.print();

    printf("\n--------\n");

    Legality(Ru, Sk1);
}

bool Legality(Relation R, Relation Sk)
{
    unsigned int n = Sk.n_set(), i;
    Relation Sk1 = Sk;

    Relation Test(n,n);
    Test.simplify();

    Test = Restrict_Domain(copy(Test), copy(Sk));
    Test = Difference(copy(Test), copy(Test));

    Test = Complement(copy(Test));
    Test.simplify();



    F_And *r2_and = Test.and_with_and();
	F_Exists *fex = r2_and->add_exists();
	F_And *fex_and = fex->add_and();

	Variable_ID ex[10];	// to tablica zmiennych e''

    Variable_ID k1 = fex->declare("k1");
    Variable_ID k2 = fex->declare("k2");

    GEQ_Handle econstr = fex_and->add_GEQ();
    econstr.update_coef(k1, 1);
    econstr.update_coef(k2, -1);
	econstr.update_const(-1);

    for(i=1; i<=Sk1.n_set(); i++)
    {
        Test.name_output_var(i, Sk.set_var(i)->name()+"'");
    }

    ex[n-1] = k1;
    for(i=1; i<n; i++)
        ex[i-1] = Test.input_var(i);

    S_Add_Exist2(Sk, Test, fex_and, ex);

    ex[n-1] = k2;
    for(i=1; i<n; i++)
        ex[i-1] = Test.output_var(i);

    S_Add_Exist2(Sk, Test, fex_and, ex);

    ex[n-1] = Test.output_var(n);
    R_Add_Exist2(R, Test, fex_and, ex, 1);

    R.print();

    Test.print();
    Test.simplify();
    Test.print();



    return Test.number_of_conjuncts() > 0;
}

