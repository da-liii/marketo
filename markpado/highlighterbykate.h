#ifndef HIGHLIGHERBYKATE_H
#define HIGHLIGHERBYKATE_H

#include <string>
#include <map>
using std::string;
using std::map;

#include "libmdcpp.h"

class QString;


namespace KTextEditor {
    class Document;
    class Editor;
    class View;
};

class HighlighterByKate : SyntaxHighlighter
{
public:
    HighlighterByKate();
    virtual ~HighlighterByKate();
    
    virtual void highlight(const string& code, const string lang, std::ostream& out);
    QString exportDocument(KTextEditor::Document* note);
private:
    KTextEditor::Editor* m_new_editor;
    KTextEditor::Document* m_note;
    KTextEditor::View* m_editor;
    
    // see /usr/share/kde4/apps/katepart/syntax/ for more info
    map<string, string> mimeMap = {
        {"awk", "AWK"},
        {"bash", "Bash"},
        {"cpp", "C++"},
        {"c", "C"},
        {"zsh", "Zsh"},
        {"ocaml", "Objective Caml"},
        {"dot", "dot"},
        {"python", "Python"},
        {"py", "Python"},
        {"java", "Java"},
        {"javascript", "JavaScript"},
        {"js", "JavaScript"},
        {"hs", "Haskell"},
        {"haskell", "Haskell"},
        {"rb", "Ruby"},
        {"ruby", "Ruby"},
        {"scala", "Scala"},
        {"scm", "Scheme"},
        {"scheme", "Scheme"},
        {"sh", "Bash"}
    };
};
#endif
