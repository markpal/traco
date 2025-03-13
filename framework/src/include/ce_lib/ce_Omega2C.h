#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>



using namespace std;

string GetCaptures(string text_line, boost::regex regex, int number);

string GetCaptures(string text_line, string reg_text, int number) {
	boost::regex regex(reg_text);
	return GetCaptures(text_line, regex, number);
}

string GetCaptures(string text_line, boost::regex regex, int number) {
    std::string text(text_line), tmp;
    int i=0;

    boost::sregex_token_iterator iter(text.begin(), text.end(), regex, 0);
    boost::sregex_token_iterator end;

    for( ; iter != end; ++iter ) {
     //   std::cout<<*iter<<'\n';
        tmp = *iter;
        //cout << tmp;
        if(i==number)
          break;
        else
           i++;
    }

    return tmp;
}

string intToStr(int n)
{
     string tmp;
     if(n < 0) {
          tmp = "-";
          n = -n;
     }
     if(n > 9)
          tmp += intToStr(n / 10);
     tmp += n % 10 + 48;

     return tmp;
}


unsigned int Count_Captures(string inp, boost::regex reg)
{
    std::string text(inp);

	unsigned int i=0;

	boost::sregex_token_iterator iter(text.begin(), text.end(), reg, 0);
	boost::sregex_token_iterator end;

	for( ; iter != end; ++iter ) {
		i++;
	}

	return i;
}

bool Regex_Match(string inp, boost::regex reg)
{
    return Count_Captures(inp, reg) > 0;
}


string ReplaceStr(string where, string oldstr, string newstr)
{
	string _where = where;
	boost::replace_all(_where, oldstr, newstr);
	return _where;
}

namespace CodeEngine
{
    class Tab_Space
    {
        public:

		string tab;
        string df;

        Tab_Space()
        {
            tab = "";
            df = "   ";
        }

        void Add()
        {
            tab = tab + df;
        }

        void Remove()
        {
            tab = tab.erase(0, df.size());
        }


    };




	class Omega2C
    {
        public:

        Omega2C()
        {
        }


        string ObliczOgr(string rel)
        {
            unsigned int i;
            string outs;

            std::vector<std::string> tab;

            rel = ReplaceStr(rel, "union", "~");
            boost::split(tab, rel, boost::is_any_of("~"));

            for(i=0; i<tab.size(); i++)
            {
                tab[i] = ObliczOgraniczenia(tab[i], false);
                cout << "oooo" << tab[i] << endl;
            }


            outs = tab[0];
            for (i = 1; i < tab.size(); i++)
                outs += " || " + tab[i];

            return outs;

        }

        string ObliczOgraniczenia(string rel, bool prim)
        {
            boost::regex reg("^.*]"), tmp;
            std::vector<std::string> GEQ;
            string temp;
            string ogr;
            unsigned int i;
            bool last = false;

         //   cout << rel << endl;

            rel = boost::regex_replace(rel , reg, "");

             while (rel != "")
             {
                 reg.assign("^[^&]*&&");


                 if (Regex_Match(rel, reg))
                    temp = GetCaptures(rel, reg, 0);
                 else
                 {
                    temp = rel;
                    last = true;
                 }
                // sprawdz czy jest to rownosc

                //tmp = new Regex("\\s=\\s"); // jest rownoscia odrzuc, tak bylo w gingers ale w reeds ograniczenia beda z Range wiec powinny one byc
                //if (!tmp.IsMatch(rel))
                //{

                    boost::regex tmp("(&&)|\\}");
                    temp = boost::regex_replace(temp , tmp, "");
                    tmp.assign("(^\\s*)|(\\s*$)");
                    temp = boost::regex_replace(temp , tmp, "");

                    temp = Replace_Multiple_EQ_GEQ_Single_EQ_GEQ(temp);
                    temp = Change_Koma_To_New_Constr(temp);

                    GEQ.push_back(temp);
                // }

                if (last)
                    rel = "";
                else
                    rel = boost::regex_replace(rel , reg, "");


             }  //while

             ogr = "";

            for (i = 0; i < GEQ.size(); i++)
            {
                if (i > 0)
                    ogr += " && ";

                string temp11 = GEQ[i];
                boost::regex regtmp("\\d[A-Za-z]");

                boost::sregex_token_iterator iter(temp11.begin(), temp11.end(), regtmp, 0);
                boost::sregex_token_iterator end;
                string mmm;

                for( ; iter != end; ++iter ) {

                    mmm = *iter;
                    string tnowy = mmm[0] + "*" + mmm[1];

                    boost::regex regtmp(mmm);
                    temp11 = boost::regex_replace(temp11, regtmp, tnowy);


                }

                ogr += temp11;//GEQ[i].ToString();
                 // ³ata - koniec

            }

            if (prim)
            {

                for (unsigned int c = 0; c < ogr.size(); c++)
                {
                    if (ogr[c] == 'i' || ogr[c] == 'j' || ogr[c] == 'k' || ogr[c] == 'l' || ogr[c] == 'v')
                    {
                        if (c > 0 && c < ogr.size() - 1)
                            if (!isalpha(ogr[c - 1]) && !isalpha(ogr[c + 1]))
                                ogr.insert(c + 1, "p");
                        if (c == 0 && c < ogr.size() - 1)
                            if (!isalpha(ogr[c + 1]))
                                ogr.insert(c + 1, "p");
                        if (c > 0 && c == ogr.size() - 1)
                            if (!isalpha(ogr[c - 1]))
                                ogr.insert(c + 1, "p");

                    }


                }
            }


            boost::replace_all(ogr, " = ", " == ");
            boost::replace_all(ogr, "v'", "v");
            boost::replace_all(ogr, "vp'", "vp");
            boost::replace_all(ogr, ":", "");

            return ogr;

        }

