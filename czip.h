#include <zip.h>
#include <string>

// Documentation
// https://libzip.org/documentation/libzip.html
class Zip
{
    //content file - file within zip file
    private:
        // I have suspicions that string class is better choice for storage string info.  
        char *content_file_name;
        const char* filepath;
        //char *data;
        struct zip_stat st;
        //file within zip file
        zip_file *content_f;
        zip *z;
        int err;


    public:
        Zip();
        Zip(const char* fname);
        ~Zip();
        void ReadData(char* cfname, std::string & data);
        // Empty
        void Create(char fname);
        int Find(char* fname);
};
