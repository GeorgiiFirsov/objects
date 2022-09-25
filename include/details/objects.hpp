#ifndef OBJECTS_DETAILS_OBJECTS_HPP_INCLUDED
#define OBJECTS_DETAILS_OBJECTS_HPP_INCLUDED

#include "common.hpp"


/**
 * @brief Basic internal macro for interface declaration. One shouldn't use it
 * and prefer OBJECTS_INTERFACE instead. 
 * 
 */
#define OBJECTS_INTERFACE_INTERNAL(Iface)                         \
    /* Interface identifier (IID) */                              \
    inline constexpr obj::iid_t IID_##Iface = #Iface;             \
    /* Forward declaration */                                     \
    struct Iface;                                                 \
    /* iidof implementation */                                    \
    inline constexpr obj::iid_t iidof_impl(const Iface*) noexcept \
    {                                                             \
        return IID_##Iface;                                       \
    }                                                             \
    /* Pointer specialisation */                                  \
    using Iface##Ptr = obj::SmartPtr<Iface>;                      \
    /* Interface itself */                                        \
    struct Iface


/**
 * @brief Macro-helper for interface declaration. 
 * Use it in the following way:
 * 
 * OBJECTS_INTERFACE(IMyInterface, obj::IObject)
 * {
 *     OBJECTS_INTERFACE_METHOD_DECL(void, DoSomething)() noexcept OBJECTS_PURE;
 * };
 * 
 */
#define OBJECTS_INTERFACE(Iface, BaseIface) \
    OBJECTS_INTERFACE_INTERNAL(Iface)       \
        : public BaseIface


/**
 * @brief Macro, that helps to declare interface methods. For an
 * example look at OBJECTS_INTERFACE macro description.
 * 
 */
#define OBJECTS_INTERFACE_METHOD_DECL(ret, name) virtual ret name


/**
 * @brief Macro, that helps to implement interface methods. 
 * Usage example:
 * 
 * class Impl : public IMyInterface
 * {
 *     OBJECTS_INTERFACE_METHOD(void, DoSomething)() noexcept override
 *     {
 *         std::cout << "Doing work...\n";
 *     }
 * };
 * 
 */
#define OBJECTS_INTERFACE_METHOD(ret, name) ret name


/**
 * @brief Auxilary macro, that says, that interface method is pure.
 * Note: all interface methods must be pure.
 * You are free to write "= 0" instead of OBJECTS_PURE.
 * 
 */
#define OBJECTS_PURE = 0


namespace obj {


/**
 * @brief Basic interface for all interfaces
 * 
 */
OBJECTS_INTERFACE_INTERNAL(IObject)
{
    /**
     * @brief Virtual destructor. Does nothing actually.
     * 
     */
    virtual ~IObject() = default;

    /**
     * @brief Increments reference counter associated with an object.
     * 
     */
    OBJECTS_INTERFACE_METHOD_DECL(void, Acquire)() noexcept OBJECTS_PURE;

    /**
     * @brief Decrements reference counter associated with an object.
     * Interface implementation is responsible for object destruction if 
     * reference counter becomes zero.
     * 
     * @return true if object is still alive and false otherwise.
     */
    OBJECTS_INTERFACE_METHOD_DECL(bool, Release)() noexcept OBJECTS_PURE;

    /**
     * @brief 
     * 
     * @param target_iid identifier of the interface to query
     * @return IObject* pointer to the requested interface. 
     * If the interface cannot be queried, return value is zero.
     * 
     */
    OBJECTS_INTERFACE_METHOD_DECL(obj::IObject*, Query)(const obj::iid_t target_iid) noexcept OBJECTS_PURE;
};

}  // namespace obj

#endif  // !OBJECTS_DETAILS_OBJECTS_HPP_INCLUDED
