# vhdb.pl
# (C) Shurik, 2011
#
# Demo script that finds dbconfig and connects to Verlihub database

use vh;
use DBI;
use AppConfig;
use strict;

my $dbh;
my $botname;

sub Main {
  my $config = AppConfig->new({CREATE=>1});

  my $vhpath = vh::GetVHCfgDir;

  for my $k(qw(db_user db_pass db_data db_charset)) {
    $config->define("$k=s");
  }

  $config->file($vhpath."/dbconfig");

  $dbh = DBI->connect("DBI:mysql:".$config->db_data, $config->db_user, $config->db_pass);
  if($config->db_charset) { $dbh->do("SET NAMES ".$config->db_charset); }

  $botname = "_PERLBOT_".vh::GetConfig("config", "hub_security");

  return 1;
}

sub VH_OnOperatorCommand {
  my $nick = shift;
  my $data = shift;
  
  if ($data =~ /^\!regscount\s*$/) {

    my $sth = $dbh->prepare("SELECT class, COUNT(nick) FROM reglist GROUP BY class ORDER BY class ASC");
    $sth->execute;

    my $s = "<$botname>\n\n";
    while(my ($c,$q) = $sth->fetchrow_array) {
      $s .= "class:$c users:$q\n";
    }
    $sth->finish;

    print $s; 
    vh::SendToUser($s."|", $nick);
    return 0;
  }
  return 1;
}

sub UnLoad {
  $dbh->disconnect;
  return 1;
}
