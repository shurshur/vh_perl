Find_Package(Perl REQUIRED)

EXECUTE_PROCESS(
  COMMAND
    ${PERL_EXECUTABLE} -MConfig -e "print \$Config{installsitearch}"
    OUTPUT_VARIABLE
      PERL_SITE_ARCH
    RESULT_VARIABLE
      PERL_SITE_ARCH_RESULT
)

add_custom_target(vh_make ALL)
add_custom_command(TARGET vh_make
  COMMAND perl Makefile.PL
  COMMAND make -f Makefile.build)

ADD_CUSTOM_COMMAND(
  OUTPUT
    blib/arch/auto/vh/vh.so
    blib/arch/auto/vh/vh.bs 
    lib/arch/auto/vh/autosplit.ix
  COMMAND perl Makefile.PL
  COMMAND make -f Makefile.build
  )

INSTALL(
  FILES
    blib/arch/auto/vh/vh.so
    blib/arch/auto/vh/vh.bs
    blib/lib/auto/vh/autosplit.ix
  DESTINATION
    ${PERL_SITE_ARCH}/auto/vh/)

INSTALL(
  FILES
    vh.pm
  DESTINATION
    ${PERL_SITE_ARCH})
