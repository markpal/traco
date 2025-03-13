#define BUF 255 //dlugosc bufora do czytania (taka moze byc najdluzsza linia)

//#include "oc/omega.h" //nie mam poecia czemu to musi byc tutaj wlaczone !!!

#include <vector>
#include <string>
#include <map>



class CStatement {
	public:
		CStatement(std::string b, std::string t, unsigned int lev) :
					  body(b), type(t), level(lev) {}
		std::string ReturnType() { return type; } //zwraca nazwe rodzaju wyrazenia
		unsigned int Level() { return level; } //poziom zagniezdzenia wyrazenia

		//Funkcje dla petli
//		virtual int LowerBound() { return NULL; } //dolna granica petli
//		virtual int UpperBound() { return NULL; } //gorna granica petli
//		virtual int Step() { return NULL; }       //krok petli
		virtual std::string IndexVarName() { return std::string(); } //nazwa zmiennej indeksowej
		virtual std::string ReturnUpperBound() { return std::string(); }
//		virtual bool IsParameterized() { return false; }

		//Funkcje dla wyrazen arytmetycznych
		virtual std::string LeftSide() { return std::string(); }
		virtual std::string RightSide() { return std::string(); }
		virtual unsigned int LeftDimension() { return NULL; }
		virtual unsigned int RightDimension() { return NULL; }

		virtual std::string ReturnBody() { return body; }

	protected:
		std::string type;	  //rodzaj wyrazenie - for, endfor lub arithmetical
		unsigned int level; //poziom zagniezdzenia petli; 1-pojedynczo zagniezdzona;
								  //2-podwojnie zagniezdzona
		std::string body;		//cialo wyrazenie, np jesli for to cialo bedzie postaci (for i=1..)

		//gorna granica petli jako string, poniewaz moze byc to zminenna sparametryzowana
};


class CFor : public CStatement {
	friend class CLoop; //obiekty klasy CLoop moga wypelniac pola klasy CFor
	public:
		CFor(std::string b, std::string t, unsigned int lev, std::string var);

//		int LowerBound() { return lowerBound; } //dolna granica petli
//		int UpperBound() { return upperBound; } //gorna granica petli
//		int Step() { return step; }       //krok petli
		std::string IndexVariableName() { return indexVarName; }
		//funkcja zwraca cialo gornej granicy dla danego for'a jako string
		std::string ReturnUpperBound() { return upperBound; }
		//funkcja sprawdza czy dany for zawiera parametr
//		bool IsParameterized();
		std::string IndexVarName() { return indexVarName; }
	private:
		std::string indexVarName;
//		int lowerBound;
//		int upperBound;
//		int step;
		std::string upperBound;

};

class CArithmetic : public CStatement {
	public:
		CArithmetic(std::string b, std::string t, unsigned int lev, std::string leftS,
						std::string rightS, unsigned int leftD, unsigned int rightD) :
						CStatement(b,t,lev), leftSide(leftS), rightSide(rightS),
						leftDimension(leftD), rightDimension(rightD) {}

		std::string LeftSide() { return leftSide; }
		std::string RightSide() { return rightSide; }
		unsigned int LeftDimension() { return leftDimension; }
		unsigned int RightDimension() { return rightDimension; }
	private:
		std::string leftSide;
		std::string rightSide;
		unsigned int leftDimension;
		unsigned int rightDimension;
};


class CLoop {
	public:
		//konstruktor czyta petle z pliku <in> i tworzy dodatkowy plik z taka sama petla
		//lecz odpowiednimi wyrazeniami arytmetycznyymi w celu znlezienia wszystkich
		//iteracji petli
		CLoop(std::string in);

		~CLoop();

		unsigned int NumberOfStatements() { return statementMap.size(); } //ilosc elementow
		CStatement * operator[] (unsigned int lineNr);

		//F. zwarca typ petli. 0-perfect loop, 1-imperfect loop
		int LoopType();

		//funckja zwraca wsk do wyrazenie bedacego petla o numerze nr
		//liczac od najbardziej zewnetrzenej petli
		CStatement * Loop(unsigned int nr);

		//funkcja zwaraca wsk do wyrazenia bedacego wyrazeniem arytmetycznym o numerze nr
		//liczac od "najwy¿szego" (pierwsze od gory).
		CStatement * Arithmetical(unsigned int nr);

		//F. zwraca wyrazenie znajdujace sie w lini <nr>
		CStatement * Statement(unsigned int nr);

		//F. zwraca numer petli ktorej zmienna indeksowa jest rowna str
		unsigned int LoopNumber(std::string &str);

		//funkcja zwraca numer lini z pliku wejsciowego w ktorej znajduje sie
		//petla lub wyrazenie arytmetyczne o numerze <nr> liczac od gory, w zaleznosci
		//od pierwszego parametru. Jesli str=="for" to zwraca numer poczatku petli, a
		//jesli str=="arithmetical" to zwraca numer wyrazenia arytmetycznego
		unsigned int NumberOfLine(std::string str, unsigned int nr);

		//funkcja zwraca ilosc poczatkwo petli, czyli ilosc zagniezdzonych petli
		unsigned int NumberOfFor();

		//funkcja zwraca numer wymiar, stopien zagniezdzenia, na jakim znajduje sie instrukcja
		//o numerze <nr>
		unsigned int StatementDimension(unsigned int nr);

		//Drukuje zczytana petle
		void Print(char *out=NULL);

		//zwraca zbior zawierajacy wszystkie iteracje w petli
//		Relation CreateAllIterations();
		std::map<int,Relation> CreateAllIterations(char *input=".\\loop.tmp");

		//funckja sparwdza czy analizowana petla zawiera zmienne sparametryzowane
		bool IsParameterized(int nrLoop);
		std::map<unsigned int, std::string> loopIndexNames;
	private:
		std::map<unsigned int, CStatement *> statementMap;


		//nazwy liczb calkowitych, moga sluzyc jako granice petli wiec nalezy je deklarowac
		//w pliku z petla do wykrywania wszystkich iteracji petli
		std::string strIntegers;

		//Funkcja tworzy petle do wyznaczenie wszystkich iteracji w pliku "loop.tmp"
		//Postac wynikowej petli zalezna jest od typu petli (perfect lub nonperfect)
		void CreateLoopForFreeIterations(char *out=NULL);

		CStatement * CreateFor(char *str, unsigned int level);
		CStatement * CreateStatement(char *str, unsigned int level);
		CStatement * CreateEndFor(char *str, unsigned int level);

		//obiekty funkcyjne i funkcje do algorytmow z STL'a
		static bool WhiteSpace(char arg);
		static void DeleteSecondStatement(std::pair<int,CStatement *> arg);

};
