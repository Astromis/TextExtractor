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
    vector<string> source_names;

    public:
    TextExtractor();
    ~TextExtractor();
    char* GetText(char* filepath);
    void GetTextFromList(vector<string> &q);
    string GetExt(string path);
    void PutTextsToFiles();
};

