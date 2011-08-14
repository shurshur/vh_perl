/***************************************************************************
 *   Copyright (C) 2003 by Dan Muller                                      *
 *   dan@verliba.cz                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "cperlscript.h"

namespace nScripts {


cPerlScript::cPerlScript()
{
	mPerl = perl_alloc();
	perl_construct(mPerl);
	//perl_parse(mPerl, NULL, argc, argv, (char **)NULL);
}

void cPerlScript::Run()
{
	perl_run(mPerl);
}

cPerlScript::~cPerlScript()
{
	perl_destruct(mPerl);
	perl_free(mPerl);
}


};
