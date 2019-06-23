#include "text_extractor.h"

int main()
{
    TextExtractor tx;
    vector<string> files = {"/home/igor/git_projects/test/text_extractor/examples/test.docx"};
    tx.GetTextFromList(files);
    tx.PutTextsToFiles("./tests/");
    //tx.GetText("./examples/test.docx");
    //tx.GetText("./examples/test_without_text.djvu");
    //tx.GetText("./examples/test_without_text.pdf");
    //tx.GetText("./examples/test_with_text.djvu");
    //tx.GetText("./examples/test_with_text.pdf");
    
    return 0;
}
