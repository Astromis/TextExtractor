#include "text_extractor.h"

int main()
{
    TextExtractor tx;
    tx.GetText("./examples/test.docx");
    tx.GetText("./examples/test_without_text.djvu");
    tx.GetText("./examples/test_without_text.pdf");
    tx.GetText("./examples/test_with_text.djvu");
    tx.GetText("./examples/test_with_text.pdf");
    return 0;
}
