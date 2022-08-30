/**
 * @file objects.hpp
 * @author Georgy Firsov (gfirsov007@gmail.com)
 * @brief Main header file of the library (you should include this file instead of separate headers)
 * @version 0.1
 * @date 2022-08-28
 * 
 * @copyright Copyright (c) Georgy Firsov 2022
 */

#ifndef OBJECTS_HPP_INCLUDED
#define OBJECTS_HPP_INCLUDED

//
// Library version
//
#define OBJECTS_VERSION_MAJOR 0
#define OBJECTS_VERSION_MINOR 1


//
// Some checks
//
#ifndef __cplusplus
#   error Objects library requires C++ support
#endif // !__cplusplus


//
// Library header files
//
#include "details/objects.hpp"

#endif // !OBJECTS_HPP_INCLUDED
