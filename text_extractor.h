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
    ddjvu_context_t *ctx_djvu;
    ddjvu_document_t *pDoc_djvu;
    poppler::document *pDoc_pdf;
    poppler::ustring pdf_text;
    bool create_doc_djvu(string filepath);
    void destroy_doc_djvu();
    bool create_doc_pdf(string filepath);

    public:
    map<fs::path, vector<int> > pages_without_text;
    map<fs::path, vector<int> > corrupted_pages;

    //vector<pagecard> DataStore;
    vector<string> failed_documents;

    TextExtractor();
    ~TextExtractor();
    void GetLayeredText(fs::path filepath);
    void GetRecognizedText(fs::path filepath, vector<int> pageno);

    bool GetTextLayerDjvu(fs::path filepath, vector<pagecard>& DataStore);
    bool GetTextLayerPdf(fs::path filepath, vector<pagecard>& DataStore);
    bool GetRecognizedTextDjvu(fs::path filepath, vector<pagecard>& DataStore, vector<int>& pageno);
    bool GetRecognizedTextPdf(fs::path filepath, vector<pagecard>& DataStore, vector<int>& pageno);


};


