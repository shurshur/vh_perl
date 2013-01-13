/**************************************************************************
*   Copyright (C) 2011-2013 by Shurik                                     *
*   shurik at sbin.ru                                                     *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include "src/script_api.h"
#include "src/cconnchoose.h"
using namespace nVerliHub::nEnums;
#include "src/cserverdc.h"
#include "cpiperl.h"
#include "wrapper.h"
using namespace nVerliHub;
using namespace nVerliHub::nPerlPlugin;

static cServerDC * GetCurrentVerlihub() {
	return (cServerDC *)cServerDC::sCurrentServer;
}

static cpiPerl * GetPI() {
	cServerDC *server = GetCurrentVerlihub();
	return (cpiPerl *)server->mPluginManager.GetPlugin("PerlScript");
}

int nVerliHub::nPerlPlugin::nWrapper::SQLQuery(char *query) {
	cpiPerl *pi = GetPI();

	pi->mQuery->Clear();
	pi->mQuery->OStream() << query;
	pi->mQuery->Query();
	
	return pi->mQuery->StoreResult();
}

MYSQL_ROW nVerliHub::nPerlPlugin::nWrapper::SQLFetch(int r, int &cols) {
	cpiPerl *pi = GetPI();
	if(!pi->mQuery->GetResult()) {
		// FIXME pass error to perl?
		return NULL;
	}

	pi->mQuery->DataSeek(r);

	MYSQL_ROW row;

	if(!(row = pi->mQuery->Row())) {
		// FIXME pass error to perl?
		return NULL;
	}

	cols = pi->mQuery->Cols();

	return row;
}

int nVerliHub::nPerlPlugin::nWrapper::SQLFree() {
	cpiPerl *pi = GetPI();

	pi->mQuery->Clear();
}

int nVerliHub::nPerlPlugin::nWrapper::IsUserOnline(char *nick) {
	cServerDC *server = GetCurrentVerlihub();
	cUser *usr = server->mUserList.GetUserByNick(nick);
	return usr == NULL ? 0 : 1;
}

int nVerliHub::nPerlPlugin::nWrapper::IsBot(char *nick) {
	cServerDC *server = GetCurrentVerlihub();
	cPluginRobot *robot = (cPluginRobot *)server->mUserList.GetUserByNick(nick);
	return robot == NULL ? 0 : 1;
}
int nVerliHub::nPerlPlugin::nWrapper::GetUpTime() {
	cServerDC *server = GetCurrentVerlihub();
	cTime upTime;
	upTime = server->mTime;
	upTime -= server->mStartTime;
	return upTime.Sec();
}

char *nVerliHub::nPerlPlugin::nWrapper::GetHubIp() {
	cServerDC *server = GetCurrentVerlihub();
	return (char*)server->mAddr.c_str();
}

char *nVerliHub::nPerlPlugin::nWrapper::GetHubSecAlias() {
	cServerDC *server = GetCurrentVerlihub();
	return (char*)server->mC.hub_security.c_str();
}

char *nVerliHub::nPerlPlugin::nWrapper::GetOPList() {
	cServerDC *server = GetCurrentVerlihub();
	return (char*)server->mOpList.GetNickList().c_str();
}

char *nVerliHub::nPerlPlugin::nWrapper::GetBotList() {
	cServerDC *server = GetCurrentVerlihub();
	return (char*)server->mRobotList.GetNickList().c_str();
}


bool nVerliHub::nPerlPlugin::nWrapper::RegBot(char *nick, int uclass, char *desc, char *speed, char *email, char *share) {
	cServerDC *server = GetCurrentVerlihub();
	cpiPerl *pi = GetPI();

	cPluginRobot *robot = pi->NewRobot(nick, uclass);

	if(robot != NULL) {
		server->mP.Create_MyINFO(robot->mMyINFO, robot->mNick, desc, speed, email, share);
		robot->mMyINFO_basic = robot->mMyINFO;

		//pi->mPerl.addBot(nick, share, (char *) robot->mMyINFO.c_str(), uclass);
		string omsg = "$Hello ";
		omsg+= robot->mNick;
		server->mHelloUsers.SendToAll(omsg, server->mC.delayed_myinfo, true);
		omsg = server->mP.GetMyInfo(robot, eUC_NORMUSER);
		server->mUserList.SendToAll(omsg, true, true);
		if(uclass >= 3)
			server->mUserList.SendToAll(server->mOpList.GetNickList(), true);
	} else {
	    // error: "Error adding bot; it may already exist"
	    return false;
	}
	return true;
}

bool nVerliHub::nPerlPlugin::nWrapper::EditBot(char *nick, int uclass, char *desc, char *speed, char *email, char *share) {
	cServerDC *server = GetCurrentVerlihub();
	cpiPerl *pi = GetPI();
	cUserRobot *robot = (cUserRobot*) server->mRobotList.GetUserBaseByNick(nick);

	if(robot != NULL) {
		//Clear myinfo
		robot->mMyINFO = "";
		server->mP.Create_MyINFO(robot->mMyINFO, robot->mNick, desc, speed, email, share);
		robot->mMyINFO_basic = robot->mMyINFO;
		//pi->mPerl.editBot(nick, share, (char *) robot->mMyINFO.c_str(), uclass);
		string omsg = server->mP.GetMyInfo(robot, eUC_NORMUSER);
		server->mUserList.SendToAll(omsg, false, true);
		if(uclass >= 3)
			server->mUserList.SendToAll(server->mOpList.GetNickList(), true);
	} else {
		// error: "???"
		return false;
	}
	return true;
}

bool nVerliHub::nPerlPlugin::nWrapper::UnRegBot(char *nick) {
	cServerDC *server = GetCurrentVerlihub();
	cpiPerl *pi = GetPI();

	cPluginRobot *robot = (cPluginRobot *)server->mUserList.GetUserByNick(nick);
	if(robot != NULL) {
		//pi->mPerl.delBot(nick);
		pi->DelRobot(robot);
	} else {
		// error: "Bot doesn't exist"
	    return false;
	}
	return true;
}
