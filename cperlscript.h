/***************************************************************************
 *   Copyright (C) 2003 by Dan Muller                                      *
 *   dan@verliba.cz                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef NSCRIPTSCPERLSCRIPT_H
#define NSCRIPTSCPERLSCRIPT_H

#include <EXTERN.h>               /* from the Perl distribution     */
#include <perl.h>                 /* from the Perl distribution     */

/** \brief script related calsses

blabla
*/
namespace nScripts {

/**
perl script wrapper

@author Daniel Muller
*/
class cPerlScript{
public:
	cPerlScript();
	~cPerlScript();
	void Run();
	PerlInterpreter *mPerl;
};

};

#endif
