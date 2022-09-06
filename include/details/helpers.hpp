#ifndef OBJECTS_DETAILS_HELPERS_HPP_INCLUDED
#define OBJECTS_DETAILS_HELPERS_HPP_INCLUDED

#include <type_traits>
#include <atomic>
#include <cstring>


namespace obj {
namespace hlp {
namespace details {

    /**
     * @brief Internal reference counter type
     * 
     */
    using ref_t = size_t;


    /**
     * @brief Atomic reference count helper
     * 
     */
    class RefCounter final
    {
    public:
        explicit RefCounter() noexcept
            : references_(0)
        { }

        ref_t Increment() noexcept { return ++references_; }

        ref_t Decrement() noexcept { return --references_; }

    private:
        std::atomic<ref_t> references_;
    };

} // namespace detais


/**
 * @brief Helper, that implements default obj::IObject methods
 * and manages reference count for dynamically allocated object. 
 * You need to inherit from it to use its functionality.
 * Ty must be inherited from obj::ObjectBase.
 * 
 * @tparam Ty actual type of an object
 * @tparam Rc reference counter type (usually you don't need to override it)
 */
template<typename Ty, typename Rc = details::RefCounter>
class DynamicObject final
    : public Ty
{
    template<typename... Tys>
    explicit DynamicObject(Tys&&... args)
        : Ty(std::forward<Tys>(args)...)
    { }

    DynamicObject(const DynamicObject&) = delete;
    DynamicObject& operator=(const DynamicObject&) = delete;

    DynamicObject(DynamicObject&&) = delete;
    DynamicObject& operator=(DynamicObject&&) = delete;

public:
    template<typename... Tys>
    static DynamicObject<Ty>* Create(Tys&&... args) 
    {
        return new DynamicObject<Ty>(std::forward<Tys>(args)...);
    }

    //
    // obj::IObject
    //

    OBJECTS_INTERFACE_METHOD(void, Acquire)() noexcept override
    {
        refcounter_.Increment();
    }

    OBJECTS_INTERFACE_METHOD(bool, Release)() noexcept override
    {
        if (refcounter_.Decrement()) 
        {
            //
            // Still valid object
            //

            return true;
        }

        delete this;

        //
        // Now object is invalid
        //

        return false;
    }

    OBJECTS_INTERFACE_METHOD(obj::IObject*, Query)(const obj::iid_t target_iid) noexcept override
    {
        if (const auto instance = Ty::QueryInternal(this, target_iid); instance) 
        {
            //
            // Interface instance found, so increment reference counter and return pointer
            //

            Acquire();
            return instance;
        }

        return nullptr;
    }

private:
    // Reference counter helper
    Rc refcounter_;
};


/**
 * @brief Helper, that implements internal logic for Query method.
 * 
 * @tparam Ty actual type of an object
 * @tparam Iface first inherited interface
 * @tparam Ifaces list of all the rest interfaces, that Ty is inherited from
 */
template<typename Ty, typename Iface, typename... Ifaces>
class ObjectBase 
{
    static_assert(!std::disjunction_v<std::is_same<obj::IObject, Iface>, std::is_same<obj::IObject, Ifaces>...>,
        "[ObjectBase]: obj::IObjects should not appear in the list of inherited interfaces");

    //
    // Number of inherited interfaces
    //
    static constexpr size_t kIfacesCount = \
        sizeof...(Ifaces) +     /* Variadic pack */
        1 +                     /* First template argument */
        1;                      /* obj::IObjects */

    //
    // Interface info
    //
    struct IfaceInfo final
    {
        obj::iid_t     iid;
        std::ptrdiff_t offset;
    };

protected:
    virtual ~ObjectBase() = default;

    obj::IObject* QueryInternal(Ty* object, const obj::iid_t target_iid) noexcept 
    {
        static const auto infos = Initialize();

        for (size_t idx = 0; idx < kIfacesCount; ++idx) 
        {
            if (0 == std::strcmp(target_iid, infos[idx].iid)) {
                return IfaceFromOffset(object, infos[idx].offset);
            }
        }

        return nullptr;
    }

private:
    template<typename Iface2>
    static std::ptrdiff_t Offset() noexcept 
    {
        //
        // Taken from COM implementation
        //

        static constexpr auto magic = 8;
        const auto temp = static_cast<Iface2*>(reinterpret_cast<Ty*>(magic));

        return reinterpret_cast<unsigned char*>(temp) - reinterpret_cast<unsigned char*>(magic);
    }

    static obj::IObject* IfaceFromOffset(Ty* object, std::ptrdiff_t offset) noexcept 
    {
        return reinterpret_cast<obj::IObject*>(reinterpret_cast<unsigned char*>(object) + offset);
    }

    template<std::size_t IfacesCount>
    static void InitializeImpl(IfaceInfo (&)[IfacesCount]) noexcept
    { }

    template<std::size_t IfacesCount, typename Iface2, typename... Ifaces2>
    static void InitializeImpl(IfaceInfo (& infos)[IfacesCount]) noexcept
    {
        infos[kIfacesCount - sizeof...(Ifaces2) - 1] = { obj::iidof<Iface2>(), Offset<Iface2>() };
        InitializeImpl<IfacesCount, Ifaces2...>(infos);
    }

    static const IfaceInfo* Initialize() noexcept
    {
        static IfaceInfo infos[kIfacesCount];

        //
        // For obj::IObject Offset is calculated as Iface's offset
        // Actually Iface should inherit it, so it will not be a problem
        //
        infos[0] = { obj::iidof<obj::IObject>(), Offset<Iface>() };
        InitializeImpl<kIfacesCount, Iface, Ifaces...>(infos);
        
        return infos;
    }
};

} // namespace hlp
} // namespace obj

#endif // !OBJECTS_DETAILS_HELPERS_HPP_INCLUDED
