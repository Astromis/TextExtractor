#include "text_extractor.h"

TextExtractor::TextExtractor()
{
}

TextExtractor::~TextExtractor()
{
    /* for(auto i: vecTextsNames)
    {
        free(i.first);
    } */
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

void TextExtractor::GetText(string filepath, string& WordData)
{
    string ext = GetExt(filepath.c_str());
    if(ext == ".djvu")
    {
        //return get_text_from_djvu(filepath.c_str(), -1);
    }
    else if(ext == ".pdf")
    {
         //get_text_from_pdf(filepath.c_str(), -1);

    }
    else if(".docx")
    {
        
        DocxReader dr(filepath.c_str());
        dr.GetText(WordData);
    }
/*     else if(".doc")
    {

    } */
}

void TextExtractor::GetTextFromList(vector<string> &q)
{
    string data;
    for(auto& i: q)
    {
        GetText(i, data);
        vecTextsNames.push_back(make_pair(data, i));
    }
}

string name_generator(string src_name)
{
    static int count = -1;
    count++;
    size_t start = src_name.rfind("/");
    string file_name = src_name.substr(start + 1, src_name.length());
    file_name = file_name.substr(0, file_name.rfind("."));
    return std::to_string(count) + "_recognized_" + file_name + ".txt"; 
}

//TODO:
//  Zip archivate condition

void TextExtractor::PutTextsToFiles(string rootpath)
{
    for(auto i: vecTextsNames)
    {
        ofstream fout;
        fout.open(rootpath + name_generator(i.second));
        if (!fout.is_open())
        {
            cout<< "Cannot open the file!" << std::endl;
        } 
        fout<<i.first;
        fout.close();
    }

}
