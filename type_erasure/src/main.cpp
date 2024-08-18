#include "fmt/format.h"
#include "fmt/ranges.h"

#include <iostream>
#include <string>
#include <vector>

#include "hd/hd_keypress.hpp"

#include "use_TE_unique_ptr.hpp"
#include "use_any.hpp"
#include "use_inheritance.hpp"

// ////////////////////////////////////////////////////////////
// // type erasure (non-intrusive)
// ////////////////////////////////////////////////////////////

// struct TypeErased_unique // not templated, but using templated ctors and virtual calls
// to internal representation

// // to use in other applications:
// // - text replace TypeErased_unique by intended common type
// // - adjust pure virtuals in TE_Interface with functions needed as common interface
// (pure virtuals)
// // - adjust "standard affordances" (cp, mv, destruct) if required (normally not
// necessary)
// // - forward calls of all functions in interface (vitual functions) to TE_Storage via
// impl_ptr
// //   (redirection to TE_Storage happens via vtable, i.e. by virtual function calls)
// //   (in case of pure data types only keep virtual standard functions and delete the
// rest)
// //
// //   TypeErased_unique can be used with full value semantics, i.e. as elements of
// collection in all standard containers

// {

//     // mv ctor and assignment
//     template <typename T>
//     TypeErased_unique(T&& rhs) noexcept
//     {
//         *this = rhs; // forward to assign
//     }

//     template <typename T>
//     TypeErased_unique& operator=(T&& rhs)
//     {
//         impl_ptr.reset(new TE_Storage<std::decay_t<T>>(std::forward<T>(rhs)));
//         return *this;
//     }

//     ///////////////////////////////////////////////////////////////////////////////////
//     // add function of common interface here to forward virtuall calls via impl_ptr
//     ///////////////////////////////////////////////////////////////////////////////////

//     std::string make_noise() const
//     {
//         return impl_ptr->make_noise();
//     }

//     int id() const
//     {
//         return impl_ptr->id();
//     }

//   private:

//     // internal base = TE_Interface (= type erased base)
//     // this defines the common interface of the types to be used polymorphically
//     // (without need for an inheritance relation between the types)
//     struct TE_Interface
//     {

//         // standard functions to enable dtor, copy ctor and move ctor
//         // (=affordances mapped to the type-erased class or struct)
//         virtual ~TE_Interface() = default;

//         // add other required function of common interface as pure virtual here
//         // i.e. all the required functions of the common interfaces (e.g.
//         serialization, deserialization, etc.)

//         virtual std::string make_noise() const = 0;
//         virtual int id() const = 0;
//     };

//     // internal derived = TE_Storage derived from TE_Interface (with templatized ctors)
//     // (knows the actual object it holds)
//     template <typename T>
//     struct TE_Storage : TE_Interface
//     {
//         // cp ctor
//         TE_Storage(const T& obj) :
//             m_obj{obj} {}

//         // use the function calls of the common interface provided by the concrete
//         types

//         std::string make_noise() const override { return m_obj.make_noise(); }
//         int id() const override { return m_obj.id(); }

//       private:

//         // here is the actual type to hold as type erased value
//         T m_obj;
//     };

//     // impl_ptr is a base class ptr to the concrete type
//     std::unique_ptr<TE_Interface> impl_ptr{nullptr};
// };

// struct TypeErased_shared // not templated, but using templated ctors and virtual calls
// to internal representation

// // to use in other applications:
// // - text replace TypeErased_shared by intended common type
// // - adjust pure virtuals in TE_Interface with functions needed as common interface
// (pure virtuals)
// // - adjust "standard affordances" (cp, mv, destruct) if required (normally not
// necessary)
// // - forward calls of all functions in interface (vitual functions) to TE_Storage via
// impl_ptr
// //   (redirection to TE_Storage happens via vtable, i.e. by virtual function calls)
// //   (in case of pure data types only keep virtual standard functions and delete the
// rest)
// //
// //   TypeErased_shared can be used with full value semantics, i.e. as elements of
// collection in all standard containers

// {

//     // ctor from original object
//     template <typename T>
//     TypeErased_shared(T obj) :
//         impl_ptr{std::make_shared<TE_Storage<T>>(std::move(obj))}
//     {
//     }

//     // copy ctor and assignement
//     TypeErased_shared(const TypeErased_shared& other) :
//         impl_ptr{other.impl_ptr->clone()} {}

//     TypeErased_shared& operator=(const TypeErased_shared& other)
//     {
//         impl_ptr = other.impl_ptr->clone();
//         return *this;
//     }

//     ///////////////////////////////////////////////////////////////////////////////////
//     // add function of common interface here to forward virtuall calls via impl_ptr
//     ///////////////////////////////////////////////////////////////////////////////////

//     std::string make_noise() const
//     {
//         return impl_ptr->make_noise();
//     }

//     int id() const
//     {
//         return impl_ptr->id();
//     }

//   private:

//     // internal base = TE_Interface (= type erased base)
//     // this defines the common interface of the types to be used polymorphically
//     // (without need for an inheritance relation between the types)
//     struct TE_Interface
//     {

//         // standard functions to enable dtor, copy ctor and move ctor
//         // (=affordances mapped to the type-erased class or struct)
//         virtual ~TE_Interface() = default;
//         virtual std::shared_ptr<TE_Interface> clone() const = 0;

//         // add other required function of common interface as pure virtual here
//         // i.e. all the required functions of the common interfaces (e.g.
//         serialization, deserialization, etc.)

//         virtual std::string make_noise() const = 0;
//         virtual int id() const = 0;
//     };

//     // internal derived = TE_Storage derived from TE_Interface (with templatized ctors)
//     // (knows the actual object it holds)
//     template <typename T>
//     class TE_Storage final : public TE_Interface
//     {

//       public:

//         TE_Storage(const T& obj) :
//             m_obj{obj} {}

//         std::shared_ptr<TE_Interface> clone() const override
//         {
//             return std::make_shared<TE_Storage<T>>(m_obj);
//         }

//         // use the function calls of the common interface provided by the concrete
//         types std::string make_noise() const override { return m_obj.make_noise(); }
//         int id() const override { return m_obj.id(); }

//       private:

//         // here is the actual type to hold as type erased value
//         T m_obj;
//     };

//     // impl_ptr is a base class ptr to the concrete type
//     std::shared_ptr<const TE_Interface> impl_ptr{nullptr};
// };

// int main(int argc, char* argv[])
int main()
{

    // demo using classical inheritance
    HD_INHERITANCE::demo();

    // demo using vector of any
    HD_ANY::demo();

    // demo using manual type erasure with unique_ptr
    HD_TE_UNIQUE_PTR::demo();

    hd::cmdl_wait_for_enter();

    return 0;
}