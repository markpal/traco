#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;


namespace CodeEngine
{

	class SynchClass
	{
		public:

		std::vector<std::string> LoopSlice;
        std::vector<std::string> OutLoops;
        string IndLoop;
        std::vector<std::vector<std::vector<std::string> > > BackVec;
        std::vector<std::vector<std::vector<std::string> > > SupForwVec;
        std::vector<std::string> BackI;
        std::vector<std::vector<std::string> > ForwVec;


		SynchClass()
		{
			o2c = new Omega2C();
		}


        void AddLoopSlice(string loop)
        {
            LoopSlice.push_back(loop);
        }

		void SetIndLoop(string loop)
        {
            IndLoop = loop;
        }

		void AddBackVec(string vec, unsigned int a1, unsigned int a2)
        {

            if (a1 > BackVec.size())
            {
                std::vector<std::vector<std::string > > *tmp = new std::vector<std::vector<std::string > >();
                BackVec.push_back(*tmp);
            }


            if (a2 > BackVec[a1 - 1].size())
            {
                std::vector<std::string > *tmp = new std::vector<std::string >();
                BackVec[a1 - 1].push_back(*tmp);
            }

            BackVec[a1 - 1][a2 - 1].push_back(o2c->ObliczOgr(vec));
            BackI.push_back(Get_I(vec));

        }


        void AddSupForwVec(string vec, unsigned int a1, unsigned int a2)
        {

            if (a1 > SupForwVec.size())
            {
				std::vector<std::vector<std::string > > *tmp = new std::vector<std::vector<std::string > >();
                SupForwVec.push_back(*tmp);
            }


            if (a2 > SupForwVec[a1 - 1].size())
            {
				std::vector<std::string > *tmp = new std::vector<std::string >();
                SupForwVec[a1 - 1].push_back(*tmp);
            }

            SupForwVec[a1 - 1][a2 - 1].push_back(vec);
         //   Console.WriteLine("[][][][]" + vec);

        }

        void AddForwVec(string vec, unsigned int a1)
        {

            if (a1 > ForwVec.size())
            {
                std::vector<std::string > *tmp = new std::vector<std::string >();
                ForwVec.push_back(*tmp);
            }

            vec = o2c->ObliczOgr(vec);
            ForwVec[a1 - 1].push_back(vec);
        }

        string Debug(string a)
        {
			string petla = "";
            _aggl = a == "1" ? 1 : 0;
            petla = GenerateCode();
			return petla;
        }

