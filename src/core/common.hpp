///////////////////////////////////////////////////////
//
// virtualeyes
//
// @brief   This file defines any common macros/includes/helpers used throughout
//          the virtualeyes project
// @author  Ben Becker
// @date    2/3/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_COMMON_H
#define VIRTUALEYES_COMMON_H

//
// global includes
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <stdint.h>

#include "debug.hpp"
#include "global.hpp"
#include "vexcept.hpp"

// Global type definitions
namespace veyes
{

// Functors
template <typename _Tp>
class compare_time_less
{
public:
    bool operator()(const _Tp &a, const _Tp &b)
    {
        return (a->time < b->time);
    }

};

template <typename _Tp>
class compare_address_less
{
public:
    bool operator()(const _Tp &a, const _Tp &b)
    {
        return (a->start_address < b->start_address);
    }

};

template <typename _Tp>
class compare_offset_less
{
public:
    bool operator()(const _Tp &a, const _Tp &b)
    {
        return (a.offset < b.offset);
    }

};

template <typename _Tp>
class comp_struct_locator
{
public:
    bool operator()(const _Tp &a, const _Tp &b)
    {
        // order by uri and name
        return ((a.uri == b.uri && a.name < b.name) ||
                (a.uri != b.uri && a.uri < b.uri));
    }

};

}

// Namespaces
using namespace std;
using namespace veyes;


#endif
