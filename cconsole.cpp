/**************************************************************************
*   Original Author: Daniel Muller (dan at verliba dot cz)                *
*                    Janos Horvath (bourne at freemail dot hu) 2004-05    *
*                                                                         *
*   Copyright (C) 2006-2011 by Verlihub Project                           *
*   devs at verlihub-project dot org                                      *
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
#include <verlihub/cconndc.h>
#include <verlihub/cserverdc.h>
#include "cconsole.h"
#include "cpiperl.h"
#include "cperlinterpreter.h"
//#include "curr_date_time.h"
#include <verlihub/stringutils.h>
#include <verlihub/i18n.h>
#include <dirent.h>

#define PADDING 25

namespace nVerliHub {
	using namespace nUtils;
	namespace nPerlPlugin {

cConsole::cConsole(cpiPerl *perl) :
	mPerl(perl),
	mCmdr(this)
{
}

cConsole::~cConsole()
{
}

int cConsole::DoCommand(const string &str, cConnDC * conn)
{
	ostringstream os;

	if(mCmdr.ParseAll(str, os, conn) >= 0)
	{
		mPerl->mServer->DCPublicHS(os.str().c_str(),conn);
		return 1;
	}
	return 0;
}

	}; // namespace nPerlPlugin
}; // namespace nVerliHub
