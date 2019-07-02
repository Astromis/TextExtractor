# TextExtractor

## Overview
This program unites some pieces of open source tools to provide the way for extracting of raw text from
 
* djvu
* docx
* pdf

An extraction consists of two steps: if text layer exists then extract it. If doen't, apply the OCR by the Tesseract engine. Extracted text is being written in text file.

## Requirement libraries and installation:
List of libraries:
```bash
    sudo apt-get install libzip-dev libpoppler-cpp-dev libdjvulibre-dev libtesseract-dev libleptonica-dev
```
After that jsut type **make** in the root directory. If there is fatal error "No such files or directory", make sure the libraries heades has installed in /usr/unclude/ or you can change that in the make file

You, also, need the data for training the Tesseract. It can be downloaded from official wiki on github [here](https://github.com/tesseract-ocr/tesseract/wiki/Data-Files). Having done donwloading, set the environmental variable:
```bash
export TESSDATA_PREFIX=/path/to/downloaded/data
```
In this directory, create one more dir named *tessdata* and place trained data there.

## Further work
* Add supporting doc files
* Add spellcheking and post OCR processing
* Add more friendly installation
