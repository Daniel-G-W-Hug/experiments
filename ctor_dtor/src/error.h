#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

// error() simply disguises throws (taken from Stoustrup "PPP"):
inline void error(const string& file, const int line, const string& s)
{
    ostringstream os;
    os << "file: " << file << ", line: " << line << ", \"" << s << "\"";
    throw runtime_error(os.str());
}

#endif // ERROR_H
