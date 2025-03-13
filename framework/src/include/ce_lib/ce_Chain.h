#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



namespace CodeEngine
{
	class ChainWhile : CodeEngine::While
	{
		public:

		// stale
		string while_block_file;
		string output_file;

		//Konstruktor
        ChainWhile()
        {
            /*Input = new ArrayList();
            Output = new ArrayList();
            Rownania = new ArrayList();
            Instrukcje = new ArrayList();

            Update = new ArrayList();
            Bounds = new ArrayList();
            LoopUDS = new List<string>();
            LoopIND = new List<string>();
            R_i = new List<string>();
            Domain_i = new List<string>();
            WhileLoop = new List<string>();
			*/
            //Omega2C oc = new Omega2C();

			while_block_file = "While_Blocks.txt";
			output_file = "generated.txt";

			agg = 0;
			graph = 0;
        }


        void _AddElement(std::string Where, std::string Data)
        {
            AddElement(Where, Data);

        }

        string _OneRun()
        {
            return OneRun();

        }

		 //zwraca instrukcje przepisania wyjsciowych na wejsciowe
        std::vector<std::string> UpdateInstr(int q)
        {
            //stworz przepisanie z zmiennych wyjsciowych na wejsciowe
			bool updated = false;
            unsigned int i, j, l;
            boost::regex reg, tmp;
            string temp = "";

            Update.clear();

			for (i = 0; i < Input.size(); i++)
            {
				if (q == -1)
                {   //dodawaj wszystkie
                    temp = Input[i] + " = " + Output[i] + ";";
                    Update.push_back(temp);
                }
				else
                {
					reg.assign("^\\s*" + Output[i]);

					 for (l = 0; l < Instrukcje2.size(); l++)
                        for (j = 0; j < Instrukcje2[l].size(); j++)
                        {
                            if (Regex_Match(Instrukcje2[l][j], reg))
                            {
                                updated = true;
                                break;
                            }
                        }

					if (updated)
                    {
                        temp = "";
                        // sprrawdz czy zmienna wejsciowa gdzies jest uzywana
                        //tmp = new Regex(Input[i].ToString()+ "[^p]");
                        tmp.assign(Output[i]);

                        for (l = 0; l < Instrukcje2.size(); l++)
                            for (j = 0; j < Instrukcje2[l].size(); j++)
                            {
                                if (Regex_Match(Instrukcje2[l][j], tmp))
                                {
                                    temp = Input[i] + " = " + Output[i] + ";";
                                    l = Instrukcje2.size() + 1;
                                    break;
                                }
                            }

                        if (temp != "")
                            Update.push_back(temp);
                    }

                    updated = false;
                }
            } //for

			return Update;
		}






        void GenerateWhile(string s)
        {
            unsigned int i, j;
            string temp;
            Tab_Space *ctab = new Tab_Space();
			Omega2C *oc = new Omega2C();

			WhileLoop.push_back("");

			string header = "void while_body(";

			for (i = 1; i <= n; i++)
            {
                header += "int t" + intToStr(i);
                if (i < n)
                    header += ", ";
            }
            header += ")";

			WhileLoop.push_back(ctab->tab + header);
            WhileLoop.push_back(ctab->tab + "{");
            ctab->Add();

			// ---------------
            // dodaj deklaracje zmiennych

            string var = "int ";

            for (j = 1; j <= n; j++)
                var += Input[j - 1] + ", ";

            for (j = 1; j <= n; j++)
            {
                var += Output[j - 1];
                if (j < n)
                    var += ", ";
                else
                    var += ";";
            }

            WhileLoop.push_back(ctab->tab + var);

            //-------------------------

			//dodaj przepisania = zamiast funkcji wartosci pocczatkowe
            for (j = 1; j <= n; j++)
                WhileLoop.push_back(ctab->tab + Output[j - 1] + " = " + Input[j - 1] + " = " + "t" + intToStr(j) + ";");


            WhileLoop.push_back(ctab->tab + "do");
            WhileLoop.push_back(ctab->tab + "{");
            ctab->Add();

			temp = "s1(";

            for (i = 0; i < n; i++)
            {
                temp += Output[i];

                if (i < n - 1)
                    temp += ",";

            }

            temp += ");";

			WhileLoop.push_back(ctab->tab + temp);

			for (j = 0; j < R_i.size(); j++)
            {
                //warunek if
                temp = "if(" + oc->ObliczOgraniczenia(Domain_i[j], false) + ")";
                WhileLoop.push_back(ctab->tab + temp);
                WhileLoop.push_back(ctab->tab + "{");
                ctab->Add();

                for (i = 0; i < Instrukcje2[j].size(); i++)
                {
                    WhileLoop.push_back(ctab->tab + "" + Instrukcje2[j][i]);
                }

                UpdateInstr(j);

                for (i = 0; i < Update.size(); i++)
                {
                    WhileLoop.push_back(ctab->tab + "" + Update[i]);
                }


                WhileLoop.push_back(ctab->tab + "continue;");
                ctab->Remove();
                WhileLoop.push_back(ctab->tab + "}");
            }

			WhileLoop.push_back(ctab->tab + "break;");
            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");
            WhileLoop.push_back(ctab->tab + "while(true);");
            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");


		}

