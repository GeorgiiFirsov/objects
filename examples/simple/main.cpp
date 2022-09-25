#include <iostream>
#include <memory>
#include <cassert>

#include "objects.hpp"


OBJECTS_INTERFACE(ISimple, obj::IObject)
{
    OBJECTS_INTERFACE_METHOD_DECL(void, Greet)() noexcept OBJECTS_PURE;
};


OBJECTS_INTERFACE(IHello, obj::IObject)
{
    OBJECTS_INTERFACE_METHOD_DECL(void, Hello)() noexcept OBJECTS_PURE;
};


class Simple1
    : public obj::hlp::ObjectBase<Simple1, ISimple, IHello>
    , public ISimple
    , public IHello
{
public:
    static ISimplePtr Create() { return ISimplePtr { obj::hlp::DynamicObject<Simple1>::Create() }; }

    //
    // ISimple
    //

    OBJECTS_INTERFACE_METHOD(void, Greet)() noexcept override { std::cout << "Hello, world!\n"; }

    //
    // IHello
    //

    OBJECTS_INTERFACE_METHOD(void, Hello)() noexcept override { std::cout << "Hello, C++!\n"; }
};


class Simple2
    : public obj::hlp::ObjectBase<Simple2, ISimple>
    , public ISimple
{
public:
    static ISimplePtr Create() { return ISimplePtr { obj::hlp::DynamicObject<Simple2>::Create() }; }

    //
    // ISimple
    //

    OBJECTS_INTERFACE_METHOD(void, Greet)() noexcept override { std::cout << "Hello, Objects!\n"; }
};


int main()
{
    auto simple1 = Simple1::Create();
    simple1->Greet();

    //
    // An object under simple1 implements IHello too,
    // so it is possible to use it via IHello interface.
    //

    IHelloPtr hello1 = simple1;
    hello1->Hello();

    auto simple2 = Simple2::Create();
    simple2->Greet();

    //
    // An object under simple2 doesn't implement IHello interface,
    // so the following pointer will be equal to nullptr.
    //

    IHelloPtr hello2 = simple2;
    assert(!hello2);

    return 0;
}
