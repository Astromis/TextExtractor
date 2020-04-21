#include <tesseract/baseapi.h>
#include <tesseract/ocrclass.h>
#include <leptonica/allheaders.h>
#include <thread>

using namespace std;




void monitorProgress(ETEXT_DESC *monitor, int page) {
    while (1) {
        printf( "OCR progress: \r%3d%%", monitor[page].progress);
        fflush (stdout);
        if (monitor[page].progress==100)
            break;
    }
}

void ocrProcess(tesseract::TessBaseAPI *api, ETEXT_DESC *monitor) {
    api->Recognize(monitor);
}


//
/**
 * @brief Basic tesseract wrapper for getting text
 * 
 * @param img [in] buffer that contain image data
 * @param size [in] size of buffer
 */
char*  recognize_text(char *img, size_t size)
{
    char * pOutText;
    PIX * image__;
    if ((image__ = pixReadMemPnm((unsigned char *)img, size)) == NULL)
    {
        printf("Error has occured");
    }

    char *outText;
    //ETEXT_DESC *monitor = new ETEXT_DESC();
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "rus")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    api->SetPageSegMode(tesseract::PSM_AUTO);
     //Open input image with leptonica library

    api->SetImage(image__);

    int page = 0;
    //std::thread t1(ocrProcess, api, monitor);
    //std::thread t2(monitorProgress, monitor, page);
    //t1.join();
    //t2.join();
    // Get OCR result
    pOutText = api->GetUTF8Text();
    printf("OCR output:\n%s", pOutText);

    // Destroy used object and release memory
    api->End();
    //delete [] outText;
    pixDestroy(&image__);
    return pOutText;
}