//C-  -*- C++ -*-
//C- -------------------------------------------------------------------
//C- DjVuLibre-3.5
//C- Copyright (c) 2002  Leon Bottou and Yann Le Cun.
//C- Copyright (c) 2001  AT&T
//C-
//C- This software is subject to, and may be distributed under, the
//C- GNU General Public License, either Version 2 of the license,
//C- or (at your option) any later version. The license should have
//C- accompanied the software or you may obtain a copy of the license
//C- from the Free Software Foundation at http://www.fsf.org .
//C-
//C- This program is distributed in the hope that it will be useful,
//C- but WITHOUT ANY WARRANTY; without even the implied warranty of
//C- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//C- GNU General Public License for more details.
//C- 
//C- DjVuLibre-3.5 is derived from the DjVu(r) Reference Library from
//C- Lizardtech Software.  Lizardtech Software has authorized us to
//C- replace the original DjVu(r) Reference Library notice by the following
//C- text (see doc/lizard2002.djvu and doc/lizardtech2007.djvu):
//C-
//C-  ------------------------------------------------------------------
//C- | DjVu (r) Reference Library (v. 3.5)
//C- | Copyright (c) 1999-2001 LizardTech, Inc. All Rights Reserved.
//C- | The DjVu Reference Library is protected by U.S. Pat. No.
//C- | 6,058,214 and patents pending.
//C- |
//C- | This software is subject to, and may be distributed under, the
//C- | GNU General Public License, either Version 2 of the license,
//C- | or (at your option) any later version. The license should have
//C- | accompanied the software or you may obtain a copy of the license
//C- | from the Free Software Foundation at http://www.fsf.org .
//C- |
//C- | The computer code originally released by LizardTech under this
//C- | license and unmodified by other parties is deemed "the LIZARDTECH
//C- | ORIGINAL CODE."  Subject to any third party intellectual property
//C- | claims, LizardTech grants recipient a worldwide, royalty-free, 
//C- | non-exclusive license to make, use, sell, or otherwise dispose of 
//C- | the LIZARDTECH ORIGINAL CODE or of programs derived from the 
//C- | LIZARDTECH ORIGINAL CODE in compliance with the terms of the GNU 
//C- | General Public License.   This grant only confers the right to 
//C- | infringe patent claims underlying the LIZARDTECH ORIGINAL CODE to 
//C- | the extent such infringement is reasonably necessary to enable 
//C- | recipient to make, have made, practice, sell, or otherwise dispose 
//C- | of the LIZARDTECH ORIGINAL CODE (or portions thereof) and not to 
//C- | any greater extent that may be necessary to utilize further 
//C- | modifications or combinations.
//C- |
//C- | The LIZARDTECH ORIGINAL CODE is provided "AS IS" WITHOUT WARRANTY
//C- | OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
//C- | TO ANY WARRANTY OF NON-INFRINGEMENT, OR ANY IMPLIED WARRANTY OF
//C- | MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//C- +------------------------------------------------------------------


/* Program ddjvu has been rewritten to use the ddjvuapi only.
 * This file should compile both as C and C++. 
 */

#include "djvu_extractor.h"
#include "tesseract_wp.h" 

//#if HAVE_PUTC_UNLOCKED
# undef putc
# define putc putc_unlocked
//#endif

/* Some day we'll redo i18n right. */
#ifndef i18n
# define i18n(x) (x)
# define I18N(x) (x)
#endif

using namespace std;

//ddjvu_context_t *ctx;
//ddjvu_document_t *doc;

unsigned long timingdata[4];