        string Change_Koma_To_New_Constr(string in_str)
        {
            // Sprawdz czy jest przecinek
            boost::regex check_koma(","), tmp;
            string output = in_str;

            if (Regex_Match(in_str, check_koma))
            {
                // Sprawdz po ktorej stronie nierownosci jest przecinek
                boost::regex left_koma(",[^<>=]*[<>=]");
                boost::regex right_koma("[<>=][^,]*,");

				if (Regex_Match(in_str, left_koma) && Regex_Match(in_str, right_koma))
				{
					string in1 = GetCaptures(in_str, "^.*=", 0);
					boost::regex tmp2("&&.*$");
					in1 = boost::regex_replace(in1 , tmp2, "");
					in1 = Change_Koma_To_New_Constr(in1);

					string in2 = GetCaptures(in_str, "=.*$", 0);
					tmp2.assign("^.*&&");
					in2 = boost::regex_replace(in2 , tmp2, "");
					in2 = Change_Koma_To_New_Constr(in2);

					output = in1 + " && " + in2;
				}
				else if(Regex_Match(in_str, left_koma))
				{
                    // przecinek jest po lewej stronie

                    // tworz pierwsze ograniczenie
                    // usun to co jest pomiedzy przecinkiem a nierownoscia
                    tmp.assign(",\\s*[^<>=\\s]*");

                    output = boost::regex_replace(in_str, tmp, string("")) + " && ";
                    // drugie ograniczenie
                    // usun to co jest przed przecinkiem
                    tmp.assign("\\s*[^,]*,\\s*");
                    output += boost::regex_replace(in_str, tmp, "");
				}
				// Sprawdz czy po prawej
                else if (Regex_Match(in_str, right_koma))
                {
                    // 1.
                    // tworz pierwsze ograniczenie
                    // usun to co jest za przecinkiem
					tmp.assign(",.*");
                    output = boost::regex_replace(in_str, tmp, string("")) + " && ";
                    //drugie ograniczenie
                    // usun to co jest pomiedzy nierownoscia a przecinkiem
                    tmp.assign("[^<>=]*,");
                    output += boost::regex_replace(in_str, tmp, "");
				}
				else
                    return "Unexpected error!";
            }

			tmp.assign("\\s+");  //usun podwojne spacje
            output = boost::regex_replace(output, tmp, string(" "));

			return output;

        }

