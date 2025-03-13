/*****************************************************************************
 Copyright (C) 1994-2000 University of Maryland
 Copyright (C) 2008 University of Southern California
 Copyright (C) 2009 University of Utah
 All Rights Reserved.

 Purpose:
   abstract base class of omega code generation builder

 Notes:
   All CG_outputRepr* pointers in parameter list are consumed inside the
 the function, i.e., not valid after the call.
 
 History:
   04/17/96 - Lei Zhou - created
   05/02/08, clarify integer floor/mod/ceil definitions, - Chun Chen
   05/31/08, use virtual clone to implement CreateCopy
*****************************************************************************/

#ifndef CG_outputBuilder_h
#define CG_outputBuilder_h

#include <code_gen/CG_outputRepr.h>
#include <basic/Tuple.h>
#include <string>

namespace omega {

class CG_outputBuilder {
public:
  virtual ~CG_outputBuilder() {};

  //---------------------------------------------------------------------------
  // place holder generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreatePlaceHolder(int indent, CG_outputRepr *stmt,
                                           Tuple<CG_outputRepr*> &funcList,
                                           Tuple<std::string> &loop_vars) const = 0;

  //---------------------------------------------------------------------------
  // assignment generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateAssignment(int indent, CG_outputRepr* lhs,
                                          CG_outputRepr* rhs) const = 0;

  //---------------------------------------------------------------------------
  // function invocation generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateInvoke(const std::string &fname,
                                      Tuple<CG_outputRepr*> &argList) const = 0;

  //---------------------------------------------------------------------------
  // comment generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateComment(int indent,
                                       const std::string &commentText) const = 0;

  //---------------------------------------------------------------------------
  // if stmt gen operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateIf(int indent, CG_outputRepr* guardCondition,
                                  CG_outputRepr* true_stmtList, CG_outputRepr* false_stmtList) const = 0;

  //---------------------------------------------------------------------------
  // inductive variable generation, to be used in CreateLoop as control
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateInductive(CG_outputRepr* index,
                                         CG_outputRepr* lower,
                                         CG_outputRepr* upper,
                                         CG_outputRepr* step) const = 0;

  //---------------------------------------------------------------------------
  // loop stmt generation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateLoop(int indent, CG_outputRepr* control,
                                    CG_outputRepr* stmtList) const = 0;

  //---------------------------------------------------------------------------
  // copy operation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateCopy(CG_outputRepr* original) const {
    if (original == NULL)
      return NULL;
    else
      return original->clone();
  }

  //---------------------------------------------------------------------------
  // basic operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateInt(int ) const = 0;
  virtual CG_outputRepr* CreateIdent(const std::string &idStr) const = 0;

  //---------------------------------------------------------------------------
  // binary arithmetic operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreatePlus(CG_outputRepr*, CG_outputRepr*) const = 0;
  virtual CG_outputRepr* CreateMinus(CG_outputRepr*, CG_outputRepr*) const = 0;
  virtual CG_outputRepr* CreateTimes(CG_outputRepr*, CG_outputRepr*) const = 0;
  
  //---------------------------------------------------------------------------
  // integer arithmetic in number theory fashion
  // floor(a/b) = div(a/b)
  // ceil(a/b) = -div((-a)/b)
  // mod(a,b) = a-b*div(a/b)
  // result of mod:
  //   if (b > 0) [0,b); else (b,0]
  // implementing div using native '/' operator (e.g. 5/2 = 2, (-5)/2 = -2):
  //   if (b < 0) a = -a, b = -b;
  //   if (a >= 0) a/b; else (a-b+1)/b
  // b is guaranteed to be positive in code generation phase.
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateIntegerDivide(CG_outputRepr*, CG_outputRepr*) const = 0;
  virtual CG_outputRepr* CreateIntegerMod(CG_outputRepr *lop, CG_outputRepr *rop) const {
    CG_outputRepr *lop2 = CreateCopy(lop);
    CG_outputRepr *rop2 = CreateCopy(rop);
    return CreateMinus(lop2, CreateTimes(rop2, CreateIntegerDivide(lop, rop)));
  }
  virtual CG_outputRepr* CreateIntegerCeil(CG_outputRepr* lop, CG_outputRepr* rop) const {
    return CreateMinus(NULL, CreateIntegerDivide(CreateMinus(NULL, lop), rop));
  }

  //---------------------------------------------------------------------------
  // binary logical operation
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateAnd(CG_outputRepr*, CG_outputRepr*) const = 0;

  //---------------------------------------------------------------------------
  // binary relational operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateGE(CG_outputRepr*, CG_outputRepr*) const = 0;
  virtual CG_outputRepr* CreateLE(CG_outputRepr*, CG_outputRepr*) const = 0;
  virtual CG_outputRepr* CreateEQ(CG_outputRepr*, CG_outputRepr*) const = 0;
 
  //---------------------------------------------------------------------------
  // stmt list gen operations
  //---------------------------------------------------------------------------
  virtual CG_outputRepr* CreateStmtList(CG_outputRepr *singleton = NULL) const = 0;
  virtual CG_outputRepr* StmtListInsertLast(CG_outputRepr* list, CG_outputRepr* node) const = 0;
  virtual CG_outputRepr* StmtListAppend(CG_outputRepr* list1, CG_outputRepr* list2) const = 0;
};

} // namespace

#endif
