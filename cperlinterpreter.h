/***************************************************************************
 *   Copyright (C) 2003 by Dan Muller                                      *
 *   dan@verliba.cz                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef NSCRIPTSCPERLINTERPRETER_H
#define NSCRIPTSCPERLINTERPRETER_H

namespace nPerl
{
#include <EXTERN.h>               /* from the Perl distribution     */
#include <perl.h>                 /* from the Perl distribution     */
};
using namespace nPerl;

namespace nScripts
{

/** \brief a wrapper for perl calling ; a c++ wrapper for the perl XS API

  *
  * Now suppose we have more than one interpreter instance running at the same time.
  * This is feasible, but only if you used the Configure option -Dusemultiplicity or
  * the options -Dusethreads -Duseithreads when building Perl. By default, enabling
  * one of these Configure options sets the per-interpreter global variable
  * PL_perl_destruct_level to 1, so that thorough cleaning is automatic.
  *
  * Using -Dusethreads -Duseithreads rather than -Dusemultiplicity is more appropriate
  * if you intend to run multiple interpreters concurrently in different threads,
  * because it enables support for linking in the thread libraries of your system
  * with the interpreter.
  *
  * @author Daniel Muller
  */
class cPerlInterpreter
{
public:
	std::string mScriptName;

	cPerlInterpreter();
	virtual ~cPerlInterpreter();

	/** \brief calling this ensures that this interpreter is gonna be used in next perl call

	   Note the calls to PERL_SET_CONTEXT(). These are necessary to initialize the global state
	   that tracks which interpreter is the "current" one on the particular process or thread
	   that may be running it. It should always be used if you have more than one interpreter
	   and are making perl API calls on both interpreters in an interleaved fashion.

	   cPerlInterpreter calls itself this function in many most of cases
	*/
	void SetMyContext();

	/** parse arguments like for a command line of perl */
	int Parse(int argc, char *argv[]);

	bool CallArgv(const char *Function, int Flags, char * Args [] );
protected:
	PerlInterpreter *mPerl;
};

};

#endif
