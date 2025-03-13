#if ! defined _closure_h
#define _closure_h

#include <omega/Relation.h>

namespace omega {

// Given a Relation R, returns a relation deltas
// that correspond to the ConicHull of the detlas of R
Relation ConicClosure (NOT_CONST Relation &R);

Relation  TransitiveClosure (NOT_CONST Relation &r, 
                             int maxExpansion = 1,
                             NOT_CONST Relation &IterationSpace=Relation::Null());

/* add by Tomasz Klimek */
int iterateCondition( NOT_CONST Relation &rNew, NOT_CONST Relation &rOld, int nEQs, \
		      int nGEQs, int nConjuncts, int iters, int maxWildcards);


void InvestigateClosure(Relation r, Relation r_closure, Relation bounds);
void print_given_bounds(const Relation & R1, NOT_CONST Relation& input_Bounds);

#define printConjunctClosure   (closure_presburger_debug & 0x1) 
#define detailedClosureDebug   (closure_presburger_debug & 0x2)

} // namespace
 
#endif
