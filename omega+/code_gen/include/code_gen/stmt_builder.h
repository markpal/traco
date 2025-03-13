#if !defined(Already_Included_stmt_builder)
#define Already_Included_stmt_builder

#include <omega/pres_gen.h>
#include <code_gen/CG_outputBuilder.h>
#include <code_gen/CG_outputRepr.h>
#include <basic/Tuple.h>

namespace omega {

Tuple<CG_outputRepr*> print_outputs_with_subs_to_repr(CG_outputBuilder* ocg, Relation &R);

} // namespace

#endif
