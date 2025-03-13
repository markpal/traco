#include <omega.h>
#include <code_gen/elim.h>

namespace omega {

int max_fs_arity(const Constraint_Handle &c) {
  int max_arity=0;
  for(Constr_Vars_Iter cv(c); cv; cv++)
    if((*cv).var->kind() == Global_Var)
      max_arity = max(max_arity,(*cv).var->get_global_var()->arity());
  return max_arity;
}

elimination_info::elimination_info() : eliminated(0),never_eliminate_lt(100000) {
}


elimination_info::elimination_info(const Tuple<Relation> &sets) {
  int max_arity=0;
  for(int i = 1; i <= sets.size(); i++) {
    Relation R = sets[i];
    assert(R.is_set());
    for(DNF_Iterator D(R.query_DNF()); D; D++)
      for(Constraint_Iterator c(*D); c; c++)
        max_arity = max(max_arity,max_fs_arity(*c));
  }
  never_eliminate_lt = max_arity;
}

bool elimination_info::may_eliminate(Variable_ID v) { 
  if(v->kind() == Input_Var || v->kind() == Output_Var)
    return v->get_position() > never_eliminate_lt;
  else
    return true;
}

Relation elimination_info::project_eliminated(NOT_CONST Relation &input_R) {
  
  Relation R = consume_and_regurgitate(input_R);

  if(!any_eliminated()) {
    if (code_gen_debug > 2)
      fprintf(DebugFile,":::projectEliminatedVariables: no vars eliminated\n");
    return R;
  } 
  
  
  R = Project(R,eliminated);
  R.finalize();
  R.simplify();

  if(code_gen_debug > 2) {
    fprintf(DebugFile, "::: projectEliminatedVariables: variables eliminated: ");
    print_eliminated(DebugFile);
    R.prefix_print(DebugFile);
  }
  return R;
}

/******************************************************************************
 * Remove variables in "r" using equations in "known", operating on
 * formulae directly.  Do not use project function since it requires
 * the relation to be transformed has all the substitution information
 * embedded plus it will complicate modular conditions unnecessarily.
 *                           -- by chun 11/9/2008
 *****************************************************************************/
Relation elimination_info::project_eliminated(const Relation &r_, const Relation &known_) {
  Relation &r = const_cast<Relation &>(r_);
  Relation &known = const_cast<Relation &>(known_);
  assert(r.is_set()); // right now only support set relation
  const int n = r.n_set();

  // find the substitution for each eliminated variable
  Tuple<int> repl_var;
  Tuple<EQ_Handle> repl_eq;
  {
    Conjunct *c = known.query_DNF()->single_conjunct();
    for (int i = n; i >= 1; i--) {
      Variable_ID v = r.set_var(i);
      if (is_eliminated(v)) {
        int high_lvl = n+1;
        EQ_Handle h;
        for (EQ_Iterator e = c->EQs(); e; e++)
          if (!(*e).has_wildcards() && (*e).get_coef(v) != 0) {
            int j;
            for (j = n; j >= 1; j--)
              if (j != i && (*e).get_coef(r.set_var(j)) != 0)
                if (j < high_lvl) {
                  high_lvl = j;
                  h = *e;
                  break;
                }
            if (j == 0) {
              high_lvl = 0;
              h = *e;
              break;
            }
          }
        assert(high_lvl <= n);
        repl_var.append(i);
        repl_eq.append(h);
      }
    }
    if (repl_var.size() == 0)
      return copy(r);
  }  

  // substitute variables
  Relation new_r(n);
  F_Exists *fe = new_r.add_and()->add_exists();
  F_And *f_root = fe->add_and();
  std::map<Variable_ID, Variable_ID> exists_mapping;
  for (DNF_Iterator d = r.query_DNF(); d; d++) {
    for (GEQ_Iterator gi = (*d)->GEQs(); gi; gi++) {
      GEQ_Handle h = f_root->add_GEQ();
      for (Constr_Vars_Iter cvi(*gi); cvi; cvi++)
        switch ((*cvi).var->kind()) {
        // case Set_Var:
        case Input_Var: {
          int pos = (*cvi).var->get_position();
          h.update_coef(new_r.set_var(pos), (*cvi).coef);
          break;
        }
        case Exists_Var:
        case Wildcard_Var: {
          std::map<Variable_ID, Variable_ID>::iterator p = exists_mapping.find((*cvi).var);
          Variable_ID e;
          if (p == exists_mapping.end()) {
            e = fe->declare();
            exists_mapping[(*cvi).var] = e;
          }
          else
            e = (*p).second;
          h.update_coef(e, (*cvi).coef);
          break;
        }
        case Global_Var: {
          Global_Var_ID g = (*cvi).var->get_global_var();
          Variable_ID v;
          if (g->arity() == 0)
            v = new_r.get_local(g);
          else
            v = new_r.get_local(g, (*cvi).var->function_of());
          h.update_coef(v, (*cvi).coef);
          break;
        }
        default:
          assert(0);
        }
      h.update_const((*gi).get_const());

      for (int i = 1; i <= repl_var.size(); i++) {
        Variable_ID v = r.set_var(repl_var[i]);
        coef_t coef = h.get_coef_during_simplify(v);
        if (coef != 0) {
          EQ_Handle &h2 = repl_eq[i];
          coef_t coef2 = h2.get_coef(v);
          coef_t common = lcm(abs(coef), abs(coef2));
          int sign = (coef>0?1:-1)*(coef2>0?1:-1);
          coef_t scale = common/abs(coef);
          coef_t scale2 = common/abs(coef2);
          for (Constr_Vars_Iter cv(h); cv; cv++)
            h.update_coef(cv.curr_var(), (scale-1)*h.get_coef_during_simplify(cv.curr_var()));
          h.update_const((scale-1)*h.get_const_during_simplify());

          for (Constr_Vars_Iter cv(h2); cv; cv++) {
            Variable_ID v = cv.curr_var();
            if (v->kind() == Global_Var) {
              Global_Var_ID g = v->get_global_var();
              if (g->arity() == 0)
                v = new_r.get_local(g);
              else
                v = new_r.get_local(g, v->function_of());
            }
            h.update_coef(v, -sign*scale2*cv.curr_coef());
          }
          h.update_const(-sign*scale2*h2.get_const());
        }
      }
    }
    
    for (EQ_Iterator ei = (*d)->EQs(); ei; ei++) {
      EQ_Handle h = f_root->add_EQ();
      for (Constr_Vars_Iter cvi(*ei); cvi; cvi++)
        switch ((*cvi).var->kind()) {
        // case Set_Var:
        case Input_Var: {
          int pos = (*cvi).var->get_position();
          h.update_coef(new_r.set_var(pos), (*cvi).coef);
          break;
        }
        case Exists_Var:
        case Wildcard_Var: {
          std::map<Variable_ID, Variable_ID>::iterator p = exists_mapping.find((*cvi).var);
          Variable_ID e;
          if (p == exists_mapping.end()) {
            e = fe->declare();
            exists_mapping[(*cvi).var] = e;
          }
          else
            e = (*p).second;
          h.update_coef(e, (*cvi).coef);
          break;
        }
        case Global_Var: {
          Global_Var_ID g = (*cvi).var->get_global_var();
          Variable_ID v;
          if (g->arity() == 0)
            v = new_r.get_local(g);
          else
            v = new_r.get_local(g, (*cvi).var->function_of());
          h.update_coef(v, (*cvi).coef);
          break;
        }
        default:
          assert(0);
        }
      h.update_const((*ei).get_const());

      for (int i = 1; i <= repl_var.size(); i++) {
        Variable_ID v = r.set_var(repl_var[i]);
        coef_t coef = h.get_coef_during_simplify(v);
        if (coef != 0) {
          EQ_Handle &h2 = repl_eq[i];
          coef_t coef2 = h2.get_coef(v);
          coef_t common = lcm(abs(coef), abs(coef2));
          int sign = (coef>0?1:-1)*(coef2>0?1:-1);
          coef_t scale = common/abs(coef);
          coef_t scale2 = common/abs(coef2);
          for (Constr_Vars_Iter cv(h); cv; cv++)
            h.update_coef(cv.curr_var(), (scale-1)*h.get_coef_during_simplify(cv.curr_var()));
          h.update_const((scale-1)*h.get_const_during_simplify());

          for (Constr_Vars_Iter cv(h2); cv; cv++) {
            Variable_ID v = cv.curr_var();
            if (v->kind() == Global_Var) {
              Global_Var_ID g = v->get_global_var();
              if (g->arity() == 0)
                v = new_r.get_local(g);
              else
                v = new_r.get_local(g, v->function_of());
            }
            h.update_coef(v, -sign*scale2*cv.curr_coef());
          }
          h.update_const(-sign*scale2*h2.get_const());
        }
      }
    }
  }
  
  new_r.copy_names(r);
  new_r.setup_names();
  return new_r;
}



void elimination_info::print_eliminated(FILE *out) {
  for(int i = 1; i <= eliminated.size(); i++)
    fprintf(out, "%s (%s %d)  ", eliminated[i]->char_name(),
            (eliminated[i]->kind() == Input_Var? "input var" : "output var"),
            eliminated[i]->get_position());
  fprintf(out, "\n");
}

std::string elimination_info::print_eliminated_to_string() {
  std::string res;
  for(int i = 1; i <= eliminated.size(); i++)
    res += eliminated[i]->name() 
      + (eliminated[i]->kind() == Input_Var? "(input " : "(output ")
      + to_string(eliminated[i]->get_position())
      + ") ";
  return res;
}

} // namespace
