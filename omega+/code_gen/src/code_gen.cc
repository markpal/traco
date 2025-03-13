/*****************************************************************************
 Copyright (C) 1994-2000 University of Maryland
 Copyright (C) 2008 University of Southern California
 Copyright (C) 2009 University of Utah
 All Rights Reserved.

 Purpose:
   code generation support functions.

 Notes:

 History:
   05/20/09 rewrite greatest_common_step function, Chun Chen
*****************************************************************************/

#include <omega.h>
#include <omega/Rel_map.h>
#include <code_gen/elim.h>
#include <code_gen/code_gen.h>
#include <basic/Collection.h>
#include <basic/Bag.h>
#include <basic/Map.h>
#include <basic/util.h>
#include <math.h>
#include <set>
#include <map>
#include <vector>
#include <stack>

//*****************************************************************************
// Omega code gen builder and internal representation
//*****************************************************************************
#include <code_gen/CG_outputBuilder.h>
#include <code_gen/CG_outputRepr.h>
#include <code_gen/CG_stringBuilder.h>
#include <code_gen/CG_stringRepr.h>
#include <code_gen/stmt_builder.h>

namespace omega {

#if ! defined DONT_EVEN_TRY_TO_COMPILE_CODE_GEN_WITH_CFRONT

static int last_level;// Should not be global, but it is.
static int OMEGA_WHINGE = -1;

SetTuple function_guards;
SetTuple new_IS;
SetTupleTuple projected_nIS;
Tuple<stmt_info *> statementNameInfo;


// ******************************************
//  Added by davew 1/28/99 to keep g++ happy
// ******************************************


CG_result::~CG_result() {
}


//*****************************************************************************
// Declarations added by D people. Lei Zhou Apr. 20, 96
//*****************************************************************************
static
CG_outputRepr* outputEasyBoundAsRepr(CG_outputBuilder* ocg, Relation &bounds,
                                     const Constraint_Handle &g, 
                                     Variable_ID v, bool ignoreWC,
                                     int ceiling);

//*****************************************************************************
// static functions declared by Omega people. 
//*****************************************************************************
// used only by CG_leaf methods 
//-----------------------------------------------------------------------------

//*****************************************************************************
// static functions declared by D people. 
//*****************************************************************************


// find floor definition for variable such as m-3 <= 4v <= m
bool findFloorInequality(Relation &r, Variable_ID v, GEQ_Handle &h, Variable_ID excluded) {
  Conjunct *c = r.single_conjunct();

  std::set<Variable_ID> var_checked;
  std::stack<Variable_ID> var_checking;
  var_checking.push(v);

  while (!var_checking.empty()) {
    Variable_ID v2 = var_checking.top();
    var_checking.pop();

    bool is_floor = false;
    for (GEQ_Iterator gi(c); gi; gi++) {
      if (excluded != NULL && (*gi).get_coef(excluded) != 0)
        continue;
      
      coef_t a = (*gi).get_coef(v2);
      if (a < 0) {
        for (GEQ_Iterator gi2(c); gi2; gi2++) {
          coef_t b = (*gi2).get_coef(v2);
          if (b == -a && (*gi).get_const()+(*gi2).get_const() < -a) {
            bool match = true;
            for (Constr_Vars_Iter cvi(*gi); cvi; cvi++)
              if ((*gi2).get_coef((*cvi).var) != -(*cvi).coef) {
                match = false;
                break;
              }
            if (!match)
              continue;
            for (Constr_Vars_Iter cvi(*gi2); cvi; cvi++)
              if ((*gi).get_coef((*cvi).var) != -(*cvi).coef) {
                match = false;
                break;
              }
            if (match) {
              var_checked.insert(v2);
              is_floor = true;
              if (v == v2)
                h = *gi;

              for (Constr_Vars_Iter cvi(*gi); cvi; cvi++)
                if (((*cvi).var->kind() == Exists_Var || (*cvi).var->kind() == Wildcard_Var) &&
                    var_checked.find((*cvi).var) == var_checked.end())
                  var_checking.push((*cvi).var);
              
              break;
            }
          }
        }
        if (is_floor)
          break;
      }
    }
    if (!is_floor)
      return false;
  }
  return true;
}

          
  


//-----------------------------------------------------------------------------

//*****************************************************************************
// static functions declaration added by D people. Lei Zhou, Apr 23, 96
//*****************************************************************************
static 
bool outputAssignment(CG_outputBuilder* ocg,
                      Conjunct *c, Variable_ID v, int indent,
                      CG_outputRepr* &aRepr, 
                      Relation &new_known, elimination_info &eliminated);


static
bool outputBounds(CG_outputBuilder* ocg,
                 const Relation &bounds, Variable_ID v, int indent,
                 const Relation &input_known, Relation &new_known, 
                 CG_outputRepr* &ctrlRepr,
                 elimination_info &eliminated);
//-----------------------------------------------------------------------------

static
CG_outputRepr* output_guard(CG_outputBuilder* ocg, Relation &guards_in);

CG_outputRepr* outputAsGuard(CG_outputBuilder* ocg, Relation &guards_in,
                             NOT_CONST Constraint_Handle &e, 
                             bool is_geq);

CG_outputRepr* outputStrideAsRepr(CG_outputBuilder* ocg, Relation &guards_in,
                                  NOT_CONST EQ_Handle &e);

CG_outputRepr* output_GEQ_strides(CG_outputBuilder* ocg, Relation &guards, 
                                  Conjunct *c);
//-----------------------------------------------------------------------------

// static
// CG_outputRepr *outputLBasRepr(CG_outputBuilder* ocg, const GEQ_Handle &g, 
//                               Relation &bounds, Variable_ID v,
//          coef_t stride, const EQ_Handle &strideEQ,
//          Relation known);

// static
// CG_outputRepr *outputUBasRepr(CG_outputBuilder* ocg, const GEQ_Handle &g, 
//                               Relation &bounds, Variable_ID v,
//          coef_t stride, const EQ_Handle &strideEQ);

//*****************************************************************************
// static function added by D people. May 20.
//*****************************************************************************
// static String GetString(CG_outputRepr* repr);


static bool boundHitsStride(const GEQ_Handle &g, Variable_ID v,
                            const EQ_Handle &strideEQ,
                            coef_t stride, Relation known);




//-----------------------------------------------------------------------------

static CG_result * gen_recursive(int level, IntTuple &isActive);

static std::string outputSpaces(int indent_level) {
  std::string spaces;
  for(int i=1; i<indent_level; i++) spaces += "  ";
  return spaces;
}

//*****************************************************************************
CG_outputRepr* outputIdent(CG_outputBuilder* ocg, Variable_ID v) {
  if(v->kind() != Global_Var || v->get_global_var()->arity() == 0)
    return ocg->CreateIdent(v->name());
  else {
    /* This should be improved to take into account the possible elimination
       of the set variables. */
    int arity = v->get_global_var()->arity();
    assert(arity <= last_level);
    Tuple<CG_outputRepr *> argList;
    Relation R = Relation::True(arity);
    name_codegen_vars(R); // easy way to make sure the names are correct.
    for(int i = 1; i <= arity; i++)
      argList.append(ocg->CreateIdent(R.set_var(i)->name()));
    CG_outputRepr *call = ocg->CreateInvoke(v->get_global_var()->base_name(), argList);
    return call;
  }
}


//*****************************************************************************
CG_outputRepr* outputAsGuard(CG_outputBuilder* ocg, Relation &guards_in,
                             NOT_CONST Constraint_Handle &input_e, 
                             bool is_geq) {
  Constraint_Handle &e = (Constraint_Handle&) input_e;
  CG_outputRepr *guardRepr;
  std::string s;
  // pick any v in EQ, print in terms of it.
  Variable_ID v=0;
  for(Constr_Vars_Iter cvi(e,false); cvi; cvi++) {
    if((*cvi).var->kind() != Wildcard_Var) {
      v = (*cvi).var;
      break;
    }
  }

  assert(v && "Must be some non-wildcards in the constraint");
  coef_t saved_coef = ((e).get_coef(v));
  assert(saved_coef);

  // The coef of v should have the same sign as saved_coef, but its abs
  // should be 1 so that outputEasy doesn't divide through by its coef
  int sign = saved_coef < 0 ? -1 : 1;
  (e).update_coef_during_simplify(v,-saved_coef+sign);
  // outputEasyBound fixes coefficients for the sign of v's coefficient,
  // so we should use abs here.

  CG_outputRepr* lop = outputIdent(ocg,v);
  if (abs(saved_coef) != 1) {
    lop = ocg->CreateTimes(ocg->CreateInt(abs(saved_coef)), lop);
  }

  CG_outputRepr* rop = outputEasyBoundAsRepr(ocg, guards_in, e, v, false, 0);
  if (is_geq) {
    if (saved_coef < 0) {
      guardRepr = ocg->CreateLE(lop, rop);
    }
    else {
      guardRepr = ocg->CreateGE(lop, rop);
    }
  } 
  else {
    guardRepr = ocg->CreateEQ(lop, rop);
  }

  (e).update_coef_during_simplify(v,saved_coef-sign);
  
  return guardRepr;
}

static void get_stride(const Constraint_Handle &h, Variable_ID &wc, coef_t &step){
  wc = 0;
  for(Constr_Vars_Iter i(h,true); i; i++) {
    assert(wc == 0);
    wc = (*i).var;
    step = ((*i).coef);
  }
}


//-----------------------------------------------------------------------------
// generate the output loop stride as CG_outputRepr
// the original name is :
// String outputStrideAsString(EQ_Handle &e)
//-----------------------------------------------------------------------------
CG_outputRepr* outputStrideAsRepr(CG_outputBuilder* ocg, Relation &guards_in,
                                  NOT_CONST EQ_Handle &input_e) {
  Constraint_Handle &e = (Constraint_Handle&) input_e;
  Variable_ID wc;
  coef_t step;
  get_stride(e, wc, step);
  assert(step != 0);
  coef_t posstep = (step < 0) ? -step : step;
  e.update_coef_during_simplify(wc,1-step);

  CG_outputRepr* lop = outputEasyBoundAsRepr(ocg, guards_in, e, wc, false, 0);
  CG_outputRepr* rop = ocg->CreateInt(posstep);
  CG_outputRepr* intMod = ocg->CreateIntegerMod(lop, rop);
  CG_outputRepr* eqNode = ocg->CreateEQ(intMod, ocg->CreateInt(0));

  e.update_coef_during_simplify(wc,step-1);

  return eqNode;
}


//-----------------------------------------------------------------------------
// output_GEQ_strides
// original name is:
//   String output_GEQ_strides(Relation &guards, Conjunct *c, bool &first)
// Collect wildcards
// For each whildcard
//   collect lower and upper bounds in which wildcard appears
//   For each lower bound
//     create constraint with each upper bound
//-----------------------------------------------------------------------------
CG_outputRepr* output_GEQ_strides(CG_outputBuilder* ocg,
                                  Relation &guards,
                                  Conjunct *c) {
  CG_outputRepr* geqRepr = NULL;

  std::set<Variable_ID> non_orphan_wildcard;
  for (GEQ_Iterator gi(c); gi; gi++) {
    int num_wild = 0;
    Variable_ID first_one;
    for (Constr_Vars_Iter cvi(*gi, true); cvi; cvi++) {
      num_wild++;
      if (num_wild == 1)
        first_one = (*cvi).var;
      else
        non_orphan_wildcard.insert((*cvi).var);
    }
    if (num_wild > 1)
      non_orphan_wildcard.insert(first_one);
  }

  for (int i = 1; i <= (*(c->variables())).size(); i++) {
    Variable_ID wc = (*(c->variables()))[i];
    if (wc->kind() == Wildcard_Var && non_orphan_wildcard.find(wc) == non_orphan_wildcard.end()) {
      Tuple<GEQ_Handle> lower, upper;
      for (GEQ_Iterator gi(c); gi; gi++) {
        if((*gi).get_coef(wc) > 0) 
          lower.append(*gi); 
        else if((*gi).get_coef(wc) < 0)
          upper.append(*gi);
      }

      // low: c*alpha - x >= 0
      // up:  -d*alpha + y >= 0
      for(Tuple_Iterator<GEQ_Handle> low(lower); low; low++) {
        for(Tuple_Iterator<GEQ_Handle> up(upper); up; up++) {
          coef_t low_coef = (*low).get_coef(wc);
          coef_t up_coef = (*up).get_coef(wc);
          assert(low_coef > 0 && up_coef < 0);
          (*low).update_coef_during_simplify(wc, 1-low_coef);
          CG_outputRepr* lowExpr = outputEasyBoundAsRepr(ocg, guards, *low, wc, false, 0);
          (*low).update_coef_during_simplify(wc, low_coef-1);
          (*up).update_coef_during_simplify(wc, -1-up_coef);
          CG_outputRepr* upExpr = outputEasyBoundAsRepr(ocg, guards, *up, wc, false, 0);
          (*up).update_coef_during_simplify(wc, up_coef+1);
 
          CG_outputRepr* intDiv = ocg->CreateIntegerDivide(upExpr, ocg->CreateInt(-up_coef));
          CG_outputRepr* rop = ocg->CreateTimes(ocg->CreateInt(low_coef), intDiv);
          CG_outputRepr* geqNode = ocg->CreateLE(lowExpr, rop);
 
          if ( geqRepr != NULL) {
            geqRepr = ocg->CreateAnd(geqRepr, geqNode);
          }
          else {
            geqRepr = geqNode;
          }
        }
      }
    }
  }

  if (non_orphan_wildcard.size() > 0) {
    // e.g.  c*alpha - x >= 0              (*)
    //       -d*alpha + y >= 0             (*)
    //       e1*alpha + f1*beta + g1 >= 0  (**)
    //       e2*alpha + f2*beta + g2 >= 0  (**)
    //       ...
    // TODO: should generate a testing loop for alpha using its lower and
    // upper bounds from (*) constraints and do the same if-condition test
    // for beta from each pair of opposite (**) constraints as above,
    // and exit the loop when if-condition satisfied.
    assert(0 && "Can't generate multiple wildcard GEQ guards right now");
  }

  return geqRepr;
}


//-----------------------------------------------------------------------------
// This returns a string containing the constraints in relation guards
// in a form suitable for C.  If there are no constraints in guards,
// nothing is returned.
//-----------------------------------------------------------------------------
static CG_outputRepr* output_guard(CG_outputBuilder* ocg, Relation &guards_in) {
  CG_outputRepr* nodeRepr = NULL;

  Relation guards = guards_in;
  assert(guards.has_single_conjunct());
  guards.setup_names();
  Conjunct *c = guards.single_conjunct();

  //---------------------------------------------------------------------------
  // equalities guards go here, like P1 == P2
  //---------------------------------------------------------------------------
  for(EQ_Iterator e(c); e; e++) {
    bool is_stride = (*e).has_wildcards();
    if (is_stride) {
      CG_outputRepr* eqNode = outputStrideAsRepr(ocg, guards, *e);
      if (nodeRepr != NULL) {
        nodeRepr = ocg->CreateAnd(nodeRepr, eqNode);
      }
      else {
        nodeRepr = eqNode;
      }
    } 
    else {
      // This is a normal EQ, no stride
      CG_outputRepr* eqNode = outputAsGuard(ocg, guards, *e, false);
      if (nodeRepr != NULL) {
        nodeRepr = ocg->CreateAnd(nodeRepr, eqNode);
      }
      else {
        nodeRepr = eqNode;
      }
      //old way:     s += (*e).print_to_string();
    }
  }

  //---------------------------------------------------------------------------
  // The 0.96 had not the line s += output_GEQ_strides(guards,c,first);
  // fortunately s1 = output_GEQ_strides(guards,c,first) is always empty.
  // output_GEQ_strides has CONNECTOR there.
  //---------------------------------------------------------------------------
  // s += output_GEQ_strides(guards, c, first);
  CG_outputRepr *geqStrideRepr = output_GEQ_strides(ocg, guards, c);
  if ( geqStrideRepr != NULL ) {
    if ( nodeRepr != NULL ) {
      nodeRepr = ocg->CreateAnd(nodeRepr, geqStrideRepr);
    }
    else {
      nodeRepr = geqStrideRepr;
    }
  }
  
  //---------------------------------------------------------------------------
  // inequalities guards go here, like (n <= t2+63 && t1 <= t2-63)
  //---------------------------------------------------------------------------
  for(GEQ_Iterator g(c); g; g++) {
    if(!(*g).has_wildcards()) {

      CG_outputRepr* geqNode = outputAsGuard(ocg, guards, *g, true);
      if(nodeRepr != NULL) {
        nodeRepr = ocg->CreateAnd(nodeRepr, geqNode);
      }
      else {
        nodeRepr = geqNode;
      }
    }
  }

  return nodeRepr;
}


//-----------------------------------------------------------------------------
// one is 1 for LB
// this function is overloaded should replace the original one
//-----------------------------------------------------------------------------
CG_outputRepr *outputLBasRepr(CG_outputBuilder* ocg, const GEQ_Handle &g, 
                              Relation &bounds, Variable_ID v,
                              coef_t stride, const EQ_Handle &strideEQ,
                              Relation known) {
#if ! defined NDEBUG
  coef_t v_coef;
  assert((v_coef = g.get_coef(v)) > 0);
#endif

  std::string s;
  CG_outputRepr *lbRepr;
  if (stride == 1) {
    lbRepr = outputEasyBoundAsRepr(ocg, bounds, g, v, false, 1);
  }
  else {
    if (!boundHitsStride(g,v,strideEQ,stride,known)) {
      bounds.setup_names(); // boundsHitsStride resets variable names

      CG_stringBuilder oscg;
      std::string c = GetString(outputEasyBoundAsRepr(&oscg, bounds, strideEQ, v, true, 0));
      CG_outputRepr *cRepr = NULL;
      if (c != std::string("0"))
        cRepr = outputEasyBoundAsRepr(ocg, bounds, strideEQ, v, true, 0);
      std::string LoverM = GetString(outputEasyBoundAsRepr(&oscg, bounds, g, v, false, 1));
      CG_outputRepr *LoverMRepr = NULL;
      if (LoverM != std::string("0"))
        LoverMRepr = outputEasyBoundAsRepr(ocg, bounds, g, v, false, 1); 

      if (code_gen_debug > 2) {
        fprintf(DebugFile,"::: LoverM is %s\n", LoverM.c_str());
        fprintf(DebugFile,"::: c is %s\n", c.c_str());
      }

      int complexity1 = 0, complexity2 = 0;
      for (size_t i = 0; i < c.length(); i++)
        if (c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/')
          complexity1++;
        else if (c[i] == ',')
          complexity1 += 2;
      for (size_t i = 0; i < LoverM.length(); i++)
        if (LoverM[i] == '+' || LoverM[i] == '-' || LoverM[i] == '*' || LoverM[i] == '/')
          complexity2++;
        else if (LoverM[i] == ',')
          complexity2 += 2;
      
      if (complexity1 < complexity2) {
        CG_outputRepr *idUp = LoverMRepr;
        CG_outputRepr *c1Repr = ocg->CreateCopy(cRepr);
        idUp = ocg->CreateMinus(idUp, c1Repr);
        idUp = ocg->CreatePlus(idUp, ocg->CreateInt(stride-1));
        CG_outputRepr *idLow = ocg->CreateInt(stride);
        lbRepr = ocg->CreateTimes(ocg->CreateInt(stride),
                                  ocg->CreateIntegerDivide(idUp, idLow));
        lbRepr = ocg->CreatePlus(lbRepr, cRepr);
      }
      else {
        CG_outputRepr *LoverM1Repr = ocg->CreateCopy(LoverMRepr);
        CG_outputRepr *imUp = ocg->CreateMinus(cRepr, LoverM1Repr);
        CG_outputRepr *imLow = ocg->CreateInt(stride);
        CG_outputRepr *intMod = ocg->CreateIntegerMod(imUp, imLow);
        lbRepr = ocg->CreatePlus(LoverMRepr, intMod);
      }
    } 
    else {
      // boundsHitsStride resets variable names
      bounds.setup_names(); 
      lbRepr = outputEasyBoundAsRepr(ocg, bounds, g, v, false, 0);
    }
  }

  return lbRepr;
}


//-----------------------------------------------------------------------------
// one is -1 for UB
// this function is overloaded should replace the original one
//-----------------------------------------------------------------------------
CG_outputRepr *outputUBasRepr(CG_outputBuilder* ocg, const GEQ_Handle &g, 
                              Relation & bounds,
                              Variable_ID v,
                              coef_t /*stride*/, // currently unused
                              const EQ_Handle &/*strideEQ*/) { //currently unused 
  assert(g.get_coef(v) < 0);
  CG_outputRepr* upRepr = outputEasyBoundAsRepr(ocg, bounds, g, v, false, 0);
  return upRepr;
}


//-----------------------------------------------------------------------------
// Print the expression for the variable given as v.  Works for both 
// GEQ's and EQ's, but produces intDiv (not intMod) when v has a nonunit 
// coefficient.  So it is OK for loop bounds, but for checking stride
// constraints, you want to make sure the coef of v is 1, and insert the
// intMod yourself.
//
// original name is outputEasyBound
//-----------------------------------------------------------------------------
static CG_outputRepr* outputEasyBoundAsRepr(CG_outputBuilder* ocg, Relation &bounds,
                                            const Constraint_Handle &g, Variable_ID v, 
                                            bool ignoreWC,
                                            int ceiling) {
  // assert ignoreWC => g is EQ
  // rewrite constraint as foo (== or <= or >=) v, return foo as string 

  CG_outputRepr* easyBoundRepr = NULL;

  coef_t v_coef = g.get_coef(v);
  int v_sign = v_coef > 0 ? 1 : -1;
  v_coef *= v_sign;
  assert(v_coef > 0);
  // foo is (-constraint)/v_sign/v_coef 

  int sign_adj = -v_sign;

  //----------------------------------------------------------------------
  // the following generates +- cf*varName
  //----------------------------------------------------------------------
  for(Constr_Vars_Iter c2(g, false); c2; c2++) {
    if ((*c2).var != v && (!ignoreWC || (*c2).var->kind()!=Wildcard_Var)) {

      coef_t cf = (*c2).coef*sign_adj;
      assert(cf != 0);

      CG_outputRepr *varName;
      if ((*c2).var->kind() == Wildcard_Var) {
        GEQ_Handle h;
        if (!findFloorInequality(bounds, (*c2).var, h, v)) {
          if (easyBoundRepr != NULL) {
            easyBoundRepr->clear();
            delete easyBoundRepr;
          }
          return NULL;
        }
        varName = outputEasyBoundAsRepr(ocg, bounds, h, (*c2).var, false, 0);
      }
      else {
        varName = outputIdent(ocg,(*c2).var);
      }
      CG_outputRepr *cfRepr = NULL;

      if (cf > 1) {
        cfRepr = ocg->CreateInt(cf);
        CG_outputRepr* rbRepr = ocg->CreateTimes(cfRepr, varName);
        easyBoundRepr = ocg->CreatePlus(easyBoundRepr, rbRepr);
      }
      else if (cf < -1) {
        cfRepr = ocg->CreateInt(-cf);
        CG_outputRepr* rbRepr = ocg->CreateTimes(cfRepr, varName);
        easyBoundRepr = ocg->CreateMinus(easyBoundRepr, rbRepr);
      }
      else if (cf == 1) {
        easyBoundRepr = ocg->CreatePlus(easyBoundRepr, varName);
      }
      else if (cf == -1) {
        easyBoundRepr = ocg->CreateMinus(easyBoundRepr, varName);
      }
    }
  }

  if (g.get_const()) {
    coef_t cf = g.get_const()*sign_adj;
    assert(cf != 0);
    if (cf > 0) {
      easyBoundRepr = ocg->CreatePlus(easyBoundRepr, ocg->CreateInt(cf));
    }
    else {
      easyBoundRepr = ocg->CreateMinus(easyBoundRepr, ocg->CreateInt(-cf));
    }
  }
  else {
    if(easyBoundRepr == NULL) {
      easyBoundRepr = ocg->CreateInt(0);
    }
  }

  if (v_coef > 1) {
    assert(ceiling >= 0);
    if (ceiling) {
      easyBoundRepr= ocg->CreatePlus(easyBoundRepr, ocg->CreateInt(v_coef-1));
    }
    easyBoundRepr = ocg->CreateIntegerDivide(easyBoundRepr, ocg->CreateInt(v_coef));
  }
  
  return easyBoundRepr;
}


static bool outputAssignment(CG_outputBuilder* ocg,
                             Conjunct *c, Variable_ID v, int indent,
                             CG_outputRepr* &aRepr, 
                             Relation &new_known, elimination_info &eliminated) {
  CG_outputRepr *lopRepr = NULL;
  CG_outputRepr *ropRepr = NULL;
  CG_outputRepr *idLopRepr = NULL;    // for lop in intDiv(lop, rop)
  
  EQ_Iterator I(c); 
  
  // Find first EQ that involves the interesting variable
  while ( I.live() && (*I).get_coef(v) == 0 ) 
    I++;
  
  if (!I.live()) {
    if (code_gen_debug > 2) 
      fprintf(DebugFile, "::: outputAssignment: no EQs?\n");
    return false;  // No EQ's but also no UB or LB's on this var
  }

  //---------------------------------------------------------------------------
  // If there is a simple substitution for this variable, (the
  // variable's coefficient is +-1) we can remove it from the generated
  // code.  In order to avoid seeing this variable in later loop bounds,
  // we will project it away (at that time) and replace it with a
  // variable that has no constraints on it.  Here we just mark it as
  // eliminated.
  //---------------------------------------------------------------------------

  coef_t divider = (*I).get_coef(v);
  int sign = 1;
  if (divider < 0) {
    divider = -divider;
    sign = -1;
  }
  assert(divider >= 1);
  if (divider == 1 && eliminated.may_eliminate(v)) {
    eliminated.eliminate(v);
  } 
  else {
    //-------------------------------------------------------------------------
    // left operand of the assignment
    //-------------------------------------------------------------------------
    lopRepr = outputIdent(ocg,v);

    for (Constr_Vars_Iter CVI(*I,false); CVI; CVI++) {

      //-----------------------------------------------------------------------
      // get the name of this constr_vars, may also include coef but no sign.(+-)
      //-----------------------------------------------------------------------
      CG_outputRepr *varRepr = outputIdent(ocg,(*CVI).var);

      //-----------------------------------------------------------------------
      // determine the sign and coefficient of this constr_vars
      //-----------------------------------------------------------------------
      if ((*CVI).var != v) {
        assert((*CVI).var->kind() != Wildcard_Var);

        if (-sign*(*CVI).coef == -1) {
          idLopRepr = ocg->CreateMinus(idLopRepr, varRepr);
        }
        else if (-sign*(*CVI).coef < -1) {
          varRepr = ocg->CreateTimes(ocg->CreateInt(sign*(*CVI).coef), varRepr);
          idLopRepr = ocg->CreateMinus(idLopRepr, varRepr);
        }
        else {
          if (-sign*(*CVI).coef != 1) {
            varRepr = ocg->CreateTimes(ocg->CreateInt(-sign*(*CVI).coef), varRepr);
          }
          idLopRepr = ocg->CreatePlus(idLopRepr, varRepr);
        }
      }
    }

    coef_t c_term = -((*I).get_const() * sign);

    if ( c_term ) {    // Not a zero
      if ( c_term > 0) {
        idLopRepr = ocg->CreatePlus(idLopRepr, ocg->CreateInt(c_term));
      }
    }
    else {
      if (idLopRepr == NULL) {
        // Must print the zero if no other terms, now c_term == 0
        idLopRepr = ocg->CreateInt(c_term);
      }
    }

    if (divider != 1) { // divider might == 1 if !may_eliminate(v)
      idLopRepr = ocg->CreatePlus(idLopRepr, ocg->CreateInt(divider-1));
      ropRepr = ocg->CreateIntegerDivide(idLopRepr, ocg->CreateInt(divider));
    }
    else {
      ropRepr = idLopRepr;
    }


    aRepr = ocg->CreateAssignment(indent, lopRepr, ropRepr);
  }

  new_known.and_with_EQ(*I);

  // See if any more EQ's with this variable
  I++;
  while(I.live() && (*I).get_coef(v) == 0) 
    I++;

  if ((code_gen_debug > 2) && I.live())
    fprintf(DebugFile, "::: outputAssignment: more than 1 EQ found\n");

  return (!I.live());
}


static bool outputBounds(CG_outputBuilder* ocg,
                         const Relation &bounds, Variable_ID v, int indent,
                         const Relation &input_known, Relation &new_known, 
                         CG_outputRepr* &ctrlRepr,
                         elimination_info &eliminated) {
  Relation b = copy(bounds);
  Relation known = const_cast<Relation &>(input_known);
  CG_outputRepr *indexRepr = NULL;
  CG_outputRepr *lbRepr = NULL;
  CG_outputRepr *ubRepr = NULL;
  CG_outputRepr *stRepr = NULL;

  if (code_gen_debug> 2) {
    fprintf(DebugFile,"::: printBounds generating bounds for\n");
    b.prefix_print(DebugFile);
  }
  Conjunct *c = b.query_DNF()->single_conjunct();

  // Elaborate stride simplification which is complementary to gist function
  // since we further target the specific loop variable.  -- by chun 08/07/2008
  Relation r1 = Relation::True(b.n_set()), r2 = Relation::True(b.n_set());
  for (EQ_Iterator ei(c); ei; ei++) {
    if ((*ei).get_coef(v) != 0 && (*ei).has_wildcards()) { // stride condition found
      coef_t sign;
      if ((*ei).get_coef(v) > 0)
        sign = 1;
      else
        sign = -1;

      coef_t stride = 0;
      for (Constr_Vars_Iter cvi(*ei, true); cvi; cvi++)
        if ((*cvi).var->kind() == Wildcard_Var) {
          stride = abs((*cvi).coef);
          break;
        }

      // check if stride hits lower bound
      bool found_match = false;
      if (abs((*ei).get_coef(v)) != 1) { // expensive matching for non-clean stride condition
        coef_t d = stride / gcd(abs((*ei).get_coef(v)), stride);
        Relation r3 = Relation::True(b.n_set());
        r3.and_with_EQ(*ei);
        
        for (GEQ_Iterator gi(c); gi; gi++) {
          if ((*gi).get_coef(v) == 1 && !(*gi).has_wildcards()) {
            Relation r4(b.n_set());
            F_And *f_root = r4.add_and();
            Stride_Handle h = f_root->add_stride(d);
            
            for (Constr_Vars_Iter cvi(*gi); cvi; cvi++)
              switch ((*cvi).var->kind()) {
              // case Set_Var:
              case Input_Var: {
                int pos = (*cvi).var->get_position();
                h.update_coef(r4.set_var(pos), (*cvi).coef);
                break;
              }
              case Global_Var: {
                Global_Var_ID g = (*cvi).var->get_global_var();
                Variable_ID v;
                if (g->arity() == 0)
                  v = r4.get_local(g);
                else
                  v = r4.get_local(g, (*cvi).var->function_of());
                h.update_coef(v, (*cvi).coef);
                break;
              }
              default:
                fprintf(DebugFile, "can't deal with the variable type in lower bound\n");
                return false;
              }
            h.update_const((*gi).get_const());

            Relation r5 = Gist(copy(r3), Intersection(copy(r4), copy(known)));

            // replace original stride condition with striding from this lower bound
            if (r5.is_obvious_tautology()) {
              r1 = Intersection(r1, r4);
              found_match = true;
              break;
            }
          }
        }
      }
      else {
        for (GEQ_Iterator gi(c); gi; gi++) {
          if ((*gi).get_coef(v) == abs((*ei).get_coef(v)) && !(*gi).has_wildcards()) { // potential matching lower bound found
            Relation r(b.n_set());
            Stride_Handle h = r.add_and()->add_stride(stride);

            for (Constr_Vars_Iter cvi(*gi); cvi; cvi++)
              switch ((*cvi).var->kind()) {
              // case Set_Var:
              case Input_Var: {
                int pos = (*cvi).var->get_position();
                if ((*cvi).var != v) {
                  int t1 = int_mod((*cvi).coef, stride);
                  if (t1 != 0) {
                    coef_t t2 = known.query_variable_mod(known.set_var(pos), stride);
                    if (t2 != posInfinity)
                      h.update_const(t1*t2);
                    else
                      h.update_coef(r.set_var(pos), t1);
                  }
                }
                else
                  h.update_coef(r.set_var(pos), (*cvi).coef);
                break;
              }
              case Global_Var: {
                Global_Var_ID g = (*cvi).var->get_global_var();
                Variable_ID v;
                if (g->arity() == 0)
                  v = known.get_local(g);
                else
                  v = known.get_local(g, (*cvi).var->function_of());
                coef_t t = known.query_variable_mod(v, stride);
                if (t != posInfinity)
                  h.update_const(t*(*cvi).coef);
                else {
                  Variable_ID v2;
                  if (g->arity() == 0)
                    v2 = r.get_local(g);
                  else
                    v2 = r.get_local(g, (*cvi).var->function_of());
                  h.update_coef(v2, (*cvi).coef);
                }
                break;
              }
              default:
                fprintf(DebugFile, "can't deal with the variable type in lower bound\n");
                return false;
              }
            h.update_const((*gi).get_const());

            bool t = true;
            {
              Conjunct *c2 = r.query_DNF()->single_conjunct();
              EQ_Handle h2;
              for (EQ_Iterator ei2(c2); ei2; ei2++) {
                h2 = *ei2;
                break;
              }
                        
              int sign;
              if (h2.get_coef(v) == (*ei).get_coef(v))
                sign = 1;
              else
                sign = -1;

              t = int_mod(h2.get_const() - sign * (*ei).get_const(), stride) == 0;

              if (t != false)
                for (Constr_Vars_Iter cvi(h2); cvi; cvi++)
                  if ((*cvi).var->kind() != Wildcard_Var &&
                      int_mod((*cvi).coef - sign * (*ei).get_coef((*cvi).var), stride) != 0) {
                    t = false;
                    break;
                  }
                  
              if (t != false)
                for (Constr_Vars_Iter cvi(*ei); cvi; cvi++)
                  if ((*cvi).var->kind() != Wildcard_Var &&
                      int_mod((*cvi).coef - sign * h2.get_coef((*cvi).var), stride) != 0) {
                    t = false;
                    break;
                  }
              
            }
            
            if (t) {
              // replace original stride condition with striding from this lower bound
              F_And *f_root = r1.and_with_and();
              Stride_Handle h = f_root->add_stride(stride);
              for (Constr_Vars_Iter cvi(*gi); cvi; cvi++)
                switch ((*cvi).var->kind()) {
                // case Set_Var:
                case Input_Var: {
                  h.update_coef(r1.set_var((*cvi).var->get_position()), (*cvi).coef);
                  break;
                }
                case Global_Var: {
                  Global_Var_ID g = (*cvi).var->get_global_var();
                  Variable_ID v;
                  if (g->arity() == 0)
                    v = r1.get_local(g);
                  else
                    v = r1.get_local(g, (*cvi).var->function_of());
                  h.update_coef(v, (*cvi).coef);
                  break;
                }
                default:
                  fprintf(DebugFile, "can't deal with the variable type in lower bound\n");
                  return false;
                }
              h.update_const((*gi).get_const());
            
              found_match = true;
              break;
            }
          }
        }
      }

      if (!found_match)
        r1.and_with_EQ(*ei);   
    }
    else if ((*ei).get_coef(v) == 0) {
        Relation r3 = Relation::True(b.n_set());
        r3.and_with_EQ(*ei);
        Relation r4 = Gist(r3, copy(known));
        if (!r4.is_obvious_tautology())
          r2.and_with_EQ(*ei);
    }
    else 
      r2.and_with_EQ(*ei);
  }
      
  // restore remaining inequalities
  {
    std::map<Variable_ID, Variable_ID> exists_mapping;
    F_Exists *fe = r2.and_with_and()->add_exists();
    F_And *f_root = fe->add_and();
    for (GEQ_Iterator gi(c); gi; gi++) {
      GEQ_Handle h = f_root->add_GEQ();
      for (Constr_Vars_Iter cvi(*gi); cvi; cvi++) {
        Variable_ID v = cvi.curr_var();
        switch (v->kind()) {
        // case Set_Var:
        case Input_Var: {
          int pos = v->get_position();
          h.update_coef(r2.set_var(pos), cvi.curr_coef());
          break;
        }
        case Exists_Var:
        case Wildcard_Var: {
          std::map<Variable_ID, Variable_ID>::iterator p = exists_mapping.find(v);
          Variable_ID e;
          if (p == exists_mapping.end()) {
            e = fe->declare();
            exists_mapping[v] = e;
          }
          else
            e = (*p).second;
          h.update_coef(e, cvi.curr_coef());
          break;
        }
        case Global_Var: {
          Global_Var_ID g = v->get_global_var();
          Variable_ID v2;
          if (g->arity() == 0)
            v2 = r2.get_local(g);
          else
            v2 = r2.get_local(g, v->function_of());
          h.update_coef(v2, cvi.curr_coef());
          break;
        }
        default:
          assert(0);
        }
      }
      h.update_const((*gi).get_const());
    }
  }
          
  // overwrite original bounds
  {
    r1.simplify();
    r2.simplify();
    Relation b2 = Intersection(r1, r2);
    b2.simplify();
    for (int i = 1; i <= b.n_set(); i++)
      b2.name_set_var(i, b.set_var(i)->name());
    b2.setup_names();
    b = b2;
    c = b.query_DNF()->single_conjunct();
  }  
    

  // get loop strides
  EQ_Handle strideEQ;
  bool foundStride = false; // stride that can be translated to loop
  bool foundSimpleStride = false; // stride that starts from const value
  coef_t step = 1;
  int num_stride = 0;

  for (EQ_Iterator ei(c); ei; ei++) {
    if ((*ei).get_coef(v) != 0 && (*ei).has_wildcards()) {
      num_stride++;

      if (abs((*ei).get_coef(v)) != 1)
        continue;

      bool t = true;
      coef_t d = 1;
      for (Constr_Vars_Iter cvi(*ei); cvi; cvi++)
        if ((*cvi).var->kind() == Wildcard_Var) {
          assert(d==1);
          d = abs((*cvi).coef);
        }
        else if ((*cvi).var->kind() == Set_Var || (*cvi).var->kind() == Input_Var) {
          if ((*cvi).var != v)
            t = false;
        }
        else
          t = false;

      if (d > step) {
        step = d;
        foundSimpleStride = t;
        strideEQ = *ei;
        foundStride = true;
      }
    }
  }

  // More than one stride or complex stride found, we should move all
  // but strideEQ to body's guard condition. alas, not implemented.
  if (!(num_stride == 0 || (num_stride == 1 && foundStride)))
    return false;

  // get loop bounds
  int lower_bounds = 0, upper_bounds = 0;
  Tuple<CG_outputRepr *> lbList;
  Tuple<CG_outputRepr *> ubList;
  coef_t const_lb = negInfinity, const_ub = posInfinity;
  for (GEQ_Iterator g(c); g; g++) {
    coef_t coef = (*g).get_coef(v);
    if (coef == 0) 
      continue;
    else if (coef > 0) { // lower bound
      lower_bounds++;
      if ((*g).is_const(v) && !foundStride) { 
        //no variables but v in constr
        coef_t L,m;
        L = -((*g).get_const());
 
        m = (*g).get_coef(v);
        coef_t sb  =  (int) (ceil(((float) L) /m));
        set_max(const_lb, sb);
      }
      else if ((*g).is_const(v) && foundSimpleStride) { 
        // no variables but v in constr
        //make LB fit the stride constraint
        coef_t L,m,s,c;
        L = -((*g).get_const());
        m = (*g).get_coef(v);
        s = step;
        c = strideEQ.get_const();
        coef_t sb  =  (s * (int) (ceil( (float) (L - (c * m)) /(s*m))))+ c;
        set_max(const_lb, sb);
      } 
      else 
        lbList.append(outputLBasRepr(ocg, *g, b, v, step, strideEQ, known));
    }
    else {  // upper bound
      upper_bounds++;
      if ((*g).is_const(v)) { 
        // no variables but v in constraint
        set_min(const_ub,-(*g).get_const()/(*g).get_coef(v));
      }
      else
        ubList.append(outputUBasRepr(ocg, *g, b, v, step, strideEQ));
    }
  }

  if (const_lb != negInfinity)
    lbList.append(ocg->CreateInt(const_lb));    
  if (lbList.size() > 1)
    lbRepr = ocg->CreateInvoke("max", lbList);
  else if (lbList.size() == 1)
    lbRepr = lbList[1];

  if (const_ub != posInfinity)
    ubList.append(ocg->CreateInt(const_ub));
  if (ubList.size() > 1)
    ubRepr = ocg->CreateInvoke("min", ubList);
  else if (ubList.size() == 1)
    ubRepr = ubList[1];

  if (upper_bounds == 0 || lower_bounds == 0) {
    if (code_gen_debug > 2) {
      fprintf(DebugFile,"::: printBounds looking for EQ:\n");
      b.prefix_print(DebugFile);
    }

    ctrlRepr = NULL;
    for (EQ_Iterator ei(c); ei; ei++)
      if (!(*ei).has_wildcards() && abs((*ei).get_coef(v)) > 1) {
        // test if this loop varialbe always has integer value
        Relation r(b.n_set());
        r.copy_names(b);
        F_And *f_super_root = r.add_and();
        F_Exists *fe = f_super_root->add_exists();
        Variable_ID e = fe->declare();
        F_And *f_root = fe->add_and();
        EQ_Handle h = f_root->add_EQ();
        for (Constr_Vars_Iter cvi(*ei); cvi; cvi++)
          switch ((*cvi).var->kind()) {
          // case Set_Var:
          case Input_Var: {
            if ((*cvi).var == v)
              h.update_coef(e, (*cvi).coef);
            else
              h.update_coef(r.set_var((*cvi).var->get_position()), (*cvi).coef);
            break;
          }
          case Global_Var: {            
            Global_Var_ID g = (*cvi).var->get_global_var();
            Variable_ID v2;
            if (g->arity() == 0)
              v2 = r.get_local(g);
            else
              v2 = r.get_local(g, (*cvi).var->function_of());
            h.update_coef(v2, (*cvi).coef);
            break;
          }
          default:
            assert(0);
          }
        h.update_const((*ei).get_const());

        if (Gist(r, copy(known), 1).is_obvious_tautology())
          continue;

        // generate condition to make sure this loop variable has integer value
        coef_t coef = (*ei).get_coef(v);
        coef_t sign = -((coef>0)?1:-1);
        coef = abs(coef);

        CG_outputRepr *term = NULL;
        for (Constr_Vars_Iter cvi(*ei); cvi; cvi++)
          if ((*cvi).var != v) {
            CG_outputRepr *varRepr = outputIdent(ocg, (*cvi).var);
            coef_t t = sign*(*cvi).coef;
            if (t == 1)
              term = ocg->CreatePlus(term, varRepr);
            else if (t == -1)
              term = ocg->CreateMinus(term, varRepr);
            else if (t > 0)
              term = ocg->CreatePlus(term, ocg->CreateTimes(ocg->CreateInt(t), varRepr));
            else if (t < 0)
              term = ocg->CreateMinus(term, ocg->CreateTimes(ocg->CreateInt(-t), varRepr));
          }
        coef_t t = sign*(*ei).get_const();
        if (t > 0)
          term = ocg->CreatePlus(term, ocg->CreateInt(t));
        else if (t < 0)
          term = ocg->CreateMinus(term, ocg->CreateInt(-t));

        term = ocg->CreateIntegerMod(term, ocg->CreateInt(coef));
        term = ocg->CreateEQ(term, ocg->CreateInt(0));

        if (ctrlRepr == NULL)
          ctrlRepr = term;
        else
          ctrlRepr = ocg->CreateAnd(ctrlRepr, term);

        // bookkeeping catched constraints in new_knwon
        new_known.and_with_EQ(*ei);
      }

    // cleanup useless outputRepr
    if (lbRepr) {
      lbRepr->clear();
      delete lbRepr;
    }
    if (ubRepr) {
      ubRepr->clear();
      delete ubRepr;
    }
  }
  else {
    // bookkeeping catched constraints in new_knwon
    F_Exists *fe = new_known.and_with_and()->add_exists();
    F_And *f_root = fe->add_and();
    std::map<Variable_ID, Variable_ID> exists_mapping;
    std::stack<std::pair<GEQ_Handle, Variable_ID> > floor_geq_stack;
    std::set<Variable_ID> floor_var_set;

    if (foundStride) {
      EQ_Handle h = f_root->add_EQ();
      for (Constr_Vars_Iter cvi(strideEQ); cvi; cvi++)
        switch ((*cvi).var->kind()) {
        // case Set_Var:
        case Input_Var: {
          int pos = (*cvi).var->get_position();
          h.update_coef(new_known.set_var(pos), (*cvi).coef);
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
          Variable_ID e;
          if (g->arity() == 0)
            e = new_known.get_local(g);
          else
            e = new_known.get_local(g, (*cvi).var->function_of());
          h.update_coef(e, (*cvi).coef);
          break;
        }
        default:
          assert(0);
        }
      h.update_const(strideEQ.get_const());
    }
    
    for (GEQ_Iterator gi(c); gi; gi++)
      if ((*gi).get_coef(v) != 0) {
        GEQ_Handle h = f_root->add_GEQ();
        for (Constr_Vars_Iter cvi(*gi); cvi; cvi++)
          switch ((*cvi).var->kind()) {
          // case Set_Var:
          case Input_Var: {
            int pos = (*cvi).var->get_position();
            h.update_coef(new_known.set_var(pos), (*cvi).coef);
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

            if (floor_var_set.find((*cvi).var) == floor_var_set.end()) {
              GEQ_Handle h2;
              findFloorInequality(b, (*cvi).var, h2, v);
              floor_geq_stack.push(std::make_pair(h2, (*cvi).var));
              floor_var_set.insert((*cvi).var);
            }
            break;
          }
          case Global_Var: {
            Global_Var_ID g = (*cvi).var->get_global_var();
            Variable_ID e;
            if (g->arity() == 0)
              e = new_known.get_local(g);
            else
              e = new_known.get_local(g, (*cvi).var->function_of());
            h.update_coef(e, (*cvi).coef);
            break;
          }
          default:
            assert(0);
          }
        h.update_const((*gi).get_const());
      }

    // add floor definition involving variables appeared in bounds
    while (!floor_geq_stack.empty()) {
      std::pair<GEQ_Handle, Variable_ID> p = floor_geq_stack.top();
      floor_geq_stack.pop();

      GEQ_Handle h1 = f_root->add_GEQ();
      GEQ_Handle h2 = f_root->add_GEQ();
      for (Constr_Vars_Iter cvi(p.first); cvi; cvi++) {
        switch  ((*cvi).var->kind()) {
        // case Set_Var:
        case Input_Var: {
          int pos = (*cvi).var->get_position();
          h1.update_coef(new_known.input_var(pos), (*cvi).coef);
          h2.update_coef(new_known.input_var(pos), -(*cvi).coef);
          break;
        }
        case Exists_Var:
        case Wildcard_Var: {
          std::map<Variable_ID, Variable_ID>::iterator p2 = exists_mapping.find((*cvi).var);
          Variable_ID e;
          if (p2 == exists_mapping.end()) {
            e = fe->declare();
            exists_mapping[(*cvi).var] = e;
          }
          else
            e = (*p2).second;
          h1.update_coef(e, (*cvi).coef);
          h2.update_coef(e, -(*cvi).coef);

          if (floor_var_set.find((*cvi).var) == floor_var_set.end()) {
            GEQ_Handle h3;
            findFloorInequality(b, (*cvi).var, h3, v);
            floor_geq_stack.push(std::make_pair(h3, (*cvi).var));
            floor_var_set.insert((*cvi).var);
          }
          break;
        }
        case Global_Var: {
          Global_Var_ID g = (*cvi).var->get_global_var();
          Variable_ID e;
          if (g->arity() == 0)
            e = new_known.get_local(g);
          else
            e = new_known.get_local(g, (*cvi).var->function_of());
          h1.update_coef(e, (*cvi).coef);
          h2.update_coef(e, -(*cvi).coef);
          break;
        }
        default:
          assert(0);
        }
      }
      h1.update_const(p.first.get_const());
      h2.update_const(-p.first.get_const());
      h2.update_const(-p.first.get_coef(p.second)-1);
    }
    new_known.simplify();
    
    if (code_gen_debug > 2) {
      Relation k0,k1,k2;
      k1 = known;
      k2 = new_known;
      k0 = Intersection(k1,k2);
      k0.simplify();
      fprintf(DebugFile,"::: Known from loop bounds:\n");
      k0.prefix_print(DebugFile);
      b = Gist(b,k0,1);
      fprintf(DebugFile,"::: Constraints not yet expressed:\n");
      b.prefix_print(DebugFile);
    }

    if (step != 1)
      stRepr = ocg->CreateInt(abs(step));
    indexRepr = outputIdent(ocg,v);
    ctrlRepr = ocg->CreateInductive(indexRepr, lbRepr, ubRepr, stRepr);
  }

  return true;
}


#ifndef NDEBUG
#define PAINFULLY_EXPENSIVE_DEBUGGING 1
#endif

int code_gen_debug=0;
int code_gen_check_zero_trip=1;

void name_codegen_vars(Relation &R) {
  for(int i = 1; i <= R.n_set(); i ++)
    R.name_set_var(i, std::string("t")+to_string(i));
}

void name_codegen_input_vars(Relation &R) {
  for(int i = 1; i <= R.n_inp(); i ++)
    R.name_input_var(i, std::string("t")+to_string(i));
}


// // Return true if there are no variables in g except wildcards & v
static bool isSimpleStride(const EQ_Handle &g, Variable_ID v) {
  EQ_Handle gg = g;  // should not be necessary, but iterators are
  // a bit brain-dammaged
  bool is_simple=true;
  for(Constr_Vars_Iter cvi(gg, false); cvi && is_simple; cvi++)
    is_simple = ((*cvi).coef == 0 || (*cvi).var == v 
                 || (*cvi).var->kind() == Wildcard_Var);
  return is_simple;
}


int countStrides(Conjunct *c, Variable_ID v, EQ_Handle &strideEQ, 
                 bool &simple) {
  int strides=0;
  for(EQ_Iterator G(c); G; G++)
    for(Constr_Vars_Iter I(*G, true); I; I++)
      if (((*I).coef != 0) && (*G).get_coef(v) != 0) {
        strides++;
        simple = isSimpleStride(*G,v);
        strideEQ = *G;
        break;
      }
  return strides;
}


Relation project_onto_levels(Relation R, int last_level, bool wildcards) {
  assert(last_level >= 0 && R.is_set() && last_level <= R.n_set());
  if (last_level == R.n_set()) return R;

  int orig_vars = R.n_set();
  int num_projected = orig_vars - last_level;
  R = Extend_Set(R,num_projected
    );  // Project out vars numbered > last_level
  Mapping m1 = Mapping::Identity(R.n_set());  // now orig_vars+num_proj

  for(int i=last_level+1; i <= orig_vars; i++) {
    m1.set_map(Set_Var, i, Exists_Var, i);
    m1.set_map(Set_Var, i+num_projected, Set_Var, i);
  }

  MapRel1(R, m1, Comb_Id);
  R.finalize();
  R.simplify();
  if (!wildcards) 
    R = Approximate(R,1);
  assert(R.is_set());
  return R;
}


// Check if the lower bound already enforces the stride by
// (Where m is coef of v in g and L is the bound on m*v):
// Check if m divides L evenly and Check if this l.bound on v implies strideEQ 
static bool boundHitsStride(const GEQ_Handle &g, Variable_ID v,
                            const EQ_Handle &strideEQ,
                            coef_t /*stride*/, // currently unused
                            Relation known) {
/* m = coef of v in g;
   L = bound on v part of g;
*/ 
  // Check if m divides L evenly
  coef_t m = g.get_coef(v);
  Relation test(known.n_set());
  F_Exists *e = test.add_exists();       // g is "L >= mv"
  Variable_ID alpha = e->declare();      // want: "l = m alpha"
  F_And *a = e->add_and();
  EQ_Handle h = a->add_EQ(); 
  for(Constr_Vars_Iter I(g,false); I; I++)
    if((*I).var != v) {
      if((*I).var->kind() != Global_Var)
        h.update_coef((*I).var, (*I).coef);
      else
        h.update_coef(test.get_local((*I).var->get_global_var()), (*I).coef);
    }

  h.update_const(g.get_const());
  h.update_coef(alpha,m);                // set alpha's coef to m
  if (!(Gist(test,copy(known)).is_obvious_tautology()))      
    return false;
  // Check if this lower bound on v implies the strideEQ 
  Relation boundRel = known;    // want: "known and l = m v"
  boundRel.and_with_EQ(g);      // add in l = mv
  Relation strideRel(known.n_set());
  strideRel.and_with_EQ(strideEQ);
  return Gist(strideRel, boundRel).is_obvious_tautology();
}



inline bool isLB(const GEQ_Handle &g, Variable_ID v) {
  return g.get_coef(v) > 0;
}

inline bool isUB(const GEQ_Handle &g, Variable_ID v) {
  return g.get_coef(v) < 0;
}


static Relation greatest_common_step2(SetTuple &I, IntTuple &active, int level, int vars, int nr_statements, const Relation &known = Relation::Null()) {
  coef_t gcs = 0;
  Relation strideRel(vars);
  F_And *stride_root = strideRel.add_and();
  EQ_Handle first_stride;
  bool is_first_stride_clean = false;
  Variable_ID t_col = set_var(level);

  // first pass working on good strides only -- by chun 10/22/2008
  Tuple<bool> check_bad_stride(nr_statements);
  Tuple<Relation> I2(nr_statements);
  for (int stmt = 1; stmt <= nr_statements; stmt++) {
    check_bad_stride[stmt] = false;
    
    if (active[stmt]) {
      // simpler stride by taking into account of known condition -- by chun 12/10/2006
      I2[stmt] = Gist(copy(I[stmt]), copy(known), 1);

      assert(I2[stmt].is_upper_bound_satisfiable());
      if (I2[stmt].is_obvious_tautology())
        return Relation::True(vars);
      
      Conjunct *c = (I2[stmt]).query_DNF()->single_conjunct();
      bool found_any_stride = false;
      bool first_extract = false;
      for (EQ_Iterator e = c->EQs(); e; e++)
        if ((*e).has_wildcards()) {
          coef_t coef = abs((*e).get_coef(t_col));
          if (coef == 0)
            continue;

          if (coef == 1) {            
            coef_t stride = abs(Constr_Vars_Iter(*e, true).curr_coef());
            assert(stride!=1);
            
            if (gcs == 0) {
              Relation R0(vars);
              F_And *a0 = R0.add_and();
              EQ_Handle new_eq = a0->add_stride(stride);

              bool found_lowerbound = false;
              for (GEQ_Iterator ge = c->GEQs(); ge; ge++) {
                if ((*ge).has_wildcards() || (*ge).get_coef(t_col) != 1)
                  continue;

                for (Constr_Vars_Iter cv(*ge); cv; cv++) {
                  switch (cv.curr_var()->kind()) {
                  case Input_Var:
                  case Output_Var:
                    new_eq.update_coef((*cv).var, cv.curr_coef());
                    break;
                  case Global_Var:
                  {
                    Global_Var_ID g = cv.curr_var()->get_global_var();
                    Variable_ID v;
                    if (g->arity() == 0)
                      v = R0.get_local(g);
                    else
                      v = R0.get_local(g, cv.curr_var()->function_of());
                    new_eq.update_coef(v, cv.curr_coef());
                    break;
                  }
                  default:
                    assert(0);
                  }
                }
                new_eq.update_const((*ge).get_const());
                found_lowerbound = true;
                break;
              }
              if (!found_lowerbound)
                return Relation::True(vars);
              R0.simplify();

              Relation R1 = Gist(copy(R0), Intersection(copy(I[stmt]), copy(known)));
              if (R1.is_obvious_tautology()) {
                Conjunct *c2 = R0.single_conjunct();
                for (EQ_Iterator e2=c2->EQs(); e2; e2++)
                  if ((*e2).has_wildcards()) {
                    first_stride = stride_root->add_EQ(*e2);
                    strideRel.simplify();
                    break;
                  }
              }
              else {
                first_stride = stride_root->add_EQ(*e);
                strideRel.simplify();
              }
              gcs = stride;
              check_bad_stride[stmt] = false;
              found_any_stride = true;
              first_extract = true;
            }        
            else if (first_extract) {
              Relation R0(vars);
              F_And *a0 = R0.add_and();
              EQ_Handle new_eq = a0->add_stride(stride);
              for (Constr_Vars_Iter cv(first_stride); cv; cv++) {
                switch (cv.curr_var()->kind()) {
                case Input_Var:
                case Output_Var:
                  new_eq.update_coef((*cv).var, cv.curr_coef());
                  break;
                case Global_Var:
                {
                  Global_Var_ID g = cv.curr_var()->get_global_var();
                  Variable_ID v;
                  if (g->arity() == 0)
                    v = R0.get_local(g);
                  else
                    v = R0.get_local(g, cv.curr_var()->function_of());
                  new_eq.update_coef(v, cv.curr_coef());
                  break;
                }
                case Wildcard_Var:
                  break;
                default:
                  assert(0);
                }
              }
              new_eq.update_const(first_stride.get_const());
              R0.simplify();
          
              Relation R1 = Gist(R0, Intersection(copy(I[stmt]), copy(known)));
              if (R1.is_obvious_tautology()) {
                gcs = lcm(gcs, stride);
              }
            }
            else {
              Relation R0(vars);
              F_And *a0 = R0.add_and();
              EQ_Handle new_eq = a0->add_stride(gcs);
              for (Constr_Vars_Iter cv(first_stride); cv; cv++) {
                switch (cv.curr_var()->kind()) {
                case Input_Var:
                case Output_Var:
                  new_eq.update_coef((*cv).var, cv.curr_coef());
                  break;
                case Global_Var:
                {
                  Global_Var_ID g = cv.curr_var()->get_global_var();
                  Variable_ID v;
                  if (g->arity() == 0)
                    v = R0.get_local(g);
                  else
                    v = R0.get_local(g, cv.curr_var()->function_of());
                  new_eq.update_coef(v, cv.curr_coef());
                  break;
                }
                case Wildcard_Var:
                  break;
                default:
                  assert(0);
                }
              }
              new_eq.update_const(first_stride.get_const());
              R0.simplify();
          
              Relation R1 = Gist(R0, Intersection(copy(I[stmt]), copy(known)));
              if (R1.is_obvious_tautology()) {
                check_bad_stride[stmt] = false;
                found_any_stride = true;
                break;                
              }
              else {
                stride = gcd(gcs, stride);
                if (stride == 1)
                  continue;

                Relation R0(vars);
                F_And *a0 = R0.add_and();
                EQ_Handle new_eq = a0->add_stride(stride);
                for (Constr_Vars_Iter cv(first_stride); cv; cv++) {
                  switch (cv.curr_var()->kind()) {
                  case Input_Var:
                  case Output_Var:
                    new_eq.update_coef((*cv).var, cv.curr_coef());
                    break;
                  case Global_Var:
                  {
                    Global_Var_ID g = cv.curr_var()->get_global_var();
                    Variable_ID v;
                    if (g->arity() == 0)
                      v = R0.get_local(g);
                    else
                      v = R0.get_local(g, cv.curr_var()->function_of());
                    new_eq.update_coef(v, cv.curr_coef());
                    break;
                  }
                  case Wildcard_Var:
                    break;
                  default:
                    assert(0);
                  }
                }
                new_eq.update_const(first_stride.get_const());
                R0.simplify();
          
                Relation R1 = Gist(R0, Intersection(copy(I[stmt]), copy(known)));
                if (R1.is_obvious_tautology()) {
                  gcs = stride;
                  check_bad_stride[stmt] = false;
                  found_any_stride = true;
                  break;                
                }
              }
            }
          }
          else {
            check_bad_stride[stmt] = true;
            found_any_stride = true;
          }
        }

      if (!found_any_stride)
        check_bad_stride[stmt] = true;
    }
  }

  // second pass working on bad strides only -- by chun 10/22/2008
  for (int stmt = 1; stmt <= nr_statements; stmt++)
    if (check_bad_stride[stmt]) {
      Conjunct *c = I2[stmt].query_DNF()->single_conjunct();
      bool found_any_stride = false;
      bool first_extract = false;
      for (EQ_Iterator e = c->EQs(); e; e++)
        if ((*e).has_wildcards()) {
          coef_t coef = abs((*e).get_coef(t_col));
          if (coef == 0 || coef == 1)
            continue;
          
          // make a guess in cases where gist solution is not clean enough -- by chun 07/27/2007
          coef_t stride = abs(Constr_Vars_Iter(*e, true).curr_coef());
          stride = stride/gcd(stride, coef);
          
          if (gcs == 0) {
            Relation R0(vars);
            F_And *a0 = R0.add_and();
            EQ_Handle new_eq = a0->add_stride(stride);

            bool found_lowerbound = false;
            for (GEQ_Iterator ge = c->GEQs(); ge; ge++) {
              if ((*ge).has_wildcards() || (*ge).get_coef(t_col) != 1)
                continue;
            
              for (Constr_Vars_Iter cv(*ge); cv; cv++) {
                switch (cv.curr_var()->kind()) {
                case Input_Var:
                case Output_Var:
                  new_eq.update_coef((*cv).var, cv.curr_coef());
                  break;
                case Global_Var:
                {
                  Global_Var_ID g = cv.curr_var()->get_global_var();
                  Variable_ID v;
                  if (g->arity() == 0)
                    v = R0.get_local(g);
                  else
                    v = R0.get_local(g, cv.curr_var()->function_of());
                  new_eq.update_coef(v, cv.curr_coef());
                  break;
                }
                default:
                  assert(0);
                }
              }
              new_eq.update_const((*ge).get_const());
              found_lowerbound = true;
              break;
            }
            if (!found_lowerbound)
              return Relation::True(vars);
            R0.simplify();
          
            Relation R1 = Gist(copy(R0), Intersection(copy(I[stmt]), copy(known)));
            if (R1.is_obvious_tautology()) {
              Conjunct *c2 = R0.single_conjunct();
              for (EQ_Iterator e2=c2->EQs(); e2; e2++)
                if ((*e2).has_wildcards()) {
                  first_stride = stride_root->add_EQ(*e2);
                  strideRel.simplify();
                  gcs = stride;
                  break;
                }
              found_any_stride = true;
              first_extract = true;
            }
          }
          else if (first_extract) {
            Relation R0(vars);
            F_And *a0 = R0.add_and();
            EQ_Handle new_eq = a0->add_stride(stride);
            for (Constr_Vars_Iter cv(first_stride); cv; cv++) {
              switch (cv.curr_var()->kind()) {
              case Input_Var:
              case Output_Var:
                new_eq.update_coef((*cv).var, cv.curr_coef());
                break;
              case Global_Var:
              {
                Global_Var_ID g = cv.curr_var()->get_global_var();
                Variable_ID v;
                if (g->arity() == 0)
                  v = R0.get_local(g);
                else
                  v = R0.get_local(g, cv.curr_var()->function_of());
                new_eq.update_coef(v, cv.curr_coef());
                break;
              }
              case Wildcard_Var:
                break;
              default:
                assert(0);
              }
            }
            new_eq.update_const(first_stride.get_const());
            R0.simplify();
          
            Relation R1 = Gist(R0, Intersection(copy(I[stmt]), copy(known)));
            if (R1.is_obvious_tautology()) {
              gcs = lcm(gcs, stride);
            }
          }
          else {
            Relation R0(vars);
            F_And *a0 = R0.add_and();
            EQ_Handle new_eq = a0->add_stride(gcs);
            for (Constr_Vars_Iter cv(first_stride); cv; cv++) {
              switch (cv.curr_var()->kind()) {
              case Input_Var:
              case Output_Var:
                  new_eq.update_coef((*cv).var, cv.curr_coef());
                  break;
              case Global_Var:
              {
                Global_Var_ID g = cv.curr_var()->get_global_var();
                Variable_ID v;
                if (g->arity() == 0)
                  v = R0.get_local(g);
                else
                  v = R0.get_local(g, cv.curr_var()->function_of());
                new_eq.update_coef(v, cv.curr_coef());
                break;
              }
              case Wildcard_Var:
                break;
              default:
                assert(0);
              }
            }
            new_eq.update_const(first_stride.get_const());
            R0.simplify();
          
            Relation R1 = Gist(R0, Intersection(copy(I[stmt]), copy(known)));
            if (R1.is_obvious_tautology()) {
              found_any_stride = true;
              break;
            }
            else {
              stride = gcd(gcs, stride);
              if (stride == 1)
                continue;
              
              Relation R0(vars);
              F_And *a0 = R0.add_and();
              EQ_Handle new_eq = a0->add_stride(stride);
              for (Constr_Vars_Iter cv(first_stride); cv; cv++) {
                switch (cv.curr_var()->kind()) {
                case Input_Var:
                case Output_Var:
                  new_eq.update_coef((*cv).var, cv.curr_coef());
                  break;
                case Global_Var:
                {
                  Global_Var_ID g = cv.curr_var()->get_global_var();
                  Variable_ID v;
                  if (g->arity() == 0)
                    v = R0.get_local(g);
                  else
                    v = R0.get_local(g, cv.curr_var()->function_of());
                  new_eq.update_coef(v, cv.curr_coef());
                  break;
                }
                case Wildcard_Var:
                  break;
                default:
                  assert(0);
                }
              }
              new_eq.update_const(first_stride.get_const());
              R0.simplify();
          
              Relation R1 = Gist(R0, Intersection(copy(I[stmt]), copy(known)));
              if (R1.is_obvious_tautology()) {
                gcs = stride;
                found_any_stride = true;
                break;
              }
            }
          }
        }

      if (!found_any_stride) {
        if (gcs != 0) {
          Relation R0 = Gist(copy(strideRel), Intersection(copy(I[stmt]), copy(known)));
          if (!R0.is_obvious_tautology())
            return Relation::True(vars);
        }
        else   
          return Relation::True(vars);
      }
    }

  if (gcs == 0 || gcs == 1)
    return Relation::True(vars);
        
  Relation R0(vars); 
  F_And *a0 = R0.add_and();
  EQ_Handle new_eq = a0->add_stride(gcs);

  new_eq.update_const(first_stride.get_const());
  for (Constr_Vars_Iter cv(first_stride, 0); cv ; cv++) {
    switch (cv.curr_var()->kind()) {
    case Input_Var:
    case Output_Var:
      new_eq.update_coef((*cv).var, cv.curr_coef());
      break;
    case Global_Var:
    {
      Global_Var_ID g = cv.curr_var()->get_global_var();
      Variable_ID v;
      if (g->arity() == 0)
        v = R0.get_local(g);
      else
        v = R0.get_local(g, cv.curr_var()->function_of());
      new_eq.update_coef(v, cv.curr_coef());
      break;
    }
    case Wildcard_Var:
      /* don't set */
      break;
    default:
      assert(0);
    }
  }
  R0.finalize();
  return R0;
}


// std::map<Variable_ID, coef_t> extract_one_lower_bound(const Relation &R, int level) {
//   Conjunct *c = const_cast<Relation &>(R).query_DNF()->single_conjunct();
//   Variable_ID t_col = const_cast<Relation &>(R).set_var(level);
//   std::map<Variable_ID, coef_t> result;
  
//   for (GEQ_Iterator ge = c->GEQs(); ge; ge++) {
//     if ((*ge).has_wildcards() || (*ge).get_coef(t_col) != 1)
//       continue;

//     for (Constr_Vars_Iter cv(*ge); cv; cv++)
//       result[cv.curr_var()] = cv.curr_coef();

//     result[NULL] = (*ge).get_const();
//     break;
//   }

//   return result;
// }


Relation create_stride_on_bound(int n, const std::map<Variable_ID, coef_t> &lb, coef_t stride) {
  Relation result(n);
  F_And *f_root = result.add_and();
  EQ_Handle h = f_root->add_stride(stride);
  
  for (std::map<Variable_ID, coef_t>::const_iterator i = lb.begin(); i != lb.end(); i++) {
    if (i->first == NULL)
      h.update_const(i->second);
    else {
      switch(i->first->kind()) {
      // case Set_Var:
      case Input_Var: {
        int pos = i->first->get_position();
        h.update_coef(result.set_var(pos), i->second);
        break;
      }
      case Global_Var: {
        Global_Var_ID g = i->first->get_global_var();
        Variable_ID v;
        if (g->arity() == 0)
          v = result.get_local(g);
        else
          v = result.get_local(g, i->first->function_of());
        h.update_coef(v, i->second);
        break;
      }
      default:
        assert(0);
      }
    }
  }

  return result;
}
  

Relation greatest_common_step(Tuple<Relation> &I, Tuple<int> &active, int level, const Relation &known = Relation::Null()) {
  assert(I.size() == active.size());
  int n = 0;

  std::vector<Relation> I1, I2;
  for (int i = 1; i <= I.size(); i++)
    if (active[i]) {
      if (n == 0)
        n = I[i].n_set();

      Relation r1;
      if (known.is_null())
        r1 = copy(I[i]);
      else {
        r1 = Intersection(copy(I[i]), copy(known));
        r1.simplify();
      }
      I1.push_back(r1);
      Relation r2 = Gist(copy(I[i]), copy(known));
      assert(r2.is_upper_bound_satisfiable());
      if (r2.is_obvious_tautology())
        return Relation::True(n);
      I2.push_back(r2);
    }

  std::vector<bool> is_exact(I2.size(), true);
  std::vector<coef_t> step(I2.size(), 0);
  std::vector<coef_t> messy_step(I2.size(), 0);
  Variable_ID t_col = set_var(level);
  std::map<Variable_ID, coef_t> lb;

  // first check all clean strides: t_col = ... (mod step)
  for (size_t i = 0; i < I2.size(); i++) {
    Conjunct *c = I2[i].query_DNF()->single_conjunct();

    bool is_degenerated = false;
    for (EQ_Iterator e = c->EQs(); e; e++) {
      coef_t coef = abs((*e).get_coef(t_col));
      if (coef != 0 && !(*e).has_wildcards()) {
        is_degenerated = true;
        break;
      }
    }
    if (is_degenerated)
      continue;

    for (EQ_Iterator e = c->EQs(); e; e++) {
      if ((*e).has_wildcards()) {
        coef_t coef = abs((*e).get_coef(t_col));
        if (coef == 0)
          continue;
        if (coef != 1) {
          is_exact[i] = false;
          continue;
        }

        coef_t this_step = abs(Constr_Vars_Iter(*e, true).curr_coef());
        assert(this_step != 1);

        if (lb.size() != 0) {
          Relation test = create_stride_on_bound(n, lb, this_step);
          if (Gist(test, copy(I1[i])).is_obvious_tautology()) {
            if (step[i] == 0)
              step[i] = this_step;
            else
              step[i] = lcm(step[i], this_step);
          }
          else
            is_exact[i] = false;
        }
        else {
          // try to find a lower bound that hits on stride
          Conjunct *c = I2[i].query_DNF()->single_conjunct();
          for (GEQ_Iterator ge = c->GEQs(); ge; ge++) {
            if ((*ge).has_wildcards() || (*ge).get_coef(t_col) != 1)
              continue;

            std::map<Variable_ID, coef_t> cur_lb;
            for (Constr_Vars_Iter cv(*ge); cv; cv++)
              cur_lb[cv.curr_var()] = cv.curr_coef();
            cur_lb[NULL] = (*ge).get_const();

            Relation test = create_stride_on_bound(n, cur_lb, this_step);        
            if (Gist(test, copy(I1[i])).is_obvious_tautology()) {
              if (step[i] == 0)
                step[i] = this_step;
              else
                step[i] = lcm(step[i], this_step);

              lb = cur_lb;
              break;
            }
          }

          // no clean lower bound, thus we use this modular constraint as is
          if (lb.size() == 0) {
            std::map<Variable_ID, coef_t> cur_lb;
            int wild_count = 0;
            for (Constr_Vars_Iter cv(*e); cv; cv++)
              if (cv.curr_var()->kind() == Wildcard_Var)
                wild_count++;
              else
                cur_lb[cv.curr_var()] = cv.curr_coef();
            cur_lb[NULL] = (*e).get_const();

            if (wild_count == 1) {
              lb = cur_lb;
              if (step[i] == 0)
                step[i] = this_step;
              else
                step[i] = lcm(step[i], this_step);
            }
          }

          if (lb.size() == 0)
            is_exact[i] = false;
        }
      }
    }
  }

  // aggregate all exact steps
  coef_t global_step = 0;
  for (size_t i = 0; i < is_exact.size(); i++)
    if (is_exact[i])
      global_step = gcd(global_step, step[i]);
  if (global_step == 1)
    return Relation::True(n);

  // now check all messy strides: a*t_col = ... (mod step)
  for (size_t i = 0; i < I2.size(); i++)
    if (!is_exact[i]) {      
      Conjunct *c = I2[i].query_DNF()->single_conjunct();
      for (EQ_Iterator e = c->EQs(); e; e++) {
        coef_t coef = abs((*e).get_coef(t_col));
        if (coef == 0 || coef == 1)
          continue;
        
        // make a guess for messy stride condition -- by chun 07/27/2007
        coef_t this_step = abs(Constr_Vars_Iter(*e, true).curr_coef());
        this_step /= gcd(this_step, coef);
        this_step = gcd(global_step, this_step);
        if (this_step == 1)
          continue;

        if (lb.size() != 0) {
          Relation test = create_stride_on_bound(n, lb, this_step);
          if (Gist(test, copy(I1[i])).is_obvious_tautology()) {
            if (step[i] == 0)
              step[i] = this_step;
            else
              step[i] = lcm(step[i], this_step);
          }
        }
        else {
          // try to find a lower bound that hits on stride
          Conjunct *c = I2[i].query_DNF()->single_conjunct();
          for (GEQ_Iterator ge = c->GEQs(); ge; ge++) {
            if ((*ge).has_wildcards() || (*ge).get_coef(t_col) != 1)
              continue;

            std::map<Variable_ID, coef_t> cur_lb;

            for (Constr_Vars_Iter cv(*ge); cv; cv++)
              cur_lb[cv.curr_var()] = cv.curr_coef();

            cur_lb[NULL] = (*ge).get_const();

            Relation test = create_stride_on_bound(n, cur_lb, this_step);        
            if (Gist(test, copy(I1[i])).is_obvious_tautology()) {
              if (step[i] == 0)
                step[i] = this_step;
              else
                step[i] = lcm(step[i], this_step);

              lb = cur_lb;
              break;
            }
          }
        }
      }
    }

  // aggregate all non-exact steps
  for (size_t i = 0; i < is_exact.size(); i++)
    if (!is_exact[i])
      global_step = gcd(global_step, step[i]);
  if (global_step == 1 || global_step == 0)
    return Relation::True(n);

  Relation result = create_stride_on_bound(n, lb, global_step);

  // check for statements that haven't been factored into global step
  for (size_t i = 0; i < I1.size(); i++)
    if (step[i] == 0) {
      if (!Gist(copy(result), copy(I1[i])).is_obvious_tautology())
        return Relation::True(n);
    }

  return result;
}


//-----------------------------------------------------------------------------
// outputStatements is going to produce an empty statement like s1(t1, t2)
//-----------------------------------------------------------------------------
CG_outputRepr* outputStatements(CG_outputBuilder *ocg, CG_outputRepr *stmt,
                                int indent, const Relation &mapping_, const Relation &known_) {
  Relation mapping = copy(mapping_);
  Relation known = copy(known_);
  Tuple<std::string> loop_vars;

  for (int i = 1; i <= mapping.n_inp(); i++)
    loop_vars.append(mapping.input_var(i)->name());

  // discard non-existant variables from iteration spaces -- by chun 12/31/2008
  if (known.n_set() > mapping.n_out()) {
    Relation r(known.n_set(), mapping.n_out());
    F_And *f_root = r.add_and();
    for (int i = 1; i <= mapping.n_out(); i++) {
      EQ_Handle h = f_root->add_EQ();
      h.update_coef(r.input_var(i), 1);
      h.update_coef(r.output_var(i), -1);
    }
    known = Range(Restrict_Domain(r, known));
    known.simplify();
  }
  
  // remove modular constraints from known to simplify mapping process -- by chun 11/10/2008
  Relation k(known.n_set());
  F_And *f_root = k.add_and();
  Conjunct *c = known.query_DNF()->single_conjunct();
  for (EQ_Iterator e = c->EQs(); e; e++) {
    if (!(*e).has_wildcards())
      f_root->add_EQ(*e);
  }
  k.simplify();
  
  // get variable substituion list
  Relation Inv_mapping = Restrict_Domain(Inverse(mapping), k);
  Tuple<CG_outputRepr*> sList = print_outputs_with_subs_to_repr(ocg, Inv_mapping);

  return ocg->CreatePlaceHolder(indent, stmt, sList, loop_vars);
}


RelTuple transformations;

bool hasBound(Relation r, int level, int UB) {
  r.simplify();
  Variable_ID v = set_var(level);
  Conjunct *s_conj = r.single_conjunct();
  for(GEQ_Iterator G(s_conj); G; G++) {
    if (UB && (*G).get_coef(v) < 0) return true;
    if (!UB && (*G).get_coef(v) > 0) return true;
  }
  for(EQ_Iterator E(s_conj); E; E++) {
    if ((*E).get_coef(v)) return true;
  }
  return false;
}


bool hasEQ(Relation r, int level) {
  r.simplify();
  Variable_ID v = set_var(level);
  Conjunct *s_conj = r.single_conjunct();
  for(EQ_Iterator G(s_conj); G; G++)
    if ((*G).get_coef(v))
      return true;
  return false;
}

static bool has_nonstride_EQ(Relation r, int level) {
  r.simplify();
  Variable_ID v = set_var(level);
  Conjunct *s_conj = r.single_conjunct();
  for(EQ_Iterator G(s_conj); G; G++)
    if ((*G).get_coef(v) && !(*G).has_wildcards())
      return true;
  return false;
}


static Relation pickEQ(Relation r, int level) {
  r.simplify();
  Variable_ID v = set_var(level);
  Conjunct *s_conj = r.single_conjunct();
  for(EQ_Iterator E(s_conj); E; E++)
    if ((*E).get_coef(v)) {
      Relation test_rel(r.n_set());
      test_rel.and_with_EQ(*E);
      return test_rel;
    }
  assert(0);
  return r;
}

/* pickBound will return an EQ as a GEQ if it finds one */
Relation pickBound(Relation r, int level, int UB) {
  r.simplify();
  Variable_ID v = set_var(level);
  Conjunct *s_conj = r.single_conjunct();
  for(GEQ_Iterator G(s_conj); G; G++) {
    if ((UB && (*G).get_coef(v) < 0)
        ||  (!UB && (*G).get_coef(v) > 0) ) {
      Relation test_rel(r.n_set());
      test_rel.and_with_GEQ(*G);
      return test_rel;
    }
  }
  for(EQ_Iterator E(s_conj); E; E++) {
    if ((*E).get_coef(v)) {
      Relation test_rel(r.n_set());
      test_rel.and_with_GEQ(*E);
      if ((UB && (*E).get_coef(v) > 0)
          ||  (!UB && (*E).get_coef(v) < 0) ) 
        test_rel = Complement(test_rel);
      return test_rel;
    }
  }
  assert(0);
  return r;
}

Relation pickOverhead(Relation r, int liftTo) {
  r.simplify();
  Conjunct *s_conj = r.single_conjunct();
  for(GEQ_Iterator G(s_conj); G; G++) {
    Relation test_rel(r.n_set());
    test_rel.and_with_GEQ(*G);
    Variable_ID v;
    coef_t pos = -1;
    coef_t c= 0;
    for(Constr_Vars_Iter cvi(*G, false); cvi; cvi++) 
      if ((*cvi).coef && (*cvi).var->kind() == Input_Var 
          && (*cvi).var->get_position() > pos) {
        v = (*cvi).var;
        pos = (*cvi).var->get_position();
        c = (*cvi).coef;
      }
#if 0
    fprintf(DebugFile,"Coef = %d, constraint = %s\n",
            c,(const char *)test_rel.print_formula_to_string());
#endif
    return test_rel;
  }
  for(EQ_Iterator E(s_conj); E; E++) {
    assert(liftTo >= 1);
    int pos = max((*E).max_tuple_pos(),max_fs_arity(*E)+1);
 
/* Pick stride constraints only when the variables with stride are outer
   loop variables */
    if ((*E).has_wildcards()  && pos < liftTo) {
      Relation test_rel(r.n_set());
      test_rel.and_with_EQ(*E);
      return test_rel;
    }
    else if (!(*E).has_wildcards()  && pos <= liftTo) {
      Relation test_rel(r.n_set());
      test_rel.and_with_EQ(*E);
      test_rel.simplify();
      test_rel = EQs_to_GEQs(test_rel,true);
      return pickOverhead(test_rel,liftTo);
    }
  }
  if (code_gen_debug>1) {
    fprintf(DebugFile,"Could not find overhead:\n");
    r.prefix_print(DebugFile);
  }
  return Relation::True(r.n_set());
}

Relation minMaxOverhead(Relation r, int level) {
  r.finalize();
  r.simplify();
  Conjunct *s_conj = r.single_conjunct();
  GEQ_Handle LBs[50],UBs[50];
  int numLBs = 0;
  int numUBs = 0;
  Variable_ID v = set_var(level);
  for(GEQ_Iterator G(s_conj); G; G++) if ((*G).get_coef(v)) {
      GEQ_Handle g = *G;
      if (g.get_coef(v) > 0) LBs[numLBs++] = g;
      else UBs[numUBs++] = g;
    }
  if (numLBs <= 1 && numUBs <= 1) {
    return Relation::True(r.n_set());
  }
  Relation r1(r.n_set());
  Relation r2(r.n_set());
  if (numLBs > 1) {
    // remove a max in lower bound
    r1.and_with_GEQ(LBs[0]);
    r2.and_with_GEQ(LBs[1]);
    r1 = project_onto_levels(Difference(r1,r2),level-1,0);
  }
  else {
    // remove a min in upper bound
    r1.and_with_GEQ(UBs[0]);
    r2.and_with_GEQ(UBs[1]);
    r1 = project_onto_levels(Difference(r1,r2),level-1,0);
  }
#if 0
  fprintf(DebugFile,"Testing %s\n",(const char *)r1.print_formula_to_string());
  fprintf(DebugFile,"will removed overhead on bounds of t%d: %s\n",level,
          (const char *)r.print_formula_to_string());
#endif
   
  return pickOverhead(r1, -1);
}



CG_split::CG_split(IntTuple &active, int lvl, Relation cond,
                   CG_result *T, CG_result *F) { 
  assert(cond.has_single_conjunct());
  // If overhead is a GEQ, make it a LB on innermost loop var
  coef_t c=0;
  int pos=-1;  // initialize c to shut up the compiler
  GEQ_Iterator G(cond.single_conjunct());
  if (G) {
    for(Constr_Vars_Iter cvi(*G, false); cvi; cvi++) 
      if ((*cvi).coef && (*cvi).var->kind() == Input_Var 
          && (*cvi).var->get_position() > pos) {
        pos = (*cvi).var->get_position();
        c = (*cvi).coef;
      }
    // Evan had an assert pos > 0 here, but we can allow pos == 0
#ifndef NDEBUG
    if(pos > lvl+1) {
      fprintf(DebugFile,"Illegal split at lvl %d\n", lvl);
      cond.prefix_print(DebugFile);
      code_gen_debug = 1;
      // fprintf(DebugFile,"Then clause:\n%s\n", (const char *) T->print(5));
      // fprintf(DebugFile,"Else clause:\n%s\n", (const char *) F->print(5));
    }
    assert(pos == 0 || pos <= lvl+1);
#endif
    if (pos > 0 && c > 0) {
      CG_result *foo = T;
      T = F;
      F = foo;
      if (code_gen_debug) {
        fprintf(DebugFile,"Reversing clause in new split node at lvl %d\n",lvl);
        cond.prefix_print(DebugFile);
      }
      cond = Complement(cond);
      // Simplify is Temporary workaround to gist problem (2/15/95)
      cond.simplify(); // if we don't do this, later we must do 
      // high redundant conjunct effort 
      assert(cond.has_single_conjunct());
    }
  }
  else { 
    assert(EQ_Iterator(cond.single_conjunct())); // Has >= 1 EQ
  }
  isActive = active;
  condition = cond;
  level = lvl;
  trueClause = T;
  falseClause = F;
}

CG_result *CG_split::new_copy() {
  Relation c = condition;
  return new CG_split(isActive,level,c,
                      trueClause->new_copy(),falseClause->new_copy());
}

std::string CG_split::printStructure(int indent) {
  std::string result = outputSpaces(indent) 
    + "// split at "
    + to_string((void *)this)
    + "\n"
    + outputSpaces(indent) + "// guard:" + guard.print_formula_to_string() + "\n"
    + outputSpaces(indent) 
    +"// if " + condition.print_formula_to_string()
    + " then\n"
    + trueClause->printStructure(indent+1)
    + outputSpaces(indent) 
    + "// else\n"
    + falseClause->printStructure(indent+1);
  return result;
}

//-----------------------------------------------------------------------------
// original CG_split::print(int) is now a wrapper of 
// printRepr(CG_outputBuilder*, int)
//-----------------------------------------------------------------------------
std::string CG_split::print(int indent) {
  CG_stringBuilder oscg;
  CG_outputRepr* splitRepr = printRepr(&oscg, indent);
  return GetString(splitRepr);
}

//*****************************************************************************
// Added by D people. Lei Zhou Apr. 20, 96
//*****************************************************************************
//-----------------------------------------------------------------------------
// CG_split member function: added by D people
// CG_outputRepr* CG_split::printRepr(CG_outputBuilder* ocg, int indent)
// Note: if code_gen_debug is set true, then the statements are indented
// more than code_gen_debug is set false.
//-----------------------------------------------------------------------------
CG_outputRepr* CG_split::printRepr(CG_outputBuilder* ocg, int indent) {
  CG_outputRepr* stmtList;

  if (code_gen_debug) {
    stmtList = ocg->CreateStmtList();
    
    std::string ifComment;
    CG_outputRepr *textRepr;
    ifComment = std::string("split at ") + to_string((void *)this);
    textRepr = ocg->CreateComment(indent, ifComment);
    stmtList = ocg->StmtListInsertLast(stmtList, textRepr);
    ifComment = "if " + condition.print_formula_to_string() + " then";
    textRepr = ocg->CreateComment(indent, ifComment);
    stmtList = ocg->StmtListInsertLast(stmtList, textRepr);

    stmtList = ocg->StmtListAppend(stmtList, trueClause->printRepr(ocg, indent+1));

    ifComment = "else";
    textRepr = ocg->CreateComment(indent, ifComment);
    stmtList = ocg->StmtListInsertLast(stmtList, textRepr);
    stmtList = ocg->StmtListAppend(stmtList, falseClause->printRepr(ocg, indent+1));
  }
  else {
    CG_outputRepr *ctrlRepr = NULL;
    if (!guard.is_null() && !guard.is_obvious_tautology()) {
      ctrlRepr = output_guard(ocg, guard);
      indent++;
    }
    if (ctrlRepr != NULL)
      stmtList = ocg->CreateIf(indent-1, ctrlRepr,
                               trueClause->printRepr(ocg, indent),
                               falseClause->printRepr(ocg, indent));
    else
      stmtList = ocg->StmtListAppend(trueClause->printRepr(ocg, indent),
                                     falseClause->printRepr(ocg, indent));
  }

  return stmtList;
}


CG_result * CG_split::liftOverhead(int depth) {
  assert(depth >= 1);
  trueClause = trueClause->liftOverhead(depth);
  falseClause = falseClause->liftOverhead(depth);
  return this;
}

CG_result * CG_split::force_finite_bounds() {
  trueClause = trueClause->force_finite_bounds();
  falseClause = falseClause->force_finite_bounds();
  return this;
}

Relation CG_split::findOverhead(int liftTo) {
  Relation r = trueClause->findOverhead(liftTo);
  if (r.is_obvious_tautology()) r = falseClause->findOverhead(liftTo);
  return r;
}

CG_result * CG_split::recompute(const Relation &k, const Relation &r, elimination_info e) {
  known = copy(k);
  restrictions = copy(r);
  eliminated = e;
  known.simplify();
  restrictions.simplify();
  Relation kr = Intersection(copy(k),copy(r));
  int numActive = 0;
  for(int s = 1; s<= isActive.size(); s++) if (isActive[s]) {
      Relation I = projected_nIS[level][s];
      if (!Intersection(copy(kr),I).is_upper_bound_satisfiable()) 
        isActive[s] = 0;
      else numActive++;
    }
  if (numActive == 0) {
    delete this;
    return new CG_null;
  }
  else if (numActive == 1 && 0) {
    // Need to rethink this -- can undo loop bounds
    // overhead removal
    CG_result *cg = gen_recursive(level, isActive);
    cg = cg->recompute(k, r, e);
    delete this;
    return cg;
  }

  Relation c = condition;
  if (code_gen_debug) {
    fprintf(DebugFile,"\nRecomputing split node %p\n", (void *)this);
    fprintf(DebugFile,"Known: %s\n", copy(k).print_formula_to_string().c_str());
    fprintf(DebugFile,"restriction: %s\n", copy(r).print_formula_to_string().c_str());
    fprintf(DebugFile,"split: %s\n", c.print_formula_to_string().c_str());
  }

  trueClause = trueClause->recompute(k, Intersection(copy(r), copy(c)), e);
  falseClause = falseClause->recompute(k, Difference(copy(r), copy(c)), e);

  if (trueClause->isNull()) {
    if (code_gen_debug) {
      fprintf(DebugFile,"Pruning true branch of %p: %s\n", (void *)this, condition.print_formula_to_string().c_str());
      fprintf(DebugFile,"Known: %s\n", known.print_formula_to_string().c_str());
      fprintf(DebugFile,"restrictions: %s\n", restrictions.print_formula_to_string().c_str());
      fprintf(DebugFile,"True branch: \n%s\n\n", trueClause->print(2).c_str());
      fprintf(DebugFile,"False branch: \n%s\n\n", falseClause->print(2).c_str());
    }
    CG_result *cg = falseClause;
    falseClause = NULL;
    delete this;
    return cg;
  }
  if (falseClause->isNull()) {
    if (code_gen_debug) {
      fprintf(DebugFile,"Pruning false branch of %p: %s\n", (void *) this, condition.print_formula_to_string().c_str());
      fprintf(DebugFile,"Known: %s\n", known.print_formula_to_string().c_str());
      fprintf(DebugFile,"restrictions: %s\n", restrictions.print_formula_to_string().c_str());
      fprintf(DebugFile,"True branch: \n%s\n\n", trueClause->print(2).c_str());
      fprintf(DebugFile,"False branch: \n%s\n\n", falseClause->print(2).c_str());
    }
    CG_result *cg = trueClause;
    trueClause = NULL;
    delete this;
    return cg;
  }
  return this;
}

Relation CG_split::hoistGuard() {
  Relation guard1 = trueClause->hoistGuard();
  Relation guard2 = falseClause->hoistGuard();
  if (guard.is_null())
    guard = Relation::True(condition.n_set());
  
  if (!guard1.is_obvious_tautology() && !guard2.is_obvious_tautology() &&
      Must_Be_Subset(copy(guard1), copy(guard2)) && Must_Be_Subset(copy(guard2), copy(guard1))) {
    trueClause->removeGuard();
    falseClause->removeGuard();
    guard = Intersection(guard, guard1);
  }
  
  return guard;
}
  

// CG_leaf implementation

Relation CG_leaf::findOverhead(int liftTo) {
  for(int s=1; s<=isActive.size(); s++) if (isActive[s]) {
      int bb = !guard[s].is_obvious_tautology();
      if (bb) {
        if (code_gen_debug)
          fprintf(DebugFile,"Trying to remove overhead on guard of statement s%d: %s\n",
                  s, guard[s].print_formula_to_string().c_str());
        Relation r =  pickOverhead(guard[s], liftTo);
        if (!r.is_obvious_tautology()) return r;
      }
    }
  return Relation::True(known.n_set());
}


std::string CG_leaf::printStructure(int) {
  std::string result;
  for(int s=1; s<=isActive.size(); s++) if (isActive[s]) {
      result += std::string("s") + to_string(s);
    }
  return result+"\n";
}



//-----------------------------------------------------------------------------
// original CG_leaf::print(int) is now a wrapper of 
// printRepr(CG_outputBuilder*, int)
//-----------------------------------------------------------------------------
std::string CG_leaf::print(int indent) {
  CG_stringBuilder oscg;
  CG_outputRepr* leafRepr = printRepr(&oscg, indent);
  return GetString(leafRepr);
}

//*****************************************************************************
// Added by D people. Lei Zhou Apr. 20, 96
//*****************************************************************************
//-----------------------------------------------------------------------------
// CG_leaf member function: 
// CG_outputRepr* CG_leaf::printRepr(CG_outputBuilder* ocg, int indent)
//-----------------------------------------------------------------------------
CG_outputRepr* CG_leaf::printRepr(CG_outputBuilder* ocg, int indent) {
  std::string result;
  CG_outputRepr* stmtList = ocg->CreateStmtList();
  CG_outputRepr* stmtNode = NULL;

  Tuple<int> working;

  if (code_gen_debug>1) {
    result = "known: " + known.print_formula_to_string();
    stmtList = ocg->StmtListInsertLast(stmtList, ocg->CreateComment(indent, result));
  }
  
  for(int s = 1; s <= isActive.size(); s++)
    if (isActive[s]) {
      if (guard[s].is_obvious_tautology()) {
        stmtNode = outputStatements(ocg, statementNameInfo[s]->place_holder(), indent, transformations[s], known);
        stmtList = ocg->StmtListInsertLast(stmtList, stmtNode);
      }
      else {
        if (code_gen_debug>1) {
          result = "restrictions: " + restrictions.print_formula_to_string();
          stmtList = ocg->StmtListInsertLast(stmtList, ocg->CreateComment(indent, result));
        }
        working.append(s);
      }
    }

  // remove duplicate if conditions at leaf level -- by chun 06/27/2006
  for (int i = 1; i <= working.size(); i++)
    if (working[i] != 0) {
      Relation g = Intersection(copy(guard[working[i]]), copy(known));
      stmtNode = outputStatements(ocg, statementNameInfo[working[i]]->place_holder(), indent+1, transformations[working[i]], g);
      
      for (int j = i+1; j <= working.size(); j++) if (working[j] != 0) {
          if (Must_Be_Subset(copy(guard[working[i]]), copy(guard[working[j]])) && Must_Be_Subset(copy(guard[working[j]]), copy(guard[working[i]]))) {
            stmtNode = ocg->StmtListInsertLast(stmtNode, outputStatements(ocg, statementNameInfo[working[j]]->place_holder(), indent+1, transformations[working[j]], g));
            working[j] = 0;
          }
        }
      
      CG_outputRepr *ifGuard = output_guard(ocg, guard[working[i]]);
      stmtNode = ocg->CreateIf(indent, ifGuard, stmtNode, NULL);
      stmtList = ocg->StmtListInsertLast(stmtList, stmtNode);
    }

  return stmtList;
}


CG_result* CG_leaf::recompute(const Relation &k, const Relation &r, elimination_info e) {
  known = copy(k);
  known.simplify();
  restrictions = copy(r);
  restrictions.simplify();
  eliminated = e;
  Relation kr = Intersection(copy(known), copy(restrictions));
  kr.simplify();
  
  guard.reallocate(isActive.size());
  if (code_gen_debug > 1) {
    fprintf(DebugFile,"Recomputing leaf node %p\n", (void *) this);
    fprintf(DebugFile,"Known: %s\n", copy(k).print_formula_to_string().c_str());
    fprintf(DebugFile,"restrictions: %s\n", copy(r).print_formula_to_string().c_str());
  }
  
  bool anyActive = false;
  for(int s = 1; s <= isActive.size(); s++)
    if (isActive[s]) {
      if (code_gen_debug > 1) {
        fprintf(DebugFile,"s%d I: %s\n", s, copy(new_IS[s]).print_formula_to_string().c_str());
      }
      Relation I = Intersection(copy(kr), copy(new_IS[s]));
      if (!I.is_upper_bound_satisfiable())
        isActive[s] = 0;
      else {
        anyActive = true;
        assert(!I.is_null());
        if (code_gen_debug > 1) {
          fprintf(DebugFile,"s%d Ikr: %s\n", s, copy(I).print_formula_to_string().c_str());
        }
        guard[s] = Gist(copy(I), copy(known), 1);
        guard[s] = eliminated.project_eliminated(guard[s], known);
        guard[s] = Intersection(guard[s], copy(function_guards[s]));
        if (code_gen_debug > 1) {
          fprintf(DebugFile,"s%d g: %s\n", s, copy(guard[s]).print_formula_to_string().c_str());
        }
      }
    }
  
  if (!anyActive) {
    if (code_gen_debug) {
      fprintf(DebugFile,"Pruning leaf node %p\n", (void *) this);
      fprintf(DebugFile,"Known: %s\n", copy(k).print_formula_to_string().c_str());
      fprintf(DebugFile,"restrictions: %s\n", copy(r).print_formula_to_string().c_str());
    }
    delete this;
    return new CG_null();
  }
  return this;
}


Relation CG_leaf::hoistGuard() {
  int s; 
  for (s = 1; s <= isActive.size() && !isActive[s]; s++)
    ;

  if (s > isActive.size())
    return Relation::True(1);

  Relation guard1 = guard[s];

  for (int i = s+1; i <= isActive.size(); i++)
    if (isActive[i] && !(Must_Be_Subset(copy(guard1), copy(guard[i])) && Must_Be_Subset(copy(guard[i]), copy(guard1))))
      return Relation::True(guard1.n_set());

  return guard1;
}

void CG_leaf::removeGuard() {
  for (int i = 1; i <= isActive.size(); i++)
    if (isActive[i])
      guard[i] = Relation::True(guard[i].n_set());
}

// CG_loop implementation

Relation CG_loop::findOverhead(int liftTo) {
// If a loop is nec., search for both guard and min/max overheads, otherwise
// skip those step
  if (needLoop) {
    int bb = !guard.is_obvious_tautology();
    if (bb) {
#if 0
      fprintf(DebugFile,"Trying to remove overhead on guard of loop %x at level %d: %s\n",
              (void *) this, level, guard.print_formula_to_string().c_str());
#endif
      Relation r = pickOverhead(guard, liftTo);
      if (!r.is_obvious_tautology()) return r;
    }
    Relation b = bounds;
    Relation r = minMaxOverhead(b,level);
    if (!r.is_obvious_tautology()) {
#if 0
      fprintf(DebugFile,"Trying to remove minMax overhead on guard of loop %x at level %d: %s\n",
              (void *) this, level, guard.print_formula_to_string().c_str());
#endif
      return r;
    }
  } // if (needLoop)...
  Relation r = body->findOverhead(liftTo);
  if (r.is_obvious_tautology()) return r;

// If there's a loop at this level, the overhead returned may use the
// current loop variable we need to take it out.  If there is NO loop
// here, then we eliminated this var before recomputing subtree, so we
// don't need to.  More importantly, it can gist away the overhead
// since we didn't output the guard we really should
// have. (i.e. bounds are stricter since they weren't gisted according
// to the guard we normally output, and so would gist away the
// overhead)

   
  // fprintf(DebugFile,"Lifting out guard past level %x at level %d: %s\n",
  // (void *) this, level, (const char *) r.print_formula_to_string());
  //fprintf(DebugFile,"Bounds are: %s\n",(const char *)bounds.print_formula_to_string());
  r = Intersection(r, copy(bounds));
  //fprintf(DebugFile,"Intersection: %s\n",(const char *)r.print_formula_to_string());
  r = project_onto_levels(r,level,0);
  //fprintf(DebugFile,"projected: %s\n",(const char *)r.print_formula_to_string());
  r = Gist(r,copy(bounds),1);
  //fprintf(DebugFile,"Got %s\n",
  //(const char *) r.print_formula_to_string());
  return r;
}

bool find_any_constraint(int s, int level, Relation &kr, int direction,
                         Relation &S, bool approx) {
  /* If we don't intersect I with restrictions, the combination 
     of S and restrictions can be unsatisfiable, which means that
     the new split node gets pruned away and we still don't have
     finite bounds -> infinite recursion. */

  Relation I = projected_nIS[level][s];
  I = Gist(I,copy(kr));
  if(approx) I = Approximate(I);
  if (hasBound(I,level,direction)) {
    Relation pickfrom;
    if(has_nonstride_EQ(I,level))
      pickfrom = pickEQ(I,level);
    else 
      pickfrom = pickBound(I,level,direction);
    S = pickOverhead(pickfrom,level);
    if(S.is_obvious_tautology()) S = Relation::Null();
    return !S.is_null();
  }
  return false;
}

CG_result * CG_loop::force_finite_bounds() {
  if (!needLoop || (hasBound(bounds,level,0) && hasBound(bounds,level,1))) {
    body = body->force_finite_bounds();
    return this;
  }
  
  if (code_gen_debug) 
    fprintf(DebugFile,"Don't have finite bounds in:\n%s\n\n", this->print(2).c_str());
  bool bb = !hasBound(bounds,level,0);
  int direction = bb ? 0 : 1;
  Relation kr = Intersection(copy(known),
                             copy(restrictions));
  int s;
  Relation S;
  for(s = 1; s <= isActive.size(); s++)
    if (isActive[s])
      if(find_any_constraint(s,level,kr,direction,S,false))
        break;
  // If we can't find one, approximate to remove GEQ strides and
  // try again.  Statement guards will ensure correctness.
  if(S.is_null())
    for(s = 1; s <= isActive.size(); s++)
      if (isActive[s])
        if(find_any_constraint(s,level,kr,direction,S,true))
          break;
 
  if(S.is_null()) {
#if 0
    fprintf(DebugFile,"hasBound(%s,%d,%s) said false, but overhead was tautology\n", I.print_formula_to_string().c_str(), level, direction?"upper bound":"lower bound");
#endif
    assert(0 && "Unable to force finite bounds");
  }

  if (code_gen_debug) 
    fprintf(DebugFile,"Spliting on %s\n", S.print_formula_to_string().c_str());
  
  CG_result *spl = new CG_split(isActive,level,S,this,this->new_copy());
  spl = spl->recompute(copy(known), copy(restrictions), eliminated);
#if 0
  if (code_gen_debug) 
    fprintf(DebugFile,"Split on to create finite bounds:\n%s\n\n", spl->print(2).c_str());
#endif
  return spl->force_finite_bounds();
}


CG_result * CG_loop::liftOverhead(int depth) {
  assert(depth >= 1);
  if (this->depth() < depth)
    return this;
  else if (!(needLoop && this->depth() == depth)) {
    body = body->liftOverhead(depth);
    return this;
  }

  Relation c = body->findOverhead(level);
  if (c.is_obvious_tautology()) return this;
  assert(c.is_upper_bound_satisfiable());
  std::string before;
  if (code_gen_debug) {
    before = print(1);
  }
  CG_result *s = new CG_split(isActive,level,c,this,this->new_copy());

  s = s->recompute(copy(known), copy(restrictions), eliminated);
  if (code_gen_debug) {
    std::string after = s->print(1);
    fprintf(DebugFile,"Lifted out overhead of %s\n", c.print_formula_to_string().c_str());
    fprintf(DebugFile,"from:\n%s\n", before.c_str());
    fprintf(DebugFile,"to get:\n%s--\n",after.c_str());
  }
  s = s->liftOverhead(depth);
  return s;
}


std::string CG_loop::printStructure(int indent) { // CG_loop print method
  std::string s = "";
  int indnt = indent;
  s += outputSpaces(indent)
    + "// loop" + (needLoop?"":"(single)") + " for t" + to_string(level) + " at "
    + to_string((void *)this)
    + "\n";
  if (eliminated.any_eliminated()) {
    s += outputSpaces(indent) + "// eliminated: ";
    s += eliminated.print_eliminated_to_string() + "\n";
  }
  s += outputSpaces(indent) + "// known: " + known.print_formula_to_string() + "\n";
  s += outputSpaces(indent) + "// guard: " + guard.print_formula_to_string() + "\n";
  s += outputSpaces(indent) + "// bounds: " + bounds.print_formula_to_string() + "\n";

  // Print each statement's bounds in debugging info
  for(int i = 1; i<= isActive.size(); i++)
    if (isActive[i]) {
      s += outputSpaces(indent)
        + "// "
        + statementNameInfo[i]->debug_name()
        + ":" + projected_nIS[level][i].print_formula_to_string()
        + "\n";
    }

  return s + body->printStructure(indnt+1) + outputSpaces(indnt+1)+ "}\n";
} 



//-----------------------------------------------------------------------------
// original CG_loop::print(int) is now a wrapper of printRepr(CG_outputBuilder*, int)
//-----------------------------------------------------------------------------
std::string CG_loop::print(int indent) {
  CG_stringBuilder oscg;
  CG_outputRepr* loopRepr = printRepr(&oscg, indent);
  return GetString(loopRepr);
}

//*****************************************************************************
// Added by D people. Lei Zhou Apr. 20, 96
//*****************************************************************************
//-----------------------------------------------------------------------------
// CG_loop member function: 
// CG_outputRepr* CG_loop::printRepr(CG_outputBuilder* ocg, int indent)
//-----------------------------------------------------------------------------
CG_outputRepr* CG_loop::printRepr(CG_outputBuilder* ocg, int indent) {
  CG_outputRepr* loopRepr = NULL;  // the entire loop
  CG_outputRepr* bodyRepr = NULL;  // loop body
  CG_outputRepr* ctrlRepr = NULL;  // loop control: index, low, up, step
  CG_outputRepr* guardRepr = NULL; // guard 
#if 0
  CG_outputRepr* spaceRepr = NULL; // indent space 
#endif
  CG_outputRepr* loopReprList = ocg->CreateStmtList();

  int indnt = indent;
  int guarded = 0;

  if (code_gen_debug) {
    std::string loopComment;
    CG_outputRepr *textRepr;
    loopComment = "loop for t" + to_string(level) + " at " + to_string((void *)this);
    textRepr = ocg->CreateComment(indent, loopComment);
    loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);

    loopComment = "known: " + known.print_formula_to_string();
    textRepr = ocg->CreateComment(indent, loopComment);
    loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);

    loopComment = "restrictions: " + restrictions.print_formula_to_string();
    textRepr = ocg->CreateComment(indent, loopComment);
    loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);

