#include "text_extractor.h"

TextExtractor::TextExtractor()
{
}

inline string TextExtractor::GetExt(string path)
{
    size_t start = path.rfind(".");
    ext = path.substr(start, path.length());
    return ext;
}


/*TextExtractor::TextExtractor(char* filepath)
{
    string sPath = (string)filepath;

}*/

void TextExtractor::GetText(char* filepath)
{
    string ext = GetExt((string)filepath);

    if(ext == ".djvu")
    {
        get_text_from_djvu(filepath, -1)
    }
    else if(ext == ".pdf")
    {
        get_text_from_pdf(filepath, -1);

    }
    else if(".docx")
    {
        DocxReader dr(filepath);
        dr.GetText();
    }
/*     else if(".doc")
    {

    } */
}

void TextExtractor::GetTextFromList(vector<string> &q)
{
    for(auto file: q)
        GetText(file)
}

//void TextExtractor::PutTextInFiles();
//This function take a pointer on array of pointers that point to memory, allocated for text. 
