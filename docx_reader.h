#include <string>
#include <regexp>
#include <zip.h>

class DocxReader::Zip
{
    //content file - file within zip file
    private:
        const std::regex re;

        void ParseXml();

    public:
        void SetRegExp(string regex);

        DocxReader();
        ~DocxReader();
        DocxReader(const char *filepath, string reg = "<w:t[А-Яа-яA-Za-z0-9 > \":=,.;]+</w:t>");
        char * GetText();

        

}