    if (eliminated.any_eliminated()) {
      loopComment = "eliminated: ";
      loopComment += eliminated.print_eliminated_to_string();
      textRepr = ocg->CreateComment(indent, loopComment);
      loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);
    }

    loopComment = "active: ";
    for(int s = 1; s <= isActive.size(); s++) {
      if (isActive[s]) {
        loopComment += to_string(s) + " ";
      }
    }
    textRepr = ocg->CreateComment(indent, loopComment);
    loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);

    loopComment = "bounds: " + bounds.print_formula_to_string();
    textRepr = ocg->CreateComment(indent, loopComment);
    loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);

    loopComment = "guard: " + guard.print_formula_to_string();
    textRepr = ocg->CreateComment(indent, loopComment);
    loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);

    // Print each statement's bounds in debugging info
    int cc = !hasBound(bounds,level,0) || !hasBound(bounds,level,1);
    if (cc) {
      int s;
      for(s = 1; s<= isActive.size(); s++) if (isActive[s]) {
          assert(Intersection(Intersection(copy(restrictions), copy(known)),
                              copy(projected_nIS[level][s])).is_upper_bound_satisfiable());

          loopComment = statementNameInfo[s]->debug_name() + ":"
            + projected_nIS[level][s].print_formula_to_string();
          textRepr = ocg->CreateComment(indent, loopComment);
          loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);
        }
  
      // Print hull in debugging info

      Relation hull(Hull(projected_nIS[level],isActive,1));
      loopComment = "hull: " + hull.print_formula_to_string();
      textRepr = ocg->CreateComment(indent, loopComment);
      loopReprList = ocg->StmtListInsertLast(loopReprList, textRepr);
    }
  }

  // Generate guard if necessary
  // If code_gen_check_zero_trip is set, use the guard as is; otherwise,
  // omit the parts of the guard that check if this is zero-trip loop
  Relation current_guard;
  if (! code_gen_check_zero_trip) {
    current_guard = guard;
  }
  else {
    // gist guard given the zero trip check
    Relation zero_trip_check = Project(Gist(copy(bounds),copy(guard)),
                                       level, set_var(level)->kind());
    current_guard = Gist(copy(guard),zero_trip_check);
  }

  // output code for guard and bounds
  if (!current_guard.is_obvious_tautology()) {
    guarded = 1;
    guardRepr = output_guard(ocg, current_guard);
    indnt++;
  }
  Variable_ID v = set_var(level); // get ID of current loop var
  Relation enforced(known);
  Relation b = Gist(copy(bounds),copy(current_guard),1); // b: actual bounds are gisted given info in guards

  bool  r = outputBounds(ocg, b, v, indnt, copy(known), enforced, ctrlRepr, eliminated);
  // TODO: should bookkeep catched contraints in loop output as enforced and check if anything missing
  // if (!Gist(copy(b), copy(enforced)).is_obvious_tautology()) {
  //   fprintf(stderr, "need to generate extra guard inside the loop\n");
  // }
    
  // Below should never happen: says the current variable v generates an
  // assignment rather than a loop, but we thought we needed a loop  
  if (needLoop && eliminated.is_eliminated(v))
    r = false;
  
  if (!r) {
    fprintf(DebugFile,"Code generation failure\n");
    fprintf(DebugFile,"Loop %p at lvl %d\n", (void *) this, level);
    fprintf(DebugFile,"printBounds failed\n");
    fprintf(DebugFile,"bounds:\n");
    bounds.prefix_print(DebugFile);
    fprintf(DebugFile,"known:\n");
    known.prefix_print(DebugFile);
    fprintf(DebugFile,"restrictions:\n");
    restrictions.prefix_print(DebugFile);
    fprintf(DebugFile,"active:");
    for(int s = 1; s <= isActive.size(); s++) 
      if (isActive[s]) fprintf(DebugFile,"%d ",s);
    fprintf(DebugFile,"\n");
    SetTuple I(isActive.size());
    Relation hull = Intersection(Hull(projected_nIS[level],isActive,1),
                                 greatest_common_step(projected_nIS[level], 
                                                      isActive, 
                                                      level));
    fprintf(DebugFile,"new hull:\n");
    hull.prefix_print(DebugFile);
    assert(0 && "printBounds failure, see debugging file for details");
  }

  if (!needLoop) {
    if (ctrlRepr) {
      bodyRepr = body->printRepr(ocg, indnt+1);
      loopRepr = ocg->CreateIf(indnt, ctrlRepr, bodyRepr, NULL);
    }
    else {
      bodyRepr = body->printRepr(ocg, indnt);
      loopRepr = bodyRepr;
    }
  }
  else {
    bodyRepr = body->printRepr(ocg, indnt+1);
    loopRepr = ocg->CreateLoop(indnt, ctrlRepr, bodyRepr);
  }

  loopReprList = ocg->StmtListInsertLast(loopReprList, loopRepr);

  if (!current_guard.is_obvious_tautology()) {
    CG_outputRepr* ifstmt = ocg->CreateIf(indent, guardRepr, loopReprList, NULL);
    CG_outputRepr* ifList= ocg->CreateStmtList();
    ifList = ocg->StmtListInsertLast(ifList, ifstmt);

    return ifList;
  }

  return loopReprList;
}


