#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#define BARVINOK_COMMAND "./barv_script"
#define BARVINOK_INPUT "barvinok_input"
#define BARVINOK_OUTPUT "ppp"

#define OMEGAPLUS_COMMAND "./omegaplus_script"
#define OMEGAPLUS_INPUT "omegaplus_input"
#define OMEGAPLUS_OUTPUT "omegaplus_output"


// 0 omega, 1 barvinok, 2 omga+


#define LOCKFILE "lock"


using namespace std;

string BarvinokCalc(const char* cmd, const char* out);

std::string Omega2Barvinok(std::string input)
{
	//{ Sym=[t1,t2] [i,j] : Exists ( alpha,beta : i+t1+2beta = 0 && j+t2+2alpha = 0 && 1 <= t2 <= j <= n && t1+2 <= i <= n && 1 <= t1)
	//OR Exists ( alpha : j+t2 = 2alpha && i = t1 && t2+2 <= j <= n && 1 <= t1 <= n && 1 <= t2) OR && j = t2 && i = t1 }

	boost::replace_all(input, "&&", "and");
	boost::replace_all(input, "OR", ") or (");
	boost::replace_all(input, "{", "");
	boost::replace_all(input, "}", ") }");
	boost::replace_all(input, "Exists", "exists");


	boost::regex regex("Sym=[^]]*] ", boost::regex::icase);

	if(Regex_Match(input, regex))
	{
		string withoutarrow = GetCaptures(input, regex, 0);
		string addarrow = withoutarrow + "-> { ";
		boost::replace_all(input, withoutarrow, addarrow);
		boost::replace_all(input, "Sym=", "");

	}
	else
	   input = "{" + input;

    boost::replace_all(input, "] :", "] : (");

	return input;
}

// c_str() return as String
std::string BarvinokCodegen(Relation T)
{
  ofstream myfile;
  remove(BARVINOK_INPUT);
  myfile.open (BARVINOK_INPUT);

  myfile << "P:= " << Omega2Barvinok(Str2string(R2String(T))) << ";" << endl;
  myfile << "codegen P;" << endl;
  myfile.close();

  return BarvinokCalc(BARVINOK_COMMAND, BARVINOK_OUTPUT);
}

// c_str() return as String
// funkcja liczy Card
std::string Card(Relation T)
{
  ofstream myfile;
  remove(BARVINOK_INPUT);
  myfile.open (BARVINOK_INPUT);
  myfile << "P:= " << Omega2Barvinok(Str2string(R2String(T))) << ";" << endl;
  myfile << "card P;" << endl;
  myfile.close();

  return BarvinokCalc(BARVINOK_COMMAND, BARVINOK_OUTPUT);
}

bool CardCompare(Relation T1, Relation T2)
{
  std::string out1, out2;
  ofstream myfile;
  remove(BARVINOK_INPUT);
  myfile.open (BARVINOK_INPUT);
  myfile << "P1:= " << Omega2Barvinok(Str2string(R2String(T1))) << ";" << endl;
  myfile << "P2:= " << Omega2Barvinok(Str2string(R2String(T2))) << ";" << endl;
  myfile << "card P1;" << endl;
  myfile.close();

  out1 = BarvinokCalc(BARVINOK_COMMAND, BARVINOK_OUTPUT);

  remove(BARVINOK_INPUT);
  myfile.open (BARVINOK_INPUT);
  myfile << "P1:= " << Omega2Barvinok(Str2string(R2String(T1))) << ";" << endl;
  myfile << "P2:= " << Omega2Barvinok(Str2string(R2String(T2))) << ";" << endl;
  myfile << "card P2;" << endl;
  myfile.close();

  out2 = BarvinokCalc(BARVINOK_COMMAND, BARVINOK_OUTPUT);

  boost::regex tmp("^.*\\{");
  out1 = boost::regex_replace(out1 , tmp, "");
  out2 = boost::regex_replace(out2 , tmp, "");
  tmp.assign(":.*$");
  out1 = boost::regex_replace(out1 , tmp, "");
  out2 = boost::regex_replace(out2 , tmp, "");

  cout << out1 << endl << out2 << endl;

  return out1 == out2;
}

