#ifndef HD_USE_TE_UNIQUE_PTR_HPP
#define HD_USE_TE_UNIQUE_PTR_HPP

#include <memory> // unique_ptr
#include <string>

#include "fmt/format.h"
#include "fmt/ranges.h"

namespace HD_TE_UNIQUE_PTR // type erasure using manual type erasure
                           // with std::unique_ptr
{

void demo();

struct Cat
{

    Cat() = default;
    Cat(const std::string& name) :
        my_name{name} {}

    std::string make_noise() const
    {
        return fmt::format("Cat says meow.");
    }
    int id() const
    {
        return 1;
    }
    float extra() const { return 1.0f; }

    int cat_int = 1;
    double cat_double = 1.0;
    std::string my_name{"No name"};
};

struct Dog
{

    Dog() = default;
    Dog(const std::string& name) :
        my_name{name} {}

    std::string make_noise() const
    {
        return fmt::format("Dog says wow.");
    }
    int id() const
    {
        return 2;
    }

    int dog_int = 2;

    std::string my_name{"No name"};
};

class TypeErased // for polymorphic usage
                 // not templated, but using templated ctors and virtual calls to internal representation
{

    // internal base = TE_Interface (= type erased base)
    // this defines the common interface of the types to be used polymorphically
    // (without need for an inheritance relation between the types)
    struct TE_Interface
    {

        // standard functions to enable dtor, copy ctor and move ctor
        // (=affordances mapped to the type-erased class or struct)
        virtual ~TE_Interface() = default;
        virtual std::unique_ptr<TE_Interface> clone() const = 0; // type erased clone

        // add other required function of common interface as pure virtual here
        // i.e. all the required functions of the common interfaces (e.g. serialization, deserialization, etc.)

        virtual std::string make_noise() const = 0;
        virtual int id() const = 0;
    };

    // internal derived = TE_Storage derived from TE_Interface (with templatized ctors)
    // (knows the actual object it holds)
    template <typename T>
    class TE_Storage final : public TE_Interface
    {

      public:

        TE_Storage(T obj) :
            m_obj{std::move(obj)} {}

        std::unique_ptr<TE_Interface> clone() const override
        {
            return std::make_unique<TE_Storage<T>>(m_obj);
        }

        // implement the function calls of the common interface provided by the concrete types
        std::string make_noise() const override { return m_obj.make_noise(); }
        int id() const override { return m_obj.id(); }

      private:

        // here is the actual type to hold as type erased value
        T m_obj;
    };

    // m_impl_ptr is a base class ptr to the concrete type
    std::unique_ptr<TE_Interface> m_impl_ptr;

  public:

    // ctor from original object
    template <typename T>
    TypeErased(T obj) :
        m_impl_ptr{std::make_unique<TE_Storage<T>>(std::move(obj))}
    {
    }

    // copy ctor and assignement
    TypeErased(const TypeErased& other) :
        m_impl_ptr{other.m_impl_ptr->clone()} {}

    TypeErased& operator=(const TypeErased& other)
    {
        m_impl_ptr = other.m_impl_ptr->clone();
        return *this;
    }

    // // return copy of orgininal object
    // template <typename T>
    // // auto clone(const T& obj) const -> T
    // auto clone() const -> T
    // {
    //     return m_impl_ptr->clone();
    // }

    ///////////////////////////////////////////////////////////////////////////////////
    // add functions of common interface here to forward virtuall calls via m_impl_ptr
    ///////////////////////////////////////////////////////////////////////////////////

    std::string make_noise() const
    {
        return m_impl_ptr->make_noise();
    }

    int id() const
    {
        return m_impl_ptr->id();
    }
};

} // namespace HD_TE_UNIQUE_PTR

#endif // HD_USE_TE_UNIQUE_PTR_HPP