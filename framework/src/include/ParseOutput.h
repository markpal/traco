#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#define PETIT_FORMAT 1

using namespace std;

int Convert(const char* input_file, const char* output_file);
string po_GetCaptures(string text_line, string reg_text, int number);
std::vector<std::string> LoadVars(const char* _file);
std::string GetOriginalLine(int no, const char* input_file);

int ParseOutput(int fs=0)
{
    std::vector<std::string> _Names;
    std::vector<std::string> _PrivateVars;

    string vars_file = "names_info.txt";
	string pseudocode_file = "pseudocode.txt";
	string tmp_pseudocode_file = "tmp_" + pseudocode_file;
	string out_pseudocode_file;
	string tabb;

    if(ifstream(INDFileC.c_str()))
    {
        string STRING;
        ifstream infile;
        std::ofstream out("pseudocode.txt", std::ios::app);
        out << endl;
        out << "// IND loop";
        out << endl;
        infile.open(INDFileC.c_str());
        while(!infile.eof()) // To get you all the lines.
        {
            getline(infile,STRING); // Saves the line in STRING.
            out<<STRING<<endl; // Prints our STRING.
        }
        infile.close();
        out.close();
    }




	if(outputFileC == "")
        out_pseudocode_file = "out_" + pseudocode_file;
    else
        out_pseudocode_file = outputFileC;

	string input_file = "input_C.txt";


	remove(input_file.c_str());

    if(PETIT_FORMAT)
    	Convert("input.txt", input_file.c_str());

    _Names = LoadVars(vars_file.c_str());  // read variables - in future can be deleted

    ifstream _reader(pseudocode_file.c_str());
    ofstream _writer(tmp_pseudocode_file.c_str());
	string line, statement; int no;
	string tmpvar;


    while(_reader)
    {
        std::getline(_reader, line);

        if(line.find("// FS loop ---") != string::npos)
            fs = 1;


        if(line.find("s1(") != string::npos && !_FS_FOR_TILING)
        {
            boost::regex reg("^\\s*s1\\(");

            boost::regex regg("^\\s*");
            boost::sregex_token_iterator p(line.begin(), line.end(), regg, 0);
            boost::sregex_token_iterator end;

            for (;p != end; ++p){
                string m(p->first, p->second);
                tabb = m;
            }


            line = boost::regex_replace(line , reg, "");
            boost::replace_all(line, ");", "");

            std::vector<std::string> curr_vars;
            boost::split(curr_vars, line, boost::is_any_of(","));

          //  if(fs) //usun pierwsza
            for(int zzz=0; zzz<_PARSEPRINT; zzz++)
                curr_vars.erase(curr_vars.begin());

            if(fs)
                curr_vars.erase(curr_vars.begin());

            //pobierz wszystkie t1, t2
			for(int j = 0; j < curr_vars.size()-1; j++)
            {
				//cout << curr_vars[j];

				tmpvar = curr_vars[j];
				if(std::find(_PrivateVars.begin(), _PrivateVars.end(), tmpvar) == _PrivateVars.end())
                    _PrivateVars.push_back(tmpvar);

            }

            //pobierz linie
			no = atoi(curr_vars[curr_vars.size()-1].c_str());

            statement = GetOriginalLine(no-1, input_file.c_str());  //?

            string outline = statement;

            for(int i=1; i<=_Names.size()-1; i++)  //bez v
            {
                boost::regex reg("(\\W|_)" + _Names[i-1] + "(\\W|_)");

                if(CODEGEN_KIND==1)
                for(int zz=1; zz<_Names[i-1].length(); zz++)
                if(_Names[i-1][zz]=='\'')
                    _Names[i-1].erase(zz);

                //cout << "!!" << _Names[i-1] << curr_vars[i-1];

                std::string baza;

                boost::sregex_token_iterator iter(statement.begin(), statement.end(), reg, 0);
                boost::sregex_token_iterator end;

                for( ; iter != end; ++iter ) {
                    //   std::cout<<*iter<<'\n';
                    baza = *iter;
                    // jesli wyrazanir jest zlozone dajemy w nawiasy bo moze byc wczesniej minus

                    string h1 = "(";
                    string h2 = ")";
                    string plus_ = "+";
                    string minus_ = "-";


                    size_t found1, found2;
                    found1=curr_vars[i-1].find(plus_);
                    found2=curr_vars[i-1].find(minus_);


                    string podmianka = curr_vars[i-1];

                    if((found1!=string::npos || found2!=string::npos) && baza[0] == '-')
                        podmianka = h1 + podmianka + h2;

                    string zamiana = baza[0]  + podmianka +  baza[baza.size()-1];


                   // std::cout<<"& " << zamiana<<'\n';
                    boost::replace_all(outline, baza, zamiana);



                }
            }
            outline = tabb + outline;
            _writer << outline << endl;
        }
        else{
            if(line != "")
                _writer << line << endl;
    }
    }
    _writer.close();
    _reader.close();

    // dodaj pragmy openmp

    _reader.open(tmp_pseudocode_file.c_str());
    _writer.open(out_pseudocode_file.c_str());

    string private_clausule = " private(";

    for(int i=0; i<_PrivateVars.size(); i++)
    {
        private_clausule += _PrivateVars[i] + ",";
    }

    private_clausule = private_clausule.substr(0, private_clausule.size()-1);
    private_clausule += ")";

    while(_reader)
    {
        std::getline(_reader, line);
        if(line.find("par for") != string::npos)
        {
           _writer << "#pragma omp parallel for" + private_clausule << endl;
           boost::replace_all(line, "par for", "for");
        }
        if(line != "")
            _writer << line << endl;
    }

    _writer.close();
    _reader.close();

   // remove(tmp_pseudocode_file.c_str());



    if(fs)
    {
        string s("python ");
        string s1(thepath + "py/fs_pragma.py ");
        //s += fs_pragma;
        s += s1;
        // nie przesuwaj instrukcji
        s += out_pseudocode_file;
        if(_FS_FOR_TILING)
            s += " 1";
        //string s("python fs_pragma.py ");

        /*
ofstream myfile;
  myfile.open ("example.txt");
  myfile << s;
  myfile.close();*/

        system(s.c_str());
    }


    return 0;
}

