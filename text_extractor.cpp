#include "text_extractor.h"

TextExtractor::TextExtractor()
{
}

TextExtractor::~TextExtractor()
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
        return get_text_from_djvu(filepath, -1);
    }
    else if(ext == ".pdf")
    {
         get_text_from_pdf(filepath, -1);

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

void TextExtractor::GetTextFromList(vector<string> &q)
{
    for(auto& i: q)
    {
        vecTexts.push_back(make_pair(GetText(i), i));
    }
}

string name_generator(string src_name)
{
    static int count = -1;
    count++;
    return tostring(count) + "_recognized_" + src_name; 
}

//TODO:
//  Zip archivate condition

void TextExtractor::PutTextsToFiles(string rootpath)
{
    for(auto i: vecTexts)
    {
        ofstream fout;
        fout.open(rootpath + name_generator(i.second)); 
        fout<<i.first;
        fout.close();
        free(text);
    }

}
