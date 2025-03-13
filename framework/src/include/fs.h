/* 
 * File:   fs.h
 * Author: marek
 *
 * Created on 12 wrzesień 2010, 19:53
 */

#ifndef _FS_H
#define	_FS_H



Relation GetRM(Relation Ru)
{

    Relation Rp = Difference(copy(Ru), copy(Ru));
    Rp = Complement(copy(Rp));
    Rp = Extend_Domain(copy(Rp));
    Rp = Extend_Range(copy(Rp));
    Rp.simplify();
   // Rp.print();

    int i;

    for(i=Rp.n_inp(); i>=2; i--)
       Rp.name_input_var(i, Rp.input_var(i-1)->name());

    for(i=Rp.n_out(); i>=2; i--)
       Rp.name_output_var(i, Rp.output_var(i-1)->name());

    Rp.name_input_var(1, "_m");
    Rp.name_output_var(1, "_m'");

    F_And *rpfand = Rp.and_with_and();

    Variable_ID exrp[10];
    for(i=0; i<Rp.n_out()-1; i++)
        exrp[i] = Rp.output_var(i+2);

    R_Add_Exist2(Ru, Rp, rpfand, exrp, 1, 1, 1);


    rpfand = Rp.and_with_and();

    Variable_ID m = Ru.input_var(1);
    Variable_ID mprim = Ru.output_var(1);

    EQ_Handle rpxx = rpfand->add_EQ();
    rpxx.update_coef(m,1);
    rpxx.update_coef(mprim,-1);
    rpxx.update_const(1);

    GEQ_Handle rpgx = rpfand->add_GEQ();
    rpgx.update_coef(m,1);
	 Rp = SimplifyNumConjuncts(Rp, 1);
//	S_Slice = InteSymp(S_Slice);
    Rp.simplify(2, 5);

    Rp.print();



    return Rp;
}


// tu jest mała niedorobka, trzeba poprawic w przyszlosci
// do range FS dodac not exists k' : k' > k & k' > 0 & constraints(range FS z zamiana k na k')
// łata została dodama, zmienna patch_fs



