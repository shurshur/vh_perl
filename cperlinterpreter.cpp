/***************************************************************************
 *   Copyright (C) 2003 by Dan Muller                                      *
 *   dan@verliba.cz                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include <iostream>
#include "cperlinterpreter.h"

using namespace std;

EXTERN_C void xs_init (pTHX);
EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);
//EXTERN_C void boot_VHPerlExt (pTHX_ CV* cv);
//EXTERN_C void boot_vh (pTHX_ CV* cv);

namespace nScripts
{

cPerlInterpreter::cPerlInterpreter()
{
	mPerl = perl_alloc();
	if (!mPerl) throw "No Memory for Perl";
	SetMyContext();
	perl_construct(mPerl);
}

cPerlInterpreter::~cPerlInterpreter()
{
	PerlInterpreter *my_perl = mPerl;
	SetMyContext();
	perl_destruct(mPerl);
	perl_free(mPerl);
}

/** \brief calling this ensures that this interpreter is gonna be used in next perl call

Note the calls to PERL_SET_CONTEXT(). These are necessary to initialize the global state
that tracks which interpreter is the "current" one on the particular process or thread
that may be running it. It should always be used if you have more than one interpreter
and are making perl API calls on both interpreters in an interleaved fashion.

cPerlInterpreter calls itself this function in many most of cases
*/
void cPerlInterpreter::SetMyContext()
{
	PERL_SET_CONTEXT((mPerl));
}

/** parse arguments like for a command line of perl */
int cPerlInterpreter::Parse(int argc, char *argv[])
{
	PerlInterpreter *my_perl = mPerl;
	SetMyContext();
	int result = perl_parse(mPerl,  xs_init, argc, argv, NULL);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
	return result;
}

bool cPerlInterpreter::CallArgv(const char *Function, int Flags, char * Args [] )
{
	PerlInterpreter *my_perl = mPerl;
	SetMyContext();
	// Don't use Flags, define another!
	dSP;
	int n;
	bool ret = true;
	ENTER;
	SAVETMPS;
	n = call_argv(Function, G_EVAL|G_SCALAR , Args );
	SPAGAIN;
	if(SvTRUE(ERRSV)) {
	  STRLEN n_a;
	  //cerr << "ERROR CALL " << Function << " [" << SvPV(ERRSV, n_a) << "]" << endl;
	} else if(n==1) {
	  ret = POPi;
	  //cerr << "CALL " << Function << " ret " << ret << endl;
	} else {
	  cerr << "Call " << Function << ": expected 1 return value, but " << n << " returned" << endl;
	}
	FREETMPS;
	LEAVE;
	return ret;
}

};

EXTERN_C void xs_init(pTHX)
{
	std::string file = __FILE__;
	/* DynaLoader is a special case */
	newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file.c_str());
	//newXS("VHPerlExt::bootstrap", boot_VHPerlExt, file.c_str());
	//newXS("vh::bootstrap", boot_vh, file.c_str());
}


