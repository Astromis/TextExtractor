#include "djvu_extractor.h"
#include "docx_reader.h"
#include "pdf_extractor.h"
#include <queue>

class TextExtractor
{
    private:
    string ext;

    public:
    TextExtractor();
    ~TextExtractor();
    void GetText(char* filepath);
    void GetTextFromList(vector<string> &q);
    string GetExt(string path);
};

