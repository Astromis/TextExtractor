#include "application.hpp"

bool EXIT = false;

void signal_callback_handler(int signum)
{
    EXIT = true;
}
    

Application::Application()
{
    signal(SIGINT, signal_callback_handler);
    page_count = 0;
    _save_counter = 0;
    _save_counter_map = 0;
}

Application::~Application()
{

}

/**
 * @brief Generates the name for saving files
 * @param filepath based filepath oject
 * @return string of generated name
 */
string Application::name_generator(fs::path filepath)
{

    page_count++;
    string file_name = filepath.filename();
    return to_string(page_count) + "_extracted_" + file_name + ".txt";
}

void Application::save_state(map<fs::path, vector<int> > pages_without)
{
    fmanager.set_basedir("/home/astromis/git_projects/TextExtractor/save");
    if(_files.size() != (_save_counter +1))
    {
        std::vector<fs::directory_entry> file_to_save(_files.begin() + _save_counter, _files.end());
        fmanager.write_vector(file_to_save, "files.save");
    }

    if(pages_without.size() > 0)
    {
        auto map_it = pages_without.begin();
        for(int i=0; i < _save_counter_map ;i ++)
        {
            map_it++;
        } 
        map<fs::path, vector<int> > new_pages_without(map_it, pages_without.end());
        
        fmanager.write_pages_without_text(new_pages_without, "pages_without_text.save");
    }
    fmanager.write_int(page_count, "page_count.save");
}

bool Application::check_saved()
{
    bool res;
    fmanager.set_relative_dir("save");
    res = fmanager.exist();
    fmanager.step_back();
    return res;
}

void Application::load_state(map<fs::path, vector<int> >& pages_without_text)
{
    fmanager.set_basedir("/home/astromis/git_projects/TextExtractor/save");
    fmanager.read_vector(_files, "files.save");
    fmanager.read_pages_without_text(pages_without_text, "pages_without_text.save");
    page_count = fmanager.read_int("page_count.save");
}

void Application::write_data()
{
    fmanager.set_basedir(output_dir);

    for(auto i: data)
    {
        fmanager.append_path( i.filepath.filename() );
        if(!fmanager.exist()) fmanager.create();
        fmanager.write_to_file(name_generator(i.filepath), i.data.c_str());
        fmanager.step_back();
    }
}

/**
 * @brief Central function that do the job
 */
void Application::process()
{
    
    if(check_saved())
    {
        cout<<"Previous saved founded."<<endl;
        load_state(extractor.pages_without_text);
    }
    else {
        fmanager.set_basedir(input_dir);
        cout<<"Scanning directories..."<<endl;
        _files = fmanager.find_by_ext(exts);
        cout<<"Scanning finished."<<endl;
    } 
   
    int counter = 1;
    for(auto f: _files)
    {
        if(EXIT)
        {
            cout<<"EXIT is TURE";
            write_data();
            save_state(extractor.pages_without_text);
            exit(0);
        }
        cout<<"Process "<<counter<<"/"<<_files.size()<<" "<<f.path()<<endl;
        string ext = f.path().extension();
        if(ext == ".djvu")
        {
            if(extractor.GetTextLayerDjvu(f.path(), data))
            {
                _save_counter++;  
            }
            counter++;
        }
        else if(ext == ".pdf")
        {
            if(extractor.GetTextLayerPdf(f.path(), data))
            {
                _save_counter++;
            }
            counter++;
        }

        else if(ext == ".docx")
        {
            DocxReader dr(f.path().c_str());
            dr.GetText();
        }        
    }

    for(auto i: extractor.pages_without_text)
    {
        if(EXIT)
        {
            write_data();
            save_state(extractor.pages_without_text);
            exit(0);
        }
        string ext = i.first.extension();
        if(ext == ".djvu")
        {
            extractor.GetRecognizedTextDjvu(i.first, data, i.second);
            _save_counter_map++;
        }

        else if (ext == ".pdf")
        {
            extractor.GetRecognizedTextPdf(i.first, data, i.second);
            _save_counter_map++;
        }
        write_data();
        save_state(extractor.pages_without_text);
        exit(0);
    }
    write_data();
}