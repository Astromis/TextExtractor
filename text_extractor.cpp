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

/*TextExtractor::TextExtractor(char* filepath)
{
    string sPath = (string)filepath;

}*/

/**
 * @brief Create the document object of djvu file
 * @param filepath string with path to file
 * @return true if object successfully created, false otherwise
 */
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

/**
 * @brief Destroy the djvty object
 */
void TextExtractor::destroy_doc_djvu()
{
    if (pDoc_djvu)
    ddjvu_document_release(pDoc_djvu);
    if (ctx_djvu)
    ddjvu_context_release(ctx_djvu);
}

/**
 * @brief Create the document object of pdf file
 * @param filepath string with path to file
 * @return true if object successfully created, false otherwise
 */
bool TextExtractor::create_doc_pdf(string filepath)
{
    pDoc_pdf = poppler::document::load_from_file(filepath);
    if(pDoc_pdf == nullptr)
    {
        cout<<"Couldn't load pdf file"<<filepath<<endl;
        return false;
    }
    return true;
}

/**
 * @brief Tries to get the text that exists as a layer in the Djvu file
 * @param filepath path object of path to the file
 * @param DataStore reference to the vector of pagecards for storing the data
 * @return true if extractios is successfull, false otherwise
 */
bool TextExtractor::GetTextLayerDjvu(fs::path filepath, vector<pagecard>& DataStore)
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
                if(pText_data == NULL)
                {
                    pages_without_text[filepath].push_back(i);
                    continue;
                }
                string d = string(pText_data);
                DataStore.push_back(pagecard(filepath, i, d));
                //The segfault is occures, when next uncommented
                //delete [] pText_data;
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

/**
 * @brief Tries to get the text that exists as a layer in the PDF file
 * @param filepath path object of path to the file
 * @param DataStore reference to the vector of pagecards for storing the data
 * @return true if extractios is successfull, false otherwise
 */

bool TextExtractor::GetTextLayerPdf(fs::path filepath, vector<pagecard>& DataStore)
{
    if(create_doc_pdf(filepath))
    {
        int pagesNbr = pDoc_pdf->pages();
        for (int i = 0; i < pagesNbr; ++i)
        {
            poppler::page* p;
            nullptr_t t;
            if((p = pDoc_pdf->create_page(i)) == t)
            {
                corrupted_pages[filepath].push_back(i);
                continue;
            }
            pdf_text = p->text();
            if(pdf_text.length() == 0)
            {
                pages_without_text[filepath].push_back(i);
            }
            else
            {
                string d = pdf_text.to_latin1();
                DataStore.push_back(pagecard(string(filepath.filename()), i, d));
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

/* void TextExtractor::GetLayeredText(fs::path filepath)
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

    else if(".docx")
    {
        DocxReader dr(filepath.c_str());
        return dr.GetText();//WordData
    }
    else if(".doc")
    {

    }
} */

/**
 * @brief Tries to recognize the text from the Djvu file
 * @param filepath path object of path to the file
 * @param DataStore reference to the vector of pagecards for storing the data
 * @param pageno the int vector of pages that need to be recognized
 * @return true if recognition is successfull, false otherwise
 */
bool TextExtractor::GetRecognizedTextDjvu(fs::path filepath, vector<pagecard>& DataStore, vector<int>& pageno)
{
    char* pPlainText;

    if(create_doc_djvu(filepath))
    {
        for(auto page: pageno)
        {
            cout<<"Recognition for "<<filepath<<" page "<<page<<endl;
            if( (pPlainText = dopage_text_recognition(pDoc_djvu, page)) == NULL)
            {
                corrupted_pages[filepath].push_back(page);
                continue;
            }
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

/**
 * @brief Tries to recognize the text from the PDF file
 * @param filepath path object of path to the file
 * @param DataStore reference to the vector of pagecards for storing the data
 * @param pageno the int vector of pages that need to be recognized
 * @return true if recognition is successfull, false otherwise
 */
bool TextExtractor::GetRecognizedTextPdf(fs::path filepath, vector<pagecard>& DataStore, vector<int>& pageno)
{
    char* pPlainText;

    if(create_doc_pdf(filepath))
    {
        for(auto page: pageno)
        {
            cout<<"Recognition for "<<filepath<<" page "<<page<<endl;
            if( (pPlainText = pdf_text_recognition(page, pDoc_pdf)) == NULL)
            {
                corrupted_pages[filepath].push_back(page);
                continue;
            }
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

/* void TextExtractor::GetRecognizedText(fs::path filepath, vector<int> pageno)
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
 */