		string GenerateCode()
		{
            // Console.WriteLine("\n\n//================ " + this._aggl.ToString() +" ==========\n\n\n");

            boost::regex newline_search("\n");
            boost::regex s1_search("s1\\(");
            boost::regex tab("^\\s*");
            string tab_space;
            unsigned int i = 0, j = 0, k = 0, l = 0;
            bool first_for = false;
            string var_agl = "";
            bool newfor_replace = false;
            int n_agl = 0;
			string petla = "";



            // dla kazdej petli loop slice
            for(unsigned int zz=0; zz<LoopSlice.size(); zz++)
            {
                string loop = LoopSlice[zz];
                string outloop = "";
                std::vector<std::string> lines;
                boost::split(lines, loop, boost::is_any_of("\n"));


                for(unsigned int yy=0; yy<lines.size(); yy++)
                {
                    string line = lines[yy];
                    string newfor = "";

                    // kod aglomeracji
                    if (!first_for)
                    {
                        if (line.find("for") != string::npos)
                        {
                            if (_aggl == 1)
                            {
                                boost::regex agl("for[^;]*");
                                //odczytaj numer zmiennej i nazwe
                                if (Regex_Match(line, agl))
                                    var_agl =  GetCaptures(line, agl, 0);

                                var_agl = ReplaceStr(var_agl, "for(", "");
                                agl.assign("=.*");
								var_agl = boost::regex_replace(var_agl, agl, "");
                                agl.assign("\\s");
                                var_agl = boost::regex_replace(var_agl, agl, "");
                                //Console.WriteLine(var_agl);

                                //odczytaj granice
                                boost::regex bounds("\\s[^(\\s)|(;)]*;");
                                string str_ub = "", str_lb = "";
                                unsigned int z;
                                for (z = 0; z <= Count_Captures(line, bounds) - 1; z++)
                                {
                                    if (z == 0)
                                        str_lb = GetCaptures(line, bounds, z);
                                    if (z == 1)
                                        str_ub = GetCaptures(line, bounds, z);

                                }

                                boost::regex tmp_z("(;)|(\\s)|(>)|(<)|(=)");
                                str_lb = boost::regex_replace(str_lb, tmp_z, "");
                                str_ub = boost::regex_replace(str_ub, tmp_z, "");
                                //Console.WriteLine(str_lb + " " + str_ub);

                                boost::regex rest("[^;]*$");
                                string str_rest = "";
                                if (Regex_Match(line, rest))
                                    str_rest = GetCaptures(line, rest, 0);

                                newfor = "for(" + var_agl + " = lb; " + var_agl + " <= ub; " + str_rest;

                                agl_head = "par for(w = 1; w <= z; w++){\n  pack = ((" + str_ub + "-" + str_lb + ")+1)/z;\n  lb = pack *(w-1)+" + str_lb + ";\n  if(w==z)\n    ub = " + str_ub + ";\n  else\n    ub = pack *w;\n\n";

                                //Console.WriteLine(newfor);

                                //aglomeracja
                                newfor_replace = true;
                            }
                            else
                            {
                                string line2 = line;
                                boost::regex tr("^\\s*");
                                line2 = boost::regex_replace(line, tr, "");
                                line2 = "par " + line2;
                                //if(0)
								//  Console.WriteLine(line2);
								petla += line2 + "\n";

                            }
                            first_for = true;
                        }
                    }

                    // -----------------

                    if (Regex_Match(line, s1_search))
                    {
                        //wstaw if i recv jesli jest rozny od false

                        //kod aglomeracja
                        if (line.find(var_agl) != string::npos && first_for)
                        {
                            string tmp_a = "";
                            boost::regex agl_tmp(".*" + var_agl);
                            if (Regex_Match(line, agl_tmp))
                            {
                                    tmp_a = GetCaptures(line, agl_tmp, 0);
                                    int ii = 1;
                                    for(unsigned int xx=0; xx<tmp_a.size(); xx++)
                                    {
                                        char c = tmp_a[xx];
                                        if (c == ',')
                                            ii++;
                                    }
                                    n_agl = ii;


                            }
                        }

                                // ------------

                        tab_space = GetCaptures(line, tab, 0);

                        if (BackVec.size() > 0)
                        {

                            for (l = 0; l < BackVec[i][j].size(); l++)
                            {

                                if (!BackVec[i][j][l].find("FALSE") != string::npos)
                                {
                                    cout << "ppppp" <<BackVec[i][j][l];

                                    //aglomeracja
                                    string warunek = "";

                                    string h = BackI[k];
                                    std::vector<std::string> h1;
                                    boost::split(h1, h, boost::is_any_of(","));

                                    string w1 = h1[n_agl - 1];
                                    //if(this._aggl==1)
                                    //    Console.WriteLine(w1 + "o");

                                    warunek += " && !(" + w1 + ">=lb && " + w1 + " <= ub)";

                                    if(_aggl == 0)
                                        warunek = "";
                                    // ------------

                                    BackVec[i][j][l] = ReplaceStr(BackVec[i][j][l],":", "");
                                    outloop += tab_space + "if(" + BackVec[i][j][l] + warunek + ")\n";
                                    outloop += tab_space + "   " + "recv(" + BackI[k] + ");\n";
                                }
                                k++;

                            }
                        }

                        outloop += line + "\n";


                        //wstaw send
                        if (ForwVec.size() > 0)
                        {
                            if (!(ForwVec[i][j].find("FALSE")!=string::npos))
                            {
                                //aglomeracja
                                string warunek = "";
                                for (l = 0; l < SupForwVec[i][j].size(); l++)
                                {

                                    if (!SupForwVec[i][j][l].find("FALSE") != string::npos)
                                    {


                                        if (warunek != "")
                                            warunek += " || ";

                                        string h = SupForwVec[i][j][l];
                                        boost::regex reg("\\[.*\\]");
                                        h = GetCaptures(h, reg, 0);

                                        reg.assign("(\\[)|(\\])");
                                        h =  boost::regex_replace(h, reg, "");
                                        std::vector<std::string> h1;
                                        boost::split(h1, h,  boost::is_any_of(","));
                                        string w1 = h1[n_agl - 1];

                                        //if (this._aggl==1)
                                        //   Console.WriteLine(w1);

                                        warunek += "!(" + w1 + ">=lb && " + w1 + " <= ub)";

                                        if (_aggl == 0)
                                            warunek = "";


                                    }

                                }
                                if (warunek != "")
                                    warunek = " && ( " + warunek + " ) ";

                                // -------------

                                ForwVec[i][j] = ReplaceStr(ForwVec[i][j],":", "");
                                outloop += tab_space + "if(" + ForwVec[i][j] + warunek + ")\n";
                                outloop += "   " + ReplaceStr(line, "s1", "send") + "\n";
                            }
                        }

                        j++;


                    }
                    else
                    {
                        if (newfor_replace)
                            outloop += newfor + "\n";
                        else
                            outloop += line + "\n";
                        newfor_replace = false;

                    }


                }

                i++;
                j = 0;

                //aglomeracja
                outloop = agl_head + outloop + "}";

                //if(0)
                 //  Console.WriteLine(outloop);
				petla += outloop + "\n";

                OutLoops.push_back(outloop);

            }

            if (!IndLoop.find("FALSE") != string::npos)
            {
               // Console.WriteLine("//======== Independent iterations ===");
				//if(0)
				petla += IndLoop + "\n";
                //Console.WriteLine(this.IndLoop);
                OutLoops.push_back(IndLoop);
            }


			return petla;

        }

		private:

		Omega2C *o2c;
        string agl_head;
        int _aggl;

		string Get_I(string input)
        {
            boost::regex reg2("\\[[^\\]]*\\]");
            string tmp = "";

            if (Regex_Match(input, reg2))
            {
                tmp = GetCaptures(input, reg2, 0);
                tmp = ReplaceStr(tmp, "[", "");
                tmp = ReplaceStr(tmp, "]", "");
            }

            return tmp;

        }


	};
}
