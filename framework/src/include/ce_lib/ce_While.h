#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;


namespace CodeEngine
{
	class While
	{

	//pola
	public:

		int agg;
		int graph;

        string Relation;
        unsigned int n;  //ilosc zmiennych
        std::vector<std::string> Input;  //zmienne wejsciowe
        std::vector<std::string> Output; //zmienne wyjsciowe

        std::vector<std::string> Rownania; //rownania
        std::vector<std::string> Instrukcje; //instrukcje modyfikacji zmiennych

        std::vector<std::vector<std::string> > Rownania2; //rownania
        std::vector<std::vector<std::string> > Instrukcje2; //instrukcje modyfikacji zmiennych

        std::vector<std::string> Update; //instrukcje przepisania zmiennych
        std::vector<std::string> Bounds;
        string Parameters;
        bool Parametrizied;
        string OldRelation; //przed wywaleniem Relation

        std::vector<std::string> LoopUDS;
        std::vector<std::string> LoopIND; //pêtla niezaleznych iteracji
        std::vector<std::string> WhileLoop;  //sama petla while
        std::vector<std::string> Loop;  //ostateczna petla
        std::vector<std::string> R_i; //skladowe R
        std::vector<std::string> Domain_i;  //range Ri
		std::vector<std::string> Range_i;  //range Ri

        string MathCmd;
        string MathOut;

        string test;
        int Rq;




		//metody

		std::vector<std::string> WybierzRownania(string Rel)
		{
			unsigned int j;
			std::vector<std::string> rownania;
			// znajdz rownosci  dziala tylko z &&

			boost::regex reg("(&&|\\])[^&]+"), tmp;

			for (j = 0; j < Count_Captures(Rel, reg); j++)
			{
				 string temp = GetCaptures(Rel, reg, j);
			//	 cout << temp;

				 tmp.assign("(^.*\\])|\\}|&&");
				 temp = regex_replace(temp, tmp, "");

				 tmp.assign("\\s=\\s"); //szuklaj rownania, jesli posiadaja znak rownosci oddzielonych spacjami, czyli wykuczamy nierownosci nieostre
				 if(Regex_Match(temp, tmp))
				 {
					 rownania.push_back(temp);
				 }
			}
//cout << "ppppp " <<Count_Captures(Rel, reg)<< endl;
	//		for(j=0; j<rownania.size(); j++)
		//	   cout << rownania[j] << endl;
       //     exit(0);

			return rownania;
		}

		// uzyskuje zmienne wejsciowe i wyjsciowe z relacji glownej
		void Load_Variable()
		{
			cout <<"Load Variable";

			unsigned int i, j;

			boost::regex regt("Derivative\\[1\\]\\[.\\]");
			Relation = boost::regex_replace(Relation, regt, "0");

			boost::regex reg("\\[[^\\]]*\\]");  //znajdz [...]    2x

			for (i = 0; i < Count_Captures(Relation, reg); i++)   //i=0 pierwsze nawiasy kamrowe, i=1 drugie nawiasy klamrowe
			{
				string zmienne = GetCaptures(Relation, reg , i);

				boost::regex tmp(",");

				n = Count_Captures(zmienne, tmp) + 1;

				tmp.assign("\\[");
				zmienne = boost::regex_replace(zmienne, tmp, "");
				tmp.assign("\\]");
				zmienne = boost::regex_replace(zmienne, tmp, "");


				for (j = 0; j < n; j++)
                {
					string x;
					tmp.assign("^[^,]*,");

					if (j < n - 1)
						x = GetCaptures(zmienne, tmp , 0);
					else
						x = zmienne;

					boost::replace_all(x, ",", "");

					if (i == 0) //zmienne wejsciowe
                        Input.push_back(x);
                    else //zmienne wyjsiowe
                        Output.push_back(x);

                    zmienne = boost::regex_replace(zmienne, tmp, "");


				}

			}
		}

