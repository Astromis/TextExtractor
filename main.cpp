#include "text_extractor.h"

int main()
{
    TextExtractor tx;
    string test;
    /* vector<string> files = {"./examples/test.docx"};
    tx.GetTextFromList(files);
    tx.PutTextsToFiles("./tests/"); */
    //tx.GetText("./examples/test.docx");
    //tx.GetText("./examples/test_without_text.djvu");
    //tx.GetText("./examples/test_without_text.pdf");
    cout<<tx.GetText("./examples/test_with_text.djvu", test);
    //cout<<test<<endl;
    //tx.GetText("./examples/test_with_text.pdf");
    
    return 0;
}