double       flag_scale = -1;
int          flag_size = -1;
int          flag_aspect = -1;
int          flag_subsample = -1;
int          flag_segment = 0;
int          flag_verbose = 0;
char         flag_mode = 0;     /* 'c', 'k', 's', 'f','b' */
char         flag_format = 0;   /* '4','5','6','p','r','t', 'f' */
int          flag_quality = -1; /* 1-100 jpg, 900 zip, 901 lzw, 1000 raw */
int          flag_skipcorrupted = 0;
int          flag_eachpage = 0;
const char  *flag_pagespec = 0; 
ddjvu_rect_t info_size;
ddjvu_rect_t info_segment;
const char  *programname = 0;
const char  *inputfilename = 0;
const char  *outputfilename = 0;

char *pagefilename = 0;
//#if HAVE_TIFF2PDF
char *tempfilename = 0;
int tiffd = -1;
//#endif
//#if HAVE_TIFF
//TIFF *tiff = 0;
//#endif
FILE *fout = 0;


void 
die(const char *fmt, ...)
{
  /* Handling messages might give a better error message */
  //handle(FALSE);
  /* Print */
  va_list args;
  fprintf(stderr,"ddjvu: ");
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr,"\n");
  /* Cleanup */
#if HAVE_TIFF2PDF
  if (tiffd >= 0)
    close(tiffd);
  if (tempfilename)
    remove(tempfilename);
#endif
  /* Terminates */
  exit(10);
}

/**
 * @brief Render page from djvu. Currently it rander to PNM only
 * 
 * @param page [in] djvulibre object
 * @param pageno number of page
 * @param img pointer for storing rendered image
 * @return size of the picture, 0 otherwise
 */
unsigned int
render(ddjvu_page_t *page, int pageno, char * &img)
{
  size_t size = 0;

  ddjvu_rect_t prect;
  ddjvu_rect_t rrect;
  ddjvu_format_style_t style;
  ddjvu_render_mode_t mode;
  ddjvu_format_t *fmt;
  int iw = ddjvu_page_get_width(page);
  int ih = ddjvu_page_get_height(page);
  int dpi = ddjvu_page_get_resolution(page);
  //ddjvu_page_type_t type = ddjvu_page_get_type(page);
  char *image = 0;
  char white = (char)0xFF;
  unsigned int rowsize;
  //PAY ATTENTION ON THIS RAW !!!. Somewhere occure error when tesseract is breakdown.
  flag_format = 1;
  
  /* Process size specification */
  prect.x = 0;
  prect.y = 0;
  if (flag_size > 0)
    {
      prect.w = info_size.w;
      prect.h = info_size.h;
    }
  else if (flag_subsample > 0)
    {
      prect.w = (iw + flag_subsample - 1) / flag_subsample;
      prect.h = (ih + flag_subsample - 1) / flag_subsample;
    }
  else if (flag_scale > 0)
    {
      prect.w = (unsigned int) (iw * flag_scale) / dpi;
      prect.h = (unsigned int) (ih * flag_scale) / dpi;
    }
  else if (flag_format)
    {
      prect.w = iw;
      prect.h = ih;
    }
  else
    {
      prect.w = (iw * 100) / dpi;
      prect.h = (ih * 100) / dpi;
    }
  /* Process aspect ratio */
  if (flag_aspect <= 0)
    {
      double dw = (double)iw / prect.w;
      double dh = (double)ih / prect.h;
      if (dw > dh) 
        prect.h = (int)(ih / dw);
      else
        prect.w = (int)(iw / dh);
    }

  /* Process segment specification */
  rrect = prect;
  if (flag_segment > 0)
    {
      rrect = info_segment;
      if (rrect.x < 0)
        rrect.x = prect.w - rrect.w + rrect.x;
      if (rrect.y < 0)
        rrect.y = prect.h - rrect.h + rrect.y;
    }

    mode = DDJVU_RENDER_BLACK; // DDJVU_RENDER_MASKONLY DDJVU_RENDER_BLACK(!) DDJVU_RENDER_BACKGROUND DDJVU_RENDER_FOREGROUND

  /* Determine output pixel format and compression */
  style = DDJVU_FORMAT_MSBTOLSB; // DDJVU_FORMAT_MSBTOLSB DDJVU_FORMAT_RGB24

  if (! (fmt = ddjvu_format_create(style, 0, 0)))
    die(i18n("Cannot determine pixel style for page %d"), pageno);
  ddjvu_format_set_row_order(fmt, 1);
  /* Allocate buffer */
  if (style == DDJVU_FORMAT_MSBTOLSB) {
    white = 0x00;
    rowsize = (rrect.w + 7) / 8; 
  } else if (style == DDJVU_FORMAT_GREY8)
    rowsize = rrect.w;
  else
    rowsize = rrect.w * 3; 
  if (! (image = (char*)malloc(rowsize * rrect.h)))
    die(i18n("Cannot allocate image buffer for page %d"), pageno);

  /* Render */
  if (! ddjvu_page_render(page, mode, &prect, &rrect, fmt, rowsize, image))
    memset(image, white, rowsize * rrect.h);

  
  /* -------------- PNM output */
  img = (char*)malloc(100 + rrect.h * rowsize);
  int i =0;
  size_t j =0;
  char *s = image;
  if (style == DDJVU_FORMAT_MSBTOLSB) {
    if (flag_verbose) 
      fprintf(stderr,i18n("Producing PBM file.\n"));
    
    sprintf(img,"P4\n%d %d\n", rrect.w, rrect.h);
  } else if (style == DDJVU_FORMAT_GREY8) {
    if (flag_verbose) 
      fprintf(stderr,i18n("Producing PGM file.\n"));
    
    sprintf(img,"P5\n%d %d\n255\n", rrect.w, rrect.h);
  } else {
    if (flag_verbose) 
      fprintf(stderr,i18n("Producing PPM file.\n"));
    
    sprintf(img,"P6\n%d %d\n255\n", rrect.w, rrect.h);
  }
  
  size = +strlen(img);

  for (i=0; i<(int)rrect.h; i++)
  {
    // passing the header of file format
    if(i == 0) j = strlen(img); else j = i*rowsize; 
    for(;j<rowsize*(i+1);j++)
    {
      img[j] = *s;
      s++;
    }
    size += rowsize;
  }
  ddjvu_format_release(fmt);
  free(image);
  return size;
}

