#include "stream.h"

namespace stream {

class MemoryStream
    : public obj::hlp::ObjectBase<MemoryStream, IStream>
    , public IStream
{

};

IStreamPtr CreateMemStream() noexcept
{
    return IStreamPtr{ obj::hlp::DynamicObject<MemoryStream>::Create() };
}


class FileStream
    : public obj::hlp::ObjectBase<FileStream, IStream>
    , public IStream
{

};

IStreamPtr CreateFileStream() noexcept
{
    return IStreamPtr{ obj::hlp::DynamicObject<FileStream>::Create() };
}

} // namespace stream
