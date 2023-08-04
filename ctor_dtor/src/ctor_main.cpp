#include <iostream>
//#include <iomanip>
#include <vector>

#include "constructor.h"

using namespace std;

X glob(2); // a global variable

X copy(X a) {return a;}

X copy2(X a) {X aa = a; return aa;}

X& ref_to(X& a) {return a;}

X* make(int i) {X a(i); return new X(a);}

struct XX { X a; X b; };

int main()
{
    try {

	cout << "\n\n entering main() ...\n\n";

	X loc {4};    // local variable

	X loc2 {loc}; // copy construction

	loc = X{5};   // copy assignment  (temp object X{5} will be removed after assignment!)

	loc2 = loc;
	
	cout << "\n\n      call by value and return examples ...\n\n";

	loc2 = copy(loc);  // call by value and return

	loc2 = copy2(loc);

	X loc3 {6};

	cout << "\n\n      call by reference and return examples ...\n\n";

	X& r = ref_to(loc); // call by reference and return  (no constructor call!)
	cout << '\n' << "loc.val=" << loc.val << ", r=ref_to(loc): " << r.val << '\n';

	cout << "\n\n      free store examples ...\n\n";

	delete make(7); 
	
	delete make(8);

	cout << "\n\n      vector example ...\n\n";

	vector<X> v(4);     // default values

	cout << "\n\n      struct local example ...\n\n";

        XX loc4;

	cout << "\n\n      X on the free store example ...\n\n";

        X* p = new X{9};    // an X on the free store

	delete p;

	cout << "\n\n      an array of Xs on the free store example ...\n\n";

	X* pp = new X[5];    // an array of Xs on the free store

	delete[] pp;

	cout << "\n\n leaving main() ...\n\n";
  
    return 0;

    }
    catch (exception& e) {
	cout << "\nException in " << e.what() << "\n\n";
    }

} // main()
