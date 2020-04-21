#ifndef PDF_EXTRACTOR_H
#define PDF_EXTRACTOR_H

#include <iostream>

#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-image.h>
#include <poppler-page-renderer.h>

#include "tesseract_wp.h"


char* pdf_text_recognition(int pagenum, poppler::document* doc);
bool img_transform(poppler::image img, char *transform_img);

#endif