		std::vector<std::string> Rownania2Instrukcje(std::vector<std::string> rownania, bool remove)
		{
			//skonstruuj mathematica
			unsigned int i, j;
			boost::regex reg, tmp;
			string MathOutput;
			std::vector<std::string> instrukcje;

			MathCmd = "Format[Solve[";

			for (i = 0; i < rownania.size(); i++)
            {
                MathCmd += ReplaceStr(rownania[i],":", "");
				if (i != rownania.size() - 1)
                    MathCmd += "&&";
			}

			MathCmd += ",{";

			for (i = 0; i < Output.size(); i++)  //obliczamy po zmiennych wyjsciowych, gdyz to one dyktuja nastpeny krok iteracji
                MathCmd += Output[i] + ",";

            for (i = 0; i < Input.size(); i++)
                MathCmd += Input[i] + ",";

            if (!Parametrizied)
                MathCmd = MathCmd.erase(MathCmd.size() - 1);
            else
                MathCmd += Parameters;

            MathCmd += "}], InputForm]";

            tmp.assign("=");

            MathCmd = boost::regex_replace(MathCmd, tmp, "==");

            // math - gotowe

			Mathematica *ml = new Mathematica();
            MathOutput = ml->Calc(MathCmd);

            // obliczono

            reg.assign("->");
            MathOutput = boost::regex_replace(MathOutput, reg, "=");

            reg.assign("\\{|\\}");
            MathOutput = boost::regex_replace(MathOutput, reg, "");

            reg.assign("[^,]*,");
            bool add = true;


            for (i = 0; i < Count_Captures(MathOutput, reg); i++)
            {
                instrukcje.push_back(GetCaptures(MathOutput, reg, i));
            }

            MathOutput = boost::regex_replace(MathOutput, reg, "");
            instrukcje.push_back(MathOutput);


            //usun instrukcje ktore nie przypisuja do zmiennych wyjsciowych
            for (i = 0; i < instrukcje.size(); i++)
            {

                reg.assign("p[^=]=");
                if (!Regex_Match(instrukcje[i], reg))
                {
                    instrukcje.erase(instrukcje.begin()+i);
                    i = 0;
                }
            }

            // przygotuj instrukcje usun p[rzecinki spacje dodaj srednik zastap i na ip
            for (i = 0; i < instrukcje.size(); i++)
            {
                instrukcje[i] = ReplaceStr(instrukcje[i],",", "");
                reg.assign("(^\\s*)|(\\s*$)");
                instrukcje[i] = boost::regex_replace(instrukcje[i], reg, "");
                instrukcje[i] = instrukcje[i] + ";";

            }

            //sp[rawdz czy ta instruykcja nie jest jp = j;
            if (remove)
                for (i = 0; i < instrukcje.size(); i++)
                {
                    add = true;
                    for (j = 0; j < Input.size(); j++)
                    {
                        tmp.assign(Output[j] + "\\s*=\\s*" + Input[j] + "\\s*;");
                        if (Regex_Match(instrukcje[i], tmp))
                        {
                            add = false;
                            break;
                        }
                    }
                    if (!add)
                    {
                        instrukcje.erase(instrukcje.begin()+i);
                        i = 0;
                    }
                }

//exit(0);
			return instrukcje;


		}

