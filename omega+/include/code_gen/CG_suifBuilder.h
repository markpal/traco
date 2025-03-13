#ifndef CG_suifBuilder_h
#define CG_suifBuilder_h

#include <basic/Tuple.h>
#include <code_gen/CG_outputBuilder.h>
#include <code_gen/CG_suifRepr.h>
#include <string>

namespace omega {

class CG_suifBuilder : public CG_outputBuilder { 
public:
  CG_suifBuilder(proc_symtab *symtab);
  ~CG_suifBuilder();

  //---------------------------------------------------------------------------
  // place holder generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreatePlaceHolder(int indent, CG_outputRepr *stmt,
                                           Tuple<CG_outputRepr*> &funcList,
                                           Tuple<std::string> &loop_vars) const;

  //---------------------------------------------------------------------------
  // assignment generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateAssignment(int indent, CG_outputRepr* lhs,
                                          CG_outputRepr* rhs) const;

  //---------------------------------------------------------------------------
  // function invocation generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateInvoke(const std::string &fname,
                                      Tuple<CG_outputRepr*> &argList) const;

  //---------------------------------------------------------------------------
  // comment generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateComment(int indent, const std::string &commentText) const;

  //---------------------------------------------------------------------------
  // if stmt gen operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateIf(int indent, CG_outputRepr* guardCondition,
                                  CG_outputRepr* true_stmtList, CG_outputRepr* false_stmtList) const;

  //---------------------------------------------------------------------------
  // inductive variable generation, to be used in CreateLoop as control
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateInductive(CG_outputRepr* index,
                                         CG_outputRepr* lower,
                                         CG_outputRepr* upper,
                                         CG_outputRepr* step) const;

  //---------------------------------------------------------------------------
  // loop stmt generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateLoop(int indent, CG_outputRepr* control,
                                    CG_outputRepr* stmtList) const;

  //---------------------------------------------------------------------------
  // basic operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateInt(int ) const;
  virtual CG_outputRepr* CreateIdent(const std::string &idStr) const;

  //---------------------------------------------------------------------------
  // binary arithmetic operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreatePlus(CG_outputRepr*, CG_outputRepr*) const;
  virtual CG_outputRepr* CreateMinus(CG_outputRepr*, CG_outputRepr*) const;
  virtual CG_outputRepr* CreateTimes(CG_outputRepr*, CG_outputRepr*) const;
  virtual CG_outputRepr* CreateIntegerDivide(CG_outputRepr*, CG_outputRepr*) const;
  virtual CG_outputRepr* CreateIntegerMod(CG_outputRepr*, CG_outputRepr*) const;

  //---------------------------------------------------------------------------
  // binary logical operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateAnd(CG_outputRepr*, CG_outputRepr*) const;

  //---------------------------------------------------------------------------
  // binary relational operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateGE(CG_outputRepr*, CG_outputRepr*) const;
  virtual CG_outputRepr* CreateLE(CG_outputRepr*, CG_outputRepr*) const;
  virtual CG_outputRepr* CreateEQ(CG_outputRepr*, CG_outputRepr*) const;
     
  //---------------------------------------------------------------------------
  // stmt list gen operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* 
    CreateStmtList(CG_outputRepr *singleton = NULL) const;
  virtual CG_outputRepr* 
    StmtListInsertLast(CG_outputRepr* list, CG_outputRepr* node) const;
  virtual CG_outputRepr* 
    StmtListAppend(CG_outputRepr* list1, CG_outputRepr* list2) const;

private:
  proc_symtab *symtab_;
};

extern char *k_ocg_comment;

bool substitute(instruction *in, var_sym *sym, operand expr,
                base_symtab *st=NULL);
bool substitute(tree_node *tn, var_sym *sym, operand expr,
                base_symtab *st=NULL);
bool substitute(tree_node_list *tnl, var_sym *sym, operand expr,
                base_symtab *st = NULL);

} // namespace

#endif
