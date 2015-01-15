#ifndef HIGHLIGHERBYKATE_H
#define HIGHLIGHERBYKATE_H

#include <string>
#include <map>
using std::string;
using std::map;

class QString;


namespace KTextEditor {
    class Document;
};

class HighlighterByKate
{
public:
    HighlighterByKate();
    ~HighlighterByKate();
    
    string highlighted(string plain, string type);
    QString exportDocument(KTextEditor::Document* note);
private:
    map<string, string> mimeMap = {
        {"cpp", "C++"},
        {"c", "C"},
        {"zsh", "Zsh"},
        {"ocaml", "Objective Caml"},
        {"dot", "dot"},
        {"python", "Python"},
        {"py", "Python"},
        {"rb", "Ruby"},
        {"java", "Java"},
        {"hs", "Haskell"},
        {"haskell", "Haskell"},
        {"scm", "Scheme"},
        {"scheme", "Scheme"}
    };
};
#endif