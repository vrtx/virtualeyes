///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines an interface for storing object data in a persistent store.
// @author  ben
// @date    9/25/2011
///////////////////////////////////////////////////////

#ifndef VEYES_STORE_HPP
#define VEYES_STORE_HPP

#include "handle.hpp"

namespace veyes {

/// @class store  Base class used for storing an object in the database
template <typename _Tp>
class store
{
public:
    store();
    static set <handle <_Tp> > find(const QString &a_query_string);
    static handle <_Tp> findOne(const QString &a_query_string);
    static int remove(handle <_Tp> &a_item);
    void save();
};

template <typename _Tp>
store <_Tp>::store()
{
}


}  // namespace


#endif // VEYES_STORE_HPP
