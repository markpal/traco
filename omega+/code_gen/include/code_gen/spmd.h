#if !defined(Already_Included_spmd)
#define Already_Included_spmd

#include <omega/Relations.h>
#include <code_gen/code_gen.h>
#include <basic/Tuple.h>
#include <string.h>

namespace omega {

extern int overheadEffort;

extern int gen_dash;
extern int overheadEffort;
extern int Block_Size;
extern int Num_Procs;
extern int code_gen_debug;

std::string program_head(std::string Decls, int timeDepth);

std::string SPMD_GenerateCode(std::string Decls,
                              Tuple<Relation> &,Tuple<Relation> &,Tuple<Relation> &,
                              Tuple<spmd_stmt_info *> &,
                              Tuple<Free_Var_Decl*> & lb,Tuple<Free_Var_Decl*> & ub,
                              Tuple<Free_Var_Decl*> & my_procs,
                              int nr_statements);

// All things that use SPMD have to allow SPMD functions in to adjust the
// arity of the mappings involved.
class spmd_stmt_info : public stmt_info {

public:
  virtual std::string name(Relation *current_map)=0;
  virtual std::string debug_name() const =0;
  virtual const char * debug_char_name()=0;
  virtual std::string declaration()=0;
  // added by D people. Lei Zhou, Apr. 25, 96
  virtual CG_outputRepr *place_holder(CG_outputBuilder* ocg, int indent,
                                      Relation *current_map) = 0;
protected:
  std::string name_debug;
    

  spmd_stmt_info() {}
  spmd_stmt_info(const std::string &in_debug_name, const Relation &in_time,
                 const Relation &in_space):
    name_debug(in_debug_name), my_time(in_time), my_space(in_space)
    { my_time.compress(); my_space.compress(); }
  spmd_stmt_info(const spmd_stmt_info& n) :
    name_debug(n.debug_name()), my_time(n.my_time), my_space(n.my_space)
    { my_time.compress(); my_space.compress(); }

  Relation my_time;
  Relation my_space;

  void add_cyclic_level(int level){
    extern void move_just_input(int from, int to, Relation &R);

    my_time.uncompress(); my_space.uncompress();
    my_time = Extend_Domain(my_time);
    move_just_input(my_time.n_inp(), level, my_time);
    my_space = Extend_Domain(my_space);
    move_just_input(my_space.n_inp(), level, my_space);
    my_time.simplify(); my_space.simplify();
    my_time.compress(); my_space.compress();
  }

  friend std::string SPMD_GenerateCode(std::string Decls,
                                       SetTuple &Space, RelTuple &Time,
                                       SetTuple &IterationSpaces,
                                       Tuple<spmd_stmt_info *> &NameInfo,
                                       Tuple<Free_Var_Decl*> &lb,
                                       Tuple<Free_Var_Decl*> &ub,
                                       Tuple<Free_Var_Decl*> &my_procs,
                                       int nr_statements);
};


// output format: work(ID, fold(vp waited upon), #remaining args,iter...)
class numbered_stmt_info : public spmd_stmt_info {
public:
  numbered_stmt_info() :  stmt_num(-1) {}
  numbered_stmt_info(int arg, const Relation &in_time,
                     const Relation &in_space, const char *stmt):
    spmd_stmt_info(std::string("s") + to_string(arg), in_time, in_space),
    stmt_num(arg),
    my_stmt(stmt) {
    assert (stmt_num >= 0);
  }
  numbered_stmt_info(const numbered_stmt_info& n) :
    spmd_stmt_info(n.name_debug,n.my_time,n.my_space), stmt_num(n.stmt_num) {
  }

  numbered_stmt_info& operator=(const numbered_stmt_info &n2) {
    assert(0);
    stmt_num = n2.stmt_num;
    name_debug = n2.name_debug;
    my_time = n2.my_time;
    my_space = n2.my_space;
    return *this;
  }

  std::string name(Relation *current_map) {
    assert(stmt_num >= 0);
    my_time.uncompress();
    my_space.uncompress();
    Relation global_time = Join(copy(*current_map),copy(my_time));
    Relation space = Join(copy(*current_map),copy(my_space));
    my_time.compress();
    my_space.compress();

    if (gen_dash) {
      std::string S = "";
      for (unsigned int i=0; i<strlen(my_stmt); i++)
        if (my_stmt[i] != '#') {
          char s[2];
          s[0] = my_stmt[i];
          s[1] = '\0';
          S += to_string(s);
        }
        else {
          int p = my_stmt[++i] - '0';
          S += current_map->print_outputs_with_subs_to_string(p);
        }
      return S;
    }
    else 
      return std::string("work(") + to_string(stmt_num)
        + ", fold(" +
        space.print_outputs_with_subs_to_string() + "),   " +
        to_string(current_map->n_out()) + ", " +
        current_map->print_outputs_with_subs_to_string() + ",   " +
        global_time.print_outputs_with_subs_to_string() + "   );";
  }
  CG_outputRepr *place_holder(CG_outputBuilder* /*ocg*/, int /* indent */,
                              Relation * /*current_map*/) {
    assert(0 && "No implementation currently");
    return NULL;
  }
  CG_outputRepr* place_holder() const {
    return NULL;
  }
  std::string debug_name() const { assert(stmt_num >= 0); return name_debug; }
  const char *debug_char_name() { assert(stmt_num >= 0); return name_debug.c_str(); }
  std::string declaration() { return "void work(int,int,int, ...);\n"; }

private:
  int stmt_num;
  const char *my_stmt;
};

} // namespace

#endif
