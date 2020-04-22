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

string name_generator(string src_name)
{
    static int count = -1;
    count++;
    size_t start = src_name.rfind("/");
    string file_name = src_name.substr(start + 1, src_name.length());
    //file_name = file_name.substr(0, file_name.rfind("."));
    return std::to_string(count) + "_recognized_" + file_name + ".txt"; 
}

bool write_to_file(string filename, char* pTextData)
{
    ofstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cout<< "Cannot open the file for writing! "<< filename << std::endl;
        return false;
    } 
    file<<pTextData;
    file.close();
    return true;
}


bool TextExtractor::create_doc_djvu(string filepath)
{
    if (! (ctx_djvu = ddjvu_context_create("test")))
    {
        cout<<"Cannot create djvu context."<<endl;
        return false;
    }
    if (! (pDoc_djvu = ddjvu_document_create_by_filename(ctx_djvu, filepath.c_str(), TRUE)))
    {
        cout<<"Cannot open djvu document"<<filepath<<endl;
        return false;
    }
    while (! ddjvu_document_decoding_done(pDoc_djvu))
        continue;
    if (ddjvu_document_decoding_error(pDoc_djvu))
    {
        cout<<"Cannot decode document."<<endl;
        return false;
    }
    return true;
}

void TextExtractor::destroy_doc_djvu()
{
    if (pDoc_djvu)
    ddjvu_document_release(pDoc_djvu);
    if (ctx_djvu)
    ddjvu_context_release(ctx_djvu);
}


bool TextExtractor::create_doc_pdf(string filepath)
{
    pDoc_pdf = poppler::document::load_from_file(filepath);
    if(pDoc_pdf == NULL)
    {
        cout<<"Couldn't load pdf file"<<filepath<<endl;
        return false;
    }
    return true;
}

bool TextExtractor::GetTextLayerDjvu(fs::path filepath)
{
    char * pText_data;
    int maxpages = 0;
    miniexp_t r = miniexp_nil;
    //const char *lvl = (detail) ? detail : "page";
    const char *lvl =  "page";
    if(create_doc_djvu(filepath))
    {
        maxpages = ddjvu_document_get_pagenum(pDoc_djvu);
        for(int i = 0; i < maxpages; i++)
        {
            if((r = ddjvu_document_get_pagetext(pDoc_djvu, i, lvl)) == miniexp_nil)
            {
                pages_without_text[filepath].push_back(i);
            }
            else
            {
                pText_data = dopage_text_extract(r, lvl, 0);
                string d = string(pText_data);
                DataStore.push_back(pagecard(filepath, i, d));
                //write_to_file(basedir + name_generator(filepath), pText_data);
                delete [] pText_data;
            }
        }
        destroy_doc_djvu();
        return true;
    }
    else
    {
        failed_documents.push_back(filepath);
        return false;
    }
}

bool TextExtractor::GetTextLayerPdf(fs::path filepath)
{
    const char * pText_data;
    if(create_doc_pdf(filepath))
    {
        int pagesNbr = pDoc_pdf->pages();
        for (int i = 0; i < pagesNbr; ++i)
        {
            txt = pDoc_pdf->create_page(i)->text();
            if(txt.length() == 0)
            {
                pages_without_text[filepath].push_back(i);
            }
            else
            {
                //cout<<txt.to_latin1().c_str();
                pText_data = txt.to_latin1().c_str();
                string d = string(pText_data);
                DataStore.push_back(pagecard(string(filepath.filename()), i, d));
                //write_to_file(basedir + name_generator(filepath), pText_data);
                //delete pText_data;
            }
        }
        return true;
    }
    else
    {
        failed_documents.push_back(filepath);
        return false;
    }
    
}

void TextExtractor::GetLayeredText(fs::path filepath)
{
    string ext = filepath.extension();
    if(ext == ".djvu")
    {
        GetTextLayerDjvu(filepath);
    }
    else if(ext == ".pdf")
    {
        GetTextLayerPdf(filepath);
    }

/*     else if(".docx")
    {
        DocxReader dr(filepath.c_str());
        return dr.GetText();//WordData
    } */
/*     else if(".doc")
    {

    } */
}

bool TextExtractor::GetRecognizedTextDjvu(fs::path filepath, vector<int>& pageno)
{
    char* pPlainText;

    if(create_doc_djvu(filepath))
    {
        for(auto page: pageno)
        {
            cout<<"Recognition for "<<filepath<<" page "<<page<<endl;
            pPlainText = dopage_text_recognition(pDoc_djvu, page);
            //write_to_file(basedir + name_generator(filepath), pPlainText);
            string d = string(pPlainText);
            DataStore.push_back(pagecard(string(filepath.filename()), page, d));
            delete [] pPlainText;
        }
        destroy_doc_djvu();
        return true;
    }
    else
    {
        failed_documents.push_back(filepath);
        return false;
    }
}

bool TextExtractor::GetRecognizedTextPdf(fs::path filepath, vector<int>& pageno)
{
    char* pPlainText;

    if(create_doc_pdf(filepath))
    {
        for(auto page: pageno)
        {
            cout<<"Recognition for "<<filepath<<" page "<<page<<endl;
            pPlainText = pdf_text_recognition(page, pDoc_pdf);
            //write_to_file(basedir + name_generator(filepath), pPlainText);
            string d = string(pPlainText);
            DataStore.push_back(pagecard(string(filepath.filename()), page, d));
            delete [] pPlainText;
        }
        //delete pDoc_djvu;
        return true;
    }
    else
    {
        failed_documents.push_back(filepath);
        return false;
    }
}

//TODO: Make an accaunt of corrupted pages
void TextExtractor::GetRecognizedText(fs::path filepath, vector<int> pageno)
{
    string ext = filepath.extension();
    if(ext == ".djvu")
    {
        GetRecognizedTextDjvu(filepath, pageno);
    }
    else if (ext == ".pdf")
    {
        GetRecognizedTextPdf(filepath, pageno);
    }
}

vector<fs::directory_entry> scan_from_root(string root)
{
    vector<fs::directory_entry> files;
    for(const auto& p: fs::recursive_directory_iterator(root))
    {    
        if(is_regular_file(p) && p.path().has_extension())
        {
            string ext = p.path().extension();
            if(ext == ".pdf" || ext == ".djvu")
                files.push_back(p);
        }
    }
    return files;
}

void TextExtractor::process(string rootpath)
{

    
}

