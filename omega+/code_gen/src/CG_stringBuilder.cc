/*****************************************************************************
 Copyright (C) 1994-2000 University of Maryland
 Copyright (C) 2008 University of Southern California
 Copyright (C) 2009 University of Utah
 All Rights Reserved.

 Purpose:
   generate string code for omega

 Notes:
     
 History:
   04/17/96 - Lei Zhou - created
   08/31/09 add parenthesis to string operands, Chun Chen
*****************************************************************************/

#include <code_gen/CG_stringBuilder.h>
#include <code_gen/CG_stringRepr.h>
#include <string>

namespace omega {

extern Tuple<stmt_info*> statementNameInfo;

//*****************************************************************************
// static function declarations
//*****************************************************************************
static std::string GetIndentSpaces(int indent);
static std::string SafeguardString(const std::string &s, char op);


//*****************************************************************************
// Class implementation
//*****************************************************************************
CG_stringBuilder::CG_stringBuilder() {
}


CG_stringBuilder::~CG_stringBuilder() {
}

//-----------------------------------------------------------------------------
// place holder generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreatePlaceHolder(int indent, CG_outputRepr *stmt,
                                                   Tuple<CG_outputRepr*> &funcList,
                                                   Tuple<std::string> &) const {
  std::string listStr = "";

  for (int i = 1; i <= funcList.size(); i++) {
    if (funcList[i] == NULL)
      listStr += "N/A";
    else 
      listStr += GetString(funcList[i]);
    if (i < funcList.size())
      listStr += ",";
  } 

  std::string stmtName = GetString(stmt);
  std::string indentStr = GetIndentSpaces(indent);

  return new CG_stringRepr(indentStr + stmtName + "(" + listStr + ");\n");
}

//-----------------------------------------------------------------------------
// assignment generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateAssignment(int indent, 
                                                  CG_outputRepr* lhs,
                                                  CG_outputRepr* rhs) const {
  if ( lhs == NULL || rhs == NULL ) {
    fprintf(stderr, "Code generation: missing lhs or rhs\n");
    return NULL;
  }

  std::string lhsStr = GetString(lhs);
  std::string rhsStr = GetString(rhs);

  std::string indentStr = GetIndentSpaces(indent);

  return new CG_stringRepr(indentStr + lhsStr + "=" + rhsStr + ";\n");
}

//-----------------------------------------------------------------------------
// function invocation generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateInvoke(const std::string &fname,
                                              Tuple<CG_outputRepr*> &list) const {
  std::string listStr = "";

  for (int i = 1; i <= list.size(); i++) {
    listStr += GetString(list[i]);
    if ( i < list.size())
      listStr += ",";
  }

  return new CG_stringRepr(fname + "(" + listStr + ")");
}
    

//-----------------------------------------------------------------------------
// comment generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateComment(int indent, const std::string &commentText) const {
  if (commentText == std::string("")) {
    return NULL;
  }

  std::string indentStr = GetIndentSpaces(indent);

  return new CG_stringRepr(indentStr + "// " + commentText + "\n");
}


//-----------------------------------------------------------------------------
// if stmt gen operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateIf(int indent, CG_outputRepr* guardList,
                                          CG_outputRepr* true_stmtList, CG_outputRepr* false_stmtList) const {
  if (true_stmtList == NULL && false_stmtList == NULL) {
    delete guardList;
    return NULL;
  }
  else if (guardList == NULL) {
    return StmtListAppend(true_stmtList, false_stmtList);
  }

  std::string guardListStr = GetString(guardList);
  std::string indentStr = GetIndentSpaces(indent);
  std::string s;
  if (true_stmtList != NULL && false_stmtList == NULL) {
    s = indentStr + "if (" + guardListStr + ") {\n"
      + GetString(true_stmtList)
      + indentStr + "}\n";
  }
  else if (true_stmtList == NULL && false_stmtList != NULL) {
    s = indentStr + "if !(" + guardListStr + ") {\n"
      + GetString(false_stmtList)
      + indentStr + "}\n";
  }
  else {
    s = indentStr + "if (" + guardListStr + ") {\n" 
      + GetString(true_stmtList)
      + indentStr + "}\n"
      + indentStr + "else {\n"
      + GetString(false_stmtList)
      + indentStr + "}\n";
  }
  
  return new CG_stringRepr(s);
}


