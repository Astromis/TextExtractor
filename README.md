# TextExtractor

## Overview
This program unites some pieces of open sourced tools to provide the way for extracting of raw text from
 
* djvu
* docx
* pdf

An extraction consists of two steps: if text layer exists then extract it. If doesn't, apply the OCR by the Tesseract engine. Extracted text is being written in text file.

## Requirement libraries and installation:
List of libraries:
```bash
sudo apt-get install libzip-dev libpoppler-cpp-dev libdjvulibre-dev libtesseract-dev libleptonica-dev libtiff-dev
```
After that, jsut type **make** in the root directory. If there is fatal error "No such files or directory", make sure the libraries heades has installed in /usr/include/ or you can change that in Makefile.

You, also, need the data for the Tesseract. You can find it in *tessdata* directory of the repo or you can download it from official wiki on github [here](https://github.com/tesseract-ocr/tesseract/wiki/Data-Files). Having done donwloading, you can put it in 
```
/usr/share/tesseract-ocr/tessdata/
```
or you can set the environmental variable on arbitrary directory:
```bash
export TESSDATA_PREFIX=/path/to/downloaded/data
```

### Helpful tips for working with Tesseract-cli
* -l -> specify the language
* -c tessedit_write_images=true -> creates a result of preprocessed image.


## Further work
* Add supporting doc files
* Add spellcheking and post OCR processing