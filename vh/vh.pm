package vh;

use 5.008;
use strict;
use warnings;
use Carp;

require Exporter;
use AutoLoader;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use vh ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(
	Ban
	CloseConnection
	GetMyINFO
	ParseCommand
	SendDataToAll
	SendDataToUser
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(
	
);

our $VERSION = '0.01';

sub AUTOLOAD {
    # This AUTOLOAD is used to 'autoload' constants from the constant()
    # XS function.

    my $constname;
    our $AUTOLOAD;
    ($constname = $AUTOLOAD) =~ s/.*:://;
    croak "&vh::constant not defined" if $constname eq 'constant';
    my ($error, $val) = constant($constname);
    if ($error) { croak $error; }
    {
	no strict 'refs';
	# Fixed between 5.005_53 and 5.005_61
#XXX	if ($] >= 5.00561) {
#XXX	    *$AUTOLOAD = sub () { $val };
#XXX	}
#XXX	else {
	    *$AUTOLOAD = sub { $val };
#XXX	}
    }
    goto &$AUTOLOAD;
}

require XSLoader;
XSLoader::load('vh', $VERSION);

# Preloaded methods go here.

sub SendToUser {
  return SendDataToUser(@_);
}

sub SendDataToAll {
  return SendToClass(@_);
}

sub Disconnect {
  return CloseConnection(@_);
}

sub DisconnectByName {
  return CloseConnection(@_);
}

# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__
# Below is stub documentation for your module. You'd better edit it!

=head1 NAME

vh - Perl extension for blah blah blah

=head1 SYNOPSIS

  use vh;
  blah blah blah

=head1 ABSTRACT

  This should be the abstract for vh.
  The abstract is used when making PPD (Perl Package Description) files.
  If you don't want an ABSTRACT you should also edit Makefile.PL to
  remove the ABSTRACT_FROM option.

=head1 DESCRIPTION

Stub documentation for vh, created by h2xs. It looks like the
author of the extension was negligent enough to leave the stub
unedited.

Blah blah blah.

=head2 EXPORT

None by default.

=head2 Exportable functions

  bool Ban(char *nick, char *op, char *nick, unsigned howlong, int bantype)
  bool CloseConnection(char *nick)
  char *GetMyINFO(char *nick)
  char * ParseCommand(char *command_line)
  bool SendDataToAll(char *data, int min_class, int max_class)
  bool SendDataToUser(char *data, char *nick)



=head1 SEE ALSO

Mention other useful documentation such as the documentation of
related modules or operating system documentation (such as man pages
in UNIX), or any relevant external documentation such as RFCs or
standards.

If you have a mailing list set up for your module, mention it here.

If you have a web site set up for your module, mention it here.

=head1 AUTHOR

Daniel Muller, E<lt>dan@localdomainE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright 2004 by Daniel Muller

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself. 

=cut
