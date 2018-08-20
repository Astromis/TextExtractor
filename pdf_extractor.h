#ifndef PDF_EXTRACTOR_H
#define PDF_EXTRACTOR_H

#include <iostream>

#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-image.h>
#include <poppler-page-renderer.h>

#include "tesseract_wp.h"


void get_text_from_pdf(const char* pathfile, int pagenum);
void pdf_txt_recog(int pagenum, poppler::document* doc);
bool img_transform(poppler::image img, char *transform_img);

#endif
