/**************************************************************************
*   Copyright (C) 2011 by Shurik                                          *
*   shurik@sbin.ru                                                        *
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
#ifndef NSCRIPTSCPERLMULTI_H
#define NSCRIPTSCPERLMULTI_H

#include "cperlinterpreter.h"
#include <vector>

namespace nVerliHub {
	namespace nPerlPlugin {

/* Class for multiplying perl interpreters for many scripts. May be rewritten in future. */

class cPerlMulti
{
public:
	cPerlMulti();
	virtual ~cPerlMulti();

	int Parse(int argc, char*argv[]);

	bool CallArgv(const char *Function, char * Args [] );
	
	int Size() { return mPerl.size(); }

	std::vector<cPerlInterpreter*> mPerl;
};

	}; // namespace nPerlPlugin
}; // namespace nVerlihub

#endif
