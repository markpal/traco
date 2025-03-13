// Parsowanie krotek z zbiorow Omegi


//definicje funkcji
bool _GetVecType(Relation S);

struct Tkrotka
{
	int *krotka;
	Tkrotka *next;
};



class Ttuplespace
{
	public :
	Tkrotka *first; // wskaznik na poczatek listy
	Tkrotka *last; // wskaznik na koniec listy
	int dim;

	// konstruktor
	Ttuplespace()
	{
		first = NULL;
		last = NULL;
	}

	//destruktor
	~Ttuplespace()
	{
		//wyczysc liste
		Tkrotka *tmp = first;

		while(tmp)
		{
			Tkrotka *kr_tmp;
			kr_tmp = tmp;
			delete kr_tmp->krotka;
			tmp = kr_tmp->next;
			delete kr_tmp;
		}

		first = last = NULL;
	}


	// CZYTAJ DO LISTY KROTEK ZE ZBIORU
	void ReadSet(Relation S)
	{
		Tkrotka *temp;
		Relation Stuple;

		dim = S.n_set();

		while(S.number_of_conjuncts() > 0)
		{

			if(_GetVecType(copy(S))==false) //zmienna
				//zczytaj pojedyncza krotke
				Stuple = Sample_Solution(copy(S));
			else
				Stuple = S;

			//zamien ja na tablice intow
			temp = ReltoTuple(copy(Stuple));
			//dodaj do listy
			AddTuple(temp);

			S = Difference(copy(S), Stuple);
		}//while
	}

	//WYSWIETL TUPLE
	void Print()
	{
		Tkrotka *tmp;
		int i;

		tmp = first;
		while(tmp)
		{
			for(i=0; i<dim; i++)
				printf("%i ", tmp->krotka[i]);

			printf("\n");
			tmp = tmp->next;
		}
	}


	private :

	//dodaj krotke do listy
	void AddTuple(Tkrotka *krotka)
	{
		if(!first)  //nie ma poczatku
			first = krotka;
		else
			last->next = krotka;

		krotka->next = NULL;
		last = krotka;
	}

	//zbior (jednorodny) do krotki
	Tkrotka* ReltoTuple(Relation uS)
	{
		int i;
		omega::coef_t upperBound1,lowerBound1;

		Tkrotka *kr = new Tkrotka;
		kr->krotka = new int[dim];

		for(i=0; i<dim; i++)
		{
			uS.query_variable_bounds(set_var(i+1),lowerBound1,upperBound1);
			//lowerBound1,upperBound1 powinny byc takie same
			kr->krotka[i] = lowerBound1;
		}

		kr->next = NULL;
		return kr;
	}




};



//typ wektora
bool _GetVecType(Relation S)
{
	bool type = true; //true - staly, false - zmienny
	int i;

	omega::coef_t lb, ub;

	S.simplify(2, 2);
	for(i=1; i<=S.n_set() && type; i++)
	{
		S.query_variable_bounds(set_var(i), lb, ub);
		if (lb != ub)
			type = false;
	}

	return type;
}



int ParallelVectors(Relation &arg1, Relation &arg2)
{
 coef_t upperBound1,lowerBound1;
 coef_t upperBound2,lowerBound2;
 bool diference = false;
 int number = 0; //numer zmiennej w zbiorze powodujacej rownoleglosc wektorow
 int dimension = arg1.n_inp();

 for(int i=1;i<=dimension;i++) {
  arg1.query_variable_bounds(arg1.set_var(i),lowerBound1,upperBound1);
  //ponizej sprawdzenie czy wektor zaleznosci dla arg1 jest wektorem stalym
//  if (lowerBound1!=upperBound1)
//   return -1;

  //ponizej sprawdzenie czy wektor zaleznosci dla arg2 jest wektorem stalym
  arg2.query_variable_bounds(arg1.set_var(i),lowerBound2,upperBound2);
//  if (lowerBound2!=upperBound2)
//   return -1;


  //ponizej sprawdzenie czy koordynaty wektorow roznia sie tylko w jednym miejscu
  if (lowerBound1 != lowerBound2 || upperBound1 != upperBound2) {
   if (diference == true)
    return -1;
   else {
    diference = true;
    number = i; //zapamietanie numeru zmiennej powodujacej rownoleglosc
   }
  }

 }

 return number;
}

bool VarDividedByConst(int constant, unsigned int varNumber, Relation &arg)
{
 Relation rel;
 Relation temp,temp1,temp2;

 rel = arg;
// rel.print();

 F_And *and1 = rel.and_with_and();
 F_Exists *exists = and1->add_exists();
 Variable_ID var = exists->declare("n");

 and1 = exists->add_and();

 EQ_Handle eq = and1->add_EQ();
 eq.update_coef(var,constant);
 eq.update_coef(rel.set_var(varNumber),-1);

 GEQ_Handle geq = and1->add_GEQ();
 geq.update_coef(var,1);
 geq.update_const(-1);

// arg.print();
// rel.print();
// rel.simplify(2,2);
// rel.print();

 temp = Difference(copy(arg),copy(rel));
// temp.print_with_subs();
 temp.simplify(2,2);
// temp.print();

 if (temp.number_of_conjuncts()) {
  //poniewaz roznica zbiorow nie jest pusta, wiec stala nie jest dzielnikiem
  //dla <arg>
  return false;
 }
 else
  return true;

}



