#include "application.hpp"

int main()
{
    Application app;
    app.SetInputDir("/media/astromis/HITACHI/Документы Игоря/Документы/Научные и справочные материалы");// /home/astromis/git_projects/TextExtractor/examples
    // 
    app.SetOutputDir("/home/astromis/output_");
    app.SetExtentions({".djvu", });
    app.process();
    
    return 0;
}
