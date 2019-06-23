#include "docx_reader.h"
#include "iostream"

DocxReader::DocxReader(const char *fpath, string reg):Zip(fpath)
{
    re.assign(reg);
    //DocxReader::filepath = fpath;

    // or string? size of parsed data will be significantly less then size original xml
    // and array should be truncate till actual size of parsed data
    // what I can truncate more efficiently char or string?
}

DocxReader::~DocxReader()
{
    cout<<"Summon deconstr of docx"<<endl;
}

void  DocxReader::GetText(string &data)
{
    ReadData("word/document.xml", data);
    ParseXml(data);
    //It will able to done with regexp, because parsing xml is hard task for my brain.
    //Probably regexp <w:t[А-Яа-яA-Za-z0-9 > \":=,.;]+</w:t>
    // https://eax.me/cpp-regex/
    // https://eax.me/regular-expr/
}

void DocxReader::ParseXml(string& data)
{
    smatch m;
    string tmp = (string)contents;

    /* regex_search(data, m, re);
    for (auto x:m) std::cout << x << "test ";
    std::cout << std::endl; */
    while (regex_search (data, m, re))
    {
        for (auto x:m) std::cout << x << " ";
        std::cout << std::endl;
        //data = m.suffix().str();
    }
    
    //s = m.suffix().str()
/*     regex xRegEx("<w:t[а-яА-Я0-9 >:=,.;]+</w:t>");
    sregex_iterator xIt(tmp.begin(), tmp.end(), xRegEx);
    sregex_iterator xInvalidIt;
    
    while(xIt != xInvalidIt)
        std::cout << xIt-> << endl; */
}

void DocxReader::SetRegExp(string regex)
{
    re.assign(regex);
}
