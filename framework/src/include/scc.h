// szukaj relacje
int GetRelationId(char* _rel, int _from, int _to)
{
	int i;


	for(i=1; i<=petitRelations.length(); i++)
	{
		String tmp = petitRelations[i].print_with_subs_to_string();




		if(strcmp(str(tmp), (const char *)_rel) ==0 && _from == petitFrom[i] && _to == petitTo[i])
			return i;
	}
	return -1;

}


int ShowScc()
{
    if(disp)
    printRelations(petitRelations, 1);



    int n = petitFrom.length();
    int i;
    std::vector<int> pFrom(n), pTo(n);
    std :: vector <Relation> pRelations;

    for(i=1; i<=petitRelations.length(); i++)
	   relSCC.append(-1);

    for(i=0; i<n; i++)
    {
        pFrom[i] = petitFrom[i+1];
        pTo[i] = petitTo[i+1];
    }



	for(i=1; i<=petitRelations.length(); i++)
	{
		pRelations.insert(pRelations.end(), petitRelations[i]);
	}

	for(i=1; i<=petitRelations.length(); i++)
	{
		String tmp = petitRelations[i].print_with_subs_to_string();
		//printf("%i %i %s", petitFrom[i], petitTo[i], str(tmp));
	}

	std :: vector <std::string> pRelationsType;

	for(i=0; i<petitRelationsType.size(); i++)
	{
		std::string tmp(petitRelationsType[i+1]);
		pRelationsType.insert(pRelationsType.end(), tmp);
	}

	CGraphRDG *_wskGraphRDG = new CGraphRDG(pRelations,pRelationsType,pFrom,pTo);

	std::map<int, std::multimap<SFromTo, Relation, SLessFromTo> > mSCCRelations = _wskGraphRDG->GetSCC();

	std::map <int, std::multimap<SFromTo, Relation, SLessFromTo> > :: iterator m1_Iter;


	FILE *plik_out;
	plik_out = fopen("wynik.txt", "w");

	for( m1_Iter=mSCCRelations.begin(); m1_Iter!=mSCCRelations.end(); ++m1_Iter)
    {

	   std::multimap<SFromTo, Relation, SLessFromTo> mapa = (*m1_Iter).second;

	   std::multimap<SFromTo, Relation, SLessFromTo>::iterator m2_Iter;

	   for( m2_Iter=mapa.begin(); m2_Iter!=mapa.end(); ++m2_Iter)
	   {
		//   fprintf(plik_out, "%i %i\n", (*m1_Iter).first, GetRelationId(str((*m2_Iter).second.print_with_subs_to_string()), (*m2_Iter).first.from, (*m2_Iter).first.to));

		 //  printf("[SCC: %i] Rel %i: %i->%i %s\n", (*m1_Iter).first,
		   //GetRelationId(str((*m2_Iter).second.print_with_subs_to_string()), (*m2_Iter).first.from, (*m2_Iter).first.to),
		   //(*m2_Iter).first.from, (*m2_Iter).first.to, str((*m2_Iter).second.print_with_subs_to_string()));
            int numrel = GetRelationId(str((*m2_Iter).second.print_with_subs_to_string()), (*m2_Iter).first.from, (*m2_Iter).first.to);
            relSCC[numrel] = (*m1_Iter).first;

	   }

    }

    if(!_SILENT)
        printf("Grafów SCC %i\n ", mSCCRelations.size());
	fclose(plik_out);
	return mSCCRelations.size();


}
