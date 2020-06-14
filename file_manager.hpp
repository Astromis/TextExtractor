#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace fs = std::experimental::filesystem;
using namespace std;

//TODO:
//  Zip archivate condition

class FileManager
{
    private:
    const fs::path workdir = fs::current_path();
    fs::path basedir;
    fs::path current_location;


    public:
    void set_basedir(fs::path root);
    void set_relative_dir(fs::path path);
    void step_back();
    void append_path(fs::path path);
    bool exist();
    void create();

    FileManager();
    FileManager(fs::path root);
    ~FileManager();

    bool write_to_file(string filename, const char* Data);
    bool write_to_file(fs::path filepath, const char* Data);
    bool write_vector(vector<fs::directory_entry> v, string fname);
    bool write_pages_without_text(map<fs::path, vector<int> > pages_without, string fname);
    vector<fs::directory_entry> find_by_ext(vector<string> extensions);
    bool read_pages_without_text(map<fs::path, vector<int> >& pages_without, string fname);
    bool read_vector(vector<fs::directory_entry> v, string fname);
    int read_int(string fname);
    int write_int(int value, string fname);



};
