#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class obj {
public:
  obj() : id(++num_obj), value(id) {
    ++num_alive_obj;
    print("default ctor called", id, value, num_alive_obj);
  }

  obj(const obj&) : id(++num_obj), value(id) {
    ++num_alive_obj;
    print("copy ctor called", id, value, num_alive_obj);
  }

  obj& operator=(const obj& other) {
    value = other.value;
    print("copy assignment called", id, value, num_alive_obj);
    return *this;
  }

  obj(obj&&) : id(++num_obj), value(id) {
    ++num_alive_obj;
    print("move ctor called", id, value, num_alive_obj);
  }

  obj& operator=(obj&& other) {
    value = std::move(other.value);
    print("move assignment called", id, value, num_alive_obj);
    return *this;
  }

  ~obj() {
    --num_alive_obj;
    print("dtor called\t", id, value, num_alive_obj);
  }

private:
  void print(string s, int id, int value, int num_alive) const {
    cout << s << "\t (id=" << id << ", value=" << value << ", #obj=" << num_alive << ")" << endl;
  }

  static int num_obj;
  static int num_alive_obj;
  const int id;
  int value;
};

obj foo(const obj& arg) {

  cout << "\nFunction foo() body begin:\n";
  obj local_object;
  local_object = arg;
  cout << "\nFunction foo() about to return:\n";
  return local_object;
  // return std::move(local_object);  // inhibits RVO !!!
}

// initialize static class variables
int obj::num_obj       = 0;
int obj::num_alive_obj = 0;

int main() {

  cout << "\nctor & dtor tests:\n\n";
  {
    {
      obj o1;
      obj o2(o1);
      obj o3(std::move(o1));
      obj o4, o5, o6;
      o5 = o4;
      o6 = std::move(o4);
    }
    cout << "\nCalling function foo():\n\n";
    obj o7;
    obj o8 = foo(o7);
    cout << "\nReturned from function foo():\n\n";
  }
  cout << "\nctor & dtor tests finished.\n\n";

  return 0;
}
