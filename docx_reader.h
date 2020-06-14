//#include <regex>
#include "czip.h"
#include <string>
//#include <boost/regex.hpp>
#include <regex>
#include <codecvt>

// g++ test_maim.cpp docx_reader.cpp zip.cpp -std=c++0x -lzip -lboost_regex -o test_zip


using namespace std;
//using namespace boost;

class DocxReader : public Zip
{
    //content file - file within zip file
    private:
        wregex re;
        char* contents;
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    public:
        void SetRegExp(wstring regex);
        void ParseXml(string &data);
        DocxReader();
        ~DocxReader();
        DocxReader(const char *filepath, wstring reg = L"<w:t[ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ\\w\\s\\d\b > \":=,.;-]+</w:t>");
        
        char* GetText();//string& data

        

};
