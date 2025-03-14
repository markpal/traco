#ifndef Already_Included_AST
#define Already_Included_AST

#include <basic/Collections.h>
#include <omega.h>
#include <assert.h>

typedef enum {eq, lt, gt, geq, leq, neq} Rel_Op;

class tupleDescriptor;

class Variable_Ref {
public:
  int anonymous;
  omega::Const_String name;
  omega::Const_String stripped_name;
  omega::Variable_ID vid;
  omega::Variable_ID id(omega::Rel_Body *R) {
    if (vid) return vid;
    if (arity == 0)
      vid = R->get_local(g);
    else
      vid = R->get_local(g,of);
    return vid;
  }
  omega::Variable_ID id(omega::Relation &R) {
    if (vid) return vid;
    if (arity == 0)
      vid = R.get_local(g);
    else
      vid = R.get_local(g,of);
    return vid;
  }
  omega::Free_Var_Decl *g;
  int arity;
  int pos;
  omega::Argument_Tuple of;
  Variable_Ref(char *s, int _arity, omega::Argument_Tuple _of);
  Variable_Ref(char *s);
  Variable_Ref();
  ~Variable_Ref();
};


typedef omega::Bag<char *> VarList;

typedef omega::Bag<Variable_Ref *> DeclList;

typedef omega::Map<omega::Const_String, Variable_Ref *> functionSymbolList;

extern functionSymbolList functionOfInput;
extern functionSymbolList functionOfOutput;

class Declaration_Site {
public:
  Declaration_Site();
  Declaration_Site(VarList *v);
  virtual Variable_Ref * extend(char *s);
  virtual Variable_Ref * extend(char *s, omega::Argument_Tuple, int);
  virtual ~Declaration_Site();

  Variable_Ref * extend();
  void print() {
    foreachSeparated(r,Variable_Ref*,declarations,printf("%s",(const char *)r->name),printf(","));
  }

  Declaration_Site * previous;
  DeclList declarations;
};

class Global_Declaration_Site  : public Declaration_Site {
public:
  virtual Variable_Ref * extend(char *s);
  virtual Variable_Ref * extend() {
    return Declaration_Site::extend();
  }
  virtual Variable_Ref * extend(char *s, omega::Argument_Tuple in_of, int in_arity) {
    return Declaration_Site::extend(s,in_of,in_arity);
  }
  void extend_both_tuples(char *s, int arity);
  virtual ~Global_Declaration_Site();
};

extern Declaration_Site *current_Declaration_Site;

inline void popScope() {
  assert(current_Declaration_Site);
  current_Declaration_Site = current_Declaration_Site->previous;
}

Variable_Ref *lookupScalar(char *s);
Declaration_Site * defined (char *);

class Exp {
public:
  Exp(omega::coef_t c);  
  Exp(Variable_Ref *v); 
  friend Exp * multiply (omega::coef_t c, Exp *x); 
  friend Exp * multiply (Exp *x, Exp *y); 
  friend Exp * negate (Exp *x);
  friend Exp * add (Exp *x, Exp *y); 
  friend Exp * subtract (Exp *x, Exp *y); 
  omega::Map<Variable_Ref *, omega::coef_t> coefs; 
  omega::coef_t constantTerm;
protected:
  void addTerm(omega::coef_t coef, omega::Variable_ID v);
};

typedef struct {
  Exp *e;
  int step;
} strideConstraint;

class AST;
class AST_constraints;
typedef omega::Bag<Exp*> ExpList;

class Tuple_Part {
public:
  Variable_Ref *from,*to;
  Tuple_Part(Variable_Ref *f, Variable_Ref *t) 
  { from = f; to = t; }
  Tuple_Part(Variable_Ref *f)
  { from = f; to = 0; }
  Tuple_Part()
  { from = 0; to = 0; }
};


class AST {
public:
  virtual void install(omega::Formula *F) = 0;
  virtual void print() = 0;
  virtual ~AST() {}
};



class AST_And : public AST {
public:
  AST_And(AST *l, AST *r) { left = l; right = r; }
  ~AST_And() { delete left; delete right; }

  virtual void install(omega::Formula *F);

  virtual void print() { 
    printf("(");
    left->print();
    printf(" && ");
    right->print();
    printf(")");
  }

  AST *left,*right;
};


