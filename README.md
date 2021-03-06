virtualeyes
-----------
virtualeyes is a utility for visualizing, analyzing and manipulating the various components of virtual machine(s), process(es), and abstract systems.  The first iteration supports data collection via vwatchd's DTrace and GDB modules.  This allows virtualeyes to collect and manipulate memory, function calls, CPU state(s) and execution state(s).  In addition, debugger symbols and heuristics are used to discover types, structures and symbols.  Future iterations should support additional host and hypervisor-based data collection modules.

The utility of this application lies mainly in debugging, reverse engineering, performance analysis, malware analysis and general system analysis.  Data can be collected from processes, kernels, hypervisors or just about any event logger and visualized with interactions in real-time.  Of particularly interest is VMWare's execution tracing, recording and replaying facilities.

Status
------
This project is just getting off the ground, but the core infrastructure is relatively complete.  Looking for other engineers/developers/analysts/hackers to invest their ideas, time and code.

virtualeyes is written in C++ and aims to be cross-platform by utilizing libraries like Qt, OpenGL, MongoDB, DTrace (POSIX), and eventually WinDBG/KDB/DIA (Windows).  Most development and testing is focused on x86 and x86\_64 POSIX hosts and guests.  

Screen Shots
------------
Main workspace: http://vrtx0.com/images/veyes-09.26.11.png (still under heavy development).  The HUD currently consists of a timeline (WIP), list of structs, scripting console, text overlay and the main GL scene for exploring the visualizations in 3D space.

Build Dependancies
------------------
  - cmake (2.6+)
  - Qt Framework (4.5+)
  - Boost Libraries (1.4.1+)
  - libmongoclient (2.0+)

Build instructions
------------------
This project uses the CMake build system.  To configure and build virtualeyes:

        $ cd virtualeyes/build
        $ cmake ../
        $ make

The resulting binary will be in virtualeyes/build/src.

Coding Idioms
-------------
 - Classes should inherit handle\_base, then use 'handle&lt;&gt;' or 'soft\_handle&lt;&gt;' template accessors for thread safety and automatic destruction.  Example:
         handle &lt;snapshot&gt; l\_snap = new snapshot();
 - Native and Derived Qt objects should use Qt's parenting system for memory allocation instead of deriving handle\_base.  Mixing the two is supported, but should be avoided for simplicity.
 - Add enums to the enum\_convert class if you would like fast, automated type conversions (e.g. enum to string).  NOTE: this class is somewhat bastardized until type-safe enums are supported in the osx clang c++0x compiler.
 - Singleton-style classes should be avoided.  Use the 'global&lt;&gt;' construct outlined in src/core/global.hpp when neccesary.
 - Objects that form a hierarchy should use a 'handle&lt;&gt;' or 'container &lt;handle &lt;&gt; &gt;' member variable to create the parent -&gt; child link and take ownership.  Example:  

         typedef set <handle <snapshot> > owned_snapshots_t;  
         ...
         class vm_run {
             owned_snapshots_t m_snapshots;     // a vm_run can own any number of snapshots
         }

 - Objects that form a cyclic hierarchy should use a 'soft\_handle&lt;&gt;' or 'container &lt;soft\_handle &lt;&gt; &gt;' member variable to create a child -&gt; parent link as this will not attempt to take ownership.  Example:

         class vm_run {
             soft_handle <session> m_session;   // a vm_run can reference the session object without taking ownership
         }

 - In general, soft\_handle&lt;&gt;s are only used to reference objects that can introduce cycles into graph of objects.


Coding Conventions
------------------
 - CamelCase is only used for Qt function overrides
 - Keep names short, but never sacrifice meaning
 - All functions and classes should be lower case
 - All class/function/variable names should use '\_' to seperate words
 - Member variables prefixed with 'm\_'
 - Use literate-style comments
 - Consistency is king!

Styling Guide
-------------
 - All GUI widgets should be styled through the style\_mgr class
 - Styles can be updated and defined by editing the text in style\_mgr.cpp's constructor
 - Use Qt's CSS when possible, otherwise implement a function to style a widget type in style\_mgr
 - There's lots of room for improvement with the styling system; input is welcome

TODO
----
Contribute!
