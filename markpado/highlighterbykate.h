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
    
    // see /usr/share/katepart5/syntax/ for more info
    map<string, string> mimeMap = {
        {"dot", "dot"},
        {"mysql", "SQL (MySQL)"},
        {"ocaml", "Objective Caml"},
        // by name
        {"cmake", "CMake"},
        {"diff", "Diff"},
        {"dockerfile", "Dockerfile"},
        {"PHP", "PHP/PHP"},
        {"R", "R Script"},
        // by suffix
        {"awk", "AWK"},
        {"c", "C"},
        {"clj", "Clojure"},
        {"cpp", "C++"},
        {"css", "CSS"},
        {"erl", "Erlang"},
        {"for", "Fortran"},
        {"fpp", "Fortran"},
        {"go", "Go"},
        {"hs", "Haskell"},
        {"ini", "INI Files"},
        {"java", "Java"},
        {"jl", "Julia"},
        {"js", "JavaScript"},
        {"json", "JSON"},
        {"lua", "Lua"},
        {"mk", "Makefile"},
        {"php", "PHP/PHP"},
        {"py", "Python"},
        {"qml", "QML"},
        {"r", "R Script"},
        {"rb", "Ruby"},
        {"rs", "Rust"},
        {"scala", "Scala"},
        {"scm", "Scheme"},
        {"sql", "SQL"},
        {"sh", "Bash"},
        {"zsh", "Zsh"}
    };
};
#endif
