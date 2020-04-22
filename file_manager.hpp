#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <vector>
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

    vector<fs::directory_entry> find_by_ext(vector<string> extensions);


};
