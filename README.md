Introduction
------------
virtualeyes is a utility for visualizing, analyzing and manipulating the various components of virtual machine(s), process(es), and abstract systems.  

The first iteration supports data collection via DTrace and GDB.  This allows virtualeyes to collect and manipulate memory, function calls, CPU state(s) and execution state(s) in addition to collecting type, structure and symbol data from debug data and heuristics.  

Future iterations should support additional host and hypervisor-based data collection modules.  Of particularly interest is VMWare's execution tracing, recording and replaying facilities.

Goal
----
The goal of this project is to provide a simple yet powerful interface for understanding/learning what a system or group of systems is doing.  The utility of this application lies mainly in debugging, reverse engineering, performance analysis and malware analysis.  Data can be collected from processes, kernels, hypervisors or just about any event logger and visualized in real-time.  Execution states can also be altered in real-time (depending on the system(s) being monitored).

Status
------
This project is just getting off the ground, but the core infrastructure is relatively complete.  Looking for other engineers/developers/analysts/hackers to invest their ideas, time and code.  

virtualeyes is written in C++ and aims to be cross-platform by utilizing libraries like Qt, OpenGL, DTrace (POSIX), GDB/MI (POSIX and Hypervisors), and eventually WinDBG/KDB/DIA (Windows).  Most development and testing is focused on x86 and x86_64 POSIX hosts and guests.  

Screen Shots
------------
Main workspace: http://alphadiabetics.com/images/veyes-09.26.11.png (still under heavy development).  The HUD currently consists of a timeline (WIP), list of structs, scripting console, text overlay and the main GL scene for exploring the visualizations in 3D space.

Build Dependancies
------------------
  - Qt Framework (4.5+)
  - Boost Libraries (1.4.1+)
  - libmigdb (0.8.12+)  (soon to be deprecated due to incomplete implementations)

Build instructions
------------------
This project uses the CMake build system.  To configure and build virtualeyes:

$ cd virtualeyes/build
$ cmake ../
$ make

The resulting binary will be in virtualeyes/build/src.

Coding Idioms
-------------
 - virtualeyes classes should inherit handle_base, then use 'handle<>' or 'soft_handle<>' template accessors for thread safety and automatic destruction.
   * Example: 'handle <snapshot> = new snapshot();'
 - Native Qt objects should use Qt's parenting system for memory allocation
 - Reusable enums should be added to the enum_convert class for automatic type conversions (e.g. enum to string).
 - Singleton-style should use the 'global<>' construct outlined in src/core/global.hpp

Coding Conventions
------------------
CamelCase is only used for Qt function overrides
Keep names short, but never sacrifice meaning
All functions and classes should be lower case
All class/function/variable names should use '_' to seperate words
Member variables prefixed with 'm_'
Static variables prefixed with 's_'
Use literate-style comments
Consistency is king!

Styling Guide
-------------
All GUI widgets should be styled through the style_mgr class
Styles can be updated and defined by editing the text in style_mgr.cpp's constructor
Use Qt's CSS when possible, otherwise implement a function to style a widget type in style_mgr (TODO: unless widget factory is implemented)

Qemu instructions
-----------------
A simple test setup for virtual machine analysis can be achieved by starting up the qemu process 
with the '-S -s' flags, which will start a gdb server using the built-in qemu stub:
qemu-system-x86_64 -hda win2k8_r2_sp1.qcow2 -cdrom win2k8_r2_dvd.iso -m 2048 -cpu core2duo -s -S

TODO
----
Contribute!