class AST_Or : public AST {
public:
  AST_Or(AST *l, AST *r) { left = l; right = r; }
  ~AST_Or() { delete left; delete right; }

  virtual void install(omega::Formula *F);

  virtual void print() {
    printf("(");
    left->print();
    printf(" || ");
    right->print();
    printf(")");
  }


  AST *left,*right;
};


class AST_Not : public AST {
public:
  AST_Not(AST *c) { child = c; }
  ~AST_Not() { delete child; }

  virtual void install(omega::Formula *F);

  virtual void print() {
    printf("(!");
    child->print();
    printf(")");
  }

  AST * child;
};



class AST_declare : public AST {
public:
  virtual void install(omega::Formula *F) = 0;

  virtual void print() {
    printf("(");
    declaredVariables->print();
    printf(" : ");
    child->print();
    printf(")");
  }

  Declaration_Site *declaredVariables;
  AST * child;
};


class AST_exists : public AST_declare {
public:
  AST_exists(Declaration_Site *dV, AST *c) {declaredVariables = dV, child = c;} 
  ~AST_exists() { delete child; delete declaredVariables; }

  virtual void install(omega::Formula *F);

  virtual void print() {
    printf("exists ");
    AST_declare::print();
  }
};

class AST_forall : public AST_declare {
public:
  AST_forall(Declaration_Site *dV, AST *c) {declaredVariables = dV, child = c; } 
  ~AST_forall() { delete child; delete declaredVariables; }

  virtual void install(omega::Formula *F);

  virtual void print() {
    printf("forall ");
    AST_declare::print();
  }
};

void printExpList(ExpList *l);

class AST_constraints : public AST {
public:
  AST_constraints(ExpList *f, Rel_Op r, AST_constraints *o);
  AST_constraints(ExpList *f, Rel_Op r, ExpList *s);
  AST_constraints(ExpList *f);
  ~AST_constraints();

  virtual void install(omega::Formula *F);

  virtual void print() {
    printExpList(first);
    if (others != 0) {
      switch(rel_op) {
      case(eq) : printf("="); break;
      case(lt) : printf("<"); break;
      case(gt) : printf(">"); break;
      case(leq) : printf("<="); break;
      case(geq) : printf(">="); break;
      case(neq) : printf("!="); break;
      }
      others->print();
    }
  }

  AST_constraints *others; 
  ExpList *first;
  Rel_Op rel_op;
};

void install_stride(omega::F_And *F, strideConstraint *c);
void install_eq(omega::F_And *F, Exp *e1, Exp *e2);
void install_geq(omega::F_And *F, Exp *e1, Exp *e2);
void install_gt(omega::F_And *F, Exp *e1, Exp *e2);
void install_neq(omega::F_And *F, Exp *e1, Exp *e2);

void printExpList(ExpList *l);

class tupleDescriptor {
public:
  tupleDescriptor() : vars(0) { size = 0; }
  void extend();
  void extend(Exp * e);
  void extend(Exp * lb, Exp *ub);
  void extend(Exp * lb, Exp *ub, omega::coef_t stride);
  void extend(char * s, Exp *e);
  void extend(char * s);
  void extend(char * s, omega::Argument_Tuple, int);

  int size;
  omega::Tuple<Variable_Ref *> vars;
  ExpList eq_constraints;
  ExpList geq_constraints;
  omega::Bag<strideConstraint*> stride_constraints;
  ~tupleDescriptor() {
    foreach(e,Exp*,eq_constraints,delete e);
    foreach(e,Exp*,geq_constraints,delete e);
    foreach(s,strideConstraint*,stride_constraints, delete s->e; delete s);
  }
};

extern Global_Declaration_Site *globalDecls; 
extern Declaration_Site *relationDecl; 
extern tupleDescriptor *currentTupleDescriptor;

void resetGlobals();


// Used to parse a list of paired relations for code generation commands
class RelTuplePair {
public:
RelTuplePair() : ispaces(0), mappings(0) {}
  omega::Tuple<omega::Relation>  ispaces;
  omega::Tuple<omega::Relation> mappings;
};

class RelTupleTriple {
public:
RelTupleTriple() : ispaces(0), space(0), time(0) {}
  omega::Tuple<omega::Relation>  ispaces;
  omega::Tuple<omega::Relation>  space;
  omega::Tuple<omega::Relation>  time;
};

#endif 
