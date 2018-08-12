#include "pdf_extractor.h"

using namespace std;

//g++ test_poppler.cpp -std=c++11 pnmwritter.cpp -ltesseract -llept -lpoppler-cpp

//Tesseract wrapper for getting text
/* void gettext(char *img, size_t size)
{
    PIX * image__;
    if ((image__ = pixReadMemPnm((unsigned char *)img, size)) == NULL)
    {
        printf("Error has occured");
    }

    char *outText;
    
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "rus")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

     //Open input image with leptonica library

    api->SetImage(image__);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete [] outText;
    pixDestroy(&image__);
} */

bool img_transform(poppler::image img, char *transform_img)
{
    int preable = 0;
    int row_length = img.width()*3;
    preable = sprintf(transform_img,"P6\n%d %d\n255\n", img.width(), img.height()); 

    char *hptr = img.data();
    size_t count =0;
    unsigned char **row;
    for (int y = 0; y < img.height(); ++y) {
        row = reinterpret_cast<unsigned char **>(&hptr);
        memcpy(transform_img+preable + y*row_length, (*row), row_length);
        count += row_length;
        hptr += img.bytes_per_row();
    }
}

void pdf_txt_recog(int pagenum, poppler::document* doc)
{
    poppler::image img;
    poppler::page_renderer render;
    char temp [64]; //crutch!!
    size_t img_size = 0;

    img = render.render_page(doc->create_page(pagenum));
    int prem_len = sprintf(temp,"P6\n%d %d\n255\n", img.width(), img.height());
    img_size = img.height() * img.width()*3 + prem_len;
    char * pnm_img =  new char [img_size];
    img_transform(img, pnm_img);
    gettext(pnm_img, img_size);
    delete pnm_img;
}

void get_text_from_pdf(const char* pathfile, int pagenum)
{
    
    poppler::document *doc = poppler::document::load_from_file(pathfile);
    const int pagesNbr = doc->pages();
    
    
    poppler::ustring txt;
    
    if(pagenum)
    {
        //cout << doc->create_page(i)->text().to_latin1().c_str() << endl;
        txt = doc->create_page(pagenum)->text();
        if( txt.length() == 0)
        {
            pdf_txt_recog(pagenum, doc);
        }
        //if(text) if text exist that put it in buffer
        else
        {
            cout << txt.to_latin1().c_str()<<endl;
        }
    }
    else
        for (int i = 0; i < pagesNbr; ++i)
        {
            txt = doc->create_page(i)->text();
            //cout << doc->create_page(i)->text().to_latin1().c_str() << endl;
            if(txt.length() == 0)
            {
                pdf_txt_recog(i, doc);
            }
            //if(text) if text exist that put it in buffer
            else
            {
                cout << txt.to_latin1().c_str()<<endl;
            }
        }


}
/*
int main()
{
    get_text_from_pdf("./test.pdf", 1);
    return 0;
}*/
