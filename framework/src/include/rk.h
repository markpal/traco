/*
 * File:   rk.h
 * Author: marek
 *
 * Created on 8 wrzesień 2010, 19:18
 */



#ifndef _RK_H
#define	_RK_H

#define disp_RK 0


/* ********************************************* */
/*        Insert symbolic variable k to          */
/*             input relation                    */
/* ********************************************* */

Relation checkExactnessRk(NOT_CONST Relation &r, NOT_CONST Relation &rk, Global_Var_ID k);



Relation InsertSymKVariable(NOT_CONST Relation &r, Global_Var_ID K) {

Relation s = consume_and_regurgitate(r);
Relation R_out = Relation::False(s.n_inp(), s.n_out());
Relation R;
EQ_Handle eqK;
Variable_ID k;


for (DNF_Iterator c(s.query_DNF()); c; c++) {
	R = Relation(s, c.curr());
	eqK = R.and_with_EQ();
	k = R.get_local(K);
	eqK.update_coef(k,1);
	eqK.update_coef(R.input_var(R.n_inp()),1);
	eqK.update_coef(R.output_var(R.n_out()),-1);
	eqK.finalize();
	R_out = Union(R_out, R);
}

//R_out.print();
//R.print();
 //R_out = Union(R_out, R);

 R_out.finalize();

 return R_out;

}




/* ****************************** */
/*       Check exactness          */
/* ****************************** */

Relation checkExactness(NOT_CONST Relation &r, NOT_CONST Relation &rk, Global_Var_ID k) {

Relation s1 = consume_and_regurgitate(r);
Relation s2 = consume_and_regurgitate(rk);
Relation R_out = Relation::False(s2.n_inp(), s2.n_out());

EQ_Handle eqK;
Relation R,Rc;
//char* tmp;

Global_Var_Decl *K_ =  new Global_Var_Decl("K");
Global_Var_ID K = K_;
//Global_Var_ID K = (globalDecls->extend(tmp))->g;

for (DNF_Iterator c(s2.query_DNF()); c; c++) {
	Rc = Relation(s2, c.curr());
	eqK = Rc.and_with_EQ();
	eqK.update_coef(Rc.get_local(K),1);
	eqK.update_coef(Rc.get_local(k),-1);
	R_out = Union(R_out, Rc);
}

Rc = Relation::Null();
R_out = Project(R_out, k);
R = Composition( copy(s1), R_out);
R_out = Relation::False(s2.n_inp(), s2.n_out());

for (DNF_Iterator c(R.query_DNF()); c; c++) {
	Rc = Relation(R, c.curr());
	eqK = Rc.and_with_EQ();
	eqK.update_coef(Rc.get_local(k),1);
	eqK.update_coef(Rc.get_local(K),-1);
	eqK.update_const(-1);
	R_out = Union(R_out, Rc);
}

R_out = Project(R_out, K);
R = Relation::Null();
Rc = Relation::Null();

for (DNF_Iterator c(s1.query_DNF()); c; c++) {
	Rc = Relation(s1, c.curr());
	eqK = Rc.and_with_EQ();
	eqK.update_coef(Rc.get_local(k),1);
	eqK.update_const(-1);
	R_out = Union(R_out, Rc);
}

Rc = Relation::Null();

return R_out;

}





/* ********************************************* */
/*        Add the last elment to domain          */
/*             and range of relation             */
/* ********************************************* */

Relation ExtendDomainAndRange(NOT_CONST Relation &r){

Relation s = consume_and_regurgitate(r);
Relation R_out = Relation::False(s.n_inp(), s.n_out());
R_out = Extend_Range(Extend_Domain(R_out));
Relation R;
EQ_Handle eq;


for (DNF_Iterator c(s.query_DNF()); c; c++) {
	R = Extend_Range(Extend_Domain(Relation(s, c.curr())));
	eq = R.and_with_EQ();
	eq.update_coef(R.input_var(R.n_inp()),-1);
	eq.update_coef(R.output_var(R.n_out()),1);
	eq.update_const(-1);

	R_out = Union(R_out, R);
}

 R_out.finalize();
 return R_out;

}

//
// Delete last input variable in relation.
//

