#include <iostream>
#include <vector>
#include "cperlmulti.h"
#include "cperlinterpreter.h"

namespace nScripts
{

cPerlMulti::cPerlMulti()
{
}

cPerlMulti::~cPerlMulti()
{
	for(std::vector<cPerlInterpreter*>::const_iterator i = mPerl.begin(); i != mPerl.end(); i++)
		delete *i;
}


int cPerlMulti::Parse(int argc, char*argv[]) {
	cPerlInterpreter *perl = new cPerlInterpreter();
	int ret = perl->Parse(argc, argv);
	mPerl.push_back(perl);
	return ret;
}

bool cPerlMulti::CallArgv(const char *Function, int Flags, char * Args [] ) {
	int s=0;
	for(std::vector<cPerlInterpreter*>::const_iterator i = mPerl.begin(); i != mPerl.end(); i++) {
		s++;
		bool ret = (*i)->CallArgv(Function, Flags, Args);
		//std::cerr << "Call " << Function << " on script " << (*i)->mScriptName << " returns " << ret << std::endl;
		if(!ret) return false;
	}
	return true;
}

}; // namespace nScripts
