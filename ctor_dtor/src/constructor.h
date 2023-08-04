#ifndef CONSTRUCTOR_TEST_H
#define CONSTRUCTOR_TEST_H

#include <iostream>
#include <string>
//#include "error.h"

using namespace std;

struct X {
    int val;

    void out(const string& s, int nv) {
	cerr << '\n' << this << "->" << s << ": " << val << " (" << nv << ")\n";
    };

    X() {                              // default constructor
	out("X()",0);
	val=0;
    };

    X(int v) {
	val=v;
	out("X(int)",v);
    };

    X(const X& x) {                    // copy constructor
	val=x.val;
	out("X(X&)",x.val);
    };

    X& operator=(const X& a) {         // copy assignment
	out("X::operator=()",a.val);
	val=a.val;
	return *this;
    };

    ~X() {                             // destructor
	out("~X()",0);
    };
    
};

#endif // CONSTRUCTOR_TEST_H
