#include "htmlgenerator.h"
#include "highlighterbykate.h"
#include "markdown.h"

#include <sstream>
#include <iostream>
using std::istringstream;
using std::ostringstream;

HTMLGenerator::HTMLGenerator(std::string plain)
{
    istringstream in(plain);
    ostringstream sout;
    ostringstream mid;
   
    string line;
    string type;
    string tmp;
    HighlighterByKate highlighter;
    bool inBlock = false;
    while (getline(in, line)) {
        if (line.empty()) {
            sout << "\n";
            continue;
        }
        istringstream stmp(line);
        stmp >> tmp;
        if (tmp == "'''") {
            if (inBlock) {
                inBlock = false;
                sout << highlighter.highlighted(string(mid.str()), type);
                mid.str("");
                type = "";
            } else {
                inBlock = true;
                stmp >> type;
            }
        } else {
            if (inBlock) {
                mid << line << std::endl;
            } else {
                sout << line << std::endl;
            }
        }
    } // endwhile
    if (inBlock)
        sout << mid.str();
    markdown::Document processor;
    
    processor.read(string(sout.str()));
    sout.str("");
    processor.write(sout);

    result = string(sout.str());
}

std::string HTMLGenerator::generated()
{
    return result;
}

HTMLGenerator::~HTMLGenerator()
{

}
