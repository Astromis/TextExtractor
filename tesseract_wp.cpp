#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;

//
/**
 * @brief Basic tesseract wrapper for getting text
 * 
 * @param img [in] buffer that contain image data
 * @param size [in] size of buffer
 */
void gettext(char *img, size_t size)
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
}