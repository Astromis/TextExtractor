#include "djvu_extractor.h"
#include "docx_reader.h"
#include "pdf_extractor.h"
#include <queue>
#include <fstream>

class TextExtractor
{
    private:
    string ext;
    vector<char *> vecTexts;

    public:
    TextExtractor();
    ~TextExtractor();
    char* GetText(char* filepath);
    void GetTextFromList(vector<string> &q);
    string GetExt(string path);
    void PutTextsToFiles();
    void Text2File(char* text, string rootpath);
};