        string Replace_Multiple_EQ_GEQ_Single_EQ_GEQ(string in_str)
        {
            boost::regex reg_delete("^\\s*.[^<>=]*(=|<=|>=|<[^=]|>[^=])\\s*");  //wyrazenia ktore sukcesywnie beda usuwane
            // np 1 <= i <= 10 znajduje 1 <=
            boost::regex reg_trim("^\\s*.[^<>=]*(=|<=|>=|<[^=]|>[^=])\\s*[^<>=\\s]*");
            // wyciaga pierwsze ograniczenie z lewej strony np 1 < i <= 10 daje 1 < i

			string temp = in_str; // obcinany sukcesywnie ciag o kolejne ograniczenia
            string output = ""; // nowo budowany lancuch w jezyku C

			while (temp != "")  //dopoki zostal lancuch ograniczen
            {
                if (Count_GEQ_EQ(temp) > 1)
                {
                    // wyciagnij ograniczenie calkiem z brzegu i dodaj do output
					output += GetCaptures(temp, reg_trim, 0) + " && " ;
                    // utnij ograniczenie do znaku EQ lub GEQ np 1<= i<=10 ucina 1<= oraz zostaje i<=10
                    temp = boost::regex_replace(temp, reg_delete, "");
                }
                else
                {
                    output += temp;
                    temp = "";
                }

            }

            return output;

        }

		// Zlicza ilosc rownosci i nierownosci w ograniczeniu
        int Count_GEQ_EQ(string inp)
        {
            std::string text(inp);
			boost::regex regex("=|<=|>=|<[^=]|>[^=]");

			unsigned int i=0;

		    boost::sregex_token_iterator iter(text.begin(), text.end(), regex, 0);
		    boost::sregex_token_iterator end;

		    for( ; iter != end; ++iter ) {
				i++;
			}

			return i;
        }

		// do analizy dalszej - or itd
        string RemoveExists(string Rel)
	{
	    boost::regex reg("(Exists[^:]*:)|\\)");
            string temp = "";
            string newrel = "";
            string lacznik = "";

	    Rel = boost::regex_replace(Rel, reg, "");

	    reg.assign("^.*\\]");

	    //przepisz zmienne w []
            if (Regex_Match(Rel, reg))
                temp = GetCaptures(Rel, reg, 0);

	    newrel = temp;
	    Rel = boost::regex_replace(Rel, reg, "");
//cout << "ooo" << temp;
//cout << Rel;
	    while (Rel != "")
            {
           //   cout << "zzz" << endl;
                // dziala tylko z &&

            //    cout << Rel;
    //    ("^[^&\\}]*(&&|\\})");
		reg.assign("^[^&\\}]*(&&|\\})");   //"^[^&}]*(&&|})"
		if (Regex_Match(Rel, reg))
		{
		//    cout << "!!!!";
		    temp = GetCaptures(Rel, reg, 0);
		  //  cout << temp << endl;
		}

		else
		{
                    newrel += temp;
              //      cout << "!dd!!!"<<newrel;
                    break;
		}
//exit(0);
				Rel = boost::regex_replace(Rel, reg, "");
				reg.assign("(alpha)|(beta)|(gamma)|(delta)");

				if (!Regex_Match(Rel, reg))
					 newrel += temp;
				else
				{
					//oblicz Mathematica
                    string MathOut;
                    MathCmd = "Format[Solve[";
					reg.assign("(&&)|\\}");

					string temp2 = boost::regex_replace(temp, reg, "");

					if (Regex_Match(temp, reg))
                        lacznik =  GetCaptures(temp, reg, 0);

					MathCmd += temp2;

					MathCmd += ",{alpha,beta,gamma,delta}], InputForm]";

					reg.assign("=");

					MathCmd =  boost::regex_replace(MathCmd, reg, "==");
					// math - gotowe

					Mathematica *ml = new Mathematica();
                    MathOut = ml->Calc(MathCmd);

					reg.assign(".*->");
                    MathOut = boost::regex_replace(MathOut, reg, "is_int((float)(");
                    reg.assign("\\}\\}");
                    MathOut = boost::regex_replace(MathOut, reg, ")) " + lacznik);
                    newrel += MathOut;

				}

				reg = boost::regex("\\}");

				if (Regex_Match(temp, reg))
                    Rel = "";
			}

			reg.assign("&&\\s*$");

	    if (Regex_Match(newrel, reg))
                newrel = boost::regex_replace(newrel, reg, "}");

            Rel = newrel;
            return Rel;
	}

        private:
        string MathCmd;


    };
}
