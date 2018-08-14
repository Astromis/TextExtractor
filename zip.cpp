#include <zip.hpp>

Zip::Zip(char* fname)
{
    err = 0;
    filepath = fname;
    inner_f = NULL;
    z = zip_open(fname, 0, &err);
    zip_stat_init(&st);
    
}

Zip::~Zip()
{
    zip_fclose(inner_f);
    zip_close(z);
    delete[] data;
}
void Zip::SetContentFileName(char* cfname)
{
    if(inner_f != NULL) zip_fclose(inner_f);
    zip_close(z);
    content_file_name = cfname;
    // I am not sure that it will be work. Need to test.
    // If it will not work, write reconstructing explicitly.
    *this = Zip(filepath);
}

char*  Zip::ReadData()
{
    inner_f = zip_fopen(z, content_file_name, 0);
    if(inner_f == NULL)
    {
        printf("Inner file %s doesn't exist\n", content_file_name);
        return NULL;
    }
    zip_fread(inner_f, data, st.size);
    zip_fclose(inner_f);

    return data;
}