CG_result * CG_loop::recompute(const Relation &k, const Relation &r, elimination_info e) {
  known = copy(k);
  known.simplify();
  restrictions = copy(r);
  restrictions.simplify();
  eliminated = e;
  Relation kr = Intersection(copy(known), copy(restrictions));
  kr.simplify();

  // check active statements are indeed active
  {
    bool anyActive = false;
    for(int s = 1; s <= isActive.size(); s++)
      if (isActive[s]) {
        if (!Intersection(copy(kr), copy(projected_nIS[level][s])).is_upper_bound_satisfiable()) {
          isActive[s] = 0;
        }
        else anyActive = true;
      }
    
    if (!anyActive) { // prune this loop node
      delete this;
      return new CG_null();
    }
  }

  // project the hull for all active statements,
  // use known condition during the process -- by chun 10/09/2008
  // keep the wildcards during the process  -- by chun 09/02/2009
  Relation hull = Hull(projected_nIS[level], isActive, 1, true, copy(kr));
  hull = Intersection(hull, copy(kr));
  hull.simplify(2, 4);
  //hull.simplify();
  
  // independently extract stride conditions
  Relation the_gcs = greatest_common_step(projected_nIS[level], isActive, level, known);
  // hull = Intersection(hull, copy(the_gcs));
  // hull.simplify(2, 4);

  // start to extract loop information from hull
  bool second_try = false;
Loop_Bound_Compute:
  // check whether the loop is a single iteration
  {
    needLoop = true;
    Relation eq_constraint = Relation::True(hull);  
    Conjunct *c = hull.query_DNF()->single_conjunct();
    Variable_ID v = set_var(level);

    for (EQ_Iterator e = c->EQs(); e; e++) {
      if (!(*e).has_wildcards() && (*e).get_coef(v) != 0) {
        needLoop = false;
        eq_constraint.and_with_EQ(*e);
        break;
      }
    }
    if (!needLoop) {
      if(eliminated.may_eliminate(v))
        eliminated.eliminate(v);
      // don't generate guard, exclude that info from known
      guard = Relation::True(hull.n_set());
      // add only info about current loop var to known, not guard info
      eq_constraint.simplify();
      bounds = copy(eq_constraint);
      bounds.copy_names(hull);
      bounds.setup_names();
      Relation new_known = Intersection(copy(known), eq_constraint);
      new_known.simplify();
      Relation new_restrictions = Gist(copy(restrictions), copy(new_known));
      body = body->recompute(new_known, new_restrictions, eliminated);
      return this;
    }
  }  

  bounds = Relation(hull.n_set());
  F_Exists *fe = bounds.add_and()->add_exists();
  F_And *f_root = fe->add_and();
  
  // extract loop bounds and guard conditions
  bool has_unresolved_bound = false;
  {
    Relation b = Gist(copy(hull), copy(known), 1);
    // b = Intersection(b, copy(the_gcs));
    // b.simplify();
    
    Conjunct *c = b.single_conjunct();
    Variable_ID v = b.set_var(level);
    std::map<Variable_ID, Variable_ID> exists_mapping;
    std::stack<std::pair<GEQ_Handle, Variable_ID> > floor_geq_stack;
    std::set<Variable_ID> floor_var_set;

    // add essential inequalities involving this loop index
    for (GEQ_Iterator gi(c); gi; gi++)
      if ((*gi).get_coef(v) != 0) {
        bool is_part_of_bound = true;
        GEQ_Handle h2;
        for (Constr_Vars_Iter cvi(*gi, true); cvi; cvi++)
          if (!findFloorInequality(b, cvi.curr_var(), h2, v)) {
            has_unresolved_bound = true;
            is_part_of_bound = false;
            break;
          }
        if (!is_part_of_bound)
          continue;

        GEQ_Handle h = f_root->add_GEQ();
        for (Constr_Vars_Iter cvi(*gi); cvi; cvi++) {
          Variable_ID v2 = cvi.curr_var();
          switch (v2->kind()) {
          // case Set_Var:
          case Input_Var: {
            int pos = v2->get_position();
            h.update_coef(bounds.set_var(pos), cvi.curr_coef());
            break;
          }
          case Exists_Var:
          case Wildcard_Var: {
            std::map<Variable_ID, Variable_ID>::iterator p = exists_mapping.find(v2);
            Variable_ID e;
            if (p == exists_mapping.end()) {
              e = fe->declare();
              exists_mapping[v2] = e;
            }
            else
              e = (*p).second;
            h.update_coef(e, cvi.curr_coef());

            if (floor_var_set.find(v2) == floor_var_set.end()) {
              findFloorInequality(b, v2, h2, v);
              floor_geq_stack.push(std::make_pair(h2, v2));
              floor_var_set.insert(v2);
            }
            break;
          }
          case Global_Var: {
            Global_Var_ID g = v2->get_global_var();
            Variable_ID v3;
            if (g->arity() == 0)
              v3 = bounds.get_local(g);
            else
              v3 = bounds.get_local(g, v2->function_of());
            h.update_coef(v3, cvi.curr_coef());
            break;
          }
          default:
            assert(0);
          }
        }
        h.update_const((*gi).get_const());
      }

    // add floor definition involving variables appeared in bounds
    while (!floor_geq_stack.empty()) {
      std::pair<GEQ_Handle, Variable_ID> p = floor_geq_stack.top();
      floor_geq_stack.pop();

      GEQ_Handle h1 = f_root->add_GEQ();
      GEQ_Handle h2 = f_root->add_GEQ();
      for (Constr_Vars_Iter cvi(p.first); cvi; cvi++) {
        Variable_ID v2 = (*cvi).var;
        switch  (v2->kind()) {
        // case Set_Var:
        case Input_Var: {
          int pos = v2->get_position();
          h1.update_coef(bounds.input_var(pos), cvi.curr_coef());
          h2.update_coef(bounds.input_var(pos), -cvi.curr_coef());
          break;
        }
        case Exists_Var:
        case Wildcard_Var: {
          std::map<Variable_ID, Variable_ID>::iterator p2 = exists_mapping.find(v2);
          Variable_ID e;
          if (p2 == exists_mapping.end()) {
            e = fe->declare();
            exists_mapping[v2] = e;
          }
          else
            e = (*p2).second;
          h1.update_coef(e, cvi.curr_coef());
          h2.update_coef(e, -cvi.curr_coef());

          if (floor_var_set.find(v2) == floor_var_set.end()) {
            GEQ_Handle h3;
            findFloorInequality(b, v2, h3, v);
            floor_geq_stack.push(std::make_pair(h3, v2));
            floor_var_set.insert(v2);
          }
          break;
        }
        case Global_Var: {
          Global_Var_ID g = v2->get_global_var();
          Variable_ID v3;
          if (g->arity() == 0)
            v3 = bounds.get_local(g);
          else
            v3 = bounds.get_local(g, v2->function_of());
          h1.update_coef(v3, cvi.curr_coef());
          h2.update_coef(v3, -cvi.curr_coef());
          break;
        }
        default:
          assert(0);
        }
      }
      h1.update_const(p.first.get_const());
      h2.update_const(-p.first.get_const());
      h2.update_const(-p.first.get_coef(p.second)-1);
    }

    // // add essential equalities involving this loop index
    // for (EQ_Iterator ei(c); ei; ei++)
    //   if ((*ei).get_coef(v) != 0) {
    //     EQ_Handle h = f_root->add_EQ();
    //     for (Constr_Vars_Iter cvi(*ei); cvi; cvi++) {
    //       Variable_ID v2 = cvi.curr_var();
    //       switch (v2->kind()) {
    //       // case Set_Var:
    //       case Input_Var: {
    //         int pos = v2->get_position();
    //         h.update_coef(bounds.set_var(pos), cvi.curr_coef());
    //         break;
    //       }
    //       case Exists_Var:
    //       case Wildcard_Var: {
    //         std::map<Variable_ID, Variable_ID>::iterator p = exists_mapping.find(v2);
    //         Variable_ID e;
    //         if (p == exists_mapping.end()) {
    //           e = fe->declare();
    //           exists_mapping[v] = e;
    //         }
    //         else
    //           e = (*p).second;
    //         h.update_coef(e, cvi.curr_coef());
    //         break;
    //       }
    //       case Global_Var: {
    //         Global_Var_ID g = v2->get_global_var();
    //         Variable_ID v3;
    //         if (g->arity() == 0)
    //           v3 = bounds.get_local(g);
    //         else
    //           v3 = bounds.get_local(g, v2->function_of());
    //         h.update_coef(v3, cvi.curr_coef());
    //         break;
    //       }
    //       default:
    //         assert(0);
    //       }
    //     }
    //     h.update_const((*ei).get_const());
    //   }

    if (has_unresolved_bound && !second_try) {
      hull = Approximate(hull);
      hull = Intersection(hull, copy(kr));
      // hull = Intersection(hull, copy(the_gcs));
      hull = Intersection(hull, bounds);
      hull.simplify(2, 4);
      second_try = true;
      goto Loop_Bound_Compute;
    }
      
    // add constraints that can't be captured by bounds to guard condition
    bounds = Intersection(bounds, copy(the_gcs));
    bounds.simplify();
    guard = Gist(copy(b), copy(bounds));
    guard = Project(guard, v);
    guard = Gist(guard, copy(known));
    guard.simplify();

    bounds.copy_names(hull);
    guard.copy_names(hull);
    bounds.setup_names();
    guard.setup_names();
  }
  
  // finally we can eliminate variables without complicating relations
  guard = eliminated.project_eliminated(guard, known);
  guard.simplify();
  bounds = eliminated.project_eliminated(bounds, known);
  bounds.simplify();

  // recursively down the AST
  Relation new_known = Intersection(Intersection(copy(bounds), copy(guard)), copy(known));
  new_known.simplify();
  Relation new_restrictions = Gist(copy(restrictions), copy(new_known)); 
  body = body->recompute(new_known, new_restrictions, eliminated);
  return this;
}

  
Relation CG_loop::hoistGuard() {
  Relation r = body->hoistGuard();
  if (!r.is_obvious_tautology()) {
    // check if the loop index variable appears in r
    bool appear = false;
    for (DNF_Iterator di(r.query_DNF()); di; di++) {
      for (GEQ_Iterator gi((*di)->GEQs()); gi; gi++)
        if ((*gi).get_coef(r.set_var(level)) != 0) {
          appear = true;
          break;
        }
      if (appear)
        break;
      
      for (EQ_Iterator ei((*di)->EQs()); ei; ei++)
        if ((*ei).get_coef(r.set_var(level)) != 0) {
          appear = true;
          break;
        }
      if (appear)
        break;
    }

    if (!appear) {
      body->removeGuard();
      guard = Intersection(guard, r);
    }
  }

  // TO DO: should return Gist(copy(guard), bounds, 1)
  // and make removeGuard paritally remove guard relation.
  if (needLoop)
    return Relation::True(bounds.n_set());
  else
    return guard;
}

