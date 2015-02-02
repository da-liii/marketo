#include "htmlgenerator.h"
#include "highlighterbykate.h"
#include "markdown.h"

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

    markdown::Document processor((markdown::SyntaxHighlighter *) m_highlighter);
    processor.read(plain);
    processor.write(sout);
    
    return string(sout.str());
}

HTMLGenerator::~HTMLGenerator()
{

}
