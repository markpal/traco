
struct SFromTo {
	SFromTo() : from(0), to(0) {}
	SFromTo(unsigned int f, unsigned int t) : from(f), to(t) {}
	SFromTo(unsigned int f, unsigned int t, std::string relType) : from(f), to(t), relationType(relType) {}
	unsigned int from;
	unsigned int to;
	std::string relationType;  //rodzaj relacji : flow, anti, output, ...
};




struct SLessFromTo {
	bool operator () (const SFromTo &arg1, const SFromTo &arg2) const
	{
		if (arg1.from<arg2.from || (arg1.from==arg2.from && arg1.to<arg2.to) )
			return true;
		else
			return false;

		//if (arg2.from != 0 && arg2.to != 0)
		//{
		//	//porownujemy wzgledem from i to
		//	if (arg1.from<arg2.from || (arg1.from==arg2.from && arg1.to<arg2.to) )
		//		return true;
		//	else
		//		return false;
		//}
		//else if (arg2.from != 0 && arg2.to == 0)
		//{
		//	//porownujmey wzgledem from
		//	if (arg1.from<arg2.from)
		//		return true;
		//	else
		//		return false;
		//
		//}
		//else if (arg2.from == 0 && arg2.to != 0)
		//{
		//	//porownujemy wzgldem to
		//	if (arg1.to<arg2.to)
		//		return true;
		//	else
		//		return false;
		//}
	}
};


//struktura slazaca do przechowywania relacji wybierajacych zalezne iteracje
//oraz wektory zaleznosci przynaleznye do tej relacji
struct SRelationVector {
	SRelationVector(const Relation &rel, std::string relType, const Relation &vec, bool vecType,
					int arg1=-1, int arg2=-1) : selectingRel(rel), relationType(relType),
					distanceVec(vec), distanceVecType(vecType),
					from(arg1), to(arg2) {}
					SRelationVector(const Relation &rel, std::string relType, const Relation &vec,
					int arg1=-1, int arg2=-1);


	//	SRelationVector(const Relation &rel);
	unsigned int from;
	unsigned int to;
	Relation selectingRel;	//relacja wybierajaca
	Relation distanceVec;	//zbior wektorow zaleznosci dla powyzszej relacji
	bool distanceVecType;	//true - wektor zaleznosci staly,
									//false - wektor zaleznosci zmienny
	std::string relationType; //rodzaj relacji : flow, anti, output, ...
};

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

