#ifndef HIGHLIGHERBYKATE_H
#define HIGHLIGHERBYKATE_H

#include <string>
using namespace std;

class QString;
namespace KTextEditor {
    class Document;
};

class HighlighterByKate
{
public:
    HighlighterByKate();
    ~HighlighterByKate();
    
    string highlighted(string plain);
    QString exportDocument(KTextEditor::Document* note);
};
#endif