		void GenerateLoop()
        {
            boost::regex reg("s1\\(");
            boost::regex reg_s("s1");
            //tab = tmp.Match(s).Captures[0].Value;

			unsigned int i;

			for (i = 0; i < LoopUDS.size(); i++)
            {

				if (!Regex_Match(LoopUDS[i], reg))  //normalna linia
				{
				//	Console.WriteLine("\n!!!!" + LoopUDS[i] + "!!!\n");
                    Loop.push_back(LoopUDS[i]);
				}
                else    //linia z s1
                {
                    if (WhileLoop.size() < 1) //nie stworzono while loopa
                        GenerateWhile(LoopUDS[i]);

                    Loop.push_back(boost::regex_replace(LoopUDS[i], reg_s, "while_body"));
                }  //else

            }  //for


            //wylaczylem przy pisaniu reedsa
            //IntMod2C();   //zmien intMod() na %

            if (LoopIND.size() > 0)
            {
                Loop.push_back("// Niezalezne iteracje");
                for (i = 0; i < LoopIND.size(); i++)
                    Loop.push_back(LoopIND[i]);
            }

            Loop.push_back("");
            Loop.push_back("");

            for(i = 0; i<WhileLoop.size(); i++)
                Loop.push_back(WhileLoop[i]);

        } // GenerateLoop()



		// generowanie samego while na potrzeby R'
        void GenerateSingleWhileLoop()
        {
            // !!!!!!!!!!! ONE RUN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


            Init_Job();
            Load_Variable();

            //this.WybierzRownania(this.Relation);  //chyba dla rq  a ograniczenia tylko dla range

            for (unsigned int i = 0; i < R_i.size(); i++)
                Rownania2[i] = WybierzRownania(R_i[i]);

            //this.Rownania2Instrukcje(this.Rownania); //chyba do rq

            for (unsigned int i = 0; i < R_i.size(); i++)
                Instrukcje2[i] = Rownania2Instrukcje(Rownania2[i], true);

            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            GenerateWhile("");

			ofstream myfile;
			myfile.open (while_block_file.c_str(), ios::app);

			for(unsigned int i=0; i < WhileLoop.size(); i++)
				myfile << WhileLoop[i] << endl;

			myfile.close();

        }

		string GenerateAggregatedWhileLoop(int first, int last)
		{
            std::vector<std::string> While_Block_Lines;
            boost::regex find_int("[^_]int");
            boost::regex find_while("while");
            boost::regex s1("^\\s*s1\\(");
            boost::regex s_end("\\);\\s*$");
            boost::regex koma(",");
			boost::regex blank_start("^\\s*");
            string line;
            unsigned int i;
			ifstream sr(while_block_file.c_str());
			ofstream sw;
			string petla = "";


			while(sr)
			{
				std::getline(sr, line);
				While_Block_Lines.push_back(line);
				cout << line << endl;
			}
			sr.close();

            remove(while_block_file.c_str());

		//	sw.open(while_block_file.c_str());

			//remove(while_block_file.c_str());

			//sw.open(while_block_file.c_str());

			if (first == 1)
            {
               // remove(output_file.c_str());

                for (i = 0; i < While_Block_Lines.size(); i++)
                {

                    if (Regex_Match(While_Block_Lines[i], find_int) && !Regex_Match(While_Block_Lines[i], find_while))
                    {

					//	cout << "pppppppppppppppppppppppppppppppppppp";
					//	cout << output_file;
						sw.open(output_file.c_str());
                        string dekl = While_Block_Lines[i];

                        dekl = boost::regex_replace(dekl, blank_start, "");
                        sw << dekl << endl;
                        cout << dekl << endl;

                        //sw.close();


						petla += dekl + "\n";
                        sw << "" << endl;
						petla += "\n";
                        break;
                    }
                }
            }
            else
            {
                sw.open(output_file.c_str(), ios::app);
            }


			for (i = 0; i < LoopUDS.size(); i++)
            {
                line = LoopUDS[i];
                //Console.WriteLine(line);

                if (Regex_Match(line, s1))
                {
					int was_do = 0, l = 0;
					string tab_start = GetCaptures(line,blank_start,0);


					line = boost::regex_replace(line, s1, "");
					line = boost::regex_replace(line, s_end, "");

					std::vector<std::string> I;

					boost::split(I, line, boost::is_any_of(","));

					while (While_Block_Lines.size() > 0 && While_Block_Lines[0] != "##-##")
					{
						string dekl1 = While_Block_Lines[0];

						if (dekl1.find("do") != string::npos)
						{
							was_do = 1;
						}

						if (was_do == 0 && dekl1.find(";") != string::npos && dekl1.find("=") != string::npos)
                        {
                            boost::regex rval("[^\\s]*;");
                            dekl1 = boost::regex_replace(dekl1, rval, I[l] + ";");
                            l++;

                            While_Block_Lines[0] = dekl1;
                        }

						if (!Regex_Match(While_Block_Lines[0], find_int) && !(While_Block_Lines[0].find("while") != string::npos) && While_Block_Lines[0].size() > 0)
						{
                            sw << tab_start + While_Block_Lines[0] << endl;
							petla += tab_start + While_Block_Lines[0] + "\n";
						}
                        if (While_Block_Lines[0].find("while(true)") != string::npos)
						{
                            sw << tab_start + While_Block_Lines[0] << endl;
							petla += tab_start + While_Block_Lines[0] + "\n";
						}

						While_Block_Lines.erase(While_Block_Lines.begin());

					}

				if (While_Block_Lines.size() > 0)
                    if (While_Block_Lines[0] == "##-##")
                         While_Block_Lines.erase(While_Block_Lines.begin());

                }
                else
				{
                    sw << LoopUDS[i] << endl;
					petla += LoopUDS[i] + "\n";
				}

            }

			if (last == 1)
            {
                for(unsigned int i=0; i < LoopIND.size(); i++)
				{
					sw << LoopIND[i] << endl;
					petla += LoopIND[i] + "\n";
				}

            }

			sw.close();
			return petla;
		}


	};
}