SetTuple filter_function_symbols(SetTuple &sets, bool keep_fs){
  SetTuple new_sets(sets.size());
  for(int i = 1; i <= sets.size(); i++) {
    Relation R = sets[i];
    Relation &S = new_sets[i];    
    assert(R.is_set());
    
    S = Relation(R.n_set());
    S.copy_names(R);
    F_Exists *fe = S.add_exists();
    F_Or *fo = fe->add_or();
    for(DNF_Iterator D(R.query_DNF()); D; D++) {
      F_And *fa = fo->add_and();
      Variable_ID_Tuple &oldlocals = (*D)->locals();
      Section<Variable_ID> newlocals = fe->declare_tuple(oldlocals.size());

      /* copy constraints.  This is much more difficult than it needs
         to be, but add_EQ(Constraint_Handle) doesn't work because it can't
         keep track of existentially quantified varaibles across calls.
         Sigh.  */

      for(EQ_Iterator e(*D); e; e++)
        if((max_fs_arity(*e) > 0) == keep_fs){
          EQ_Handle n = fa->add_EQ();
          for(Constr_Vars_Iter cvi(*e,false);cvi;cvi++)
            if((*cvi).var->kind() == Wildcard_Var)
              n.update_coef(newlocals[oldlocals.index((*cvi).var)],
                            (*cvi).coef);
            else
              if((*cvi).var->kind() == Global_Var)
                n.update_coef(S.get_local((*cvi).var->get_global_var(),
                                          (*cvi).var->function_of()),
                              (*cvi).coef);
              else
                n.update_coef((*cvi).var,(*cvi).coef);
          n.update_const((*e).get_const());
          n.finalize();
        }

      for(GEQ_Iterator g(*D); g; g++)
        if((max_fs_arity(*g) > 0) == keep_fs) {
          GEQ_Handle n = fa->add_GEQ();
          for(Constr_Vars_Iter cvi(*g,false);cvi;cvi++)
            if((*cvi).var->kind() == Wildcard_Var)
              n.update_coef(newlocals[oldlocals.index((*cvi).var)],
                            (*cvi).coef);
            else
              if((*cvi).var->kind() == Global_Var)
                n.update_coef(S.get_local((*cvi).var->get_global_var(),
                                          (*cvi).var->function_of()),
                              (*cvi).coef);
              else
                n.update_coef((*cvi).var,(*cvi).coef);
          n.update_const((*g).get_const());
          n.finalize();
        }
    }
    S.finalize();
  }

  return new_sets;
}


