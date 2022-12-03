#ifndef OBJECTS_DETAILS_EXCEPTION_HPP_INCLUDED
#define OBJECTS_DETAILS_EXCEPTION_HPP_INCLUDED

#include <stdexcept>


namespace obj {

/**
 * @brief Custom exception type used in the library
 * Simply inherits std::runtime_error for now.
 */
class ObjectsException : public std::runtime_error
{
    using MyBase = std::runtime_error;

public:
    using MyBase::runtime_error;
    using MyBase::what;
};

}  // namespace obj

#endif  // !OBJECTS_DETAILS_EXCEPTION_HPP_INCLUDED
