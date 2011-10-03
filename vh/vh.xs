#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include "const-c.inc"

#include "src/script_api.h"

using namespace nVerliHub;

bool Ban(char *nick, char *op, char *reason, unsigned howlong, unsigned bantype) {
	return Ban(nick,string(op),string(reason),howlong,bantype);
}

bool SendDataToAll(char *data, int min_class, int max_class) {
	return SendToClass(data, min_class, max_class);
}

MODULE = vh		PACKAGE = vh		

INCLUDE: const-xs.inc

bool
Ban(nick, op, reason, howlong, bantype)
	char *	nick
	char *  op
	char *  reason
	unsigned	howlong
	int	bantype

bool
CloseConnection(nick)
	char *	nick

char *
GetUserCC(nick)
	char * nick

char *
GetMyINFO(nick)
	char *	nick

bool
AddRegUser(nick, uclass, passwd, op)
	char * nick
	int uclass
	char * passwd
	char * op

bool
DelRegUser(nick)
	char * nick

int
GetUserClass(nick)
	char *	nick

char *
GetUserHost(nick)
	char *	nick

char *
GetUserIP(nick)
	char *	nick

char *
ParseCommand(command_line)
	char *	command_line

bool
SendToClass(data, min_class, max_class)
	char *	data
	int	min_class
	int	max_class

bool
SendToAll(data)
	char *	data

bool
SendPMToAll(data, from, min_class, max_class)
	char *	data
	char *	from
	int	min_class
	int	max_class

bool
KickUser(op, nick, reason)
	char *	op
	char *	nick
	char *	reason

bool
SendDataToUser(data, nick)
	char *	data
	char *	nick

bool
SetConfig(configname, variable, value)
	char *	configname
	char *	variable
	char *	value

char *
GetConfig(configname, variable)
	char *	configname
	char *	variable
PPCODE:
	char * val = new char[64];
	int size = GetConfig(configname, variable, val, 64);
	if (size<0) {
		croak("Error calling GetConfig");
		delete [] val;
		XSRETURN_UNDEF;
	}
	if(size >= 63) {
		delete [] val;
		val = new char[size+1];
		int size = GetConfig(configname, variable, val, size+1);
	}
	XPUSHs(sv_2mortal(newSVpv(val, size)));
	delete [] val;

int
GetUsersCount()

char *
GetNickList()

double
GetTotalShareSize()

char *
GetVHCfgDir()
