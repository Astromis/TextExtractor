//#include <regex>
#include "czip.h"
#include <string>
//#include <boost/regex.hpp>
#include <regex>


// g++ test_maim.cpp docx_reader.cpp zip.cpp -std=c++0x -lzip -lboost_regex -o test_zip


using namespace std;
//using namespace boost;

class DocxReader : public Zip
{
    //content file - file within zip file
    private:
        regex re;
        char* contents;


    public:
        void SetRegExp(string regex);
        void ParseXml(string &data);
        DocxReader();
        ~DocxReader();
        DocxReader(const char *filepath, string reg = "<w:t[А-Яа-яA-Za-z0-9>\":=,.;]+</w:t>");
        
        void GetText(string& data);

        

};
