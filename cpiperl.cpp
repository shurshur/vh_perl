/***************************************************************************
 *   Copyright (C) 2003 by Dan Muller                                      *
 *   dan@verliba.cz                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include <config.h>
#include "src/cserverdc.h"
#include "src/stringutils.h"
#include "cpiperl.h"

using namespace nVerliHub::nUtils;

nVerliHub::nPerlPlugin::cpiPerl::cpiPerl():
mConsole(this)
{
	mName = "PerlScript";
	mVersion= PERLSCRIPT_VERSION;
}

nVerliHub::nPerlPlugin::cpiPerl::~cpiPerl()
{}

bool nVerliHub::nPerlPlugin::cpiPerl::RegisterAll()
{
	RegisterCallBack("VH_OnNewConn");
	RegisterCallBack("VH_OnCloseConn");
	RegisterCallBack("VH_OnParsedMsgChat");
	RegisterCallBack("VH_OnParsedMsgPM");
	RegisterCallBack("VH_OnParsedMsgSearch");
	RegisterCallBack("VH_OnParsedMsgSR");
	RegisterCallBack("VH_OnParsedMsgMyINFO");
	RegisterCallBack("VH_OnParsedMsgValidateNick");
	RegisterCallBack("VH_OnParsedMsgAny");
	RegisterCallBack("VH_OnParsedMsgSupport");
	RegisterCallBack("VH_OnParsedMsgMyPass");
	RegisterCallBack("VH_OnUnknownMsg");
	RegisterCallBack("VH_OnOperatorCommand");
	RegisterCallBack("VH_OnOperatorKicks");
	RegisterCallBack("VH_OnOperatorDrops");
	RegisterCallBack("VH_OnValidateTag");
	RegisterCallBack("VH_OnUserCommand");
	RegisterCallBack("VH_OnUserLogin");
	RegisterCallBack("VH_OnUserLogout");
	RegisterCallBack("VH_OnTimer");
	RegisterCallBack("VH_OnNewReg");
	RegisterCallBack("VH_OnNewBan");
	return true;
}

void nVerliHub::nPerlPlugin::cpiPerl::OnLoad(cServerDC* server)
{
	cVHPlugin::OnLoad(server);

	mScriptDir = mServer->mConfigBaseDir + "/scripts/";

	AutoLoad();
}

bool nVerliHub::nPerlPlugin::cpiPerl::AutoLoad()
{
	if(Log(0))
		LogStream() << "Open dir: " << mScriptDir << endl;
	string pathname, filename;
	DIR *dir = opendir(mScriptDir.c_str());
	if(!dir) {
		if(Log(1))
			LogStream() << "Error opening directory" << endl;
		return false;
	}
	struct dirent *dent = NULL;

	while(NULL != (dent=readdir(dir))) {
		filename = dent->d_name;
		if((filename.size() > 3) && (StrCompare(filename,filename.size()-3,3,".pl")==0)) {
			pathname = mScriptDir + filename;
			char *argv[] = { (char*)"", (char*)pathname.c_str(), NULL };
			mPerl.Parse(2, argv);
			// FIXME: check weither all ok?
			if(Log(1))
				LogStream() << "Success loading and parsing Perl script: " << filename << endl;
		}
	}

	closedir(dir);
	return true;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnNewConn(cConnDC * conn)
{
	char *args[] =  { (char *)conn->AddrIP().c_str(), NULL };
	bool ret = mPerl.CallArgv("VH_OnNewConn",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnCloseConn(cConnDC * conn)
{
	char *args[] =  { (char *)conn->AddrIP().c_str(), NULL };
	bool ret = mPerl.CallArgv("VH_OnCloseConn",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgAny(cConnDC *conn , cMessageDC *msg)
{
	char *args[] =  {	(char *)conn->AddrIP().c_str(),
				(char *)msg->mStr.c_str(),
				NULL };
	bool ret = mPerl.CallArgv("VH_OnParsedMsgAny",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgSupport(cConnDC *conn , cMessageDC *msg)
{
	char *args[] =  {	(char *)conn->AddrIP().c_str(),
				(char *)msg->mStr.c_str(),
				NULL };
	bool ret = mPerl.CallArgv("VH_OnParsedMsgSupport",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgValidateNick(cConnDC *conn , cMessageDC *msg)
{
	char *args[] =  {	(char *)conn->AddrIP().c_str(),
				(char *)msg->ChunkString(eCH_1_ALL).c_str(),
				NULL }; // eCH_1_ALL, eCH_1_PARAM
	bool ret = mPerl.CallArgv("VH_OnParsedMsgValidateNick",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgMyPass(cConnDC *conn , cMessageDC *msg)
{
	char *args[] =  {	(char *)conn->AddrIP().c_str(),
				(char *)msg->ChunkString(eCH_1_ALL).c_str(),
				NULL }; // eCH_1_ALL, eCH_1_PARAM
	bool ret = mPerl.CallArgv("VH_OnParsedMsgMyPass",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgMyINFO(cConnDC *conn , cMessageDC *msg)
{
	char *args[] =  {	(char *)conn->AddrIP().c_str(),
				(char *)msg->ChunkString(eCH_MI_ALL).c_str(),
				NULL }; // eCH_MI_ALL, eCH_MI_DEST, eCH_MI_NICK, eCH_MI_INFO, eCH_MI_DESC, eCH_MI_SPEED, eCH_MI_MAIL, eCH_MI_SIZE;
	bool ret = mPerl.CallArgv("VH_OnParsedMsgMyINFO",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgSearch(cConnDC *conn , cMessageDC *msg)
{
	char *args[] =  {	(char *)conn->AddrIP().c_str(),
				(char *)msg->mStr.c_str(),
				NULL }; // active: eCH_AS_ALL, eCH_AS_ADDR, eCH_AS_IP, eCH_AS_PORT, eCH_AS_QUERY; passive: eCH_PS_ALL, eCH_PS_NICK, eCH_PS_QUERY;
	bool ret = mPerl.CallArgv("VH_OnParsedMsgSearch",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgSR(cConnDC *conn , cMessageDC *msg)
{
	char *args[] =  {	(char *)conn->AddrIP().c_str(),
				(char *)msg->ChunkString(eCH_SR_ALL).c_str(),
				NULL }; // eCH_SR_ALL, eCH_SR_FROM, eCH_SR_PATH, eCH_SR_SIZE, eCH_SR_SLOTS, eCH_SR_SL_FR, eCH_SR_SL_TO, eCH_SR_HUBINFO, eCH_SR_TO;
	bool ret = mPerl.CallArgv("VH_OnParsedMsgSR",G_EVAL|G_DISCARD, args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgChat(cConnDC *conn , cMessageDC *msg)
{
	char *args[]= {
		(char *)conn->mpUser->mNick.c_str(), 
		(char *) msg->ChunkString(eCH_CH_MSG).c_str(), 
		NULL}; // eCH_CH_ALL, eCH_CH_NICK, eCH_CH_MSG;
	bool ret = mPerl.CallArgv("VH_OnParsedMsgChat",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnParsedMsgPM(cConnDC *conn , cMessageDC *msg)
{
	char *args[]= {
		(char *)conn->mpUser->mNick.c_str(), 
		(char *) msg->ChunkString(eCH_PM_MSG).c_str(), 
		(char *) msg->ChunkString(eCH_PM_TO).c_str(),
		NULL}; // eCH_PM_ALL, eCH_PM_TO, eCH_PM_FROM, eCH_PM_CHMSG, eCH_PM_NICK, eCH_PM_MSG;
	bool ret = mPerl.CallArgv("VH_OnParsedMsgPM",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnValidateTag(cConnDC *conn , cDCTag *tag)
{
	char *args[]= {	(char *)conn->mpUser->mNick.c_str(),
				(char *) tag->mTag.c_str(),
				NULL};
	bool ret = mPerl.CallArgv("VH_OnValidateTag",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnOperatorCommand(cConnDC *conn , std::string *str)
{
	if((conn != NULL) && (conn->mpUser != NULL) && (str != NULL))
		if(mConsole.DoCommand(*str, conn))
			return false;

	char *args[]= {	(char *)conn->mpUser->mNick.c_str(),
				(char *) str->c_str(),
				NULL};
	bool ret = mPerl.CallArgv("VH_OnOperatorCommand",G_EVAL|G_DISCARD,args);
	LogStream() << endl << "=" << ret << endl << endl;
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnOperatorKicks(cUser *op , cUser *user, std::string *reason)
{
	char *args[]= {	(char *)op->mNick.c_str(),
				(char *)user->mNick.c_str(),
				(char *)reason->c_str(),
				NULL };
	bool ret = mPerl.CallArgv("VH_OnOperatorKicks",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnOperatorDrops(cUser *op , cUser *user)
{
	char *args[]= {	(char *)op->mNick.c_str(),
				(char *)user->mNick.c_str(),
				NULL };
	bool ret = mPerl.CallArgv("VH_OnOperatorDrops",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnUserCommand(cConnDC *conn , std::string *str)
{
	char *args[]= {	(char *)conn->mpUser->mNick.c_str(),
				(char *) str->c_str(),
				NULL};
	bool ret = mPerl.CallArgv("VH_OnUserCommand",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnUserLogin(cUser *user)
{
	char *args[]= { (char *)user->mNick.c_str(), NULL };
	bool ret = mPerl.CallArgv("VH_OnUserLogin",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnUserLogout(cUser *user)
{
	char *args[]= { (char *)user->mNick.c_str(), NULL };
	bool ret = mPerl.CallArgv("VH_OnUserLogout",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnTimer()
{
	char *args[]= { NULL };
	bool ret = mPerl.CallArgv("VH_OnTimer",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnNewReg(cRegUserInfo *reginfo)
{
	char *args[]= { NULL };
	bool ret = mPerl.CallArgv("VH_OnNewReg",G_EVAL|G_DISCARD,args);
	return ret;
}

bool nVerliHub::nPerlPlugin::cpiPerl::OnNewBan(cBan *ban)
{
	char *args[]= { NULL };
	bool ret = mPerl.CallArgv("VH_OnNewReg",G_EVAL|G_DISCARD,args);
	return ret;
}

REGISTER_PLUGIN(nVerliHub::nPerlPlugin::cpiPerl);