RelTuple strip_function_symbols(SetTuple &sets) {
  return filter_function_symbols(sets,false);
}

RelTuple extract_function_symbols(SetTuple &sets) {
  return filter_function_symbols(sets,true);
}


std::string MMGenerateCode(RelTuple &T, SetTuple &old_IS, Tuple<stmt_info *> &name_func_tuple, Relation &known, int effort) {
  CG_stringBuilder oscg;
  CG_outputRepr *sRepr = MMGenerateCode(&oscg, T, old_IS, name_func_tuple, 
                                        known, effort);
#if DUMP_TEST
  cout << "#" << endl;
  cout << "# ----- Beginning of CG_stringBuilder ------" << endl;
  sRepr->Dump();
  cout << "# -------- End of CG_stringBuilder ---------" << endl << endl;
#endif

  return GetString(sRepr);
}

std::string MMGenerateCode(RelTuple &T, SetTuple &old_IS, Relation &known, int effort) {
  Tuple<stmt_info *> NameInfo;
  for (int stmt = 1; stmt <= T.size(); stmt++) {
    // NameInfo.append(new default_stmt_info(stmt));
    NameInfo.append(new default_stmt_info(stmt));
  }
  
  std::string result = MMGenerateCode(T, old_IS, NameInfo, known, effort);
  for (int i = 1; i <= NameInfo.size(); i++)
    delete NameInfo[i];
  return result;
}


