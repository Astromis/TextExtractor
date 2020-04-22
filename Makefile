CC=g++
CFLAGS=-c -Wall -std=c++11 -g

all: test

test: application.o file_manager.o main.o djvu_extractor.o pdf_extractor.o tesseract_wp.o text_extractor.o docx_reader.o czip.o
	$(CC) main.o application.o file_manager.o djvu_extractor.o pdf_extractor.o tesseract_wp.o text_extractor.o docx_reader.o czip.o -std=c++11 -o test -llept -ltiff -ldjvulibre -ltesseract -lpoppler-cpp -lzip -lpthread -lstdc++fs
    
main.o: main.cpp
	$(CC) $(CFLAGS) -c -std=c++11 main.cpp -I /usr/include/poppler/cpp/ -lpthread -lstdc++fs

application.o: application.cpp
	$(CC) $(CFLAGS) -c -std=c++11 application.cpp -I /usr/include/poppler/cpp/ -lstdc++fs

file_manager.o: file_manager.cpp
	$(CC) $(CFLAGS) -c -std=c++11 file_manager.cpp -I /usr/include/poppler/cpp/ -lstdc++fs

text_extractor.o: text_extractor.cpp
	$(CC) $(CFLAGS) -c text_extractor.cpp -I /usr/include/poppler/cpp/ -lstdc++fs

djvu_extractor.o: djvu_extractor.cpp
	$(CC) $(CFLAGS) -ltesseract -llept -ltiff -ldjvulibre djvu_extractor.cpp -lstdc++fs
	
pdf_extractor.o: pdf_extractor.cpp
	$(CC) $(CFLAGS) pdf_extractor.cpp -ltesseract -llept -lpoppler-cpp -I /usr/include/poppler/cpp/ -lstdc++fs
	 
tesseract_wp.o: tesseract_wp.cpp
	$(CC) $(CFLAGS) -ltesseract tesseract_wp.cpp -lpthread -lstdc++fs

#zcompressor.c:
#	$(CC) $(CFLAGS) -lz zcompressor.c

czip.o : czip.cpp
	$(CC) $(CFLAGS) -c czip.cpp -lzip 
	
docx_reader.o : docx_reader.cpp
	$(CC) $(CFLAGS) docx_reader.cpp -lzip

clean:
	rm -rf *.o test
