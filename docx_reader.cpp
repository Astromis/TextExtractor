#include <docx_reader.h>

DocxReader::DocxReader(const char *fpath, string reg = "<w:t[А-Яа-яA-Za-z0-9 > \":=,.;]+</w:t>")
{
    filepath = fpath;

    // or string? size of parsed data will be significantly less then size original xml
    // and array should be truncate till actual size of parsed data
    // what I can truncate more efficiently char or string?
}

DocxReader::~DocxReader()
{
}

char * DocxReader::GetText()
{
    SetContentFileName("word/document.xml");
    contents = ReadData();
    //parse_xml(contents)
    //It will able to done with regexp, because parsing xml is hard task for my brain.
    //Probably regexp <w:t[А-Яа-яA-Za-z0-9 > \":=,.;]+</w:t>
    // https://eax.me/cpp-regex/
    // https://eax.me/regular-expr/

    return contents;
}


}
void DocxReader::SetRegExp(string regex)
{
    re.assign(regex);
}
