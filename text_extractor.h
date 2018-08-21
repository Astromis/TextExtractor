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
    void GetText(char* filepath);
    void GetTextFromList(vector<string> &q);
    string GetExt(string path);
};

