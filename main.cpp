#include "application.hpp"

int main()
{
    Application app;
    app.SetInputDir("/home/astromis/git_projects/TextExtractor/examples");//  /media/astromis/HITACHI/Документы Игоря/Документы/Научные и справочные материалы
    // 
    app.SetOutputDir("/home/astromis/git_projects/TextExtractor/");
    app.SetExtentions({".djvu", });
    app.process();
    
    return 0;
}
