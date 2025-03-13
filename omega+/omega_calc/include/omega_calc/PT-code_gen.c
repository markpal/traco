// For basic code gen:

#include <code_gen/spmd.h>
#include <code_gen/code_gen.h>

instantiate_Tuple(omega::stmt_info *);
instantiate_Tuple(omega::spmd_stmt_info *);

// For "tcodegen" extensions:

#include <code_gen/MMap.h>

instantiate_Tuple(omega::PartialMMap);
instantiate_Tuple(omega::MMap);
instantiate_Tuple(omega::PartialRead);
instantiate_Tuple(omega::Read);
instantiate_Tuple(omega::stm_info);
