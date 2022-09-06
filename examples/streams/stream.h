#pragma once

#include "objects.hpp"


namespace stream {
    
OBJECTS_INTERFACE(IStream, obj::IObject)
{
    OBJECTS_INTERFACE_METHOD_DECL(std::size_t, Read)(unsigned char* buffer, 
        std::size_t buffer_size) noexcept OBJECTS_PURE;

    OBJECTS_INTERFACE_METHOD_DECL(void, Write)(const unsigned char* buffer,
        std::size_t buffer_size) noexcept OBJECTS_PURE;
};


IStreamPtr CreateMemStream() noexcept;

IStreamPtr CreateFileStream() noexcept;

} // namespace stream
