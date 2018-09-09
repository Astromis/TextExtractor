CC=g++
CFLAGS=-c -Wall -std=c++11 -g

all: test

test: main.o djvu_extractor.o pdf_extractor.o tesseract_wp.o text_extractor.o docx_reader.o czip.o
	$(CC) main.o djvu_extractor.o pdf_extractor.o tesseract_wp.o text_extractor.o docx_reader.o czip.o -std=c++11 -o test -llept -ltiff -ldjvulibre -ltesseract -lpoppler-cpp -lzip
    
main.o: main.cpp
	$(CC) $(CFLAGS) -c -std=c++11 main.cpp -I /usr/local/include/poppler/cpp/

text_extractor.o: text_extractor.cpp
	$(CC) $(CFLAGS) -c text_extractor.cpp -I /usr/local/include/poppler/cpp/

djvu_extractor.o: djvu_extractor.cpp
	$(CC) $(CFLAGS) -ltesseract -llept -ltiff -ldjvulibre djvu_extractor.cpp
	
pdf_extractor.o: pdf_extractor.cpp
	$(CC) $(CFLAGS) pdf_extractor.cpp -ltesseract -llept -lpoppler-cpp -I /usr/local/include/poppler/cpp/
	
tesseract_wp.o: tesseract_wp.cpp
	$(CC) $(CFLAGS) -ltesseract tesseract_wp.cpp 

#zcompressor.c:
#	$(CC) $(CFLAGS) -lz zcompressor.c

czip.o : czip.cpp
	$(CC) $(CFLAGS) -c czip.cpp -lzip 
	
docx_reader.o : docx_reader.cpp
	$(CC) $(CFLAGS) docx_reader.cpp -lzip

clean:
	rm -rf *.o test