/**
 * @brief Regonize text from rendered page
 * 
 * @param pDoc pointer of DJVU documet
 * @param pageno [in] page number
 * @return The char pointer on text, NULL otherwise
 */
char* dopage_text_recognition(ddjvu_document_t *pDoc, int pageno)
{
  char* TextData;
  ddjvu_page_t *page;
  /* Decode page */
  if (! (page = ddjvu_page_create_by_pageno(pDoc, pageno-1)))
  {
      cout<<"Cannot access page ."<<pageno<<endl;
      return NULL;
  }
  while (! ddjvu_page_decoding_done(page))
    continue;
  if (ddjvu_page_decoding_error(page))
    {
      cout<<"Cannot decode page"<<pageno<<endl;
      return NULL;
    }

  /* Render */
  char* image = NULL;
  unsigned int img_size;
  if((img_size = render(page, pageno, image)) == 0)
  {
    printf("Page of djvy isn't renered into a picture\n");
    return NULL;
  }

  TextData = recognize_text(image, img_size);    
  free(image);
  ddjvu_page_release(page);
  return TextData;

}

/**
 * @brief Extract text layer from djvu
 * 
 * @param r [in] djvuLibere object that contain text
 * @param detail [in] see djvu doc
 * @param escape [in] see djvu doc
 */
char * dopage_text_extract(miniexp_t r, const char * detail, int escape)
{
  //char * TextData;
  if ((r = miniexp_nth(5, r)) && miniexp_stringp(r))
  {
    return (char *)miniexp_to_str(r); 
  }
  else
  {
    std::cout<<"Page has not contain a text"<<std::endl;
    return NULL;
  } 
  //return false;
  }