//-----------------------------------------------------------------------------
// inductive variable generation, to be used in CreateLoop as control
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateInductive(CG_outputRepr* index,
                                                 CG_outputRepr* lower, CG_outputRepr* upper,
                                                 CG_outputRepr* step) const {
  if (index == NULL) {
    fprintf(stderr, "Code generation: missing loop index\n");
    return NULL;
  }

  if (lower == NULL || upper == NULL) {
    fprintf(stderr, "Code generation: missing loop bound\n");
  }

  std::string indexStr = GetString(index);
  std::string lowerStr, upperStr;
  if (lower != NULL)
    lowerStr = GetString(lower);
  else
    lowerStr = std::string("-infinity");
  if (upper != NULL)
    upperStr = GetString(upper);
  else
    upperStr = std::string("+infinity");

  std::string doStr = "for(" + indexStr + " = " + lowerStr + "; " 
    + indexStr + " <= " + upperStr + "; " 
    + indexStr;
  
  if (step != NULL) {
    std::string stepStr = GetString(step);
    doStr += " += " + stepStr;
  }
  else {
    doStr += "++";
  }
    
  doStr += ")";
      
  return new CG_stringRepr(doStr);
}


//-----------------------------------------------------------------------------
// loop stmt generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateLoop(int indent, CG_outputRepr* control,
                                            CG_outputRepr* stmtList) const {
  if (stmtList == NULL) {
    delete control;
    return NULL;
  }
  else if (control == NULL) {
    fprintf(stderr, "Code generation: no inductive for this loop\n");
    return stmtList;
  }

  std::string ctrlStr = GetString(control);
  std::string stmtStr = GetString(stmtList);

  std::string indentStr = GetIndentSpaces(indent);

  std::string s = indentStr + ctrlStr + " {\n" 
    + stmtStr 
    + indentStr + "}\n";

  return new CG_stringRepr(s);
}

//-----------------------------------------------------------------------------
// basic int, identifier gen operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateInt(int _i) const {
  std::string _s = to_string(_i);
  return new CG_stringRepr(_s);
}


CG_outputRepr* CG_stringBuilder::CreateIdent(const std::string &_s) const {
  if (&_s == NULL || _s == std::string("")) {
    return NULL;
  }

  return new CG_stringRepr(_s);
}


//-----------------------------------------------------------------------------
// binary arithmetic operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreatePlus(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL) {
    return lop;
  }
  else if (lop == NULL) {
    return rop;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr(lopStr + "+" + ropStr);
}


CG_outputRepr* CG_stringBuilder::CreateMinus(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL) {
    return lop;
  }
  else if (lop == NULL) {
    std::string ropStr = GetString(rop);
    return new CG_stringRepr("-" + SafeguardString(ropStr, '-'));
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr(lopStr + "-" + SafeguardString(ropStr, '-'));
}


CG_outputRepr* CG_stringBuilder::CreateTimes(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL || lop == NULL) {
    delete rop;
    delete lop;
    return NULL;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr(SafeguardString(lopStr, '*') + "*" + SafeguardString(ropStr, '*'));
}


CG_outputRepr* CG_stringBuilder::CreateIntegerDivide(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL) {
    fprintf(stderr, "Code generation: divide by NULL\n");
    return NULL;
  }
  else if (lop == NULL) {
    delete rop;
    return NULL;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr("intDiv(" + lopStr + "," + ropStr + ")");
}