//*****************************************************************************
// MMGenerateCode implementation, added by D people. Lei Zhou, Apr. 24, 96
//*****************************************************************************
CG_outputRepr* MMGenerateCode(CG_outputBuilder* ocg, RelTuple &T, SetTuple &old_IS, Relation &known, int effort) {
  Tuple<stmt_info *> NameInfo;
  for (int stmt = 1; stmt <= T.size(); stmt++) {
    // NameInfo.append(new default_stmt_info(stmt));
    NameInfo.append(new default_stmt_info(stmt));
  }
  CG_outputRepr *result = MMGenerateCode(ocg, T, old_IS, NameInfo, known, effort);
  for (int i = 1; i <= NameInfo.size(); i++)
    delete NameInfo[i];
  return result;
}


CG_outputRepr* MMGenerateCode(CG_outputBuilder* ocg, RelTuple &T, SetTuple &old_IS, Tuple<stmt_info *> &name_func_tuple, Relation &known, int effort) {
  int stmts = T.size();
  if (OMEGA_WHINGE < 0)
    OMEGA_WHINGE = getenv("OMEGA_WHINGE") ? atoi(getenv("OMEGA_WHINGE")) : 0;
  if (stmts == 0)
    return ocg->CreateComment(1, "No statements found!");
  if (!known.is_null())
    known.simplify();
  
  // prepare iteration spaces by splitting disjoint conjunctions
  int maxStmt = 1;
  last_level = 0;
  for (int stmt = 1; stmt <= stmts; stmt++) {
    int old_dim = T[stmt].n_out();
    if (old_dim > last_level)
      last_level = old_dim;

    for (int i = 1; i <= old_IS[stmt].n_set(); i++)
      T[stmt].name_input_var(i, old_IS[stmt].set_var(i)->name());
    for (int i = 1; i <= old_dim; i++)
      T[stmt].name_output_var(i, std::string("t")+to_string(i));
    T[stmt].setup_names();
    
    Relation R = Range(Restrict_Domain(copy(T[stmt]), copy(old_IS[stmt])));
    R.simplify();
    while(R.is_upper_bound_satisfiable()) {
      new_IS.reallocate(maxStmt);
      transformations.reallocate(maxStmt);
      statementNameInfo.reallocate(maxStmt);
      DNF *dnf = R.query_DNF();
      DNF_Iterator c(dnf);
      Relation R2 = Relation(R, *c);
      R2.simplify();
      if (known.is_null()) {
        new_IS[maxStmt] = R2;
        transformations[maxStmt] = T[stmt];
        statementNameInfo[maxStmt] = name_func_tuple[stmt];
        maxStmt++;
      }
      else {
        Relation R2_extended = copy(R2);
        Relation known_extended = copy(known);
        if (R2.n_set() > known.n_set())
          known_extended = Extend_Set(known_extended, R2.n_set()-known.n_set());
        else if (R2.n_set() < known.n_set())
          R2_extended = Extend_Set(R2_extended, known.n_set()-R2.n_set());
        if (Intersection(R2_extended, known_extended).is_upper_bound_satisfiable()) {
          new_IS[maxStmt] = R2;
          transformations[maxStmt] = T[stmt];
          statementNameInfo[maxStmt] = name_func_tuple[stmt];
          maxStmt++;
        }
      }
      c.next();
      if (!c.live()) 
        break;
      if(code_gen_debug) {
        fprintf(DebugFile, "splitting iteration space for disjoint form\n");
        fprintf(DebugFile, "Original iteration space: \n");
        R.print_with_subs(DebugFile);
        fprintf(DebugFile, "First conjunct: \n");
        R2.print_with_subs(DebugFile);
      }
      Relation remainder(R, *c);
      c.next();
      while (c.live()) {
        remainder = Union(remainder, Relation(R, *c));
        c.next();
      }
      R = Difference(remainder, copy(R2));
      R.simplify();
      if(code_gen_debug) {
        fprintf(DebugFile, "Remaining iteration space: \n");
        R.print_with_subs(DebugFile);
      }
    }
  }

  // reset number of statements
  stmts = maxStmt-1;
  if(stmts == 0)
    return ocg->CreateComment(1, "No points in any of the iteration spaces!");

  // entend iteration spaces to maximum dimension
  for (int stmt = 1; stmt <= stmts; stmt++) {
    int old_dim = new_IS[stmt].n_set();
    if (old_dim < last_level) {
      new_IS[stmt] = Extend_Set(new_IS[stmt], last_level-old_dim);
      F_And *f_root = new_IS[stmt].and_with_and();
      for (int i = old_dim+1; i <= last_level; i++) {
        EQ_Handle h = f_root->add_EQ();
        h.update_coef(new_IS[stmt].set_var(i), 1);
        h.update_const(posInfinity);
      }
    }   
  }
  
  // standarize the known condition
  if(known.is_null()) {
    known = Relation::True(last_level);
  }
  known = Extend_Set(known, last_level-known.n_set());
  for (int i = 1; i <= last_level; i++)
    known.name_set_var(i, std::string("t")+to_string(i));
  known.setup_names();

  // Function symbols are removed from the iteration space at the top,
  // then inserted into statement guards at the leaves, since set
  // variables can't be projected away when they are arguments to
  // function symbols.
  function_guards = extract_function_symbols(new_IS);
  new_IS = strip_function_symbols(new_IS);
  elimination_info eliminated(function_guards);

  // prepare projected subspaces for each loop level
  projected_nIS.clear();
  projected_nIS.reallocate(last_level);
  for(int i = 1; i <= last_level; i++ ) {
    projected_nIS[i].reallocate(stmts);
  }
  for (int stmt = 1; stmt <= stmts; stmt++) {
    if (last_level > 0)
      projected_nIS[last_level][stmt] = new_IS[stmt];
    for (int i = last_level-1; i >= 1; i--) {
      projected_nIS[i][stmt] = Project(copy(projected_nIS[i+1][stmt]), i+1, Set_Var);
      projected_nIS[i][stmt].simplify();
    }
  }

  // recursively generate AST
  IntTuple allStmts(stmts);
  for(int i = 1; i <= stmts; i++)
    allStmts[i] = 1;
  CG_result *cg = gen_recursive(1, allStmts); 

  // always force finite bounds
  cg = cg->recompute(known, Relation::True(last_level), eliminated);
  cg = cg->force_finite_bounds();

  // loop overhead removal based on actual nesting depth -- by chun 09/17/2008
  for (int i = 1; i <= min(effort, cg->depth()); i++)
    cg = cg->liftOverhead(i);

  // merge adjacent if-conditions -- by chun 10/24/2006
  cg->hoistGuard();

  // really print out the loop
  print_in_code_gen_style++;
  CG_outputRepr* sRepr = cg->printRepr(ocg, 1);
  print_in_code_gen_style--;
  delete cg;
  cg = NULL;
  projected_nIS.clear();
  transformations.clear();
  new_IS.clear();

  return sRepr;
}

