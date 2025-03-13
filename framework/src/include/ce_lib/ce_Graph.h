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
	class GraphWhile : While
	{
        public:

        std::vector<std::string> Inverse_Rownania2; //rownania
        std::vector<std::string> Inverse_Instrukcje2; //instrukcje modyfikacji zmiennych


		GraphWhile()
        {
			agg = 0;
			graph = 1;
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
            //Update = new ArrayList();
            //stworz przepisanie z zmiennych wyjsciowych na wejsciowe
            bool updated = false;
            unsigned int i, j;
            boost::regex reg, tmp;
            string temp = "";

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

                    for (j = 0; j < Instrukcje2[q].size(); j++)
                    {
                        if (Regex_Match(Instrukcje2[q][j], reg))
                        {
                            updated = true;
                            break;
                        }
                    }

                    if (updated)
                    {
                        temp = "";
                        // sprrawdz czy zmienna wejsciowa gdzies jest uzywana - wylaczone
                        tmp.assign(Input[i] + "[^p]");

                        for (j = 0; j < Instrukcje2[q].size(); j++)
                        {
                            if (Regex_Match(Instrukcje2[q][j], tmp))
                            {
                                temp = Input[i] + " = " + Output[i] + ";";
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


		 // engine calego projektu !
        void GenerateWhile(string s)
        {
            unsigned int i, j, j1;
            string temp, var;
            Tab_Space *ctab = new Tab_Space();

            Omega2C *oc = new Omega2C();

            WhileLoop.push_back("");

            WhileLoop.push_back("przelacz = 1;");
            WhileLoop.push_back("while(curr>0)");
            WhileLoop.push_back(ctab->tab + "{");
            ctab->Add();


            WhileLoop.push_back(ctab->tab + "if(przelacz)");
            WhileLoop.push_back(ctab->tab + "{");
            ctab->Add();
            WhileLoop.push_back(ctab->tab + "p_tmp = S_tmp;");
            WhileLoop.push_back(ctab->tab + "p = P;");
            WhileLoop.push_back(ctab->tab + "przelacz--;");
            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");

            WhileLoop.push_back(ctab->tab + "else");
            WhileLoop.push_back(ctab->tab + "{");
            ctab->Add();
            WhileLoop.push_back(ctab->tab + "p_tmp = P;");
            WhileLoop.push_back(ctab->tab + "p = S_tmp;");
            WhileLoop.push_back(ctab->tab + "przelacz++;");
            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");
            WhileLoop.push_back(ctab->tab + "curr_tmp = 0;");
            WhileLoop.push_back(ctab->tab + "");


            var = "while(curr > 0)";
            WhileLoop.push_back(ctab->tab + var);
            WhileLoop.push_back(ctab->tab + "{");
            ctab->Add();

            //przepisanie zmiennych z Tmp->array() do zmiennych
            for (j = 0; j < n; j++)
            {
                var = Input[j] + " = *p++;";
                WhileLoop.push_back(ctab->tab + var);
            }

            //-------------------------
            //tmp = tmp-Next
            var = "curr--;";
            WhileLoop.push_back(ctab->tab + var);

            temp = "ps1(";
            temp += KomaInsert(Input);
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


                temp = "t = &A[ip][jp][kp];";
                WhileLoop.push_back(ctab->tab + temp);
                WhileLoop.push_back(ctab->tab + "if(*t == (char)-1)");
                WhileLoop.push_back(ctab->tab + "{");
                ctab->Add();
                WhileLoop.push_back(ctab->tab + "*t = 0;");
                for (j1 = 0; j1 < R_i.size(); j1++)
                    if (j1 != j)
                    {
                        temp = "if(" + oc->ObliczOgraniczenia(Range_i[j1], true) + ")";
                        WhileLoop.push_back(ctab->tab + temp);
                        ctab->Add();
                        WhileLoop.push_back(ctab->tab + "(*t)++;");
                        ctab->Remove();
                    }
                ctab->Remove();
                WhileLoop.push_back(ctab->tab + "}");
                WhileLoop.push_back(ctab->tab + "else");
                ctab->Add();
                WhileLoop.push_back(ctab->tab + "*t = *t - 1;");
                ctab->Remove();

                WhileLoop.push_back(ctab->tab + "if(*t == (char)0)");
                WhileLoop.push_back(ctab->tab + "{");
                ctab->Add();
                WhileLoop.push_back(ctab->tab + "curr_tmp++;");

                /*
                for (i = 1; i <= Output.Count; i++)
                    WhileLoop.push_back(ctab->tab + "*p_tmp++ = " + Output[i - 1].ToString() + ";");
                */
                for (i = 0; i <= Instrukcje2[j].size() - 1; i++)
                {

                    string temp9 = ctab->tab + "" + Instrukcje2[j][i];
                    boost::regex rg9("^.*=");
                    temp9 = boost::regex_replace(temp9, rg9, "");

                    var = "*p_tmp++ = " + temp9;
                    WhileLoop.push_back(ctab->tab + var);
                }

                ctab->Remove();
                WhileLoop.push_back(ctab->tab + "}");

                ctab->Remove();
                WhileLoop.push_back(ctab->tab + "}");

                // --------

            }

            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");

            var = "curr = curr_tmp;";
            WhileLoop.push_back(ctab->tab + var);

            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");
        }

		// string koma insert
        string KomaInsert(std::vector<std::string> tab)
        {
            unsigned int i;
            string temp = "";

            for (i = 0; i < tab.size(); i++)
            {
                temp += tab[i];

                if (i < n - 1)
                    temp += ",";

            }

            return temp;
        }


		void GenerateLoop()
        {
            boost::regex reg("s1\\(");
            //tab = tmp.Match(s).Captures[0].Value;

            unsigned int i;
            int par = 0, akt_par = -1;


            //Loop = new List<string>();

            for (i = 0; i < LoopUDS.size(); i++)
            {
                if (!Regex_Match(LoopUDS[i], reg))  //normalna linia
                    Loop.push_back(LoopUDS[i]);
                else    //linia z s1
                {
                    if (WhileLoop.size() < 1) //nie stworzono while loopa
                        GenerateWhile(LoopUDS[i]);

                    //Loop.Add(reg_s.Replace(LoopUDS[i], "syn_slice"));

                    string linia = LoopUDS[i];
                    boost::regex tabs("^\\s*");
					string tab_s = GetCaptures(linia,tabs,0);
                    tabs.assign("^\\s*s1\\(");
                    linia = boost::regex_replace(linia, tabs, "");
                    tabs.assign("\\);");
                    linia = boost::regex_replace(linia, tabs, "");
                    tabs.assign(",");

                    std::vector<std::string> pola;
					boost::split(pola, linia, boost::is_any_of(","));

					linia = tab_s;

                    unsigned int i_1;
                    for (i_1 = 0; i_1 < pola.size(); i_1++)
                        linia += "*p=" + pola[i_1] + "; p++; ";

                    linia += "\n" + tab_s + "curr++;";
                    Loop.push_back(linia);


                }  //else

                //szukaj konca petli par for
                if (LoopUDS[i].find("{")!=string::npos)
                    par++;

                if (LoopUDS[i].find("}")!=string::npos)
                    par--;

                if (LoopUDS[i].find("for")!=string::npos && akt_par == -1)
                    akt_par = par;

                if (LoopUDS[i].find("}")!=string::npos && akt_par == par)
                {
                    akt_par = -1;
                    Loop.push_back("    // end of par for");
                }

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

        }

		void aggGenerateWhile(string s)
        {
            unsigned int i, j;
            string temp;
            Tab_Space *ctab = new Tab_Space();
            Omega2C *oc = new Omega2C();

            WhileLoop.push_back("");

            string header = "void Run_slice(struct Tuple * S_tmp)";

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
            var = "struct Tuple *S_nowe, *Tmp;";
            WhileLoop.push_back(ctab->tab + var);

            var = "while(S_tmp != NULL)";
            WhileLoop.push_back(ctab->tab + var);
            WhileLoop.push_back(ctab->tab + "{");
            ctab->Add();
            var = "Tmp = S_tmp;";
            WhileLoop.push_back(ctab->tab + var);
            var = "S_nowe = NULL;";
            WhileLoop.push_back(ctab->tab + var);
            var = "while(Tmp != NULL)";
            WhileLoop.push_back(ctab->tab + var);
            WhileLoop.push_back(ctab->tab + "{");
            ctab->Add();

            //przepisanie zmiennych z Tmp->array() do zmiennych
            for (j = 0; j < n; j++)
            {
                var = Input[j] + " = " + Output[j] + " = Tmp->array[" + intToStr(j) + "];";
                WhileLoop.push_back(ctab->tab + var);
            }

            //-------------------------

            temp = "s1(";

            for (i = 0; i < n; i++)
            {
                temp += Input[i];

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

                // dodaj nowych potomkow do S_nowe

                var = "S_nowe = Add_List(S_nowe, ";

                for (i = 1; i <= n; i++)
                {
                    var += Output[i - 1];
                    if (i < n)
                        var += ", ";
                    else
                        var += ");";
                }
                WhileLoop.push_back(ctab->tab + var);

                // --------

                ctab->Remove();
                WhileLoop.push_back(ctab->tab + "}");


            }


            var = "Tmp = Tmp->next;";
            WhileLoop.push_back(ctab->tab + var);
            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");
            var = "Delete_List(S_tmp);";
            WhileLoop.push_back(ctab->tab + var);
            var = "S_tmp = S_nowe;";
            WhileLoop.push_back(ctab->tab + var);
            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");
            ctab->Remove();
            WhileLoop.push_back(ctab->tab + "}");
        }



		void aggGenerateLoop()
        {
            boost::regex reg("s1\\(");
            boost::regex reg_s("s1\\(");
            boost::regex tmpr;
            string tmp;
            //tab = tmp.Match(s).Captures[0].Value;
            string var_par = "";

            unsigned int i;
            int par = 0, akt_par = -1;


            //Loop = new List<string>();

            for (i = 0; i < LoopUDS.size(); i++)
            {
                if (Regex_Match(LoopUDS[i], reg))  //linia z s1
                {
                    if (WhileLoop.size() < 1) //nie stworzono while loopa
                        aggGenerateWhile(LoopUDS[i]);

                    Loop.push_back(boost::regex_replace(LoopUDS[i], reg_s, "Add_List(S_tmp,"));
                }  //else

                //szukaj konca petli par for
                if (LoopUDS[i].find("{")!=string::npos)
                {
                    par++;
                }

                if (LoopUDS[i].find("for")!=string::npos && akt_par == -1)
                {
                    akt_par = par;


                    tmp = LoopUDS[i];
                    tmpr.assign("^.*for\\(");
                    tmp = boost::regex_replace(tmp, tmpr, "");
                    tmpr.assign("=.*$");
                    tmp = boost::regex_replace(tmp, tmpr, "");
                    var_par = tmp;
                }
                //Loop.Add(par.ToString() + " " + akt_par.ToString() + LoopUDS[i]);

                if (LoopUDS[i].find("}")!=string::npos && akt_par == par)
                {

                    akt_par = -1;
                    Loop.push_back("if(" + var_par + "% chunksize == 0)");
                    Loop.push_back("   Run_slice(S_tmp);");
                }

                if (LoopUDS[i].find("}")!=string::npos)
                    par--;

                if (!Regex_Match(LoopUDS[i], reg))  //normalna linia
                    Loop.push_back(LoopUDS[i]);

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

	};
}