string BarvinokCalc(const char* cmd, const char* out)
   		{
			remove(LOCKFILE);

			string sRes = "", sww="";
			int i = 0;
			try
			{
		        // execute script
                system(cmd);

		        //get data
		        while(1)
		        {
		            ifstream ifile(LOCKFILE);

                    if (ifile)
                       break;

                    usleep(100000);

                    i++;
                    if(i>50)
                    {
                        cout << "Error! Too long!" << endl;
                        exit(1);

                    }
		        }

                ifstream _reader(out);

                while(_reader)
                {
                    std::getline(_reader, sRes);
                    boost::replace_all(sRes, "for (", "for(");
                    //cout << sRes;
                    if(sRes.find(">>>") == string::npos && sRes != "")
                    {
                        boost::replace_all(sRes, "s0(", "s1(");
                        boost::replace_all(sRes, "S1(", "s1(");
                        boost::replace_all(sRes, "  (", "  s1(");
                        boost::replace_all(sRes, ", ", ",");
                        boost::replace_all(sRes, "int ", "");
                        sww += sRes + "\n";
                    }

               //     if(sRes.find("Out[1]=") != string::npos)
               //     {
               //          boost::replace_all(sRes, "Out[1]= ", "");
                //         sww = sRes;

                //    }

                }
                _reader.close();

			}
            catch( char * str ) {
                cout << "Exception raised: " << str << '\n';
            }

		//	cout << sww << endl;
			return sww;

		}






	//std::string out = "P := [n,m] -> { [i,j] : 0 <= i <= n and i <= j <= m };";

	//std::string in = "{ Sym=[t1,t2,n] [i,j] -> [i] : Exists ( alpha,beta : i+t1+2beta = 0 && j+t2+2alpha = 0 && 1 <= t2 <= j <= n && t1+2 <= i <= n && 1 <= t1) OR Exists ( alpha : j+t2 = 2alpha && i = t1 && t2+2 <= j <= n && 1 <= t1 <= n && 1 <= t2) OR j = t2 && i = t1 }";



// ------------------------------------------------------------------------------------------------------------
// OMEGA +


//relation.print pobrac sym= i dodac symbolic
// print_with_subs i przekazac do omega+ pobrac wynik kasujac puste linie i >>>>


std::string OmegaPlusCodegen(Relation S)
{
   std::string rel = Str2string(S.print_with_subs_to_string(true, true));
   cout << rel;
   std::vector<std::string> symb;

   boost::regex regex("Sym=[^]]*] ", boost::regex::icase);

   if(Regex_Match(rel, regex))
   {
      string symbolic = GetCaptures(rel, regex, 0);
      boost::replace_all(symbolic, "Sym=[", "");
      boost::replace_all(symbolic, "]", "");


      boost::split(symb, symbolic, boost::is_any_of(","));

      for(unsigned int i = 0; i < symb.size(); i++)
      {
          boost::replace_all(symb[i], " ", "");
          symb[i] = "symbolic " + symb[i] + ";";
          //cout << symb[i] << endl;

      }


  }

  ofstream myfile;
  remove(OMEGAPLUS_INPUT);
  myfile.open (OMEGAPLUS_INPUT);

  for(unsigned int i = 0; i < symb.size(); i++)
     myfile << symb[i] << endl;

  myfile << "P:= " << Str2string(S.print_with_subs_to_string(false, false)) << ";" << endl;
  myfile << "codegen P;" << endl;
  myfile.close();

  return BarvinokCalc(OMEGAPLUS_COMMAND, OMEGAPLUS_OUTPUT);


}


// Generowanie petli - codegen
// parametry
// S - set
// n stopien generowania kodu

String LoopCodeGen(Relation S, int n)
{

	if(CODEGEN_KIND == 0)
	{
        Tuple<naming_info *> name_func;
        String out_loop;

        Relation rf = Relation::True(S.n_set());

        Relation R_transform = IdentityRelation(S.n_set());

        Tuple<Relation> R_t_coll, S_coll;

        R_t_coll.append(R_transform);
        S_coll.append(S);

        name_func.append(new default_stmt_info(1));
           // Relation Z;
      //     printf("%s",name_func[1]->debug_name());

           // Z.print();
        int w = n;

        out_loop = MMGenerateCode(R_t_coll, S_coll, name_func, rf, w);


        return out_loop;
	}
	if(CODEGEN_KIND == 1)
	{
	 //   cout << "p" << endl;

//cout << BarvinokCodegen(S);
return BarvinokCodegen(S).c_str();

	}

    else
        return OmegaPlusCodegen(S).c_str();

}



