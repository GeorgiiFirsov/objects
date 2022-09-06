#ifndef OBJECTS_DETAILS_POINTER_HPP_INCLUDED
#define OBJECTS_DETAILS_POINTER_HPP_INCLUDED

#include <utility>
#include <type_traits>

#include "common.hpp"
#include "exception.hpp"


namespace obj {

//
// Just a forward declaration
//
struct IObject;


/**
 * @brief Smart pointer template for objects, that inherit 
 * interfaces created using Objects library.
 * 
 * @tparam Iface interface type
 */
template<typename Iface>
class SmartPtr
{
public:
    using iface_t = Iface;

public:
    SmartPtr() noexcept
        : pointer_(nullptr)
    { }

    SmartPtr(std::nullptr_t) noexcept
        : SmartPtr()
    { }

    template<typename OtherIface, typename = std::enable_if_t<
        !std::is_same_v<Iface, OtherIface>>>
    SmartPtr(const SmartPtr<OtherIface>& other) noexcept
        : pointer_(other ? static_cast<Iface*>(other->Query(iidof())) : nullptr) 
    { }

    template<typename OtherIface, typename std::enable_if_t<
        std::is_same_v<Iface, OtherIface> && !std::is_same_v<obj::IObject, OtherIface>, int> = 0>
    explicit SmartPtr(OtherIface* pointer) noexcept
        : pointer_(pointer)
    {
        AcquireInternal();
    }

    template<typename OtherIface, typename std::enable_if_t<
        !std::is_same_v<Iface, OtherIface> && std::is_base_of_v<obj::IObject, OtherIface>, int> = 0>
    explicit SmartPtr(OtherIface* pointer) noexcept
        : pointer_(pointer ? static_cast<Iface*>(pointer->Query(iidof())) : nullptr)
    { }

    SmartPtr(const SmartPtr& other) noexcept
        : pointer_(other.pointer_)
    {
        AcquireInternal();
    }

    SmartPtr(SmartPtr&& other) noexcept
        : pointer_(std::exchange(other.pointer_, nullptr))
    { }

    ~SmartPtr()
    {
        ReleaseInternal();
    }

    SmartPtr& operator=(const SmartPtr& other) noexcept
    {
        if (this == &other || other.pointer_ == pointer_) {
            return *this;
        }

        ReleaseInternal();
        pointer_ = other.pointer_;
        AcquireUnsafe();

        return *this;
    }

    SmartPtr& operator=(SmartPtr&& other) noexcept
    {
        if (this == &other || other.pointer_ == pointer_) {
            return *this;
        }

        ReleaseInternal();
        pointer_ = std::exchange(other.pointer_, nullptr);

        return *this;
    }

    SmartPtr& operator=(Iface* other) noexcept
    {
        if (other == pointer_) {
            return *this;
        }

        ReleaseInternal();
        pointer_ = other;
        AcquireInternal();

        return *this;
    }

    Iface* operator->() const
    { 
        ValidatePointer("[obj::SmartPtr::operator->]: null interface pointer");
        return pointer_; 
    }

    Iface** operator&() noexcept
    {
        ReleaseInternal();
        return &pointer_;
    }

    operator Iface*() noexcept { return pointer_; }
    operator const Iface*() const noexcept { return pointer_; }

    operator bool() const noexcept { return pointer_; }

    void Attach(Iface* pointer) noexcept
    {
        ReleaseInternal();
        pointer_ = pointer;
    }

    Iface* Detach() noexcept
    {
        return std::exchange(pointer_, nullptr);
    }

    static constexpr obj::iid_t iidof() noexcept { return obj::iidof<Iface>(); }

private:
    void AcquireInternal() noexcept
    {
        if (pointer_) {
            AcquireUnsafe();
        }
    }

    void AcquireUnsafe() noexcept
    {
        pointer_->Acquire();
    }

    bool ReleaseInternal() noexcept
    {
        if (pointer_) {
            return ReleaseUnsafe();
        }

        return false;
    }

    bool ReleaseUnsafe() noexcept
    {
        return std::exchange(pointer_, nullptr)->Release();
    }

    IObject* QueryUnsafe(const iid_t target_iid) noexcept
    {
        return pointer_->Query(target_iid);
    }

    void ValidatePointer(const char* error_message) const
    {
        if (!pointer_) {
            throw ObjectsException{ error_message };
        }
    }

private:
    // Internal raw pointer
    Iface* pointer_;
};

} // namespace obj

#endif // !OBJECTS_DETAILS_POINTER_HPP_INCLUDED
