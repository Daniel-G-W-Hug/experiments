#include <cstddef> // for size_t

#include "fmt/format.h"
#include "fmt/ranges.h"

// create a litte wrapper class around a raw array to realize raii
// RAII: Resource Aquisition is initialization

template <typename T>
class DynamicArray
{
    size_t m_size{0};
    T* m_array{nullptr};

  public:

    DynamicArray(size_t size) :
        m_size{size}, m_array{size > 0 ? new T[size] : nullptr}
    {
        // if (m_array != nullptr)
        // {
        //     fmt::print("Constructed array of {} elements.\n", m_size);
        // }
        // fmt::print("m_array is {}\n", fmt::ptr(m_array));
    }

    ~DynamicArray()
    {
        if (m_size > 0)
        {
            // fmt::print("About to delete array of {} elements.\n", m_size);
            delete[] m_array;
        }
        // to print the ptr here is UB
        // (a deleted ptr must not be accessed)
        // fmt::print("m_array is {}\n", fmt::ptr(m_array));
    }

    size_t size() const { return m_size; }

    void set(size_t idx, T value) { m_array[idx] = value; }

    T get(size_t idx) { return m_array[idx]; }

    T& operator[](size_t idx)
    {
        return m_array[idx];
    }
};

int main(int argc, char* argv[])
{
    fmt::print("\nStart RAII demo.\n\n");

    {
        constexpr size_t DIM = 10;
        DynamicArray<float> ia{DIM};

        ia.set(4, 42.2);
        ia[DIM - 1] = 9.99999;

        for (size_t cnt = 0; cnt < ia.size(); ++cnt)
        {
            fmt::print("ia[{}] = {}\n", cnt, ia[cnt]);
        }
    }

    fmt::print("\nEnd RAII demo.\n\n");

    return 0;
}