/* Code generation output routines contributed by Fortran D group.
   Modified slightly to move out of the omega core and presburger, using
   new Substitutions interface. */

#include <omega.h>
#include <code_gen/stmt_builder.h>
#include <omega/pres_subs.h>

namespace omega {

//***********************************************************************
// Static implementation added by D people.
// Lei Zhou, Apr 24, 96.
//***********************************************************************

#if defined QUESTIONABLE_CODEGEN_UPGRADE_MAYBE_NEEDED_FOR_TCODEGEN
static bool nonunit_coef(Variable_ID v, Conjunct *C){
  for(EQ_Iterator e(C); e; e++)
    if ((*e).get_coef(v) != 0 && abs((*e).get_coef(v)) != 1) return true;
  return false;
}

static Relation project_other_outputs(Variable_ID v, const Relation &Crel){
  // Ugh.  Must be some horrible thing Dave or a Davestudent might
  // come up with. 
  assert(v->kind() == Output_Var);
  Relation K = Crel;
  Section<Variable_ID> rest_of_output(&output_vars, v->get_position()+1,
                                      K.n_out());
  if (rest_of_output.size()) K = Project(K, rest_of_output);
  Section<Variable_ID> beg_of_output(&output_vars,1, v->get_position()-1);
  if (beg_of_output.size())  K = Project(K, beg_of_output);
  return K;
}
#endif


/************************************************************************
 * Don't use Substitutions class since it can't handle integer
 * division.  Instead, use relation mapping to a single output
 * variable to get substitution.  -- by chun, 07/19/2007
 ************************************************************************/
Tuple<CG_outputRepr*> print_outputs_with_subs_to_repr(CG_outputBuilder* ocg, Relation &R) {
  const int n = R.n_out();
  Tuple<CG_outputRepr*> oReprList;

  R.setup_names();
  assert(R.has_single_conjunct());

  // Eliminate redundent equations to avoid substitution using phantom loop variables.
  bool *is_var_const = new bool[R.n_inp()+R.n_out()];
  for (int i = 0; i < R.n_inp()+R.n_out(); i++)
    is_var_const[i] = false;
  while (true) {
    Conjunct *C = R.single_conjunct();
    bool is_changed = false;
    for (EQ_Iterator ei(C); ei; ei++) {
      int pos = -1;
      bool is_interested = true;
      for (Constr_Vars_Iter cvi(*ei); cvi; cvi++) {
        switch (cvi.curr_var()->kind()) {
        case Input_Var:
        // case Set_Var:
        {
          int p = cvi.curr_var()->get_position() - 1 ;
          if (!is_var_const[p]) {
            if (pos < 0)
              pos = p;
            else
              is_interested = false;
          }
          break;
        }
        case Output_Var:
        {
          int p = cvi.curr_var()->get_position() + R.n_inp() - 1;
          if (!is_var_const[p]) {
            if (pos < 0)
              pos = p;
            else
              is_interested = false;
          }
          break;
        }
        case Wildcard_Var:
          is_interested = false;
          break;
        default:
          break;
        }
        if (!is_interested)
          break;
      }
      if (is_interested && pos >= 0) {
        is_var_const[pos] = true;
        is_changed = true;
      }
    }
    if (is_changed) {
      for (int i = 0; i < R.n_inp(); i++)
        if (is_var_const[i])
          R = Project(R, i+1, Input_Var);
    }
    else
      break;
  }
  delete[] is_var_const;

  while (true) {
    Relation R2 = Domain(copy(R));
    Conjunct *C = R2.single_conjunct();

    bool is_changed = false;
    for (EQ_Iterator ei(C); ei; ei++) {
      int pos = 0;
      bool is_interested = true;
      for (Constr_Vars_Iter cvi(*ei); cvi; cvi++) {
        switch (cvi.curr_var()->kind()) {
        case Input_Var:
        // case Set_Var:
        {
          int p = cvi.curr_var()->get_position();
          if (pos < p)
            pos = p;
          break;
        }
        case Wildcard_Var:
          is_interested = false;
          break;
        default:
          break;
        }
        if (!is_interested)
          break;
      }
      if (is_interested && pos > 0) {
        R = Project(R, pos, Input_Var);
        is_changed = true;
        break;
      }
    }
    if (!is_changed)
      break;
  }
     
  // Find substitution for each output variable
  for (int i = 1; i <= n; i++) {
    Relation mapping(n, 1);
    F_And *f_root = mapping.add_and();
    EQ_Handle h = f_root->add_EQ();
    h.update_coef(mapping.output_var(1), 1);
    h.update_coef(mapping.input_var(i), -1);

    Relation S = Composition(mapping, copy(R));
    S.setup_names();
    S.simplify();
    assert(S.has_single_conjunct());
    Conjunct *C = S.single_conjunct();

    Variable_ID v = S.output_var(1);
    bool is_replaced = false;
    CG_outputRepr *repr = NULL;
    for (EQ_Iterator ei(C); ei; ei++) {
      if ((*ei).has_wildcards())
        continue;
      int d = (*ei).get_coef(v);
      if (d != 0) {
        int sign = (d>0)?-1:1;
        d = -sign * d;

        for (Constr_Vars_Iter cvi(*ei); cvi; cvi++)
          if ((*cvi).var != v) {
            int coef = sign * (*cvi).coef;
            CG_outputRepr *op = ocg->CreateIdent((*cvi).var->name());
            if (coef > 1)
              op = ocg->CreateTimes(ocg->CreateInt(coef), op);
            else if (coef < -1)
              op = ocg->CreateTimes(ocg->CreateInt(-coef), op);              
            if (coef > 0)
              repr = ocg->CreatePlus(repr, op);
            else if (coef < 0)
              repr = ocg->CreateMinus(repr, op);
          }

        int c = sign * (*ei).get_const();
        if (c > 0)
          repr = ocg->CreatePlus(repr, ocg->CreateInt(c));
        else if (c < 0)
          repr = ocg->CreateMinus(repr, ocg->CreateInt(-c));
        else if (repr == NULL)
          repr = ocg->CreateInt(0);
        
        if (d != 1)
          repr = ocg->CreateIntegerDivide(repr, ocg->CreateInt(d));
        
        is_replaced = true;
        break;
      }
    }

    if (is_replaced)
      oReprList.append(repr);
    else
      oReprList.append(NULL);
  }

  return oReprList;
}

} // namespace
