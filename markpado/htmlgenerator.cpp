#include "htmlgenerator.h"
#include "highlighterbykate.h"
#include "libmdcpp.h"

#include <sstream>
#include <iostream>
using std::istringstream;
using std::ostringstream;

HTMLGenerator::HTMLGenerator()
{
    m_highlighter = new HighlighterByKate;
}

std::string HTMLGenerator::generated(string plain)
{
    ostringstream sout;

    Procesoro processor((SyntaxHighlighter *) m_highlighter, "markdown");
    std::cout << "[debug]" << plain;
    processor.read(plain);
    processor.write(sout);
    
    return string(sout.str());
}

HTMLGenerator::~HTMLGenerator()
{

}
