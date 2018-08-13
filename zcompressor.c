#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "zlib.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

// Links:
// http://zlib.net.ru/#compress
// https://zlib.net/manual.html
// https://eax.me/zlib/

//TODO: There is no methods in the library that can pick up size of uncompressed data from compressed file
// It probably to solve by appending this information in file directly

Bytef* compress_memory(char * buf_in, uLongf buf_size)
{
    // TODO: maybe this function should return size of compressed buffer 
    // and take pointer on this buffer in argumetns
    // And it will look like
    // pointer = (Bytef*)malloc(compress_buff_size);
    uLongf compress_buff_size = compressBound(buf_size);
    Bytef* compress_buff = (Bytef*)malloc(compress_buff_size);
    {
        fprintf(stderr,
            "malloc(compress_buff_size) failed, "
            "compress_buff_size = %lu\n",
            compress_buff_size);
        exit(1);
    }

    int res = compress(compress_buff, &compress_buff_size, buf_in, buf_size);
    if(res != Z_OK)
    {
        fprintf(stderr, "compress(...) failed, res = %d\n", res);
        exit(1);
    }
    return compress_buff;
}

void uncompress_memory(Bytef* buf_in, uLongf buf_size)
{
    uLongf decompressed_size = buf_size; // ?
    res = uncompress(buf_in, &decompressed_size,
        buf_in, buf_size);
    if(res != Z_OK)
    {
        fprintf(stderr, "uncompress(...) failed, res = %d\n", res);
        exit(1);
    }
}

void write_buf_into_gz(const char* file_path, const char* mode, char * buf, size_t buf_size)
{
    gzFile file  =  gzopen(file_path, mode);
    while(gzeof(file) != 1)
    {
        gzwrite(file, buf, buf_size);
    }
    gzclose(file);
}

/* void read_file_into_buf(const char* file_path, const char* mode, char * buf, size_t buf_size)
{
    gzFile file  =  gzopen(file_path, mode);
    while(gzeof(file) != 1)
    {

} */

int main()
{
    SET_BINARY_MODE(stdin);
    SET_BINARY_MODE(stdout);

    FILE * f = fopen("test.c", "rb");
    if(f == NULL)
    {
        printf("Error openig file");
        exit(1);
    }
    //get a size of file
    long lSize = ftell(f);
    printf("size init buff: %lo\n", lSize);
    unsigned char * buffer = (unsigned char*) malloc(sizeof(unsigned char) * lSize);
    uLongf result = fread(buffer, 1, lSize, f);
    gzdopen(f, "wb9");
    fclose(f);
    
}
