
#include <bit> // tests for endianness
#include <bitset>
#include <cctype> // isprint
#include <chrono>
#include <climits> // CHAR_BIT
#include <cstddef> // max_align_t
#include <float.h>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <limits>
#include <string>
#include <thread>

#include "common_type.hpp"
#include "hd/hd_keypress.hpp"

using namespace std;
using namespace std::chrono;

template <typename T> struct BinaryForm {
    BinaryForm(const T& v) : _bs(v) {}
    const std::bitset<sizeof(T) * CHAR_BIT> _bs;
};

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const BinaryForm<T> bf)
{
    return os << bf._bs;
}

void write_id()
{
    cout << "thread id of new thread = " << this_thread::get_id() << "\n\n";
}

string time_as_string(const system_clock::time_point& tp)
{
    // convert to system time:
    time_t t = system_clock::to_time_t(tp);
    string ts = ctime(&t);    // convert to calendar time
    ts.resize(ts.size() - 1); // skip trailing newline
    return ts;
}

template <typename C> // function template to print clock data of clock C
void print_clock_data()
{
    cout << "- precision: ";
    // if time unit is less or equal one microsecond
    typedef typename C::period P; // type of time unit
    if (ratio_less_equal<P, micro>::value) {
        // convert to and print as microseconds
        typedef typename ratio_multiply<P, mega>::type TT;
        cout << fixed << double(TT::num) / TT::den << " \u00B5s" << endl;
        // Unicode character \u00B5 is � in UTF8 encoding
    }
    else {
        // print as seconds
        cout << fixed << double(P::num) / P::den << " s" << endl;
    }

    cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

int main()
{
    {
        // // print extended ascii table
        // int col = 1;
        // for (int c = -128; c < 128; ++c) {

        //   if (c==0) {
        //     std::cout << "\n";
        //     col = 1;
        //   }
        //   if (c >= 0 && c <= 32) continue;  // don't print unprintable characters
        //   std::cout << std::setw(6) << c << std::setw(3) << static_cast<char>(c);

        //   col++;
        //     if (col > 7)
        //     {
        //        col = 1;
        //        std::cout << "\n"; // start new row
        //     }
        //  }
        //  std::cout << "\n";

        cout << "\nNumber of bits in char: CHAR_BIT=" << CHAR_BIT
             << "\n"; // CHAR_BIT from limits.h
        if (numeric_limits<char>::is_signed) cout << "char is signed\n\n";
        else cout << "char is unsigned\n\n";

        cout << "Size of built-in types in bytes:\n\n";
        cout << "sizeof(char):          " << sizeof(char) << "\n";
        cout << "sizeof(unsigned char): " << sizeof(unsigned char);
        cout << " (represented by " << numeric_limits<unsigned char>::digits
             << " bits)\n";
        cout << "sizeof(bool):          " << sizeof(bool) << "\n";
        cout << "sizeof(size_t):        " << sizeof(size_t) << "\n";
        cout << "sizeof(short):         " << sizeof(short) << "\n";
        cout << "sizeof(unsigned int):  " << sizeof(unsigned int) << "\n";
        cout << "sizeof(int):           " << sizeof(int) << "\n";
        cout << "sizeof(long):          " << sizeof(long) << "\n";
        cout << "sizeof(long long):     " << sizeof(long long) << "\n";
        cout << "sizeof(float):         " << sizeof(float) << "\n";
        cout << "sizeof(double):        " << sizeof(double) << "\n";
        cout << "sizeof(long double):   " << sizeof(long double) << "\n\n";

        cout << "alignof(char) = " << alignof(char) << "\n";
        cout << "alignof(unsigned char) = " << alignof(unsigned char) << "\n";
        cout << "alignof(bool) = " << alignof(bool) << "\n";
        cout << "alignof(size_t) = " << alignof(size_t) << "\n";
        cout << "alignof(short) = " << alignof(short) << "\n";
        cout << "alignof(unsigned int) = " << alignof(unsigned int) << "\n";
        cout << "alignof(int) = " << alignof(int) << "\n";
        cout << "alignof(long) = " << alignof(long) << "\n";
        cout << "alignof(long long) = " << alignof(long long) << "\n";
        cout << "alignof(float) = " << alignof(float) << "\n";
        cout << "alignof(double) = " << alignof(double) << "\n";
        cout << "alignof(long double) = " << alignof(long double) << "\n";

        cout << "alignof(std::max_align_t) = " << alignof(std::max_align_t) << "\n\n";

        cout << "influence of padding on structs:\n\n";

        struct my_struct1 {
            char c;
            int i;
        } ms1;

        struct my_struct2 {
            char c1;
            char c2;
            int i;
        } ms2;

        struct my_struct3 {
            char c1;
            int i;
            char c2;
        } ms3;

        cout << "struct my_struct1 {\n";
        cout << "  char c;\n";
        cout << "  int i;\n";
        cout << "}\n";
        cout << "sizeof(my_struct1):   " << sizeof(ms1) << "\n";
        cout << "alignof(my_struct1):  " << alignof(my_struct1) << "\n\n";

        cout << "struct my_struct2 {\n";
        cout << "  char c1;\n";
        cout << "  char c2;\n";
        cout << "  int i;\n";
        cout << "}\n";
        cout << "sizeof(my_struct2):   " << sizeof(ms2) << "\n";
        cout << "alignof(my_struct2):  " << alignof(my_struct2) << "\n\n";

        cout << "struct my_struct3 {\n";
        cout << "  char c1;\n";
        cout << "  int i;\n";
        cout << "  char c2;\n";
        cout << "}\n";
        cout << "sizeof(my_struct3):   " << sizeof(ms3) << "\n";
        cout << "alignof(my_struct3):  " << alignof(my_struct3) << "\n\n";
    }

    {
        cout << "casting and bit patterns:\n\n";

        short i1 = 100;
        short i2 = -100;
        signed char c1 = 100;
        signed char c2 = -100;

        cout << "short i1 =  100;\n";
        cout << "short i2 = -100;\n";
        cout << "i1 =  " << i1 << ", binary representation: " << BinaryForm{i1} << "\n";
        cout << "i2 = " << i2 << ", binary representation: " << BinaryForm{i2} << "\n\n";
        cout << "signed char c1 =  100;\n";
        cout << "signed char c2 = -100;\n";
        cout << "c1 = " << c1 << ", binary representation: " << BinaryForm{c1} << "\n";
        cout << "c2 = " << c2 << ", binary representation: " << BinaryForm{c2} << "\n\n";

        unsigned char uc1_s, uc1_r, uc2_s, uc2_r;

        uc1_s = static_cast<unsigned char>(c1);
        uc1_r = reinterpret_cast<unsigned char&>(c1);
        uc2_s = static_cast<unsigned char>(c2);
        uc2_r = reinterpret_cast<unsigned char&>(c2);

        cout << "static_cast<unsigned char>(c1)      : " << uc1_s
             << ", binary representation: " << BinaryForm{uc1_s} << "\n";
        cout << "reinterpret_cast<unsigned char&>(c1): " << uc1_r
             << ", binary representation: " << BinaryForm{uc1_r} << "\n";
        cout << "static_cast<unsigned char>(c2)      : " << uc2_s
             << ", binary representation: " << BinaryForm{uc2_s} << "\n";
        cout << "reinterpret_cast<unsigned char&>(c2): " << uc2_r
             << ", binary representation: " << BinaryForm{uc2_r} << "\n\n";

        unsigned short ui1_s, ui1_r, ui2_s, ui2_r;

        ui1_s = static_cast<unsigned short>(i1);
        ui1_r = reinterpret_cast<unsigned short&>(i1);
        ui2_s = static_cast<unsigned short>(i2);
        ui2_r = reinterpret_cast<unsigned short&>(i2);

        cout << "static_cast<unsigned short>(i1)      : " << ui1_s
             << ", binary representation: " << BinaryForm{ui1_s} << "\n";
        cout << "reinterpret_cast<unsigned short&>(i1): " << ui1_r
             << ", binary representation: " << BinaryForm{ui1_r} << "\n";
        cout << "static_cast<unsigned short>(i2)      : " << ui2_s
             << ", binary representation: " << BinaryForm{ui2_s} << "\n";
        cout << "reinterpret_cast<unsigned short&>(i2): " << ui2_r
             << ", binary representation: " << BinaryForm{ui2_r} << "\n\n";
    }

    {
        cout << "Min/Max values of built-in types:\n";
        cout << "smallest char:          " << int(numeric_limits<char>::min()) << "\n";
        cout << "largest char:           " << int(numeric_limits<char>::max()) << "\n\n";

        /*
        cout << "printable characters in that range are:\n";
        for (int i = numeric_limits<char>::min(); i != numeric_limits<char>::max();
             ++i)
        {
            if (isprint(i))
            {
                cout << "i= " << i << ": " << char(i) << endl;
            }
        }
        */

        cout << "\nsmallest unsigned char: " << int(numeric_limits<unsigned char>::min())
             << "\n";
        cout << "largest unsigned char:  " << int(numeric_limits<unsigned char>::max())
             << "\n\n";

        /*
        for (int i = numeric_limits<unsigned char>::min();
                i != numeric_limits<unsigned char>::max(); ++i)
        {
             if (isprint(i))
             {
               cout << "i= " << i << ": " << (unsigned char)(i) << endl;
             }
        }
        */

        cout << "smallest bool:           " << numeric_limits<bool>::min() << endl;
        cout << "largest bool:            " << numeric_limits<bool>::max() << endl;
        cout << "smallest size_t:         " << numeric_limits<size_t>::min() << endl;
        cout << "largest size_t:          " << numeric_limits<size_t>::max() << endl;
        cout << "smallest unsigned short: " << numeric_limits<unsigned short>::min()
             << endl;
        cout << "largest unsigned short:  " << numeric_limits<unsigned short>::max()
             << endl;
        cout << "smallest short:          " << numeric_limits<short>::min() << endl;
        cout << "largest short:           " << numeric_limits<short>::max() << endl;
        cout << "smallest unsigned int:   " << numeric_limits<unsigned int>::min()
             << endl;
        cout << "largest unsigned int:    " << numeric_limits<unsigned int>::max()
             << endl;
        cout << "smallest int:            " << numeric_limits<int>::min() << endl;
        cout << "largest int:             " << numeric_limits<int>::max() << endl;
        cout << "smallest unsigned long:  " << numeric_limits<unsigned long>::min()
             << endl;
        cout << "largest unsigned long:   " << numeric_limits<unsigned long>::max()
             << endl;
        cout << "smallest long:           " << numeric_limits<long>::min() << endl;
        cout << "largest long:            " << numeric_limits<long>::max() << endl;
        cout << "smallest long long:      " << numeric_limits<long long>::min() << endl;
        cout << "largest long long:       " << numeric_limits<long long>::max() << endl;
        cout << "smallest float:          " << numeric_limits<float>::min() << endl;
        cout << "largest float:           " << numeric_limits<float>::max() << endl;
        cout << "smallest double:         " << numeric_limits<double>::min() << endl;
        cout << "largest double:          " << numeric_limits<double>::max() << endl;
        cout << "smallest long double:    " << numeric_limits<long double>::min() << endl;
        cout << "largest long double:     " << numeric_limits<long double>::max() << endl
             << endl;

        //  cout << "sizeof(Int64)=        " << sizeof(Int64) << "\n";
        //  cout << "smallest Int64:       " << numeric_limits<Int64>::min()  << endl;
        //  cout << "largest Int64:        " << numeric_limits<Int64>::max() << endl
        //  << endl;
    }

    {
        cout << "Common types (attention signed and unsigned don't mix well!):\n";
        cout << "(because unsigned is the common type)\n";

        Number<unsigned int> ui1 = {1}, ui2 = {2};
        Number<short int> si1 = {1};
        Number<int> i1 = {1}, i2 = {-2};
        Number<long> li1 = {1}, li2 = {2};
        Number<float> f1 = {2.3f};
        Number<double> d1 = {2.3}, d2 = {3.5};
        describe("ui1 + i2", ui1 + i2);
        describe("i1 + ui2", i1 + ui2);
        describe("si1 + i2", si1 + i2);
        describe("i1 + i2", i1 + i2);
        describe("ui1 + li2", ui1 + li2);
        describe("li1 + i2", li1 + i2);
        describe("i1 + d2", i1 + d2);
        describe("f1 + i2", f1 + i2);
        describe("f1 + d2", f1 + d2);
        describe("d1 + i2", d1 + i2);
        describe("d1 + d2", d1 + d2);
        cout << endl;
    }

    {
        cout << "Defined constants:";

        // from float.h
        cout << "FLT_DIG (float no. of decimal digits precision):  " << FLT_DIG << endl;
        cout << "DBL_DIG (double no. of decimal digits precision):  " << DBL_DIG << endl;
        cout << "FLT_EPSILON (1.0 + FLT_EPSILON != 1.0):  " << FLT_EPSILON << endl;
        cout << "DBL_EPSILON (1.0 + DBL_EPSILON != 1.0):  " << DBL_EPSILON << endl
             << endl;
    }


    std::cout << '\n';
    auto endian = std::endian::native;
    switch (endian) {
        case std::endian::big:
            cout << "Internal native data format is big endian.\n\n";
            break;
        case std::endian::little:
            cout << "Internal native data format is little endian.\n\n";
            break;
        default:
            cout << "Internal native data format endianess cannot be determined "
                    "(mixed endian).\n\n";
    }

    cout << "\nClock information:\n";
    cout << "\nsystem_clock: \n";
    print_clock_data<system_clock>();
    // epoch
    system_clock::time_point tp;
    cout << "- epoch: " << time_as_string(tp) << endl;
    // current time
    tp = system_clock::now();
    cout << "- now: " << time_as_string(tp) << endl;
    // this block chrashes on gcc 4.8.1
    // minimum time
    // tp = system_clock::time_point::min();
    // cout << "- min: " << time_as_string(tp) << endl;
    // maximum time
    // tp = system_clock::time_point::max();
    // cout << "- max: " << time_as_string(tp) << endl;

    cout << "\nhigh_resolution_clock: \n";
    print_clock_data<high_resolution_clock>();
    cout << "\nsteady_clock: \n";
    print_clock_data<steady_clock>();

    cout << "\n\nConcurrency information:\n\n";
    cout << "no. of parallel threads supported by hardware: "
         << thread::hardware_concurrency() << "\n\n";
    cout << "thread id of master thread = " << this_thread::get_id() << "\n\n";
    thread uninitialized_thread;
    thread::id uninitialized_id = uninitialized_thread.get_id();
    cout << "uninitialized thread id = " << uninitialized_id << "\n\n";
    thread t(write_id); // write id of thread t to stdout
    t.join();

    hd::cmdl_wait_for_enter();

    return (0);
}
