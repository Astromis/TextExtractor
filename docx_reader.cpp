#include "docx_reader.h"
#include "iostream"
#include <cwctype>
#include <clocale>
#include <locale>

DocxReader::DocxReader(const char *fpath, wstring reg):Zip(fpath)
{
    setlocale(LC_ALL, "");
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

char*  DocxReader::GetText()//string &data
{
    char * data;
    ReadData("word/document.xml", data);
    //cout<<*data;
    string d((const char * )data);
    ParseXml(d);
    //It will able to done with regexp, because parsing xml is hard task for my brain.
    //Probably regexp <w:t[\w\s\d\b > \":=,.;-]+</w:t>
    // https://eax.me/cpp-regex/
    // https://eax.me/regular-expr/
}

void DocxReader::ParseXml(string& data)
{
    wsmatch m;
    wstring tmp = converter.from_bytes(string(data));

    /* regex_search(data, m, re);
    for (auto x:m) std::cout << x << "test ";
    std::cout << std::endl; */
    while (regex_search (tmp, m, re))
    {
        for (auto x:m) cout << converter.to_bytes(x) << " ";
        cout<<endl;
        tmp = m.suffix().str();
    }
    
    //s = m.suffix().str()
/*     regex xRegEx("<w:t[а-яА-Я0-9 >:=,.;]+</w:t>");
    sregex_iterator xIt(tmp.begin(), tmp.end(), xRegEx);
    sregex_iterator xInvalidIt;
    
    while(xIt != xInvalidIt)
        std::cout << xIt-> << endl; */
}

void DocxReader::SetRegExp(wstring regex)
{
    re.assign(regex);
}