CG_result *gen_recursive(int level, IntTuple &isActive) {
  int stmts = isActive.size();

  Set<int> active;
  int s;
  for(s = 1; s <= stmts; s++)
    if(isActive[s]) active.insert(s);

  assert (active.size() >= 1);
  if(level > last_level) return new CG_leaf(isActive);

  if (active.size() == 1)
    return new CG_loop(isActive,level, gen_recursive(level+1,isActive));

  if(code_gen_debug) {
    fprintf(DebugFile, "::: gen_recursive: level %d\n",level);
    fprintf(DebugFile, ":::   incoming isActive statements: ");
    foreach(i, int, active, fprintf(DebugFile, "%d ", i));
    if(code_gen_debug > 1) {
      fprintf(DebugFile, "\n::: incoming transformed iteration spaces:\n");
      for(int i=1; i<=stmts; i++) {
        if (isActive[i]) {
          fprintf(DebugFile, "statement %d:\n", i);
          projected_nIS[level][i].prefix_print(DebugFile);
        }
      }
    }
    fprintf(DebugFile, "\n");
  }

#if PAINFULLY_EXPENSIVE_DEBUGGING
  // Assert that the isActive list is in correspondence
  // with the iteration spaces
  if (code_gen_debug) {
    foreach(check,int,active,
            { 
              assert(!isActive[check] 
                     || (!projected_nIS[level][check].is_null() && 
                         projected_nIS[level][check].is_upper_bound_satisfiable()));});
  }
#endif


  bool constantLevel = true;
   
  int test_rel_size;
  coef_t start,finish; 
  finish = -(posInfinity-1); // -(MAXINT-1);
  start = posInfinity;     // MAXINT;
  Tuple<coef_t> when(stmts);
  for(s=1; s<=stmts; s++) if (isActive[s]) {
      coef_t lb,ub;
      test_rel_size = projected_nIS[level][s].n_set();
      projected_nIS[level][s].single_conjunct()
        ->query_variable_bounds(
          projected_nIS[level][s].set_var(level),
          lb,ub);
      if(code_gen_debug) {
        fprintf(DebugFile, "IS%d:  " coef_fmt " <= t%d <= " coef_fmt "\n",s,
                lb,level,ub);
        projected_nIS[level][s].prefix_print(DebugFile);
      }
      if (lb != ub) {
        constantLevel = false;
        break;
      }
      else {
        set_max(finish,lb);
        set_min(start,lb);
        when[s] = lb;
      }
    }

 
  if (constantLevel && finish-start <= stmts) {
    IntTuple newActive(isActive.size());
    for(int i=1; i<=stmts; i++)  
      newActive[i] = isActive[i] && when[i] == start;
    CG_result *r  = new CG_loop(isActive,level, 
                                gen_recursive(level+1,newActive));
    for(coef_t time = start+1; time <= finish; time++) {
      int count = 0;
      for(int i=1; i<=stmts; i++)   {
        newActive[i] = isActive[i] && when[i] == time;
        if (newActive[i]) count++;
      }
      if (count) {
        Relation test_rel(test_rel_size);
        GEQ_Handle g = test_rel.and_with_GEQ(); 
        g.update_coef(test_rel.set_var(level),-1);
        g.update_const(time-1);
   
        r = new CG_split(isActive,level,test_rel,r,
                         new CG_loop(isActive,level, 
                                     gen_recursive(level+1,newActive)));
      }  
    }
    return r;
  }
  
// Since the Hull computation is approximate, we will get regions that
// have no stmts.  (since we will have split on constraints on the
// hull, and thus we are looking at a region outside the convex hull
// of all the iteration spaces.)
#if 1
  Relation hull = Hull(projected_nIS[level],isActive,1);
#else
  Relation hull = Hull(projected_nIS[level],isActive,0);
#endif

#if PAINFULLY_EXPENSIVE_DEBUGGING
  if(code_gen_debug)
    foreach(s,int,active,assert(Must_Be_Subset(copy(projected_nIS[level][s]),copy(hull))));
#endif
  if(code_gen_debug) {
    fprintf(DebugFile, "Hull (level %d) is:\n",level);
    hull.prefix_print(DebugFile);
  }

  
  IntTuple firstChunk(isActive);
  IntTuple secondChunk(isActive);

  for (int s = 1; s <= isActive.size(); s++)
    if (isActive[s]) {
      Relation gist = Gist(copy(projected_nIS[level][s]),copy(hull),1);
      if (gist.is_obvious_tautology()) break;
      gist.simplify();
      Conjunct *s_conj = gist.single_conjunct();
      for(GEQ_Iterator G(s_conj); G; G++) {
        Relation test_rel(gist.n_set());
        test_rel.and_with_GEQ(*G);
        Variable_ID v = set_var(level);
        coef_t sign = (*G).get_coef(v);
        if(sign > 0) test_rel = Complement(test_rel);
        if(code_gen_debug) {
          fprintf(DebugFile, "Considering split from stmt %d:\n",s);
          test_rel.prefix_print(DebugFile);
        }
  
        firstChunk[s] = sign <= 0;
        secondChunk[s] = sign > 0;
        int numberFirst = sign <= 0;
        int numberSecond = sign > 0;
        
        for (int s2 = 1; s2 <= isActive.size(); s2++)
          if (isActive[s2] && s2 != s) {
            if(code_gen_debug) 
              fprintf(DebugFile,"Consider stmt %d\n",s2);
            bool t = Intersection(copy(projected_nIS[level][s2]),
                                  copy(test_rel)).is_upper_bound_satisfiable();
            bool f = Difference(copy(projected_nIS[level][s2]),
                                copy(test_rel)).is_upper_bound_satisfiable();
            assert(t || f);
            if(code_gen_debug  && t&&f) 
              fprintf(DebugFile, "Slashes stmt %d\n",s2);
            if (t&&f) goto nextGEQ;
            if(code_gen_debug) {
              if (t)
                fprintf(DebugFile, "true for stmt %d\n",s2);
              else 
                fprintf(DebugFile, "false for stmt %d\n",s2);
            }
            if (t) numberFirst++;
            else numberSecond++;
            firstChunk[s2] = t;
            secondChunk[s2] = !t;
          }
            
        assert(numberFirst+numberSecond>1 && "Can't handle wildcard in iteration space");
        if(code_gen_debug) 
          fprintf(DebugFile, "%d true, %d false\n",
                  numberFirst,
                  numberSecond);
        if (numberFirst && numberSecond) {
          // Found a dividing constraint
          if(code_gen_debug) {
            fprintf(DebugFile, "Splitting on:");
            test_rel.prefix_print(DebugFile);
            fprintf(DebugFile, "First chunk:");
            foreach(s3,int,active,
                    {assert(firstChunk[s3] || secondChunk[s3]);
                      assert(!(firstChunk[s3] && secondChunk[s3]));
                      if (firstChunk[s3]) fprintf(DebugFile,"s%d ",s);
                    });
            fprintf(DebugFile, "\n");
          }
   
          return new CG_split(isActive,level,test_rel,
                              gen_recursive(level,firstChunk),
                              gen_recursive(level,secondChunk));
        }
      nextGEQ: ;
      }
    }

  // No way found to divide stmts without splitting, generate loop

  return new CG_loop(isActive,level, gen_recursive(level+1,isActive));
}


