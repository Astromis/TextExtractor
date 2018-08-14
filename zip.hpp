#include <zip.h>
#include <string>

class Zip
{
    //content file - file within zip file
    private:
        // I have suspicions that string class is better choice for storage string info.  
        char *content_file_name;
        char *filepath;
        char *data;
        struct zip_stat st;
        //file within zip file
        zip_file *inner_f;
        zip *z;
        int err;

    public:
        Zip();
        Zip(char* fname);
        ~Zip();
        void SetContentFileName(char * cfname);
        char* ReadData();
        void Create(char fname);


}
