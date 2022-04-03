#include "fmt/format.h"
#include "fmt/ranges.h"

#include <memory>
#include <string>
#include <vector>

// ////////////////////////////////////////////////////////////
// // classical inheritance (intrusive)
// ////////////////////////////////////////////////////////////

// struct Four_legged
// {
//     virtual std::string make_noise() const = 0;
//     virtual int id() const = 0;
// };

// struct Cat_inherited : Four_legged
// {
//     std::string make_noise() const override
//     {
//         return fmt::format("Cat says meow.");
//     }
//     int id() const override { return 1; }
// };

// struct Dog_inherited : Four_legged
// {
//     std::string make_noise() const override
//     {
//         return fmt::format("Dog says wow.");
//     }
//     int id() const override { return 2; }
// };

// ////////////////////////////////////////////////////////////
// // type erasure (non-intrusive)
// ////////////////////////////////////////////////////////////

// struct TypeErased_unique // not templated, but using templated ctors and virtual calls to internal representation

// // to use in other applications:
// // - text replace TypeErased_unique by intended common type
// // - adjust pure virtuals in TE_Interface with functions needed as common interface (pure virtuals)
// // - adjust "standard affordances" (cp, mv, destruct) if required (normally not necessary)
// // - forward calls of all functions in interface (vitual functions) to TE_Storage via impl_ptr
// //   (redirection to TE_Storage happens via vtable, i.e. by virtual function calls)
// //   (in case of pure data types only keep virtual standard functions and delete the rest)
// //
// //   TypeErased_unique can be used with full value semantics, i.e. as elements of collection in all standard containers

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
//         // i.e. all the required functions of the common interfaces (e.g. serialization, deserialization, etc.)

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

//         // use the function calls of the common interface provided by the concrete types

//         std::string make_noise() const override { return m_obj.make_noise(); }
//         int id() const override { return m_obj.id(); }

//       private:

//         // here is the actual type to hold as type erased value
//         T m_obj;
//     };

//     // impl_ptr is a base class ptr to the concrete type
//     std::unique_ptr<TE_Interface> impl_ptr{nullptr};
// };

// struct TypeErased_shared // not templated, but using templated ctors and virtual calls to internal representation

// // to use in other applications:
// // - text replace TypeErased_shared by intended common type
// // - adjust pure virtuals in TE_Interface with functions needed as common interface (pure virtuals)
// // - adjust "standard affordances" (cp, mv, destruct) if required (normally not necessary)
// // - forward calls of all functions in interface (vitual functions) to TE_Storage via impl_ptr
// //   (redirection to TE_Storage happens via vtable, i.e. by virtual function calls)
// //   (in case of pure data types only keep virtual standard functions and delete the rest)
// //
// //   TypeErased_shared can be used with full value semantics, i.e. as elements of collection in all standard containers

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
//         // i.e. all the required functions of the common interfaces (e.g. serialization, deserialization, etc.)

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

//         // use the function calls of the common interface provided by the concrete types
//         std::string make_noise() const override { return m_obj.make_noise(); }
//         int id() const override { return m_obj.id(); }

//       private:

//         // here is the actual type to hold as type erased value
//         T m_obj;
//     };

//     // impl_ptr is a base class ptr to the concrete type
//     std::shared_ptr<const TE_Interface> impl_ptr{nullptr};
// };

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

    // return copy of orgininal object
    template <typename T>
    auto clone(const T& obj) -> T
    {
        return m_impl_ptr->clone();
    }

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

int main(int argc, char* argv[])
{

    // fmt::print("Using classical inheritance:\n");

    // Cat_inherited cat_inh;
    // Dog_inherited dog_inh;
    // // std::vector<const Four_legged*> vec_inherited{&cat_inh, &dog_inh};
    // std::vector<const Four_legged*> vec_inherited;
    // vec_inherited.push_back(&cat_inh);
    // vec_inherited.push_back(&dog_inh);

    // for (const auto& e : vec_inherited)
    // {
    //     fmt::print("{}", e->make_noise());
    //     fmt::print(" My id is {}.\n", e->id());
    // }

    // fmt::print("\n\n");

    fmt::print("Using type erasure (non-intrusive):\n");

    struct Cat
    {
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
        std::string cat_string{"Schmusekatze"};
    };

    struct Dog
    {
        std::string make_noise() const
        {
            return fmt::format("Dog says wow.");
        }
        int id() const
        {
            return 2;
        }

        int dog_int = 2;
    };

    // using TE = TypeErased_unique;
    using TE = TypeErased;

    TE c0 = TE{Cat()};
    TE d0 = TE{Dog()};

    fmt::print("Size of Cat = {}\n", sizeof(Cat));
    fmt::print("Size of Dog = {}\n", sizeof(Dog));
    fmt::print("Size of TE = {}\n\n", sizeof(TE));
    fmt::print("Size of c0 = {}\n", sizeof(c0));
    fmt::print("Size of d0 = {}\n\n", sizeof(d0));

    Cat* cp = new Cat;
    fmt::print("Address of cp = {}\n", fmt::ptr(cp));
    fmt::print("{}", cp->make_noise());
    fmt::print(" My id is {}.\n", cp->id());
    fmt::print(" Cat extra() is {}\n", cp->extra());
    fmt::print(" cat_int is {}\n", cp->cat_int);
    fmt::print(" cat_double is {}\n", cp->cat_double);
    fmt::print(" cat_string is {}\n", cp->cat_string);

    // TE* ap = new TE(*cp);
    // fmt::print("Address of ap = {}\n", fmt::ptr(ap));
    // fmt::print("{}", ap->make_noise());
    // fmt::print(" My id is {}.\n", ap->id());
    // fmt::print(" Cat extra() is {}\n", ap->extra());
    // fmt::print(" cat_data is {}\n", ap->cat_data());

    // Cat* c7 = reinterpret_cast<Cat*>(ap->clone(Cat()));
    // Cat c7 = ap->clone();
    // fmt::print("Address of c7 = {}\n", fmt::ptr(&c7));
    // fmt::print("{}", c7.make_noise());
    // fmt::print(" My id is {}.\n", c7.id());
    // fmt::print(" Cat extra() is {}\n", c7.extra());
    // fmt::print(" cat_int is {}\n", c7.cat_int);
    // fmt::print(" cat_double is {}\n", c7.cat_double);
    // fmt::print(" cat_string is {}\n", c7.cat_string);

    // TE a = Dog();
    // fmt::print("{}", a.make_noise());
    // fmt::print(" My id is {}.\n", a.id());

    // std::vector<TE> ani;
    // ani.push_back(Cat());
    // ani.emplace_back(Dog());

    // TE c1{Cat()};
    // TE c2{Cat()};
    // TE c3{c2};
    // ani.push_back(c1);
    // ani.push_back(c2);
    // c2 = c1;
    // TE d1{Dog()};
    // ani.push_back(Dog());

    // for (const auto& e : ani)
    // {
    //     fmt::print("{}", e.make_noise());
    //     fmt::print(" My id is {}.\n", e.id());
    // }

    return 0;
}