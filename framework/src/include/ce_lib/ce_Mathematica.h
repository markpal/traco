#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <boost/regex.hpp>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <stdio.h>

using namespace std;

namespace CodeEngine
{
    class Mathematica
    {
        public :
		string inputDataFile;
        string inputOutputFile;
        string scriptFile;
        string commandText;
        string lockfile;

        Mathematica()
		{
			inputDataFile = "data";
			inputOutputFile = "o";
			scriptFile = "./m";
			lockfile = "lock";

			commandText = "";
		}

		string Calc(string Input)
   		{
			remove(lockfile.c_str());
			remove(inputDataFile.c_str());
			string sRes = "", sww="";
			int i = 0;
			try
			{
		        // save input data
		        ofstream _writer(inputDataFile.c_str(), ios::app);
		        commandText = Input;
		        _writer << commandText << endl;
		        _writer.close();

		        // execute script
                system(scriptFile.c_str());

		        //get data
		        while(1)
		        {
		            ifstream ifile(lockfile.c_str());

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

                ifstream _reader(inputOutputFile.c_str());

                while(_reader)
                {
                    std::getline(_reader, sRes);
                    if(sRes.find("Out[1]=") != string::npos)
                    {
                         boost::replace_all(sRes, "Out[1]= ", "");
                         sww = sRes;

                    }

                }
                _reader.close();

			}
            catch( char * str ) {
                cout << "Exception raised: " << str << '\n';
            }

			cout << sww << endl;
			return sww;

		}

    };






}
