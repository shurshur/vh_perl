/***************************************************************************
 *   Copyright (C) 2003 by Dan Muller                                      *
 *   dan@verliba.cz                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef CPIPERL_H
#define CPIPERL_H

#include "src/cvhplugin.h"
#include "src/cconndc.h"
//#include "cperlinterpreter.h"
#include "cconsole.h"
#include "cperlmulti.h"

using namespace nScripts;
/*
using namespace nDirectConnect;
using namespace nDirectConnect::nPlugin;
*/

/**
a Plugin that allows to load a Perl script

@author Daniel Muller
*/

namespace nVerliHub {
	namespace nPerlPlugin {

class cpiPerl : public nPlugin::cVHPlugin
{
public:
	cPerlMulti mPerl;

	cpiPerl();
	virtual ~cpiPerl();
	virtual void OnLoad(cServerDC* server);
	virtual bool RegisterAll();
	virtual bool OnNewConn(cConnDC *);
	virtual bool OnCloseConn(cConnDC *);
	virtual bool OnParsedMsgChat(cConnDC *, cMessageDC *);
	virtual bool OnParsedMsgPM(cConnDC *, cMessageDC *);
	virtual bool OnParsedMsgSearch(cConnDC *, cMessageDC *);
	virtual bool OnParsedMsgSR(cConnDC *, cMessageDC *);
	virtual bool OnParsedMsgMyINFO(cConnDC *, cMessageDC *);
	virtual bool OnParsedMsgValidateNick(cConnDC *, cMessageDC *);
	virtual bool OnParsedMsgAny(cConnDC *, cMessageDC *);
	virtual bool OnParsedMsgSupport(cConnDC *, cMessageDC *);
	virtual bool OnParsedMsgMyPass(cConnDC *, cMessageDC *);
	//virtual bool OnUnknownMsg(cConnDC *, cMessageDC *);
	virtual bool OnOperatorCommand(cConnDC *, std::string *);
	virtual bool OnOperatorKicks(cUser *, cUser *, std::string *);
	virtual bool OnOperatorDrops(cUser *, cUser *);
	virtual bool OnValidateTag(cConnDC *, cDCTag *);
	virtual bool OnUserCommand(cConnDC *, std::string *);
	virtual bool OnUserLogin(cUser *);
	virtual bool OnUserLogout(cUser *);
	virtual bool OnTimer();
	virtual bool OnNewReg(cRegUserInfo *);
	virtual bool OnNewBan(cBan *);

	int Size() { return mPerl.Size(); }

private:
	cConsole mConsole;
	virtual bool AutoLoad();
	string mScriptDir;
};

	}; // namespace nPerlPlugin
}; // namespace nVerliHub

#endif
