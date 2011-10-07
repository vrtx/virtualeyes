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

#ifndef VIRTUALEYES_VEXCEPT_HPP
#define VIRTUALEYES_VEXCEPT_HPP

//
// Includes
//
#include <exception>
#include <string>

using namespace std;

namespace veyes 
{

        ///////////////////////////////////////////////////////
        //
        /// @class   vexcept
        /// @brief   This class defines the generic exception object
        ///          used _ONLY_ for catestrphic failure.
        //
        ///////////////////////////////////////////////////////
        class vexcept : public exception
        {
        public:

                // default ctor
                vexcept();

                // init ctor
                vexcept(const string &a_error);

                // dtor
                virtual ~vexcept() throw();

                // description
                virtual const char *what() const throw();

        private:
                
                string m_error;

        };

}


#endif
