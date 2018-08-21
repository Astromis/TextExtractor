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

char* TextExtractor::GetText(char* filepath)
{
    string ext = GetExt((string)filepath);

    if(ext == ".djvu")
    {
        return get_text_from_djvu(filepath, -1)
    }
    else if(ext == ".pdf")
    {
        return get_text_from_pdf(filepath, -1);

    }
    else if(".docx")
    {
        DocxReader dr(filepath);
        return dr.GetText();
    }
/*     else if(".doc")
    {

    } */
}

void TextExtractor::GetTextFromFiles(vector<string> &q)
{
    for(auto file: q)
        vecTexts.push_back(GetText(file));
}

//TODO: Name generator
//  Zip archivate condition
void TextExtractor::Text2File(char* text, string rootpath)
{
    ofstream fout;
    fout.open(rootpath + "name"); 
    fout<<text;
    fout.close();
    free(text);
}

void TextExtractor::PutTextsToFiles()
{
    for(auto txt:vecTexts)
        Text2File(txt);
}
//This function take a pointer on array of pointers that point to memory, allocated for text. 
