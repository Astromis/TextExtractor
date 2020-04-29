#include "text_extractor.h"
#include "file_manager.hpp"

class Application
{
    TextExtractor extractor;
    FileManager fmanager;
    string input_dir, output_dir;
    vector<string>  exts;
    vector<pagecard> data; 
    int save_counter;

    
    public:
    Application();
    ~Application();
    void process();
    string name_generator(fs::path filepath);
    
    int page_count;

    void SetInputDir(string inp_dir)
    {
        input_dir = inp_dir;
    }

    void SetOutputDir(string out_dir)
    {
        output_dir = out_dir;
    }

    void SetExtentions(vector<string> ex)
    {
        exts = ex;
    }
};