// VERIFY FUNCTIONS


bool CG_result::verify_overhead_removal(int) {
  return true;
}

bool CG_null::verify_overhead_removal(int) {
  return true;
}

bool CG_split::verify_overhead_removal(int depth) {
  bool b1 = trueClause->verify_overhead_removal(depth);
  bool b2 = falseClause->verify_overhead_removal(depth);
  return b1 && b2;
}

bool CG_leaf::verify_overhead_removal(int depth) {
  bool no_guards = true;
  if(depth < 0)
    for(int i = 1; i <= isActive.size(); i++)
      if(isActive[i]) {
        if (!guard[i].is_obvious_tautology()) {
          /* Exclude strides that can't be move further out */
          for(DNF_Iterator d(guard[i].query_DNF()); d; d++)
            for(EQ_Iterator e(*d); e; e++)
              /* FERD -- Should be able to check on fs_arity more precisely. */
              if(!(((*e).has_wildcards() 
                    && (*e).max_tuple_pos() == last_level)
                   || max_fs_arity(*e) > 0 )) {
                fprintf(stderr,"statement guard overhead found on "
                        "statement %d\n",i);
                no_guards = false;
              }
        }
      }
  return no_guards;
}


/*
  Overheads here are in the form of min/maxes and guards
  Zero-trip loops are checked by the guards, and z-t guards are
  not removed from them till printing, so we don't have to examine 
  bounds for those.
*/
bool CG_loop::verify_overhead_removal(int depth) {
  bool no_over_guard=true,no_over_minmax=true; 
  if(depth < 0) {
    if(!guard.is_obvious_tautology()) {
      /* Exclude strides that can't be moved further out */
      for(DNF_Iterator d(guard.query_DNF()); d; d++)
        for(EQ_Iterator e(*d); e; e++)
          if(!(((*e).has_wildcards() 
                && (*e).max_tuple_pos() == level-1)
               || max_fs_arity(*e) == level-1)) {
            no_over_guard = false;
            fprintf(stderr,"loop guard overhead found at level %d\n",level);
          }
    }
    coef_t coef;
    int upper_bounds=0,lower_bounds=0;
    Variable_ID v = set_var(level);
 
    if(needLoop) {
      for(GEQ_Iterator CI(bounds.single_conjunct()); CI; CI++) 
        if ((coef = (*CI).get_coef(v)) != 0) {  // In this constraint?
          if(coef > 0) // lb or ub
            lower_bounds++;
          else 
            upper_bounds++;
        }
//     assert(lower_bounds > 0 && upper_bounds > 0);
      if (lower_bounds > 1 || upper_bounds > 1 ) {
        fprintf(stderr,"min/max overhead found at level %d\n",level);
        no_over_minmax = false;
      }
    }
    else {
      // no overheads result from a single-valued level
      no_over_minmax = true;
    }
  }
  bool no_over_body = body->verify_overhead_removal(needLoop?depth-1:depth);
  return (no_over_guard && no_over_minmax && no_over_body);
}


#else

int code_gen_debug = 0;

std::string MMGenerateCode(Tuple<Relation> &, Tuple<Relation> &, Relation &, int) {
  assert(0);
  abort();
  return "";
}

std::string MMGenerateCode(Tuple<Relation> &, Tuple<Relation> &, Tuple<char*> &, Relation, int) {
  assert(0);
  abort();
  return "";
}

#endif

} // namespace
