#include "application.hpp"

int main()
{
    Application app;
    app.SetInputDir("examples");
    app.SetOutputDir("output");
    app.SetExtentions({".djvu", ".pdf"});
    app.process();
    
    return 0;
}
