#if !defined(Already_Included_code_gen)
#define Already_Included_code_gen

#include <basic/Tuple.h>
#include <omega/Relation.h>
#include <code_gen/CG.h>
#include <code_gen/CG_outputRepr.h>
#include <code_gen/CG_outputBuilder.h>

namespace omega {

typedef Tuple<int> IntTuple;
typedef Tuple<Relation> SetTuple;
typedef Tuple<SetTuple> SetTupleTuple;
typedef Tuple<Relation> RelTuple;
typedef Tuple<RelTuple> RelTupleTuple;

extern int code_gen_check_zero_trip;

class stmt_info;

Relation project_onto_levels(Relation R, int last_level, bool wildcards);

CG_outputRepr *
MMGenerateCode(CG_outputBuilder* ocg,
               Tuple<Relation> &, Tuple<Relation> &, Relation &known,
               int effort=1);

CG_outputRepr *
MMGenerateCode(CG_outputBuilder* ocg,
               Tuple<Relation> &, Tuple<Relation> &,
               Tuple<stmt_info *> &,
               Relation &known, int effort=1);

std::string MMGenerateCode(Tuple<Relation> &, Tuple<Relation> &, Relation &known,
                      int effort=1);

std::string MMGenerateCode(Tuple<Relation> &, Tuple<Relation> &,
                      Tuple<stmt_info *> &,
                      Relation &known, int effort=1);

class spmd_stmt_info;
inline std::string MMGenerateCode(Tuple<Relation> &tup1, Tuple<Relation> &tup2,
                             Tuple<spmd_stmt_info *> &blip,
                             Relation &known, int effort=1){
  Tuple<stmt_info *> ni(0);
  foreach(s,spmd_stmt_info*,blip,ni.append((stmt_info*)s));
  return MMGenerateCode(tup1,tup2,ni,known,effort);
}


int countStrides(Conjunct *c, Variable_ID v, EQ_Handle &strideEQ, 
                 bool &simple);

std::string outputLBasString(const GEQ_Handle &g, Relation &bounds, Variable_ID v,
                             coef_t stride, const EQ_Handle &strideEQ, 
                             Relation known);
std::string outputUBasString(const GEQ_Handle &g, Relation &bounds, Variable_ID v,
                             coef_t stride, const EQ_Handle &strideEQ);
CG_outputRepr *outputLBasRepr(CG_outputBuilder* ocg, const GEQ_Handle &g, 
                              Relation &bounds, Variable_ID v,
                              coef_t stride, const EQ_Handle &strideEQ,
                              Relation known);

CG_outputRepr *outputUBasRepr(CG_outputBuilder* ocg, const GEQ_Handle &g, 
                              Relation &bounds, Variable_ID v,
                              coef_t stride, const EQ_Handle &strideEQ);

void name_codegen_vars(Relation &R);

CG_outputRepr* outputStatements(CG_outputBuilder* ocg, CG_outputRepr *stmt, int indent, 
                                const Relation &mapping, const Relation &known);

} // namespace

#endif
