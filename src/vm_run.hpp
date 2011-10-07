///////////////////////////////////////////////////////
/// virtualeyes
///
/// Copyright (c) 2011 - 2011 Benjamnin Becker
/// All Rights Reserved
///
/// @brief   This class represents a single VM run
/// @author  ben
/// @date    7/12/2011
///////////////////////////////////////////////////////

#ifndef VEYE_VM_RUN_HPP
#define VEYE_VM_RUN_HPP

#include "handle_base.hpp"
#include "handle.hpp"
#include <QVector>

namespace veyes {

        ///////////////////////////////////////////////////////
        /// @class   vm_run
        /// @brief   This class represents a single VM run
        ///////////////////////////////////////////////////////
        class vm_run : public handle_base
        {
        public:
                vm_run();
                ~vm_run();
                quint64 time_start;
                quint64 time_end;

        };

        // Type definitions
        typedef vector <handle <vm_run> > vm_run_list_t;
        typedef vector <soft_handle <vm_run> > vm_run_soft_list_t;
        typedef vm_run_list_t owned_vm_runs_t;
        typedef vm_run_soft_list_t soft_vm_runs_t;

}

#endif
