#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include "const-c.inc"

#include <verlihub/script_api.h>
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
GetMyINFO(nick)
	char *	nick

int
GetUserClass(nick)
	char *	nick

char *
ParseCommand(command_line)
	char *	command_line

bool
SendDataToAll(data, min_class, max_class)
	char *	data
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

int
GetConfig(configname, variable, configvalue, valuesize)
	char *	configname
	char *	variable
	char *  configvalue
	int     valuesize
