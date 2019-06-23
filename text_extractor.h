#include "djvu_extractor.h"
#include "docx_reader.h"
#include "pdf_extractor.h"
#include <string>
#include <fstream>

class TextExtractor
{
    private:
    string ext;
    vector<char *> vecTexts;
    vector<pair<string, string> > vecTextsNames;
    vector<string> source_names;
    //char* pWordData;

    public:
    TextExtractor();
    ~TextExtractor();
    void GetText(string filepath, string& WordData);
    void GetTextFromList(vector<string> &q);
    string GetExt(string path);
    void PutTextsToFiles(string);
};