Relation  DeleteLastDomainElement(NOT_CONST Relation &S){
  Relation R = consume_and_regurgitate(S);

  if (R.is_null())
      throw std::invalid_argument("cannot delete domain element on null relation");

  Rel_Body *r = R.split();
  r->In_Names.delete_last();
  r->number_input--;
  assert(!r->is_null());

  if (r->number_input > r->number_output)
     R.invalidate_leading_info(r->number_input);

  return R;

}

//
// Delete last output variable in relation.
//

Relation  DeleteLastRangeElement(NOT_CONST Relation &S){
  Relation R = consume_and_regurgitate(S);

  if (R.is_null())
      throw std::invalid_argument("cannot delete range element on null relation");

  Rel_Body *r = R.split();
  r->Out_Names.delete_last();
  r->number_output--;
  assert(!r->is_null());

  if (r->number_output > r->number_input)
     R.invalidate_leading_info(r->number_output);

  return R;

}

Relation Project(NOT_CONST Relation &S, Variable_ID v) {
  Tuple<Variable_ID> s;
  s.append(v);
  return Project(S, s);
}

/* ********************************************* */
/*        Calculate relation R^k of single       */
/*         or multiple conjunct relation         */
/* ********************************************* */

Relation Rk(NOT_CONST Relation &r){

 Relation s = consume_and_regurgitate(r);
 Relation R,Re,space;
 //int count = 0;
 char* tmp;
 // printf("o\n");
 asprintf(&tmp, "k");

Global_Var_Decl *K_ =  new Global_Var_Decl("K");
Global_Var_ID K = K_;


 /* ******************************* */
 /*   Extend Domain and Range of    */
 /*       of input relation         */
 /* ******************************* */


 /* (1) */  R = ExtendDomainAndRange(copy(s));


 /* ******************************* */
 /*      Calculate R* on whole      */
 /*             space               */
 /* ******************************* */

 /* (2) */

 space = Union(Domain(copy(R)), Range(copy(R)));

 if(APROX)
     R = ApproxClosure(R);
 else
     R = TransitiveClosure3(R, space );

 /* ******************************* */
 /*    Insert symbolic variable     */
 /*             k                   */
 /* ******************************* */
;

 /* (3) */  R = InsertSymKVariable(R, K);

 /* ******************************* */
 /*    Project out last value       */
 /* ******************************* */

 /* (4) */  R = Project(R, R.input_var(R.n_inp()));

 /* (5) */  R = Project(R, R.output_var(R.n_out()));

 /* (6) */  R = DeleteLastDomainElement(R);
 /* (7) */  R = DeleteLastRangeElement(R);
//printf("o\n");
  Re = checkExactnessRk(copy(s), copy(R), K);

//printf("o\n");
  if (Must_Be_Subset(copy(Re), copy(R)) && Must_Be_Subset(copy(R), copy(Re))){
	 Re = Relation::Null();
	 R.simplify(2,4);
	 return R;
  }

 Re = Relation::Null();

 for (DNF_Iterator c(R.query_DNF()); c; c++)
	 (c.curr())->make_inexact();

 R.finalize();
 R.simplify(2,4);

 return R;

}


