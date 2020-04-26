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
    /* fmanager.set_basedir("log");
    
    int save_counter = 0;
    for(int _ = 0;  _ < files.size(); _++)
    {
        save_counter++;
        fs::directory_entry d = files[files.size() - 1];
        extractor.GetLayeredText(d.path());
        files.pop_back();
        if(save_counter == 100)
        {
            fmanager.write_vector(files, "unprocessed_lay.txt");
        }
    }

    save_counter = 0;
    for(int _ = 0;  _ < extractor.pages_without_text.size(); _++)
    {
        save_counter++;
        
        //fs::directory_entry d = files[files.size() - 1];
        extractor.GetLayeredText(d.path());
        files.pop_back();
        if(save_counter == 100)
        {
            fmanager.write_vector(files, "unprocessed_recog.txt");
        }
    } */
    for(auto f: files)
    {
        extractor.GetLayeredText(f.path());
    }
    for(auto i: extractor.pages_without_text)
    {
        extractor.GetRecognizedText(i.first, i.second);
    }
    fmanager.set_basedir("output");
    for(auto i: extractor.DataStore)
    {
        fmanager.append_path( i.filepath.filename() );
        if(!fmanager.exist()) fmanager.create();
        fmanager.write_to_file(name_generator(i.filepath), i.data.c_str());
        fmanager.step_back();
    }

}