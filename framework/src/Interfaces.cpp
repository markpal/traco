#include "stdafx.h"

#include <stdio.h>
#include <omega.h>

#include <map>

#include ".\include\Interfaces.h"


SRelationVector::SRelationVector(const Relation &rel, std::string relType, const Relation &vec,
								 int arg1, int arg2) : selectingRel(rel), relationType(relType),
								 distanceVec(vec), from(arg1), to(arg2)
{
	coef_t upperBound,lowerBound;

	//ustalenie czy wektor dystansu dla relacji <selectingRel> jest staly
	for(int i=1;i<=distanceVec.n_set();i++) {
		distanceVec.query_variable_bounds(set_var(i),lowerBound,upperBound);
		if (lowerBound!=upperBound) {
			distanceVecType = false;
			break;
		}
		else {
			distanceVecType = true;
		}
	}
	//rodzaj wektora dystansu ustalony
}