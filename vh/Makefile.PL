use 5.008;
use ExtUtils::MakeMaker;
use ExtUtils::Embed;

open LIBS,'-|', "verlihub_config --libs" || die "Verlihub is not installed, use make install in it's folder";
my $VERLIHUB_LIBS = <LIBS>;
close LIBS;
open CFLAGS,'-|', "verlihub_config --cflags" || die "Verlihub is not installed, use make install in it's folder";
my $VERLIHUB_CFLAGS = <CFLAGS>;
close CFLAGS;

# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile(
    'NAME'		=> 'vh',
    'VERSION_FROM'	=> 'vh.pm', # finds $VERSION
    'PREREQ_PM'		=> {}, # e.g., Module::Name => 1.1
    ($] >= 5.005 ?    ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM => 'vh.pm', # retrieve abstract from module
       AUTHOR     => 'Daniel Muller <dan at verliba dot cz>') : ()),
    'LIBS'		=> [''], # e.g., '-lm'
    'DEFINE'		=> '', # e.g., '-DHAVE_SOMETHING'
    'INC'		=> '-I. '.$VERLIHUB_CFLAGS, # e.g., '-I. -I/usr/include/other'
	# Un-comment this if you add C files to link with later:
    'OBJECT'		=> '$(O_FILES) -lvhapi '.$VERLIHUB_LIBS.' '.&ldopts, # link all the C files too
    'CC'                => 'g++ -xc++',
    'LD'                => 'g++'
);
if  (eval {require ExtUtils::Constant; 1}) {
  # If you edit these definitions to change the constants used by this module,
  # you will need to use the generated const-c.inc and const-xs.inc
  # files to replace their "fallback" counterparts before distributing your
  # changes.
  my @names = (qw());
  ExtUtils::Constant::WriteConstants(
                                     NAME         => 'vh',
                                     NAMES        => \@names,
                                     DEFAULT_TYPE => 'IV',
                                     C_FILE       => 'const-c.inc',
                                     XS_FILE      => 'const-xs.inc',
                                  );

}
else {
  use File::Copy;
  use File::Spec;
  foreach my $file ('const-c.inc', 'const-xs.inc') {
    my $fallback = File::Spec->catfile('fallback', $file);
    copy ($fallback, $file) or die "Can't copy $fallback to $file: $!";
  }
}
