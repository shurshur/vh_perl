#ifndef NSCRIPTSCPERLMULTI_H
#define NSCRIPTSCPERLMULTI_H

#include "cperlinterpreter.h"
#include <vector>

namespace nScripts
{

/* Class for multiplying perl interpreters for many scripts. May be rewritten in future. */

class cPerlMulti
{
public:
	cPerlMulti();
	virtual ~cPerlMulti();

	int Parse(int argc, char*argv[]);

	bool CallArgv(const char *Function, int Flags, char * Args [] );
protected:
	std::vector<cPerlInterpreter*> mPerl;
};

};

#endif
