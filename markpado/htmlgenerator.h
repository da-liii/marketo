#ifndef HTMLGENERATOR_H
#define HTMLGENERATOR_H

#include "highlighterbykate.h"

#include <string>
using std::string;

class HTMLGenerator {
public:
    HTMLGenerator();
    ~HTMLGenerator();
    string generated(string plain);
private:
    string result;
    HighlighterByKate *m_highlighter;
};

#endif