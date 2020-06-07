#include "file_manager.hpp"
#include <cstring> 
struct compare
{
	string key;
	compare(string const &i): key(i) { }

	bool operator()(string const &i)
	{
		return (i == key);
	}
};
/**
 * @brief Filter files by extentions
 * @param extensions vector of string with desired extentions
 * @return vecotor of dir_entries with filtered files
 */ 
vector<fs::directory_entry> FileManager::find_by_ext(vector<string> extensions)
{
    vector<fs::directory_entry> files;
    for(const auto& p: fs::recursive_directory_iterator(current_location))
    {    
        if(is_regular_file(p) && p.path().has_extension())
        {
            string ext = p.path().extension();
            if(any_of(extensions.begin(), extensions.end(), compare(ext)))
                files.push_back(p);
        }
    }
    return files;
}

FileManager::FileManager()
{

}
FileManager::FileManager(fs::path root)
{
    set_basedir(root);
}

FileManager::~FileManager()
{
    
}

void FileManager::set_basedir(fs::path root)
{
    basedir = root;
    if(!fs::exists(basedir))
    {
        fs::create_directories(basedir);
    } 
    current_location = basedir;
}

void FileManager::set_relative_dir(fs::path path)
{
    current_location = basedir / path;
}

void FileManager::step_back()
{
    current_location = current_location.parent_path();
}

void FileManager::append_path(fs::path path)
{
    current_location = current_location / path;
}

/**
 * @brief Check weather the location exists
 */
bool FileManager::exist()
{
    return fs::exists(current_location);
}

void FileManager::create()
{
    fs::create_directories(current_location);
}

/**
 * @brief write data to a file based on current location
 * @param filename string with filename
 * @param Data const char pointer on data that need to be writen
 */
bool FileManager::write_to_file(string filename, const char* Data)
{
    fs::path filepath = current_location / filename;
    ofstream file;
    file.open(filepath);
    if (!file.is_open())
    {
        cout<<"Cannot open the file for writing!"<< filepath << std::endl;
        cout<<"Check if the location exists"<<endl;
        return false;
    } 
    file<<Data;
    file.close();
    return true;
}

/**
 * @brief write data to a file based on fiven location
 * @param filepath path object of path to write that data
 * @param Data const char pointer on data that need to be writen
 */

bool FileManager::write_to_file(fs::path filepath, const char* Data)
{
    ofstream file;
    file.open(filepath);
    if (!file.is_open())
    {
        cout<<"Cannot open the file for writing!"<< filepath << std::endl;
        cout<<"Check if the location exists"<<endl;
        return false;
    } 
    file<<Data;
    file.close();
    return true;
}

bool FileManager::write_vector(vector<fs::directory_entry> v, string fname)
{
    ofstream file;
    fs::path filepath = current_location / fname;
    file.open(filepath);
    if (!file.is_open())
    {
        cout<<"Cannot open the file for writing!"<< filepath << std::endl;
        cout<<"Check if the location exists"<<endl;
        return false;
    } 
    for(auto i:v)
    {

        file<<i.path()<<endl;
    }
    file.close();
    return true;
}