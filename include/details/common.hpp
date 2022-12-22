/**
 * @file common.hpp
 * @brief Definition of common types and functions.
 */

#ifndef OBJECTS_DETAILS_COMMON_HPP_INCLUDED
#define OBJECTS_DETAILS_COMMON_HPP_INCLUDED


namespace obj {

/**
 * @brief Interface identifier type. 
 * 
 * Actually interface identifier is just its name.
 */
using iid_t = const char*;


/**
 * @brief Returns an interface identifier
 * 
 * This function (and implementations) intentionally violates 
 * naming convention to be more consistent with sizeof, __uuidof
 * and some other operators.
 * 
 * @tparam iface Interface which identifier to return of.
 * @returns Interface identifier.
 */
template<typename Iface>
inline constexpr iid_t iidof() noexcept
{
    //
    // Just call an implementation. It will be found via ADL.
    //

    return iidof_impl(static_cast<const Iface*>(nullptr));
}

}  // namespace obj

#endif  // !OBJECTS_DETAILS_COMMON_HPP_INCLUDED
