# bor.pl
# (C) Shurik, 2011
# 
# Скрипт показывает пользователю одну случайную цитату с bash.org.ru по команде +bor

use vh;
use LWP::Simple;
use HTML::Entities;
use Encode;
use encoding "cp1251";
use strict;

sub VH_OnUserCommand {
  my $nick = shift;
  my $data = shift;

  if ($data =~ /^\+bor\s*$/) {
    my $pg = get "http://bash.org.ru/random";
    $pg =~ m#<div>(.+?)</div>#imx;
    my $q = "<br>".$1;
    $q =~ s#<br[\s/]*>#\n\ \ \ \ #igmx;
    $q = decode_entities($q);
    vh::SendToUser(encode("cp1251","<bash.org.ru> Случайная цитата:\n".$q."\n|"), $nick);
    return 0;
  }

  return 1;
}

