#include "czip.h"
#include <iostream>
#include <string>
using namespace std;

Zip::Zip(const char* fname)
{
    err = 0;
    filepath = fname;
    content_f = NULL;
    //data = NULL;

    if((z = zip_open(fname, 0, &err)) == NULL)
    {
        cout<<"Can't open file "<<(string)fname<<endl;
    }
    
    
}
Zip::Zip()
{
    content_f = NULL;
    //data = NULL;
    z = NULL;
}
Zip::~Zip()
{
    cout<<"Summon deconstr of zip"<<endl;
    if(content_f != NULL) zip_fclose(content_f);
    if(z != NULL) zip_close(z);
    //if(data != NULL) delete[] data;
}

void Zip::ReadData(char* cfname, string &data)
{
    if(content_f != NULL) zip_fclose(content_f);
    content_file_name = cfname;
    zip_stat_init(&st);
    zip_stat(z, content_file_name, 0, &st);
    //Allocalte memory for file data
    char* cdata = (char *)malloc(st.size);
    //Get pointer on file in archive 
    content_f = zip_fopen(z, content_file_name, 0);
    if(content_f == NULL)
    {
        printf("Content file %s doesn't exist.\n", content_file_name);
        //return NULL;
    }
    //Read data from inner file
    if(zip_fread(content_f, cdata, st.size) == -1)
    {
        cout<<"Cant read the data"<<endl;
        //exit(1);
    }
    zip_fclose(content_f);
    data = string(cdata);
    //cout<<data;
    content_f = NULL;
}