		void Init_Job()
		{
            cout <<"Init Job"<<endl;

            try
            {
                int q = R_i.size();
                Omega2C *oc = new Omega2C();

				//zmienne symboliczne
                GetSymbolic();

				//exists
                Relation = oc->RemoveExists(Relation);

                for (unsigned int i = 0; i < R_i.size(); i++)
                {
                    R_i[i] = oc->RemoveExists(R_i[i]);

                    Domain_i[i] = oc->RemoveExists(Domain_i[i]);
					if(graph)
						Range_i[i] = oc->RemoveExists(Range_i[i]);
                }


                //prim
                boost::regex reg("'");
                Relation = boost::regex_replace(Relation, reg, "p");  //zast¹p ' na p
                for (unsigned int i = 0; i < R_i.size(); i++)
                {
                    R_i[i] =  boost::regex_replace(R_i[i], reg, "p");
                }

                Rq = q;


				//zainicjuj zmienne dla Ri

                for(int qq = 0; qq < q; qq++)
                {
                    std::vector<std::string > *tmp = new std::vector<std::string >();
                    Rownania2.push_back(*tmp);

                    tmp = new std::vector<std::string >();
                    Instrukcje2.push_back(*tmp);

                //    tmp = new std::vector<std::string >();
                //    Inverse_Rownania2.push_back(tmp);

                 //   tmp = new std::vector<std::string >();
                 //   Inverse_Instrukcje2.push_back(tmp);



                }


                /*
                Rownania2 = new ArrayList[q];
                Instrukcje2 = new ArrayList[q];


				Inverse_Rownania2 = new ArrayList[q];
				Inverse_Instrukcje2 = new ArrayList[q];

                for (int i = 0; i < q; i++)
                {
                    Rownania2[i] = new ArrayList();
                    Instrukcje2[i] = new ArrayList();
                }
				            for (int i = 0; i < q; i++)
				{
					Inverse_Rownania2[i] = new ArrayList();
					Inverse_Instrukcje2[i] = new ArrayList();
				}
*/

			}
            catch (int e)
            {
                cout << "error";
            }

		}

		void GetSymbolic()
		{
            string temp;
            OldRelation = Relation;
            boost::regex reg("Sym[^\\]]*\\]");

            Parametrizied = Regex_Match(Relation, reg);
            if (Parametrizied)
            {
                temp = GetCaptures(Relation, reg, 0);
                reg.assign("(Sym)|\\[|\\]|=");
                Parameters = boost::regex_replace(temp, reg, "");
            }

            reg.assign("Sym[^\\]]*\\]");
            Relation = boost::regex_replace(Relation, reg, "");

            //usun Sym[] tez z relacji skladowych
            for (unsigned int i = 0; i < R_i.size(); i++)
            {
                R_i[i] = boost::regex_replace(R_i[i], reg, "");
                Domain_i[i] = boost::regex_replace(Domain_i[i], reg, "");
				if(graph)
					Range_i[i] = boost::regex_replace(Range_i[i], reg, "");
            }
		}

		string OneRun()
        {
            Init_Job();

            Load_Variable();


			string petla = "";

            //this.WybierzRownania(this.Relation);  //chyba dla rq  a ograniczenia tylko dla range

            for (unsigned int i = 0; i < R_i.size(); i++)
            {
              //  cout << i <<  R_i[i] << endl;
                Rownania2[i] = WybierzRownania(R_i[i]);
            }
                //


            //this.Rownania2Instrukcje(this.Rownania); //chyba do rq

            for (unsigned int i = 0; i < R_i.size(); i++)
                Instrukcje2[i] = Rownania2Instrukcje(Rownania2[i], true);




            if (agg == 1)
                aggGenerateLoop();
            else
                GenerateLoop();

			for(unsigned int i=0; i<Loop.size(); i++)
                petla += Loop[i] + '\n';

			return petla;
        }

		std::string AddElement(std::string Where, std::string Data)
        {
            if(Where == "#Relacja")
				Relation = Data;
			if(Where == "#Loop_UDS")
                boost::split(LoopUDS, Data, boost::is_any_of("\n"));
			if(Where == "#Loop_IND")
            {
                if (Data.find("FALSE") != string::npos)
                { }
                else
                   LoopIND.push_back(Data);
            }
			if(Where == "#R_i")
			{
			   // cout << "addelement" << Data;
			    R_i.push_back(Data);
			  //  cout << R_i[0];
			}

			if(Where == "#Domain_i")
				Domain_i.push_back(Data);
			if(Where == "#Range_i")
				Range_i.push_back(Data);

			return "=====";
        }

		virtual void aggGenerateLoop(){};
		virtual void GenerateLoop(){};
		virtual ~While(void){};


	};


}
