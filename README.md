# `Objects`

COM-inspired, lightweight object management framework for C++17 and later.

## Installation

`Objects` is header-only framework, so you can just clone this repository
and include the framework as follows:

```cpp
#include "objects.hpp"
```

Nothing else is required.

## Examples

```cpp
//
// Defines all following stuff:
//  - Interface identifier: obj::iid_t IID_ISequentialStream;
//  - Smart pointer specialization: ISequentialStreamPtr (as 
//    obj::SmartPtr<ISequentialStream>);
//  - Struct ISequentialStream inherited from obj::IObject.
//
OBJECTS_INTERFACE(ISequentialStream, obj::IObject)
{
    //
    // Read from stream
    //
    OBJECTS_INTERFACE_METHOD_DECL(std::size_t, Read)(unsigned char* buffer, 
        std::size_t buffer_size) OBJECTS_PURE;

    //
    // Write to stream
    //
    OBJECTS_INTERFACE_METHOD_DECL(void, Write)(const unsigned char* buffer, 
        std::size_t buffer_size) OBJECTS_PURE;
};


//
// This interface inherits from ISequentialStream and already contains
// 'Read' and 'Write' methods.
//
OBJECTS_INTERFACE(IStream, ISequentialStream)
{
    enum class SeekBase {
        Begin,
        End,
        Current
    };

    OBJECTS_INTERFACE_METHOD_DECL(void, Seek)(SeekBase base, 
        std::ptrdiff_t offset) OBJECTS_PURE;
};


//
// Implementation class:
//  - it inherits obj::hlp::ObjectBase, that implements
//    internal logic for obj::IObject::Query;
//  - for creation it uses obj::hlp::DynamicObject, that
//    implements Acquire, Release and Query methods (the
//    last one is implemented using obj::hlp::ObjectBase
//    methods).
//
class Stream
    : public obj::hlp::ObjectBase<Stream, IStream>
    , public IStream
{
public:
    static IStreamPtr Create() noexcept
    {
        return IStreamPtr(obj::hlp::DynamicObject<Stream>::Create());
    }

    //
    // ISequentialStream
    //

    OBJECTS_INTERFACE_METHOD(std::size_t, Read)(unsigned char* buffer,
        std::size_t buffer_size)
    {
        // Implementation
    }

    OBJECTS_INTERFACE_METHOD(void, Write)(const unsigned char* buffer, 
        std::size_t buffer_size)
    {
        // Implementation
    }

    //
    // IStream
    //

    OBJECTS_INTERFACE_METHOD(void, Seek)(IStream::SeekBase base, 
        std::ptrdiff_t offset)
    {
        // Implementation
    }
};


void ProcessSequentialData(ISequentialStream* stream)
{
    // Implementation
}


int main()
{
    const auto data = GetDataFrom("127.0.0.1", 8080);

    //
    // Now we create Stream object, that is wrapped
    // into IStreamPtr pointer.
    // It allows us to use it just like IStream* interface 
    // pointer in C++.
    //

    IStreamPtr stream = Stream::Create();
    stream->Write(data.data());

    //
    // For some purposes we may need to obtain an instance
    // of another interface (in our case it is ISequentialStream).
    // It is very simple: just create another smart pointer.
    // There will be no copies, just reference counter increment.
    // Underlying object will be destroyed as soon as both of
    // pointers will go out of scope.
    //

    ISequentialStreamPtr seq_stream = stream;

    //
    // SmartPtr<Iface> can be implicitly casted to an internal
    // pointer type (Iface*) and used in some API functions,
    // that does not require ownership sharing.
    //

    ProcessSequentialData(seq_stream);

    return 0;
}
```

More examples you can find in so named folder.
