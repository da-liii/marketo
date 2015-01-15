#ifndef HTMLGENERATOR_H
#define HTMLGENERATOR_H

#include <string>
using std::string;

class HTMLGenerator {
public:
    HTMLGenerator(string plain);
    ~HTMLGenerator();
    string generated();
private:
    string result;
};

#endif