#include "text_extractor.h"
#include "file_manager.hpp"

class Application
{
    TextExtractor extractor;
    FileManager fmanager;

    public:
    Application();
    ~Application();
    void process();
    string name_generator(fs::path filepath);
    int page_count;
};


