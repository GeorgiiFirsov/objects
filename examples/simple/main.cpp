#include <iostream>
#include <memory>
#include "objects.hpp"


OBJECTS_INTERFACE(ISimple, obj::IObject)
{
    OBJECTS_INTERFACE_METHOD_DECL(void, Greet)() noexcept OBJECTS_PURE;
};


class Simple1
    : public obj::hlp::ObjectBase<Simple1, ISimple>
    , public ISimple
{
public:
    static ISimplePtr Create() { return ISimplePtr(obj::hlp::DynamicObject<Simple1>::Create()); }

    //
    // ISimple
    //

    OBJECTS_INTERFACE_METHOD(void, Greet)() noexcept override { std::cout << "Hello, world!\n"; }
};


class Simple2
    : public obj::hlp::ObjectBase<Simple2, ISimple>
    , public ISimple
{
public:
    static ISimplePtr Create() { return ISimplePtr(obj::hlp::DynamicObject<Simple2>::Create()); }

    //
    // ISimple
    //

    OBJECTS_INTERFACE_METHOD(void, Greet)() noexcept override { std::cout << "Hello, Objects!\n"; }
};


int main() 
{
    auto simple1 = Simple1::Create();
    simple1->Greet();

    auto simple2 = Simple2::Create();
    simple2->Greet();

    return 0;
}
