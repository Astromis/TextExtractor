#include "application.hpp"

Application::Application()
{
    page_count = 0;
}

Application::~Application()
{

}

string Application::name_generator(fs::path filepath)
{

    page_count++;
    string file_name = filepath.filename();
    return to_string(page_count) + "_extracted_" + file_name + ".txt";
}
 
void Application::process()
{
    fmanager.set_basedir("examples");
    
    vector<string>  exts = {".djvu", ".pdf"};
    
    vector<fs::directory_entry> files = fmanager.find_by_ext(exts);
    for(auto f: files)
    {
        extractor.GetLayeredText(f.path());
    }
    /* for(auto i: extractor.pages_without_text)
    {
        extractor.GetRecognizedText(i.first, i.second);
    } */
    fmanager.set_basedir("output");
    for(auto i: extractor.DataStore)
    {
        fmanager.append_path( i.filepath.filename() );
        if(!fmanager.exist()) fmanager.create();
        if(i.filepath.extension() == ".pdf") cout<<i.data<<endl;
        fmanager.write_to_file(name_generator(i.filepath), i.data.c_str());
        fmanager.step_back();
    }

}