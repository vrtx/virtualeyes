///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    4/11/11
//
///////////////////////////////////////////////////////

#include "vexcept.hpp"
using namespace veyes;

// ctor
vexcept::vexcept(const string &a_error):
        m_error(a_error)
{
        
}

// ctor
vexcept::vexcept()
{
        
}

// dtor
vexcept::~vexcept() throw()
{
        
}

// error description
const char *vexcept::what() const throw()
{
        
        return m_error.c_str();
        
}
