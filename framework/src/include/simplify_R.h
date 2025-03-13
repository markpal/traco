Relation SimplifyNumConjuncts(Relation R, int z = 0)
{
if(z==0)
    return R;
	Relation R_OUT, Ri, Rj, Di, Dj, Ror, Rh, Diff1, Diff2;
	Tuple<Relation> Rels;
	int i, j, q;
	//int before, past;

	//before = R.number_of_conjuncts();
//	printf("--- %i ---", before);

	if(R.number_of_conjuncts() < 2)
		return R;

	// divide Relation to Relations from conjuntcs
	Rels = Divide_Relation(R);

//	print_Relations(Rels);
	for(i=1; i<Rels.length(); i++)
	{
		j = i+1;
		while(j <= Rels.length())
		{
			Ri = Rels[i];
			Rj = Rels[j];

			if(!R.is_set())
			{

				Di = Deltas(copy(Ri));
				Dj = Deltas(copy(Rj));


				Di.simplify();
				Dj.simplify();

				Diff1 = Difference(copy(Di), copy(Dj));
				Diff2 = Difference(copy(Dj), copy(Di));

				Diff1.simplify();
				Diff2.simplify();
			}
			else
			{
				Diff1 = Difference(copy(R), copy(R));
				Diff2 = Difference(copy(R), copy(R));
				Diff1.simplify();
				Diff2.simplify();

			}



			if(Diff1.number_of_conjuncts() == 0 && Diff2.number_of_conjuncts() == 0)
			{
				Ror = Union(copy(Ri), copy(Rj));
				Ror.simplify();

				Rh = Hull(copy(Ror));   //czasami convex daje lepsze wyniki

				Rh.simplify();

				Diff1 = Difference(copy(Rh), copy(Ror));
				Diff2 = Difference(copy(Ror), copy(Rh));

				Diff1.simplify();
				Diff2.simplify();

				if(Rh.number_of_conjuncts() == 1 && Diff1.number_of_conjuncts() == 0 && Diff2.number_of_conjuncts() == 0)
				{
					//udalo sie
					//printf("Zastepuje relacje R%i relacja R%i OR R%i\n", i, i, j);
					//Rj.print();
					Rels[i] = Rh;

					for(q=j+1; q<=Rels.length(); q++)
						Rels[q-1] = Rels[q];

					Rels.delete_last();

				}
				else
					j++;
			}
			else
				j++;

		}   //while

	}

//	print_Relations(Rels);
	R_OUT = Rels[1];

	for(i=2; i<=Rels.length(); i++)
		R_OUT = Union(copy(R_OUT), copy(Rels[i]));

	R_OUT.simplify();

	// past = R_OUT.number_of_conjuncts();

	//printf("\nZredukowano z %i do %i\n", before, past);

	Diff1 = Difference(copy(R), copy(R_OUT));
	Diff2 = Difference(copy(R_OUT), copy(R));

	Diff1.simplify();
	Diff2.simplify();

	if(Diff1.number_of_conjuncts() == 0 && Diff2.number_of_conjuncts() == 0)
	{}
	//	printf("\nWeryfikacja OK");
	else
	{
		printf("\nWeryfikacja Bad");
		return R;
	}

	return R_OUT;
}



Tuple <Relation> SimplifyNumRels(Tuple <Relation> Rels, bool str = false)
{
	Relation R_OUT, Ri, Rj, Di, Dj, Ror, Rh, Diff1, Diff2;

	int i, j, q;
	//int before, past;

	//before = Rels.length();
	//printf("--- %i ---", before);

	if(Rels.length() < 2)
		return Rels;


	for(i=1; i<Rels.length(); i++)
	{
		j = i+1;
		while(j <= Rels.length())
		{
			Ri = Rels[i];
			Rj = Rels[j];
			//printf("Badam relacje %i %i\n", i, j);

			Di = Deltas(copy(Ri));
			Dj = Deltas(copy(Rj));

			Di.simplify();
			Dj.simplify();

			Di.print();
			Dj.print();

			Diff1 = Difference(copy(Di), copy(Dj));
			Diff2 = Difference(copy(Dj), copy(Di));

			Diff1.simplify();
			Diff2.simplify();

			//printf("--- %i ---", before);


			if(((Diff1.number_of_conjuncts() == 0 && Diff2.number_of_conjuncts() == 0) || str) && Ri.number_of_conjuncts() == 1 && Rj.number_of_conjuncts() == 1)
			{


				Ror = Union(copy(Ri), copy(Rj));
				Ror.simplify();

				Ror.simplify(2, 4);
				Ror.print();


				Rh = Hull(copy(Ror));

				Rh.print();

				Diff1 = Difference(copy(Rh), copy(Ror));
				Diff2 = Difference(copy(Ror), copy(Rh));

				Diff1.simplify();
				Diff2.simplify();



				if(Rh.number_of_conjuncts() == 1 && Diff1.number_of_conjuncts() == 0 && Diff2.number_of_conjuncts() == 0)
				{
					//udalo sie
					printf("Zastepuje relacje R%i relacja R%i OR R%i\n", i, i, j);
					Rj.print();
					Rels[i] = Rh;

					for(q=j+1; q<=Rels.length(); q++)
						Rels[q-1] = Rels[q];

					Rels.delete_last();

				}
				else
					j++;
			}
			else
				j++;

		}   //while

	}


	//past = Rels.length();
	//printf("\nZredukowano z %i do %i\n", before, past);


	return Rels;
}

//upraszczanie
Relation InteSymp(Relation S)
{
	S.simplify();
	if(S.is_set())
		S = ReduceSet(S);
	S = SimplifyNumConjuncts(S);
	S.simplify();
	return S;
}


Relation TryHull(Relation R)
{
    Relation H = Hull(copy(R));
    Relation c1 = Difference(copy(R), copy(H));
    Relation c2 = Difference(copy(H), copy(R));
    c1.simplify();
    c2.simplify();

    if(c1.number_of_conjuncts() == 0 && c2.number_of_conjuncts() == 0 && H.number_of_conjuncts() < R.number_of_conjuncts())
        return H;
    else
        return R;


}