Relation Rk_FS(Relation Ru, int get_only_Sk=0)
{
    int i;

    Relation UDS = Difference(Domain(copy(Ru)), Range(copy(Ru)));
    UDS.simplify(2, 5);
   // printf("UDS\n");
  //  UDS.print();
   // printf("Rk obliczanie\n");
    double begin5 = gettime();
    Relation Z = Rk(copy(Ru));

    double end5 = gettime();
    printf("\n--------> Czas liczenia Rk: %.2f\n", (double)((end5 - begin5)));
    printf("Rk:\n");


    double begin6 = gettime();
    Z = Upper_Bound(copy(Z));

    Z.print();
    if(!Z.is_exact())
        printf("Rk unknown !!\n");

    //Z.print();
   // printf("Jest Rk!!\n");
    Relation Sk = Range(Restrict_Domain(copy(Z), copy(UDS)));

    if(APROX)
        Sk = Difference(copy(Sk), Range(Composition(copy(Z), ApproxClosure(Ru))));  //?
    else
        Sk = Difference(copy(Sk), Range(Composition(copy(Z), Star(Ru, 1))));  //?


    Sk.simplify();

    Sk.print();

   // exit(0);
    Relation SOUT = Sk;
    SOUT = Complement(Difference(copy(Sk), copy(Sk)));
    SOUT.simplify();

    SOUT = Extend_Set(copy(SOUT), 1);
    SOUT.simplify();
    SOUT.print();




    int dim = Sk.n_set();

    Variable_ID ex[10];


    for(i=0; i<dim; i++)
        ex[i] = SOUT.input_var(i+2);



    F_And *fex_and = SOUT.and_with_and();


     S_Add_Exist2(Sk, SOUT, fex_and, ex);

     SOUT.name_set_var(1, "y");
     String nazwa;

     for(i=1; i<=Sk.n_set(); i++)
     {
	  nazwa =  Sk.set_var(i)->name();
          SOUT.name_set_var(i+1, nazwa);
     }


     Variable_ID v;
     for(i=1; i<=SOUT.global_decls()->length(); i++)
     {
       v = SOUT.global_decls()->operator [](i);
       if(strcmp(str(v->name()), "K")==0)
           break;
     }


     Variable_ID x = SOUT.set_var(1);
     F_And *fand = SOUT.and_with_and();
     EQ_Handle xx = fand->add_EQ();
     xx.update_coef(x,-1);
     xx.update_coef(v,1);
     SOUT.print();
     SOUT = Project(copy(SOUT), v);



     SOUT.simplify(2, 5);
     SOUT = TryHull(SOUT);
     SOUT.print();

     if(get_only_Sk)
        return SOUT;

     double end6 = gettime();
     printf("\n--------> Czas liczenia Sk: %.2f\n", (double)((end6 - begin6)));

     double begin7 = gettime();

     String petla1 = LoopCodeGen(UDS, 1);
     String petla2 = LoopCodeGen(SOUT, 1);

     double end7 = gettime();
     printf("\n--------> Czas liczenia codegen: %.2f\n", (double)((end7 - begin7)));

     printf("// UDS loop ---\n");
     printf("%s", str(petla1));
     printf("// FS loop ---\n");
     printf("%s", str(petla2));

     FILE *_file = fopen("pseudocode.txt", "w");
     fprintf(_file,"// UDS loop ---\n");
     fprintf(_file,"%s", str(petla1));
     fprintf(_file,"// FS loop ---\n");
     fprintf(_file,"%s", str(petla2));
     fclose(_file);

     return SOUT;

}
#endif	/* _RK_H */

Relation checkExactnessRk(NOT_CONST Relation &r, NOT_CONST Relation &rk, Global_Var_ID k) {

Relation s1 = consume_and_regurgitate(r);
Relation s2 = consume_and_regurgitate(rk);
Relation R_out = Relation::False(s2.n_inp(), s2.n_out());

EQ_Handle eqK;
Relation R,Rc;
char* tmp;

asprintf(&tmp, "K");
Global_Var_Decl *K_ =  new Global_Var_Decl("K");
Global_Var_ID K = K_;

for (DNF_Iterator c(s2.query_DNF()); c; c++) {
	Rc = Relation(s2, c.curr());
	eqK = Rc.and_with_EQ();
	eqK.update_coef(Rc.get_local(K),1);
	eqK.update_coef(Rc.get_local(k),-1);
	R_out = Union(R_out, Rc);
}

Rc = Relation::Null();
R_out = Project(R_out, k);
R = Composition( copy(s1), R_out);
R_out = Relation::False(s2.n_inp(), s2.n_out());

for (DNF_Iterator c(R.query_DNF()); c; c++) {
	Rc = Relation(R, c.curr());
	eqK = Rc.and_with_EQ();
	eqK.update_coef(Rc.get_local(k),1);
	eqK.update_coef(Rc.get_local(K),-1);
	eqK.update_const(-1);
	R_out = Union(R_out, Rc);

}
R_out.print();

if(R_out.number_of_conjuncts()>0)
    R_out = Project(R_out, K);

R = Relation::Null();
Rc = Relation::Null();

for (DNF_Iterator c(s1.query_DNF()); c; c++) {
	Rc = Relation(s1, c.curr());
	eqK = Rc.and_with_EQ();
	eqK.update_coef(Rc.get_local(k),1);
	eqK.update_const(-1);
	R_out = Union(R_out, Rc);
}

Rc = Relation::Null();

return R_out;

}
