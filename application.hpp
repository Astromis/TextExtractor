#include "text_extractor.h"
#include "file_manager.hpp"
#include <unistd.h>
#include <signal.h>

class Application
{
    TextExtractor extractor;
    FileManager fmanager;
    string input_dir, output_dir;
    vector<string>  exts;
    vector<pagecard> data; 
    int _save_counter, _save_counter_map;
    vector<fs::directory_entry> _files;
    
    public:
    Application();
    ~Application();
    void process();
    string name_generator(fs::path filepath);
    void save_state(map<fs::path, vector<int> > pages_without);
    void load_state(map<fs::path, vector<int> >& pages_without);
    bool check_saved();
    void write_data();

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


