#ifndef TESSERACT_WP_H
#define TESSERACT_WP_H

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

char* recognize_text(char *img, size_t size);
void monitorProgress(ETEXT_DESC *monitor, int page);
void ocrProcess(tesseract::TessBaseAPI *api, ETEXT_DESC *monitor);

#endif
