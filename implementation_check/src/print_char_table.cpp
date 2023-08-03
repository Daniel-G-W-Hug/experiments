#include <iostream>
#include <limits>

using namespace std;

int main(int /*argc*/, char* /*argv*/[]) {

  cout << "\nPrinting char table:\n\n";
  for (int i=int(numeric_limits<char>::min()); i<int(numeric_limits<char>::max()); ++i) {
    cout << "char(" << i << ") = " << char(i) << endl;

  }

   return 0;
}
