#include "application.hpp"

Application::Application()
{
    page_count = 0;
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

/**
 * @brief Central function that do the job
 */
void Application::process()
{
    fmanager.set_basedir(input_dir);
    cout<<"Scanning directories..."<<endl;
    vector<fs::directory_entry> files = fmanager.find_by_ext(exts);
    cout<<"Scanning finished."<<endl;
    //fmanager.set_basedir("log");
    
    int save_counter = 0;
    /*
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
    int counter = 1;
    for(auto f: files)
    {
        cout<<"Process "<<counter<<"/"<<files.size()<<" "<<f.path()<<endl;
        string ext = f.path().extension();
        if(ext == ".djvu")
        {
            if(extractor.GetTextLayerDjvu(f.path(), data))
            {
                save_counter++;  
            }
            counter++;
        }
        else if(ext == ".pdf")
        {
            if(extractor.GetTextLayerPdf(f.path(), data))
            {
                save_counter++;
            }
            counter++;
        }
        //if(counter == 1000) break;
        
    }
    cout<<endl;

    /* for(auto i: extractor.pages_without_text)
    {
        string ext = i.first.extension();
        if(ext == ".djvu")
        {
            extractor.GetRecognizedTextDjvu(i.first, data, i.second);
        }
        else if (ext == ".pdf")
        {
            extractor.GetRecognizedTextPdf(i.first, data, i.second);
        }
    } */

    fmanager.set_basedir(output_dir);

    for(auto i: data)
    {
        fmanager.append_path( i.filepath.filename() );
        if(!fmanager.exist()) fmanager.create();
        fmanager.write_to_file(name_generator(i.filepath), i.data.c_str());
        fmanager.step_back();
    }

}