String GetFS(Relation Ru, int disp, Rel_Struct Sources1)
{
    int i;
    int patch_fs = 1; //czy dodac late na oblizanie dla multiple sources

   // Relation UDS = Sources1.R[1];

    
    Relation UDS = Difference(Domain(copy(Ru)), Range(copy(Ru)));
    UDS.simplify(2,5);

    printf("UDS\n");
    UDS.print();


    Relation Rm = GetRM(copy(Ru));
    printf("Rm\n");
    Rm.print_with_subs();
    printf("\n\n");

    Relation Rmplus;
    if(APROX)
    {
         Rmplus = ApproxClosure(Rm);
         Rmplus = Upper_Bound(copy(Rmplus));
         Rmplus.simplify();

    }
    else
        Rmplus = Star(Rm, 0);
        // Rmplus = Star(Rm, 1);
   // Rmplus = SimplifyNumConjuncts(Rmplus, 1);
    Rmplus.simplify();

   // if(disp)
    printf("Rm*\n");
    Rmplus.print_with_subs();
    printf("\n\n");

    Relation Fs = Difference(copy(Ru), copy(Ru));
    Fs = Complement(copy(Fs));
    Fs = Extend_Range(copy(Fs));
    Fs.simplify();


    for(i=Fs.n_out(); i>=2; i--)
       Fs.name_output_var(i, Fs.output_var(i-1)->name());

    Fs.name_output_var(1, "_k");

    if(disp)
    Fs.print();

    F_And *fsfand = Fs.and_with_and();

    Variable_ID exfs[10];
    for(i=0; i<Fs.n_inp(); i++)
        exfs[i] = Fs.input_var(i+1);

    R_Add_Exist2(UDS, Fs, fsfand, exfs, 2, 1);

    if(disp)
    UDS.print();
    if(disp)
    Fs.print();



    Relation FIS = Union(Domain(copy(Ru)), Range(copy(Ru)));


    FIS.simplify(2, 5);

    FIS = TryHull(FIS);
    FIS.simplify(2, 5);

    for(i=0; i<Fs.n_out()-1; i++)
        exfs[i] = Fs.output_var(i+2);

    fsfand = Fs.and_with_and();

    // prawdopodobine ten warunek jest niepotrzebny
  //  R_Add_Exist2(FIS, Fs, fsfand, exfs, 2, 0, 0, 0, 1);


  //  Fs.simplify(2, 5);

    if(disp)
    FIS.print();
    if(disp)
    Fs.print();

    fsfand = Fs.and_with_and();


    for(i=0; i<Fs.n_out(); i++)
        exfs[i] = Fs.output_var(i+1);
    //    exit(0);
    Rmplus = Star(Rm, 0);
    
   // Rmplus = Repair_Relation(Rmplus);
   // Rmplus.simplify();
    Rmplus.print();

    R_Add_Exist2(Rmplus, Rmplus, fsfand, exfs, 1, 1, 0, 1);

Rmplus = Star(Rm, 0);

printf("R'*\n");
Rmplus.print_with_subs();
Relation ZZi = Range(copy(Rmplus));
ZZi.simplify();
printf("range R'+\n");
ZZi.print_with_subs();


Rmplus = Star(Rm, 1);

printf("R'+\n");
Rmplus.print_with_subs();
ZZi = Range(copy(Rmplus));
ZZi.simplify();
printf("range R'+\n");
ZZi.print_with_subs();



    if(disp)
    Rmplus.print();
    
    if(disp)
    Fs.print();

   // Fs.simplify(2, 5);

    if(disp)
    Fs.print();

    fsfand = Fs.and_with_and();
    F_Not* fsnot = fsfand->add_not();
    F_Exists *fex = fsnot->add_exists();
    F_And *fex_and_x = fex->add_and();
    F_And *fex_and = fex_and_x->add_and();


    exfs[0] = fex->declare("k'");

    GEQ_Handle rpxx = fex_and->add_GEQ();
    rpxx.update_coef(Fs.output_var(1) ,-1);
    rpxx.update_coef(exfs[0],1);
    rpxx.update_const(-1);

    fex_and = fex_and_x->add_and();

    R_Add_Exist2(Rmplus, Rmplus, fex_and, exfs, 1, 1, 0, 1);

   // if(disp)
    Fs.print();

    Fs.simplify(2, 5);

   // Fs = SimplifyNumConjuncts(Fs);

   // if(disp)
    printf("\n--------------FS------------\n");
    Fs.print_with_subs();

    Relation PAR = Range(copy(Fs));
    PAR.simplify(2, 5);
     printf("\n--------------1!------------\n");
    PAR.print_with_subs();
     printf("\n--------------1!------------\n");



     // ------------------------------------------------------------
     //łata
     if(patch_fs){
          Relation PAR2 = PAR;
         for(i=0; i<PAR.n_set(); i++)
            exfs[i] = PAR.set_var(i+1);

         fsfand = PAR.and_with_and();
         fsnot = fsfand->add_not();
         fex = fsnot->add_exists();
         fex_and_x = fex->add_and();
         fex_and = fex_and_x->add_and();


         exfs[0] = fex->declare("k'");

         rpxx = fex_and->add_GEQ();
         rpxx.update_coef(PAR.set_var(1) ,-1);
         rpxx.update_coef(exfs[0],1);
         rpxx.update_const(-1);

         fex_and = fex_and_x->add_and();

         PAR2.print();
         S_Add_Exist2(PAR2, PAR, fex_and, exfs);

        printf("\n--------------łata------------\n");
        PAR.print();

        PAR.simplify(2, 5);
         printf("\n--------------1!------------\n");
        PAR.print_with_subs();
     }

    // ------------------------------------------------------------





    Relation W = Maximize(PAR);
    W.simplify();
    W.print_with_subs();

    if(APROX == 0)
    {
        printf("\n--------------sprawdzanie warunku------------\n");
        Relation tmp1 = Difference(copy(Fs), copy(Fs));
        tmp1.simplify(2, 5);
        tmp1 = Complement(copy(tmp1));
        tmp1.simplify(2, 5);

        Relation tmp2 = tmp1;

        Free_Var_Decl _m0("m00");

        Variable_ID m0 = tmp1.get_local(&_m0);
        Variable_ID _var = tmp1.output_var(1);
        fsfand = tmp1.and_with_and();
        EQ_Handle rpy = fsfand->add_EQ();
        rpy.update_coef(_var ,-1);
        rpy.update_coef(m0 ,1);
        rpxx = fsfand->add_GEQ();
        rpxx.update_coef(m0 ,1);
        rpxx.update_const(-2);

        m0 = tmp2.get_local(&_m0);
        _var = tmp2.output_var(1);
        fsfand = tmp2.and_with_and();
        rpy = fsfand->add_EQ();
        rpy.update_coef(_var ,-1);
        rpy.update_coef(m0 ,1);
        rpy.update_const(-1);
        rpxx = fsfand->add_GEQ();
        rpxx.update_coef(m0 ,1);
        rpxx.update_const(-2);

        tmp1.print();
        tmp2.print();

        Relation rk1 = Intersection(copy(Fs), copy(tmp1));
        Relation rk2 = Intersection(copy(Fs), copy(tmp2));

        rk1.simplify(2, 5);
        rk1.print();
        rk2.simplify(2, 5);
        rk2.print();

        rk1 = Range(copy(rk1));
        rk1.simplify();


        Relation t = Range(Restrict_Domain(copy(Rm), Range(copy(rk2))));
        t.simplify(2, 5);
        t.print();

        Relation ZZ1 = Difference(copy(rk1), copy(t));
        ZZ1.simplify(2, 5);
        ZZ1.print();

        Relation ZZ2 = Difference(copy(t), copy(rk1));
        ZZ2.simplify(2, 5);
        ZZ2.print();

        if(ZZ1.number_of_conjuncts() == 0 && ZZ2.number_of_conjuncts() == 0)
            printf("\nWarunek spełniony\n");
        else
            printf("\nWarunek NIE spełniony\n");
    

    }


    
    return LoopCodeGen(PAR, 0);


}

#endif	/* _FS_H */