std::string GetOriginalLine(int no, const char* input_file)
{
    ifstream _reader(input_file);
    string line; int z=0;

    while(_reader)
    {
        std::getline(_reader, line);

        if(z == no)
        {
            _reader.close();
           // cout << line <<endl;
            return line;
        }
        else
            z++;
    }
    _reader.close();
    return "### ERROR ###";
}

std::vector<std::string> LoadVars(const char* _file)
{
    string line;
    ifstream _reader(_file);
    std::vector<std::string> _Names;

    while(_reader)
    {
        std::getline(_reader, line);
        boost::split(_Names, line, boost::is_any_of(","));

    }
    _reader.close();

    return _Names;

}


int Convert(const char* input_file, const char* output_file)
{
    ifstream _reader(input_file);
    std::string line;
    std::vector<std::string> lines;
    bool convert = false;

    while(_reader)
    {
        std::getline(_reader, line);
        lines.push_back(line);
        // ... append line to buffer and go on
    }
    _reader.close();

    for(int i=0; i<lines.size(); i++)
    {
         //cout << lines[i] << endl;
        string s = lines[i];
		string var, lb, ub, tab_space;

		tab_space = po_GetCaptures(s, "^\\s*", 0);  //odstep
		//cout << tab_space << "test" << endl;


		if((s.find("for") != string::npos) && (s.find("to") != string::npos))
		{
            convert = true;
            std::string temp = s;

            boost::regex reg("for.*=");

            temp = po_GetCaptures(temp, "for.*=", 0);

            boost::replace_all(temp, "for", "");
            boost::replace_all(temp, "=", "");
            boost::replace_all(temp, " ", "");

            var = temp;
            //cout << var;

            temp = s;

            temp = po_GetCaptures(temp, "=.*to", 0);

            boost::replace_all(temp, "=", "");
            boost::replace_all(temp, "to", "");
            boost::replace_all(temp, " ", "");

            lb = temp;

            temp = s;

            temp = po_GetCaptures(temp, "to.*do", 0);

            boost::replace_all(temp, "to", "");
            boost::replace_all(temp, "do", "");
            boost::replace_all(temp, " ", "");

            ub = temp;

            temp = tab_space + "for(" + var + " = " + lb + "; " + var + " <= " + ub + "; " + var + "++){";

            s = temp;

		}

        if(s.find("endfor") != string::npos)
            boost::replace_all(s, "endfor", "}");

        if(s.find("endif") != string::npos)
            boost::replace_all(s, "endif", "}");

        if((s.find("}") == string::npos) && (s.find("for") == string::npos))
        {
            bool tabstart=false, tabstop=false;
            string out1 = ""; char z = ' ';

            for(int q=0; q<s.size(); q++)
            {
                z = s[q];

                if(s[q] == '(' && tabstart)
				{
					z = '[';
					tabstop = true;
					tabstart = false;
				}

				if(s[q] == ')' && tabstop)
				{
					z = ']';
					tabstop = false;
				}


				if(isalpha(s[q]) || isdigit(s[q]))
					tabstart = true;
				else if(s[q] != ' ')
					tabstart = false;


				out1 += z;

				if(q == s.size()-1)
					out1 += ";";



            }

            s = out1;

            boost::replace_all(s, "\n", "");
            boost::replace_all(s, ",", "][");
            boost::replace_all(s, ";;", ";");

        }

        if(convert)
			lines[i] = s;

    }

    ofstream _writer(output_file, ios::app);

    for(int i=0; i<lines.size(); i++)
        _writer << lines[i] << endl;

    _writer.close();





    return 0;

}

string po_GetCaptures(string text_line, string reg_text, int number) {
    std::string text(text_line), tmp;
    boost::regex regex(reg_text);
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

