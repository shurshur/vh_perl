Find_Package(Perl REQUIRED)

EXECUTE_PROCESS(
  COMMAND
    ${PERL_EXECUTABLE} -MConfig -e "print \$Config{installsitearch}"
    OUTPUT_VARIABLE
      PERL_SITE_ARCH
    RESULT_VARIABLE
      PERL_SITE_ARCH_RESULT
)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/Makefile.PL.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Makefile.PL")

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/vh.pm"
  "${CMAKE_CURRENT_BINARY_DIR}/vh.pm")

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
    ${CMAKE_CURRENT_BINARY_DIR}/blib/arch/auto/vh/vh.so
    ${CMAKE_CURRENT_BINARY_DIR}/blib/arch/auto/vh/vh.bs
    ${CMAKE_CURRENT_BINARY_DIR}/blib/lib/auto/vh/autosplit.ix
  DESTINATION
    ${PERL_SITE_ARCH}/auto/vh/)

INSTALL(
  FILES
    vh.pm
  DESTINATION
    ${PERL_SITE_ARCH})
