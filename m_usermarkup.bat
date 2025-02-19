@echo off
rem Copyright (c) 2013, International Business Machines
rem Corporation and others.  All rights reserved.

if NOT "%_MAKEDEBUG%"=="" goto debug


rem =========== set nodebug variables =================
set _USERMARKUP_CFLAGS=%_USERMARKUP_CFLAGS_NODEBUG%
set _USERMARKUP_CUFLAGS=%_USERMARKUP_CUFLAGS_NODEBUG%
set _USERMARKUP_CPPFLAGS=%_USERMARKUP_CPPFLAGS_NODEBUG%
set _USERMARKUP_LINKFLAGS=%_USERMARKUP_LINKFLAGS_NODEBUG%
set _USERMARKUP_OBJ=%_USERMARKUP_OBJ_NODEBUG%
set _USERMARKUP_DLL=%_USERMARKUP_DLL_NODEBUG%
goto exit

rem =========== set debug variables =================
:debug

set _USERMARKUP_CFLAGS=%_USERMARKUP_CFLAGS_DEBUG%
set _USERMARKUP_CUFLAGS=%_USERMARKUP_CUFLAGS_DEBUG%
set _USERMARKUP_CPPFLAGS=%_USERMARKUP_CPPFLAGS_DEBUG%
set _USERMARKUP_LINKFLAGS=%_USERMARKUP_LINKFLAGS_DEBUG%
set _USERMARKUP_OBJ=%_USERMARKUP_OBJ_DEBUG%
set _USERMARKUP_DLL=%_USERMARKUP_DLL_DEBUG%

:exit
