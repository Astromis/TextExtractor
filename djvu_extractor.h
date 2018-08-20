#ifndef DJVU_EXTRACTOR_H
#define DJVU_EXTRACTOR_H


# include "djvu_config.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <locale.h>
#include <fcntl.h>
#include <errno.h>
#undef HAVE_TIFF2PDF
#ifdef UNIX
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
#endif


#include "libdjvu/ddjvuapi.h"
#include "libdjvu/miniexp.h"
#include "tesseract_wp.h"

/* Djvuapi events */
void handle(int wait);
void  die(const char *fmt, ...);

void render(ddjvu_page_t *page, int pageno);
void dopage_text_recognition(int pageno);
void dopage_text_extract(miniexp_t r, const char * detail, int escape);
void get_text_from_djvu(const char* filename, int pagenum, char* detail = "page");

#endif