CG_outputRepr* CG_stringBuilder::CreateIntegerMod(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL || lop == NULL) {
    return NULL;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr("intMod(" + lopStr + "," + ropStr + ")");
}

CG_outputRepr* CG_stringBuilder::CreateIntegerCeil(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL || lop == NULL) {
    return NULL;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr("intCeil(" + lopStr + "," + ropStr + ")");
}


//-----------------------------------------------------------------------------
// binary logical operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateAnd(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL || lop == NULL) {
    return NULL;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr(lopStr + " && " + ropStr);
}


//-----------------------------------------------------------------------------
// binary relational operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateGE(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL || lop == NULL) {
    return NULL;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr(lopStr + " >= " + ropStr);
}


CG_outputRepr* CG_stringBuilder::CreateLE(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL || lop == NULL) {
    return NULL;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr(lopStr + " <= " + ropStr);
}


CG_outputRepr* CG_stringBuilder::CreateEQ(CG_outputRepr* lop, CG_outputRepr* rop) const {
  if (rop == NULL || lop == NULL) {
    return NULL;
  }

  std::string lopStr = GetString(lop);
  std::string ropStr = GetString(rop);

  return new CG_stringRepr(lopStr + " == " + ropStr);
}


//-----------------------------------------------------------------------------
// stmt list gen operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_stringBuilder::CreateStmtList(CG_outputRepr *singleton) const {
  if (singleton == NULL) {
    return new CG_stringRepr("");
  }

  std::string listStr = GetString(singleton);

  return new CG_stringRepr(listStr);
}


CG_outputRepr* CG_stringBuilder::StmtListInsertLast(CG_outputRepr* list, CG_outputRepr* node) const {
  return StmtListAppend(list, node);
//   if ( list == NULL ) {
//     assert(0 && "list is empty, can not be inserted a node");
//     return NULL;
//   }
//   else if ( node == NULL ) {
//     return list;
//   }

//   String listStr = GetString(list);
//   String nodeStr = GetString(node);

//   return new CG_stringRepr(listStr + nodeStr);
}


CG_outputRepr* CG_stringBuilder::StmtListAppend(CG_outputRepr* list1, CG_outputRepr* list2) const {
  if (list2 == NULL) {
    return list1;
  }
  else if (list1 == NULL) {
    return list2;
  }

  std::string list1Str = GetString(list1);
  std::string list2Str = GetString(list2);

  return new CG_stringRepr(list1Str + list2Str);
}


//*****************************************************************************
// static function implementations
//*****************************************************************************
static std::string GetIndentSpaces(int indent) {
  std::string indentStr;
  for (int i=1; i<indent; i++) {
    indentStr += "  ";
  }
  return indentStr;
}

std::string GetString(CG_outputRepr* repr) {
  std::string result = ((CG_stringRepr *) repr)->GetString();
  delete repr;
  return result;
}

static std::string SafeguardString(const std::string &s, char op) {
  int len = s.length();
  int paren_level = 0;
  int num_plusminus = 0;
  int num_mul = 0;
  int num_div = 0;
  for (int i = 0; i < len; i++)
    switch (s[i]) {
    case '(':
      paren_level++;
      break;
    case ')':
      paren_level--;
      break;
    case '+':
    case '-':
      if (paren_level == 0)
        num_plusminus++;
      break;
    case '*':
      if (paren_level == 0)
        num_mul++;
      break;
    case '/':
      if (paren_level == 0)
        num_div++;
      break;
    default:
      break;
    }

  bool need_paren = false;
  switch (op) {
  case '-':
    if (num_plusminus > 0)
      need_paren = true;
    break;
  case '*':
    if (num_plusminus > 0 || num_div > 0)
      need_paren = true;
    break;
  case '/':
    if (num_plusminus > 0 || num_div > 0 || num_mul > 0)
      need_paren = true;
    break;
  default:
    break;
  }

  if (need_paren)
    return "(" + s + ")";
  else
    return s;
}
    
} // namespace
