#include "pdf_extractor.h"

using namespace std;

//g++ test_poppler.cpp -std=c++11 pnmwritter.cpp -ltesseract -llept -lpoppler-cpp


/**
 * @brief Transfrom image to PNB
 * 
 * @param img [in] poopler object of image
 * @param transform_img [in|out] buffer, in which will save pnb image
 * @return true if transformation complite
 * @return false 
 */
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
    return true;
}
/**
 * @brief Recognize text from rendered pdf page
 * 
 * @param pagenum [in] Number of page
 * @param doc [in] poppler object of pdf document
 */
char* pdf_text_recognition(int pagenum, poppler::document* doc)
{
    char* pTextData;
    poppler::image img;
    poppler::page_renderer render;
    char temp [64]; //crutch!!
    size_t img_size = 0;

    const poppler::page *pPage;
    if((pPage = doc->create_page(pagenum)) == NULL)
    {
        cout<<"Couldn't create PDF page for recognition"<<endl;
        return NULL;
    }
    img = render.render_page(pPage);
    int prem_len = sprintf(temp,"P6\n%d %d\n255\n", img.width(), img.height());
    img_size = img.height() * img.width()*3 + prem_len;
    char * pnm_img =  new char [img_size];
    img_transform(img, pnm_img);
    pTextData = recognize_text(pnm_img, img_size);
    delete pnm_img;
    return pTextData;
}