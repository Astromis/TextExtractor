#include "djvu_extractor.h"
#include "docx_reader.h"
#include "pdf_extractor.h"
#include <string>
#include <fstream>
#include <map>


#include <fstream>
#include <iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


struct pagecard
{
    pagecard(string fn, int p, string& d)
    {
        filepath = fn;
        page = p;
        data = d;
    };
    fs::path filepath;
    int page;
    string data;
};

class TextExtractor
{
    private:
    string ext;
    vector<char *> vecTexts;
    vector<pair<string, string> > vecTextsNames;
    vector<string> source_names;
    vector<string> failed_documents;
    string basedir = "output/";
    //char* pWordData;
    ddjvu_context_t *ctx_djvu;
    ddjvu_document_t *pDoc_djvu;
    poppler::document *pDoc_pdf;
    poppler::ustring txt;
    bool create_doc_djvu(string filepath);
    void destroy_doc_djvu();
    bool create_doc_pdf(string filepath);

    public:
    map<fs::path, vector<int> > pages_without_text;
    vector<pagecard> DataStore;

    TextExtractor();
    ~TextExtractor();
    void GetLayeredText(fs::path filepath);
    void GetRecognizedText(fs::path filepath, vector<int> pageno);
    void process(string rootpath);

    string GetExt(string path);
    bool GetTextLayerDjvu(fs::path filepath);
    bool GetTextLayerPdf(fs::path filepath);
    bool GetRecognizedTextDjvu(fs::path filepath,vector<int>& pageno);
    bool GetRecognizedTextPdf(fs::path filepath, vector<int>& pageno);


};


